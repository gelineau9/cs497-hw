#pragma once

#include <plx/object/Symbolic.hpp>

namespace PLX {

    class Evaluator;
    class Triple;

    class Identifier : public Symbolic {
    public:
        static Identifier* create(const std::string& name);

        // Overridden functions --------------------------------------------
        Object* eval(Evaluator* etor) override;
        TypeId typeId() const override;

    private:
        Identifier(const std::string& name);

    };

}