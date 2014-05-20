
#include <iostream>
#include "foundation.h"
#include "boost/program_options.hpp"
#include "commandLineOptions.h"

namespace core {


    CommandLineOptions::CommandLineOptions(int argc, char* argv[]) : _DontLoadInit(false),
								     _IgnoreInitImage(false),
								     _ExecCode(""),
								     _GotRandomNumberSeed(false),
								     _RandomNumberSeed(0),
								     _Version(false),
								     _SilentStartup(true)

#if 0   // uses boost::program_options which is broken on OS X with -std=c++11
    {
	try 
	{ 
	    /** Define and parse the program options 
	     */ 
	    namespace po = boost::program_options; 
	    po::options_description desc("Options"); 
	    desc.add_options()
		("help,h", "produce help message")
		("image,I","ignore the initialization image - puts :ignore-init-image in *features*")
		("feature,f",po::value< std::vector<std::string> >(),"turn on feature")
		("exec,e",po::value<std::string>(),"execute string")
		("noload,n","dont load the startup code - go straight into repl")
		("seed,s",po::value<int>(),"seed the random number generators")
		("interactive,i","Don't bring up interactive REPL after script/command evaluated")
		;
	    po::parsed_options parsed = po::command_line_parser(argc,argv)
		.options(desc)
//	    .allow_unregistered()
		.run();
	    po::variables_map vm; 

	    try 
	    { 
		po::store(parsed,vm);
 
		/** --help option 
		 */ 
		if ( vm.count("help") )
		{
		    std::stringstream ss;
		    ss << desc;
		    printf("%s\n",ss.str().c_str());
		    return;
		}

		//
		//
		const char* execName = argv[0]+strlen(argv[0])-1;
		while (execName >= argv[0] && *execName != '/') execName--;
		execName++;
		this->_FunctionName = execName;
		this->_RCFileName = KERNEL_NAME "/init.lsp";
		DLINE();
		if ( vm.count("image") )
		{
		    SYMBOL_EXPORT_SC_(KeywordPkg,ignoreInitImage);
		    Cons_sp features = cl::_sym_STARfeaturesSTAR->symbolValue().as_or_nil<Cons_O>();
		    features = Cons_O::create(kw::_sym_ignoreInitImage,features);
		    cl::_sym_STARfeaturesSTAR->setf_symbolValue(features);
		}
		DLINE();
		if ( vm.count("feature") )
		{
		    vector<string> feature = vm["feature"].as< vector<string> >();
		    Cons_sp features = cl::_sym_STARfeaturesSTAR->symbolValue().as_or_nil<Cons_O>();
		    for ( vector<string>::iterator fit=feature.begin(); fit!=feature.end(); fit++ )
		    {
			if ( (*fit) == "" )
			{
			    SIMPLE_ERROR(BF("You must provide a feature with -+"));
			}
			features = Cons_O::create(_lisp->internKeyword(lispify_symbol_name(*fit)),features);
		    }
		    cl::_sym_STARfeaturesSTAR->setf_symbolValue(features);
		}
		if ( vm.count("noload") )
		{
		    this->_dont_load_startup = true;
		    this->_Interactive = true;
		}
		if ( vm.count("interactive") )
		{
		    this->_Interactive = false;
		}
		if ( vm.count("seed") )
		{
		    string seed= vm["seed"].as<string>();
		    long iseed = atol(seed.c_str());
		    LOG(BF("Parsing option -s %s") % seed.c_str()  );
		    seedRandomNumberGenerators(iseed);
		} else
		{
		    seedRandomNumberGenerators(this->mpiRank());
		}

		//
		// Pass whatever is left over to the Lisp environment
		//
		LOG(BF("Parsing what is left over into lisp environment arguments") );
		Cons_sp args = Cons_O::createFromVectorStringsCommandLineArguments(to_pass_further,_lisp);
		LOG(BF(" Command line arguments are being set in Lisp to: %s") % _rep_(args) );
		this->_Roots._CommandLineArguments = args;

		if ( !compileInputFile ) return;

		//
		// Get the script from the command line or the input-file
		//
		if ( vm.count("exec") != 0 )
		{
		    string script = vm["exec"].as<string>();
		    this->_ScriptInFile = false;
		    this->_FileNameOrCode = script+"\n";
		} else 
		{
		    LOG(BF("Evaluating first argument as the script name") );
		    Symbol_sp sym = _sym_STARARGSSTAR;
		    LOG(BF("Binding symbol(%s) to: %s") % sym->fullName() % _rep_(this->_CommandLineArguments) );
		    sym->setf_symbolValue(this->_Roots._CommandLineArguments);
//        this->globalEnvironment()->extend(sym,this->_CommandLineArguments);
		    this->_ScriptInFile = true;
		    T_sp cla = oCar(this->_Roots._CommandLineArguments);
		    this->_FileNameOrCode = "";
		    if ( cla.notnilp() ) this->_FileNameOrCode = oCar(this->_Roots._CommandLineArguments).as<Str_O>()->get();
		}
		po::notify(vm); // throws on error, so do after help in case 
		// there are any problems 
	    } 
	    catch(po::error& e) 
	    { 
		std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
		std::cerr << desc << std::endl; 
		throw(e);
	    } 
 
	    // application code here // 
 
	} 
	catch(std::exception& e) 
	{ 
	    std::cerr << "Unhandled Exception reached the top of main: " 
		      << e.what() << ", application will now exit" << std::endl; 
	    throw(e);
	} 
    }
#else
    {
	int iarg = 1;
	while (iarg<argc) {
	    string arg = argv[iarg];
	    if ( arg == "-h" || arg == "--help" ) {
		printf("brcl options\n"
		       "-I/--ignore-image  - ignore the boot image\n"
		       "-v/--version       - print version\n"
		       "-s/--verbose       - print more info as booting\n"
		       "-f/--feature feature - Add the feature to *features*\n"
		       "-e/--exec cmd        - Execute a command\n"
		       "-l/--load file       - LOAD the file\n"
		       "-n/--noload          - Don't load the init.lsp (very bare start)\n"
		       "-s/--seed #          - Seed the random number generator\n"
		       "{ARGS}*              - Add arguments to core:*command-line-arguments*\n"
		       "Run with brcl -I -f ecl-min to bootstrap minimal image\n"
		       "Run with brcl -f ecl-min to load minimal image and compile full image\n"
		       "Run with brcl to run and load full image\n");
		exit(1);
	    } else if ( arg == "-I" || arg == "--ignore-mage" ) {
		this->_IgnoreInitImage = true;
	    } else if ( arg == "-v" || arg == "--version" ) {
		this->_Version = true;
	    } else if ( arg == "-s" || arg == "--verbose" ) {
		this->_SilentStartup = false;
	    } else if ( arg == "-f" || arg == "--feature" ) {
		ASSERTF(iarg<(argc+1),BF("Missing argument for --feature,-f"));
		this->_Features.push_back(argv[iarg+1]);
		iarg++;
	    } else if ( arg == "-e" || arg == "--exec" ) {
		ASSERTF(iarg<(argc+1),BF("Missing argument for --exec,-e"));
		this->_ExecCode = argv[iarg+1];
		iarg++;
	    } else if ( arg == "-l" || arg == "--load" ) {
		ASSERTF(iarg<(argc+1),BF("Missing argument for --load,-l"));
		this->_LoadFile = argv[iarg+1];
		iarg++;
	    } else if ( arg == "-n" || arg == "--noload") {
		this->_DontLoadInit = true;
	    } else if ( arg == "-s" || arg == "--seed") {
		this->_RandomNumberSeed = atoi(argv[iarg+1]);
		iarg++;
	    } else {
		this->_Args.push_back(arg);
	    }
	    iarg++;
	}
    }
#endif



};
