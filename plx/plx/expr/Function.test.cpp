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
    class Function_Test : public PlxTestFixture {};

    TEST_F(Function_Test, CreateInstance) {
        List* parameters = GLOBALS->EmptyList();
        Object* body = GLOBALS->NilObject();
        Function* fun1 = new Function(parameters, body);
        EXPECT_TRUE(fun1->isA(TypeId::E_FUNCTION));
        EXPECT_EQ("Function", fun1->typeName());
    }

    TEST_F(Function_Test, Eval) {
        Identifier* x = Identifier::create("x");
        Identifier* y = Identifier::create("y");
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        List* parameters = new List(x);
        Object* body = new Array({x, y});
        Function* fun1 = new Function(parameters, body);
        Evaluator* etor = new Evaluator();
        etor->bind(y, i200);
        Object* value1 = etor->evalExpr(fun1);
        ASSERT_TRUE(value1->isA(TypeId::D_CLOSURE));
        // the only way to test if the closure was created correctly
        // is to apply it to arguments
        Closure* closure1 = static_cast<Closure*>(value1);
        List* args = new List(i100);
        Object* value2 = closure1->apply(etor, args);
        Array* expectedArray = new Array({i100, i200});
        EXPECT_TRUE(value2->equals(expectedArray));
    }

    TEST_F(Function_Test, ShowOn) {
        Identifier* x = Identifier::create("x");
        Identifier* y = Identifier::create("y");
        List* parameters = new List(x);
        Object* body = y;
        Function* fun1 = new Function(parameters, body);
        std::stringstream ss;
        ss << fun1;
        EXPECT_EQ("fun (x) = y", ss.str());
    }

}
