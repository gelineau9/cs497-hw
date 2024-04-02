#include <cassert>

#include <plx/data/List.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Apply.hpp>
#include <plx/data/Closure.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    Apply::Apply(Object* abstractionObj, List* arguments){
        _abstractionObj = abstractionObj;
        _arguments = arguments;
    }

    Object* Apply::eval(Evaluator* etor){
        Object* value = nullptr;
        Object* testObj = etor->evalExpr(_abstractionObj);
        if(testObj->isA(TypeId::D_CLOSURE)){
            Closure* newClosure = dynamic_cast<Closure*>(testObj);
            value = newClosure->apply(etor, _arguments);
        }
        return value;
    }

    void Apply::showOn(std::ostream& ostream) const {
        switch (_abstractionObj->typeId()) {
            case TypeId::D_CLOSURE:
            case TypeId::E_FUNCTION:
            case TypeId::E_NAMEDFUNCTION:
                ostream << '(' << _abstractionObj << ')';
                break;
            default:
                ostream << _abstractionObj;
                break;
        }
        _arguments->showOnWith(ostream, "(", ", ", ")");
    }

    TypeId Apply::typeId() const {
        return TypeId::E_APPLY;
    }

}
