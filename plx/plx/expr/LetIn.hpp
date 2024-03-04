namespace PLX{
    class LetIn : public Object {
        public:
            LetIn(Triple* bindings, Object* bodyExpression);

            //Overriden Functions
            Object* eval(Evaluator* etor) override;
            TypeId typeId() const override;
            void showOn(std::ostream& ostream) const override;

        private:
            Triple* _bindings;
            Object* _bodyExp;
        };
}
