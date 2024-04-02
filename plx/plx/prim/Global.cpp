#include <cassert>

#include <plx/data/HashTable.hpp>
#include <plx/data/List.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/literal/Boolean.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/literal/String.hpp>
#include <plx/literal/Symbol.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/Object.hpp>
#include <plx/prim/Primitive.hpp>

namespace PLX {
    namespace Prim_Global {

        Object* argMap(Evaluator* etor, List* args) {
            const std::string PRIM_NAME = "argMap";
            evalNArgs(PRIM_NAME, etor, args, {});
            return GLOBALS->ArgMap();
        }

        Object* eval(Evaluator* etor, List* args) {
            const std::string PRIM_NAME = "eval";
            List* argValues = evalArgs(etor,args);
            Object* arg = argValues->first();
            return etor->evalExpr(arg);
        }

        Object* notOperator(Evaluator* etor, List* args) {
            const std::string PRIM_NAME = "not";
            Boolean* boolEval = dynamic_cast<Boolean*>(eval(etor,args));
            if(boolEval->boolValue() == (true)){
                boolEval = new Boolean(false);
            }
            else{
                boolEval = new Boolean(true);
            }
            return boolEval;
        }

        Object* type(Evaluator* etor, List* args) {
            const std::string PRIM_NAME = "type";
            List* argVals = evalNArgs(PRIM_NAME, etor, args, {TypeId::Z_ANY});
            Object* arg = argVals->first();
            return Symbol::create(arg->typeName());
        }

    }
}
