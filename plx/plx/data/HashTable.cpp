#include <cassert>
#include <unordered_map>

#include <plx/data/Array.hpp>
#include <plx/data/HashTable.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Triple.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/HashCode.hpp>
#include <plx/object/TypeIds.hpp>
#include <plx/evaluator/Evaluator.hpp>

namespace PLX {

    HashTable::HashTable() {}

    bool HashTable::boolValue() const {
        // return _nBindings != 0;
        return _map.size() != 0;
    }

    int HashTable::count() const {
        // return _nBindings;
        return _map.size();
    }

    bool HashTable::equals(const Object* other) const {
        if (!other->isA(TypeId::D_HASHTABLE)) {
            return false;
        }
        const HashTable* otherHashTable = static_cast<const HashTable*>(other);
        if (count() != otherHashTable->count()) {
            return false;
        }
        for (const auto& pair : _map) {
            Object* key = pair.first;
            Object* value = pair.second;
            Object* otherValue;
            if (!otherHashTable->get(key, otherValue)) {
                return false;
            }
            if (!value->equals(otherValue)) {
                return false;
            }
        }
        return true;
    }
    Object* HashTable::eval(Evaluator* etor){
        HashTable* evalHash = new HashTable();
        for (auto iter = _map.begin(); iter != _map.end(); iter++) {
            try{
                Object* evalKey=etor->evalExpr(iter->first);
                Object* evalValue=etor->evalExpr(iter->second);
                evalHash->put(evalKey,evalValue);
            }
            catch (const std::exception& e) {
                std::cerr << "Error evaluating key-value pair: " << e.what() << std::endl;
            }
        }
        return evalHash;
    }
    bool HashTable::get(Object* key, Object*& value) const {
        auto iter = _map.find(key);
        if (iter != _map.end()) {
            value = iter->second;
            return true;
        }
        return false;
    }

    bool HashTable::index(Object* indexer, Object*& retrievedValue) {
        return get(indexer, retrievedValue);
    }

    bool HashTable::isEmpty() const {
        return _map.empty();
    }

    Array* HashTable::keys() const {
        Array* keyArray = new Array(count());
        int n = 0;
        for (auto iter = _map.begin(); iter != _map.end(); iter++, n++) {
            keyArray->set(n, iter->first);
        }
        return keyArray;
    }

    bool HashTable::length(int& len) {
        len = count();
        return true;
    }

    void HashTable::put(Object* key, Object* value) {
        _map[key] = value;
    }

    void HashTable::removeAllBindings() {
        _map.clear();
    }

    void HashTable::showOn(std::ostream& ostream) const {
        ostream << "#{";
        bool firstIter = true;
        for (auto iter = _map.begin(); iter != _map.end(); iter++) {
            if (firstIter) {
                firstIter = false;
            }
            else {
                ostream << ", ";
            }
            Object* key = iter->first;
            Object* value = iter->second;
            ostream << key << '=' << value;
        }
        ostream << '}';
    }

    TypeId HashTable::typeId() const {
        return TypeId::D_HASHTABLE;
    }

}
