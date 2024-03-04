namespace PLX{
    class Quote : public Object {
        public:
            Quote(Object* contents);

            //Overriden Functions
            Object* eval(Evaluator* etor) override;
            TypeId typeId() const override;
            void showOn(std::ostream& ostream) const override;

        private:
            Object* _contents;
        };
}