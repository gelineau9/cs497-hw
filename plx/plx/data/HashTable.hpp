#pragma once

#include <unordered_map>

#include <plx/object/Object.hpp>

namespace PLX {

    class Array;
    class Triple;

    class HashTable : public Object {
    public:
        HashTable();

        // Unique functions ------------------------------------------------

        int count() const;
        bool isEmpty() const;
        Array* keys() const;
        bool get(Object* key, Object*& value) const;
        void put(Object* key, Object* value);
        void removeAllBindings();

        // Overridden functions --------------------------------------------

        bool boolValue() const override;
        bool equals(const Object* other) const override;
        bool index(Object* indexer, Object*& retrievedValue) override;
        bool length(int& len) override;
        void showOn(std::ostream& ostream) const override;
        Object* eval(Evaluator* etor) override;
        TypeId typeId() const override;

    private:
        std::unordered_map<Object*, Object*> _map;

    };

}
