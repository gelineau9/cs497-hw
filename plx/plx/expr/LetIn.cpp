#include <plx/data/Array.hpp>
#include <plx/data/HashTable.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/LetIn.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/literal/String.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/Object.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    LetIn::LetIn(Triple* bindings, Object* bodyExpression) {
        _bindings = bindings;
        _bodyExp = bodyExpression;
    }

    Object* LetIn::eval(Evaluator* etor) {
        Triple* env = etor->environment();
        Triple* curr = _bindings;
        Object* evaluated;
        while(!(curr->isEmpty())){
            evaluated = etor->evalExpr(curr->value());
            curr->setValue(evaluated);
            curr = curr->next();
        }
        
        
        etor->setEnvironment(env);
        return evaluated;
    }


    TypeId LetIn::typeId() const {
        return TypeId::E_LETIN;
    }
    void LetIn::showOn(std::ostream& ostream) const {
        Triple* curr = _bindings;
        ostream <<"let ";
        while(!(curr->isEmpty())) {
            if(curr->next()->isEmpty()){
                ostream <<curr->key()<<"="<<curr->value();
            }
            else{
                ostream <<curr->key()<<"="<<curr->value()<<", ";
            }
           
            curr = curr->next(); 
        }
        ostream <<" in "<<_bodyExp;
    }
}