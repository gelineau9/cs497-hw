#pragma once

#include <vector>

#include <plx/object/Object.hpp>

namespace PLX {

    class List;
    class Queue;
    class Triple;

    class Array : public Object {
    public:
        Array(int nElems);
        Array(int nElems, Object* initialValue);
        Array(std::initializer_list<Object*> elems);

        // Unique functions ------------------------------------------------

        int length();
        bool get(int index, Object*& value) ;
        bool set(int index, Object* newElem);

        // Overridden functions --------------------------------------------

        bool boolValue() const override;
        bool equals(const Object* other) const override;
        bool hashCode(HashCode& hashCode) override;
        bool index(Object* indexer, Object*& retrievedValue) override;
        bool length(int& len) override;
        void showOn(std::ostream& ostream) const override;
        bool toArray(Array*& array) override;
        bool toList(List*& list) override;
        bool toQueue(Queue*& queue) override;
        Object* eval(Evaluator* etor) override;
        TypeId typeId() const override;

    private:
        std::vector<Object*> _elems;
    };

}
