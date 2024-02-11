#pragma once

#include <list>

#include <plx/object/Globals.hpp>
#include <plx/object/Object.hpp>

namespace PLX {

    class List;

    class Queue : public Object {
    public:
        Queue();
        Queue(std::initializer_list<Object*> elems);

        // Unique functions ------------------------------------------------

        List* asList() const;
        void enq(Object* elem);
        void enq(std::initializer_list<Object*> elems);
        Object* deq();
        bool isEmpty() const;
        int length() const;

        // Overridden functions --------------------------------------------

        bool boolValue() const override;
        bool equals(const Object* other) const override;
        bool length(int& len) override;
        void showOn(std::ostream& ostream) const override;
        bool toArray(Array*& array) override;
        bool toList(List*& list) override;
        bool toQueue(Queue*& queue) override;
        Object* eval(Evaluator* etor) override;
        TypeId typeId() const override;

    private:
        List* _head {GLOBALS->EmptyList()};
        List* _tail {GLOBALS->EmptyList()};
        int _nElems {0};

    };

}
