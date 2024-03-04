#include <plx/data/Array.hpp>
#include <plx/data/HashTable.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Let.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/literal/String.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/Object.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    Let::Let(Triple* bindings) {
        _bindings = bindings;
    }

    Object* Let::eval(Evaluator* etor) {
        Triple* env = etor->environment();
        Triple* curr = _bindings;
        Object* evaluated;
        int numValues = 0; 
        while(!(curr->isEmpty())){
            evaluated = etor->evalExpr(curr->value());
            env = etor->bind(curr->key(), evaluated);
            curr = _bindings->next();
        }        
        etor->setEnvironment(env);
        return GLOBALS->NilObject();
    }


    TypeId Let::typeId() const {
        return TypeId::E_LET;
    }
    void Let::showOn(std::ostream& ostream) const {
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
    }
}