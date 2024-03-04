#include <plx/data/Array.hpp>
#include <plx/data/HashTable.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Quote.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/literal/String.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/Object.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    Quote::Quote(Object* contents) {
        _contents = contents;
    }

    Object* Quote::eval(Evaluator* etor) {
        return _contents;
    }

    TypeId Quote::typeId() const {
        return TypeId::E_QUOTE;
    }
    void Quote::showOn(std::ostream& ostream) const {
        ostream<<"'"<<_contents<<"'";
    }
}