#pragma once

#include <plx/object/Object.hpp>

namespace PLX {


    class Apply : public Object {
        public:
            Apply(Object* abstractionObj, List* arguments);
            //Overriden function -------------
            Object* eval(Evaluator* etor) override;
            void showOn(std::ostream& ostream) const override;
            TypeId typeId() const override;
        private:
            Object* _abstractionObj;
            List* _arguments;
        };

}
