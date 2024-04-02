#include <cassert>

#include <plx/data/Array.hpp>
#include <plx/data/Closure.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Function.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/literal/String.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    Closure::Closure(Function* function, Triple* env)
    {
        _function = function;
        _env = env;
    }

    Object* Closure::apply(Evaluator* etor, List* arguments) {
        Object* value = GLOBALS->NilObject();
        Triple* savedEnv = etor->environment();
        List* params = _function->getParams();
        etor->setEnvironment(_env);
        while (!params->isEmpty() && !arguments->isEmpty()) {
            Object* arg = arguments->first();
            Object* param = params->first();
            etor->bind(param,arg);
            arguments = arguments->restAsList();
            params = params->restAsList();
        }
        value = etor->evalExpr(_function->getBody());
        etor->setEnvironment(savedEnv);
        return value;
            
    }

    void Closure::showOn(std::ostream& ostream) const {
        ostream << "fun ";
        _function->getParams()->showOn2(ostream); 
        ostream << " = " << _function->getBody();
    }

    TypeId Closure::typeId() const {
        return TypeId::D_CLOSURE;
    }

}