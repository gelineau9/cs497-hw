#include <plx/data/Array.hpp>
#include <plx/data/HashTable.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Do.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/literal/String.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/Object.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    Do::Do(List* exprs) {
        _exprs = exprs;
    }

    Object* Do::eval(Evaluator* etor) {
        if (_exprs->isEmpty()) {
            return GLOBALS->NilObject();
        }
        Triple* env = etor->environment();
        Object* evaluated;
        while(!(_exprs->isEmpty())) {
            evaluated = etor->evalExpr(_exprs->first());
            _exprs = _exprs->restAsList();
        }
        etor->setEnvironment(env);
        return evaluated;
    }

    TypeId Do::typeId() const {
        return TypeId::E_SEQ;
    }
    void Do::showOn(std::ostream& ostream) const {
        List* curr = _exprs;
        ostream <<"do ";
        while(!(curr->isEmpty())) {
            ostream <<curr->first()<<" ";
            curr = curr->restAsList(); 
        }
        ostream <<"end";
    }
}