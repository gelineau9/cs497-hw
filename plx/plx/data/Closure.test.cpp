#include <gtest/gtest.h>

#include <test/PlxTestFixture.hpp>

#include <plx/data/Array.hpp>
#include <plx/data/Closure.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Function.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/object/Globals.hpp>

namespace PLX {

    class Closure_Test : public PlxTestFixture {};

    TEST_F(Closure_Test, CreateInstance) {
        List* parameters = GLOBALS->EmptyList();
        Object* body = GLOBALS->NilObject();
        Function* function = new Function(parameters, body);
        Triple* lexicalEnvironment = GLOBALS->EmptyTriple();
        Closure* closure1 = new Closure(function, lexicalEnvironment);
        EXPECT_TRUE(closure1->isA(TypeId::D_CLOSURE));
        EXPECT_EQ("Closure", closure1->typeName());
    }

    TEST_F(Closure_Test, Apply_NoArgs) {
        List* parameters = GLOBALS->EmptyList();
        Object* body = GLOBALS->NilObject();
        Function* function = new Function(parameters, body);
        Triple* lexicalEnvironment = GLOBALS->EmptyTriple();
        Closure* closure1 = new Closure(function, lexicalEnvironment);
        Evaluator* etor = new Evaluator();
        List* arguments = GLOBALS->EmptyList();
        Object* value = closure1->apply(etor, arguments);
        EXPECT_EQ(GLOBALS->NilObject(), value);
    }

    TEST_F(Closure_Test, Apply_MultipleArgs) {
        Identifier* x = Identifier::create("x");
        Identifier* y = Identifier::create("y");
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        List* parameters = new List(x, new List(y));
        Object* body = new Array({x, y});
        Function* function = new Function(parameters, body);
        Triple* lexicalEnvironment = GLOBALS->EmptyTriple();
        Closure* closure1 = new Closure(function, lexicalEnvironment);
        Evaluator* etor = new Evaluator();
        List* arguments = new List(i100, new List(i200));
        Object* value = closure1->apply(etor, arguments);
        ASSERT_TRUE(value->isA(TypeId::D_ARRAY));
        Array* valueArray = static_cast<Array*>(value);
        Array* expectedArray = new Array({i100, i200});
        EXPECT_TRUE(expectedArray->equals(valueArray));
    }

    TEST_F(Closure_Test, Apply_LexicalEnvironment) {
        Identifier* x = Identifier::create("x");
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        List* parameters = GLOBALS->EmptyList();
        Object* body = x;
        Function* function = new Function(parameters, body);
        Triple* lexicalEnvironment = new Triple(x, i100);
        Closure* closure1 = new Closure(function, lexicalEnvironment);
        Evaluator* etor = new Evaluator();
        // The lexical environment has x=100 and the dynamic environment has x=200.
        // The lexical environment should be used before the dynamic environment.
        etor->bind(x, i200);
        List* arguments = GLOBALS->EmptyList();
        Object* value = closure1->apply(etor, arguments);
        ASSERT_TRUE(value->isA(TypeId::L_INTEGER));
        EXPECT_TRUE(i100->equals(value));
    }

    TEST_F(Closure_Test, Apply_DynamicEnvironment) {
        Identifier* x = Identifier::create("x");
        Integer* i100 = new Integer(100);
        List* parameters = GLOBALS->EmptyList();
        Object* body = x;
        Function* function = new Function(parameters, body);
        Triple* lexicalEnvironment = GLOBALS->EmptyTriple();
        Closure* closure1 = new Closure(function, lexicalEnvironment);
        Evaluator* etor = new Evaluator();
        // The lexical environment is empty and the dynamic environment has x=200.
        // The dynamic environment is not visible to this expression, though.
        etor->bind(x, i100);
        List* arguments = GLOBALS->EmptyList();
        EXPECT_THROW(closure1->apply(etor, arguments), Array*);
    }

    TEST_F(Closure_Test, ShowOn) {
        Identifier* x = Identifier::create("x");
        Identifier* y = Identifier::create("y");
        Identifier* z = Identifier::create("z");
        Integer* i100 = new Integer(100);
        List* parameters = new List(x);
        Object* body = y;
        Function* function = new Function(parameters, body);
        Triple* lexicalEnvironment = new Triple(z, i100);
        Closure* closure1 = new Closure(function, lexicalEnvironment);
        std::stringstream ss;
        ss << closure1;
        EXPECT_EQ("fun (x) = y", ss.str());
    }

}
