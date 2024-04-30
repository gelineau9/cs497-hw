#include <cassert>

#include <plx/data/Triple.hpp>
#include <plx/data/Queue.hpp>
#include <plx/expr/Let.hpp>
#include <plx/expr/LetIn.hpp>
#include <plx/parser/P_Primitive.hpp>
#include <plx/parser/P_ReservedWords.hpp>
#include <plx/parser/P_Any.hpp>
#include <plx/parser/P_SpecialChars.hpp>


namespace PLX {

     bool pLet(List*& tokens, Object*& value) {
        Object* ignore;
        if (!pReservedLet(tokens, ignore)) {
            return false;
        }
        Object* identifier1;
        if (!pIdentifier(tokens, identifier1)) {
            return false;
        }

        if (!pIgnoreEquals(tokens, ignore)) {
            return false;
        }
        
        Object* expression;
        if (!pRequireAny(tokens, expression)) {
            return false;
        }
        Triple* bindings = new Triple(identifier1,expression);
        if (pReservedIn(tokens, ignore)) {
            Object* body;
            if (!pRequireAny(tokens, body)) {
                return false;
            }
            value = new LetIn(bindings, body);
            return true;
        }
        value = new Let(bindings);
        

        return true;
    }

}