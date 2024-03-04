namespace PLX{
    class Let : public Object {
        public:
            Let(Triple* bindings);

            //Overriden Functions
            Object* eval(Evaluator* etor) override;
            TypeId typeId() const override;
            void showOn(std::ostream& ostream) const override;

        private:
            Triple* _bindings;
        };
}
