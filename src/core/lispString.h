#ifndef	_core_String_H
#define _core_String_H

#include "core/foundation.h"
#include "core/object.h"
#include "lispVector.h"

namespace core
{

FORWARD(String);
class String_O : public Vector_O
{
    LISP_BASE1(Vector_O);
    LISP_CLASS(core,ClPkg,String_O,"String");




    DECLARE_INIT();
#if defined(XML_ARCHIVE)
    DECLARE_ARCHIVE();
#endif // defined(XML_ARCHIVE)
public:
    explicit String_O() : T_O(), Base() {};
    virtual ~String_O() {};
public:
	void initialize();

private: // instance variables here


public: // Functions here



};

}; /* core */

TRANSLATE(core::String_O);



namespace core {

    Str_sp af_string(T_sp str);


    Str_sp af_string_upcase(T_sp arg);
    Str_sp af_string_downcase(T_sp arg);


    brclChar af_char(T_sp str, int idx);

    bool brcl_memberChar(brclChar c, T_sp charBag);

    Str_sp af_string_trim(Sequence_sp charbag, T_sp str);
    Str_sp af_string_left_trim(Sequence_sp charbag, T_sp str);
    Str_sp af_string_right_trim(Sequence_sp charbag, T_sp str);
};
#endif /* _core_String_H */


