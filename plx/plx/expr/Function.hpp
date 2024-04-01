#pragma once

#include <plx/object/Object.hpp>

namespace PLX {

    class List;

    class Function : public Object {
    public:
        Function(List* parameters, Object* body);

        // Unique functions ------------------------------------------------
        Object* getBody();
        List* getParams();
        // Overridden functions --------------------------------------------

        Object* eval(Evaluator* etor) override;
        void showOn(std::ostream& ostream) const override;
        TypeId typeId() const override;

    private:
        List* _parameters;
        Object* _body;
    };

}
