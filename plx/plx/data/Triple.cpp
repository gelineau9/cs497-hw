#include <cassert>

#include <plx/data/Array.hpp>
#include <plx/data/Triple.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/literal/String.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/Object.hpp>
#include <plx/object/ThrowException.hpp>
#include <plx/object/TypeIds.hpp>
#include <plx/evaluator/Evaluator.hpp>

namespace PLX {

    Triple::Triple()
        : Triple(GLOBALS->NilObject(), GLOBALS->NilObject(), this)
    {}

    Triple::Triple(Object* key, Object* value)
        : Triple(key, value, GLOBALS->EmptyTriple())
    {}

    Triple::Triple(Object* key, Object* value, Triple* next)
        : _key {key}
        , _value {value}
        , _next {next}
    {}

    bool Triple::boolValue() const {
        return this != GLOBALS->EmptyTriple();
    }

    bool Triple::equals(const Object* other) const {
        if (!other->isA(TypeId::D_TRIPLE)) {
            return false;
        }
        const Triple* othertriple = static_cast<const Triple*>(other);
        if (isEmpty()) {
            return othertriple->isEmpty();
        }
        return _key->equals(othertriple->_key) && _value->equals(othertriple->_value);
    }

    Object* Triple::eval(Evaluator* etor){
        if(this->isEmpty()==true){
            return this;
        }
        else{
            Object* evalKey = etor->evalExpr(this->key());
            Object* evalVal = etor->evalExpr(this->value());
            Object* evalNext = this->next()->eval(etor);
            Triple* evalTriple = new Triple();
            evalTriple->setKey(evalKey);
            evalTriple->setValue(evalVal);
            Triple* tripleNext = static_cast<Triple*>(evalNext);
            evalTriple->setNext(tripleNext);
            return evalTriple;
        } 
    }

    bool Triple::isEmpty() const {
        return this == GLOBALS->EmptyTriple();
    }

    bool Triple::length(int& len) {
        Triple* triple = this;
        len = 0;
        while (!triple->isEmpty()) {
            len++;
            triple = triple->_next;
        }
        return true;
    }

    Triple* Triple::locate(const Object* key) {
        Triple* triple = this;
        while (!triple->isEmpty()) {
            if (key->equals(triple->_key)) {
                break;
            }
            triple = triple->_next;
        }
        return triple;
    }

    bool Triple::lookup(const Object* key, Object*& value) {
        Triple* binding = locate(key);
        if (binding->isEmpty()) {
            return false;
        }
        value = binding->value();
        return true;
    }

    Object* Triple::key() const {
        return _key;
    }

    Object* Triple::value() const {
        return _value;
    }

    Triple* Triple::next() const {
        return _next;
    }

    void Triple::setKey(Object* key) {
        if (isEmpty()) {
            throwException("Triple", "Operation not allowed on empty triple", this);
        }
        _key = key;
    }

    void Triple::setNext(Triple* next) {
        if (isEmpty()) {
            throwException("Triple", "Operation not allowed on empty triple", this);
        }
        _next = next;
    }

    void Triple::setValue(Object* value) {
        if (isEmpty()) {
            throwException("Triple", "Operation not allowed on empty triple", this);
        }
        _value = value;
    }

    void Triple::showOn(std::ostream& ostream) const {
        showOnWith(ostream, ", ");
    }

    void Triple::showOnWith(std::ostream& ostream, const std::string& separator) const {
        bool firstIter = true;
        const Triple* triple = this;
        while (!triple->isEmpty()) {
            if (firstIter) {
                firstIter = false;
            }
            else {
                ostream << separator;
            }
            ostream << triple->_key << '=' << triple->_value;
            triple = triple->_next;
        }
    }

    TypeId Triple::typeId() const {
        return TypeId::D_TRIPLE;
    }

}
