#include <plx/data/Array.hpp>
#include <plx/data/HashTable.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/If.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/literal/String.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/Object.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    If::If(Object* cond, Object* conseq, Object* alt) {
        _cond = cond;
        _conseq = conseq;
        _alt = alt;
    }

    Object* If::eval(Evaluator* etor) {
        if(_cond->eval(etor)->boolValue()) {
            Object* result = etor->evalExpr(_conseq);
            return result;
        } else {
            Object* result = etor->evalExpr(_alt);
            return result;
        }
    }

    TypeId If::typeId() const {
        return TypeId::E_IF;
    }
    void If::showOn(std::ostream& ostream) const {
        ostream <<"if "<<_cond<<" then "<< _conseq<<" else "<< _alt;
    }
}