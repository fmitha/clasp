#ifndef clbind_wrapped_iterator_H
#define clbind_wrapped_iterator_H

#include "core/foundation.h"
#include "core/iterator.h"
#include <core/instance.h>
#include <clbind/adapter.fwd.h>
#include <clbind/inheritance.h>

namespace clbind
{

    template <class IT, /* class End,*/ typename Policy=reg::null_type>
    class Iterator : public core::Iterator_O /*, public gctools::GC_MergeKinds */ {
    public:
        IT      _Iterator;
//        End     _end;
    public:
        Iterator(IT it /*, End end */) : _Iterator(it) /* , _end(end) */ {};

        core::T_sp unsafeElement() const {
            return translate::to_object<IT>::convert(this->_Iterator);
        }
        void step() {++this->_Iterator;};
        bool operator==(core::T_sp other) const {
            if ( mem::smart_ptr<Iterator > io = other.asOrNull<Iterator<IT> >() ) {
                return this->_Iterator == io.get()->_Iterator;
            }
            return false;
        }
        bool operator<(core::T_sp other) {
            if ( Iterator<IT>* io = other.as<Iterator<IT> >() ) {
                return this->_Iterator < io->rawIterator();
            }
            return false;
        }
    };


};

#endif // clbind_wrapped_iterator
