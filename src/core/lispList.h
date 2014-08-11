#ifndef	_core_List_H
#define _core_List_H

#include "core/foundation.h"
#include "sequence.h"
#include "numbers.fwd.h"

namespace core
{

#if 0
    FORWARD(List);
    c l a s s List_O : public T_O
    {
        L I S P_BASE1(T_O);
        L I S P_CLASS(core,ClPkg,List_O,"List");
//    DECLARE_ARCHIVE();
    public: // Simple default ctor/dtor
//    DEFAULT_CTOR_DTOR(List_O);
    public: // ctor/dtor for classes with shared virtual base
        explicit List_O() : T_O() {};
        virtual ~List_O() {};
    public:
    private: // instance variables here


    public: // Functions here
        virtual T_sp revappend(T_sp tail) {_OF(); SUBCLASS_MUST_IMPLEMENT();};
        virtual T_sp nreconc(T_sp tail) {_OF(); SUBCLASS_MUST_IMPLEMENT();};

        virtual Cons_sp copyList() const {_G(); SUBCLASS_MUST_IMPLEMENT();};
        virtual T_sp onth(int idx) const {_G(); SUBCLASS_MUST_IMPLEMENT();};
        virtual T_sp onthcdr(int idx) const { _G(); SUBCLASS_MUST_IMPLEMENT();};

        virtual T_sp last(int idx=1) const {_G(); SUBCLASS_MUST_IMPLEMENT();};

    };
#endif
};



namespace core {
    T_sp cl_revappend(T_sp tail);
    T_sp cl_nreconc(T_sp list, T_sp tail);
    T_sp cl_nth(int idx, T_sp arg);
    T_sp cl_nthcdr(int idx, T_sp arg);
    

    T_sp cl_copyList(T_sp arg);

    T_sp cl_nconc(Cons_sp rest);

    /*! Replace the last CONS of l with y and return l,  if l was nil return y */
    T_sp clasp_nconc(T_sp l, T_sp y);

    T_sp cl_last(T_sp list, int n=1);
    T_sp cl_nbutlast(T_sp list, Integer_sp n);


    void initialize_list();
};


#endif /* _core_List_H */


