#pragma once

namespace PLX {

    class If : public Object {
    public:
        If(Object* cond, Object* conseq, Object* alt);

        // Overridden functions --------------------------------------------

        Object* eval(Evaluator* etor) override;
        TypeId typeId() const override;
        void showOn(std::ostream& ostream) const override;

    private:
        Object* _cond;
        Object* _conseq;
        Object* _alt;

    };

}