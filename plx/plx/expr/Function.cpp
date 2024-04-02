#include <plx/data/Array.hpp>
#include <plx/data/Closure.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Function.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/literal/String.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/ThrowException.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    Function::Function(List* parameters, Object* body)
    {
        _parameters = parameters;
        _body = body;
    }

    Object* Function::eval(Evaluator* etor) {
        Closure* newClosure = new Closure(this, etor->environment());
        return newClosure;
        //MAKE NOTE TO TALK TO JEFF ABOUT THE THREE ARGS OF CLOSURE
    }

    void Function::showOn(std::ostream& ostream) const {
        ostream << "fun ";
        _parameters->showOn2(ostream);
        ostream << " = " << _body; 
    }

    TypeId Function::typeId() const {
        return TypeId::E_FUNCTION;
    }
    
    Object* Function::getBody(){
        return _body;
    }

    List* Function::getParams(){
        return _parameters;
    }

}