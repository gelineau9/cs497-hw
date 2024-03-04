#pragma once

namespace PLX {

    class Do : public Object {
    public:
        Do(List* exprs);

        //Overridden Functions
        
        Object* eval(Evaluator* etor) override;
        TypeId typeId() const override;
        void showOn(std::ostream& ostream) const override;


    private:
        List* _exprs;
    };

}