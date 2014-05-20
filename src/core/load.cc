#include "foundation.h"
#include "object.h"
#include "load.h"
#include "lispStream.h"
#include "symbolTable.h"
#include "arguments.h"
#include "str.h"
#include "primitives.h"
#include "unixfsys.h"
#include "pathname.h"
#include "lispReader.h"
#include "evaluator.h"
#include "gctools/gctoolsPackage.h"
#include "predicates.h"
#include "wrappers.h"


namespace core {




#define ARGS_af_loadSource "(source &optional verbose print external-format)"
#define DECL_af_loadSource ""
#define DOCS_af_loadSource "loadSource"
void af_loadSource(T_sp source, bool verbose, bool print, T_sp externalFormat)
{_G();
    Stream_sp strm;
    if ( cl_streamp(source) ) {
	strm = source.as<Stream_O>();
	if ( !strm->inputStreamP() ) {
	    SIMPLE_ERROR(BF("Stream must be an input stream"));
	}
    } else {
	strm = af_open(source,
		       kw::_sym_input,
		       cl::_sym_Character_O,
		       _Nil<T_O>(),
		       _Nil<T_O>(),
		       kw::_sym_default);
	if ( strm.nilp() ) return;
    }
    try {
	while (true) {
	    bool echoReplRead = _sym_STARechoReplReadSTAR->symbolValue().isTrue();
	    T_sp x = read_lisp_object(strm,false,_Unbound<T_O>(),false);
	    if ( x.unboundp() ) break;
	    if ( echoReplRead ) {
		_lisp->print(BF("Read: %s\n") % _rep_(x) );
	    }
	    _lisp->invocationHistoryStack().setExpressionForTop(x);
	    _lisp->invocationHistoryStack().setActivationFrameForTop(_Nil<ActivationFrame_O>());
	    if (x.number_of_values() > 0 ) {
		af_evalWithEnv(x,_Nil<Environment_O>());
		if ( print ) {
		    _lisp->print(BF(";; -- read- %s\n") % _rep_(x));
		};
                gctools::af_cleanup();
	    }
	}
	strm->close(false);
    } catch (...) {
	strm->close(true); // abort
	throw;
    }
}
	






