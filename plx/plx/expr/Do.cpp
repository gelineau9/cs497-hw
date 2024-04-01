#include <cassert>
#include <plx/data/Triple.hpp>
#include <plx/data/List.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Do.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    Do::Do(List* exprs)
        : _exprs {exprs}
        , _reverseExprs {exprs->reverse()}
    {}

    Object* Do::eval(Evaluator* etor) {
        Object* value = GLOBALS->NilObject();
        List* exprs = _exprs;
        Triple* savedEnv = etor->environment();
        while (!exprs->isEmpty()) {
            Object* expr = exprs->first();
            value = etor->evalExpr(expr);
            exprs = exprs->restAsList();
        }
        etor->setEnvironment(savedEnv);
        return value;
    }

    void Do::showOn(std::ostream& ostream) const {
        ostream << "do";
        if (!_exprs->isEmpty()) {
            ostream << ' ';
        }
        _exprs->showOnWith(ostream, "", " ", " end");
    }

    TypeId Do::typeId() const {
        return TypeId::E_SEQ;
    }

}
