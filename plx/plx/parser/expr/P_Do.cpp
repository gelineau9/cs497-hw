#include <cassert>

#include <plx/data/Queue.hpp>
#include <plx/expr/Do.hpp>
#include <plx/parser/P_Primitive.hpp>
#include <plx/parser/P_ReservedWords.hpp>

namespace PLX {

    bool pDo(List*& tokens, Object*& value) {
        Object* ignore;
        Queue* values = new Queue();
        if (!pReservedDo(tokens, ignore)) {
            return false;
        }
        else{
            Object* result;
            while(pAny(tokens, result)){
                values->enq(result);
            }
        }
        if(tokens->isEmpty()) {
            return false;
        }

        if (!pReservedEnd(tokens, ignore)) {
            return false;
        }
        
        value = new Do(values->asList());
        

        return true;
    }

}
