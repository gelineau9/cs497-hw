#include <vector>

#include <plx/data/Array.hpp>
#include <plx/data/Queue.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/literal/String.hpp>
#include <plx/literal/Symbol.hpp>
#include <plx/object/ThrowException.hpp>

namespace PLX {

    Array::Array(int nElems)
        : Array {nElems, GLOBALS->NilObject()}
    {}

    Array::Array(int nElems, Object* initialValue)
        : _elems {static_cast<std::vector<Object*>::size_type>(nElems), initialValue}
    {}

    Array::Array(std::initializer_list<Object*> elems)
        : Array(elems.size())
    {
        int n=0;
        for (Object* elem : elems) {
            set(n++, elem);
        }
    }

    bool Array::boolValue() const {
        return _elems.size() > 0;
    }

    bool Array::equals(const Object* other) const {
        if (this == other) {
            return true;
        }
        if (!other->isA(TypeId::D_ARRAY)) {
            return false;
        }
        const Array* otherArray = static_cast<const Array*>(other);
        if (_elems.size() != otherArray->_elems.size()) {
            return false;
        }
        // Simple comparison of internal vectors, like this:
        // _elems == otherArray->_elems;
        // doesn't work. The elements must be compared one at a time.
        for (std::vector<Object*>::size_type n=0; n<_elems.size(); n++) {
            if (!_elems[n]->equals(otherArray->_elems[n])) {
                return false;
            }
        }
        return true;
    }

    Object* Array::eval(Evaluator* etor) {
        int nElems = _elems.size();
        Array* newArray = new Array(nElems);
        for (int n=0; n<nElems; n++) {
            Object* elem = _elems[n];
            Object* value = etor->evalExpr(elem);
            newArray->set(n, value);
        }
        return newArray;
    }

    List* Array::freeVars(List* freeVars) {
        for (Object* elem : _elems) {
            freeVars = elem->freeVars(freeVars);
        }
        return freeVars;
    }

    bool Array::get(int index, Object*& value) {
        if (index < 0 || index >= static_cast<int>(_elems.size())) {
            value = new Array({
                new String("Array index out of bounds"),
                new Integer(index),
                this
            });
            return false;
        }
        value = _elems[index];
        return true;
    }

    bool Array::hashCode(HashCode& hashCode) {
        static const int typeHashCode = std::hash<int>{}(static_cast<int>(typeId()));
        HashCode hashCode1 = typeHashCode;
        for (Object* elem : _elems) {
            HashCode hashCode2;
            if (!elem->hashCode(hashCode2)) {
                return false;
            }
            hashCode1 = hashRotateLeft(hashCode1) ^ hashCode2;
        }
        hashCode = hashCode1;
        return true;
    }

    bool Array::index(Object* indexer, Object*& retrievedValue) {
        if (!indexer->isA(TypeId::L_INTEGER)) {
            throwException("Array", "Indexer must be an integer", 
                new Array({indexer, indexer->typeSymbol()}));
        }
        Integer* indexerInt = static_cast<Integer*>(indexer);
        int n = indexerInt->value();
        if (n < 0 || n >= static_cast<int>(_elems.size())) {
            throwException("Array", "Index out of range", 
                new Array({indexerInt, this}));
        }
        retrievedValue = _elems[n];
        return true;
    }

    int Array::length() {
        int len;
        length(len);
        return len;
    }

    bool Array::length(int& len) {
        len = _elems.size();
        return true;
    }

    void Array::markChildren() {
        for (Object* elem : _elems) {
            elem->mark();
        }
    }

    bool Array::match(Object* other, Triple*& bindings) {
        if (!other->isA(TypeId::D_ARRAY)) {
            return false;
        }
        Array* otherArray = static_cast<Array*>(other);
        if (otherArray->_elems.size() != _elems.size()) {
            return false;
        }
        for (std::vector<Object*>::size_type n=0; n<_elems.size(); n++) {
            if (!_elems[n]->match(otherArray->_elems[n], bindings)) {
                return false;
            }
        }
        return true;
    }

    bool Array::set(int index, Object* newElem) {
        if (index < 0 || index >= static_cast<int>(_elems.size())) {
            return false;
        }
        _elems[index] = newElem;
        return true;
    }

    void Array::showOn(std::ostream& ostream) const {
        ostream << '{';
        for (std::vector<Object*>::size_type n=0; n<_elems.size(); n++) {
            if (n > 0) {
                ostream << ", ";
            }
            ostream << _elems[n];
        }
        ostream << '}';
    }

    bool Array::toArray(Array*& array) {
        array = this;
        return true;
    }

    bool Array::toList(List*& list) {
        Queue* queue;
        toQueue(queue);
        list = queue->asList();
        return true;
    }

    bool Array::toQueue(Queue*& queue) {
        queue = new Queue();
        for (Object* elem : _elems) {
            queue->enq(elem);
        }
        return true;
    }

    TypeId Array::typeId() const {
        return TypeId::D_ARRAY;
    }

}