  /*! Translated from from ecl::load.d */
#define ARGS_af_load "(source &key (verbose *load-verbose*) (print *load-print*) (if-does-not-exist :error) (external-format :default) (search-list core::*load-search-list*))"
#define DECL_af_load ""
#define DOCS_af_load "CLHS: load"
    T_sp af_load(T_sp source, T_sp verbose, T_sp print, T_sp if_does_not_exist, T_sp external_format, T_sp search_list)
    {_G();
	Pathname_sp pathname;
	T_sp pntype;
	T_sp hooks;
	T_sp filename;
	T_sp function = _Nil<T_O>();
	T_sp ok;
	bool not_a_filename = false;


//        printf("%s:%d af_load source= %s\n", __FILE__, __LINE__, _rep_(source).c_str());

	/* If source is a stream, read conventional lisp code from it */
	if (Stream_sp strm = source.asOrNull<Stream_O>() ) {
	    /* INV: if "source" is not a valid stream, file.d will complain */
	    filename = strm;
	    function = _Nil<T_O>();
	    not_a_filename = true;
	    goto NOT_A_FILENAME;
	}
	/* INV: coerce_to_file_pathname() creates a fresh new pathname object */
	source   = af_mergePathnames(source);
//        printf("%s:%d af_load after mergePathnames source= %s\n", __FILE__, __LINE__, _rep_(source).c_str());

	pathname = af_coerceToFilePathname(source);
	pntype   = pathname->_Type;

	filename = _Nil<T_O>();
	hooks = af_symbolValue(ext::_sym_STARloadHooksSTAR);
	if (Null(pathname->_Directory) &&
	    Null(pathname->_Host) &&
	    Null(pathname->_Device) &&
	    !Null(search_list))
	{
	    for ( ; search_list.notnilp(); search_list = oCdr(search_list) ) {
		T_sp d = oCar(search_list);
		T_sp f = af_mergePathnames(pathname,d);
		T_sp ok = af_load( f, verbose, print, _Nil<T_O>(), external_format, _Nil<T_O>());
		if (!Null(ok)) {
		    return ok;
		}
	    } 
	}
	if (!Null(pntype) && (pntype != kw::_sym_wild )) {
	    /* If filename already has an extension, make sure
	       that the file exists */
	    T_sp kind;
	    filename = af_coerceToFilePathname(pathname);
	    kind = af_file_kind(filename.as<Pathname_O>(), _lisp->_true());
	    if (kind != kw::_sym_file && kind != kw::_sym_special) {
		filename = _Nil<T_O>();
	    } else {
		function = _Nil<T_O>();
		if ( af_consP(hooks) ) {
		    function = oCdr(hooks.as<Cons_O>()->assoc(pathname->_Type,
							      _Nil<T_O>(),
							      cl::_sym_string_EQ_,
							      _Nil<T_O>()));
		}
	    }
	} else {
	    for ( ; hooks.notnilp(); hooks = oCdr(hooks) ) {
		/* Otherwise try with known extensions until a matching
		   file is found */
		T_sp kind;
		filename = pathname;
		pathname->_Type = oCaar(hooks);
		function = oCdar(hooks);
		kind = af_file_kind(pathname, _lisp->_true());
		if (kind == kw::_sym_file || kind == kw::_sym_special)
		    break;
		else
		    filename = _Nil<T_O>();
	    }
	};
	if (Null(filename)) {
	    if (Null(if_does_not_exist))
		return _Nil<T_O>();
	    else {
		CANNOT_OPEN_FILE_ERROR(source);
	    }
	}
    NOT_A_FILENAME:
	if (verbose.notnilp()) {
	    eval::funcall(cl::_sym_format,_lisp->_true(),
			  Str_O::create("~&;;; Loading ~s~%"),
			  filename);
	}
	DynamicScopeManager scope(cl::_sym_STARpackageSTAR,af_symbolValue(cl::_sym_STARpackageSTAR));
	scope.pushSpecialVariableAndSet(cl::_sym_STARreadtableSTAR,af_symbolValue(cl::_sym_STARreadtableSTAR));
	scope.pushSpecialVariableAndSet(cl::_sym_STARloadPathnameSTAR, not_a_filename ? _Nil<T_O>() : source );
	T_sp truename = af_truename(filename);
	scope.pushSpecialVariableAndSet(cl::_sym_STARloadTruenameSTAR, not_a_filename ? _Nil<T_O>() : truename );
	if ( !not_a_filename ) filename = truename;
	if (!Null(function)) {
	    ok = eval::funcall( function, filename, verbose, print, external_format);
	} else {
#if 0 /* defined(ENABLE_DLOPEN) && !defined(ECL_MS_WINDOWS_HOST)*/
	    /*
	     * DISABLED BECAUSE OF SECURITY ISSUES!
	     * In systems where we can do this, we try to load the file
	     * as a binary. When it fails, we will revert to source
	     * loading below. Is this safe? Well, it depends on whether
	     * your op.sys. checks integrity of binary exectables or
	     * just loads _anything_.
	     */
	    if (not_a_filename) {
		ok = ECL_T;
	    } else {
		ok = si_load_binary(filename, verbose, print);
	    }
	    if (!Null(ok))
#endif
		af_loadSource(filename, verbose, print, external_format);
	    ok = _lisp->_true();
	}
	if (!Null(ok)) {
	    SIMPLE_ERROR(BF("LOAD: Could not load file %s (Error: %s") % _rep_(filename) % _rep_(ok));
	}
	if (print.notnilp() ) {
	    eval::funcall(cl::_sym_format, _lisp->_true(),
			  Str_O::create("~&;;; Loading ~s~%"),
			  filename);
	}
	return filename;
    }
	    

    void initialize_load()
    {
	SYMBOL_EXPORT_SC_(CorePkg,loadSource);
	Defun(loadSource);
	Defun(load);
    }





};
