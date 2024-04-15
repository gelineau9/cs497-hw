#include <gtest/gtest.h>

#include <test/PlxTestFixture.hpp>

#include <plx/data/Array.hpp>
#include <plx/data/List.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Apply.hpp>
#include <plx/expr/Function.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/literal/Integer.hpp>

namespace PLX {

    class Apply_Test : public PlxTestFixture {};

    TEST_F(Apply_Test, CreateInstance) {
        Identifier* x = Identifier::create("x");
        Apply* apply = new Apply(x, GLOBALS->EmptyList());
        EXPECT_TRUE(apply->isA(TypeId::E_APPLY));
        EXPECT_EQ("Apply", apply->typeName());
    }

    TEST_F(Apply_Test, Eval) {
        Identifier* x = Identifier::create("x");
        Identifier* y = Identifier::create("y");
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        List* parameters = new List(x);
        Object* body = new Array({x, y});
        Function* fun1 = new Function(parameters, body);
        List* args = new List(i100);
        Apply* app1 = new Apply(fun1, args);
        Evaluator* etor = new Evaluator();
        etor->bind(y, i200);
        Object* value = etor->evalExpr(app1);
        Array* expectedArray = new Array({i100, i200});
        EXPECT_TRUE(value->equals(expectedArray));
    }

    TEST_F(Apply_Test, MarkChildren) {
        Identifier* x = Identifier::create("x");
        Identifier* y = Identifier::create("y");
        List* arguments = new List(y);
        Apply* app1 = new Apply(x, arguments);
        EXPECT_FALSE(app1->isMarked());
        EXPECT_FALSE(arguments->isMarked());
        EXPECT_FALSE(x->isMarked());
        EXPECT_FALSE(y->isMarked());
        app1->markChildren();
        EXPECT_FALSE(app1->isMarked());
        EXPECT_TRUE(arguments->isMarked());
        EXPECT_TRUE(x->isMarked());
        EXPECT_TRUE(y->isMarked());
    }

    TEST_F(Apply_Test, ShowOn) {
        {
            Identifier* x = Identifier::create("x");
            Identifier* y = Identifier::create("y");
            List* arguments = new List(y);
            Apply* app1 = new Apply(x, arguments);
            std::stringstream ss;
            ss << app1;
            EXPECT_EQ("x(y)", ss.str());
        }
        {
            Identifier* x = Identifier::create("x");
            Function* fun1 = new Function(new List(x), x);
            Identifier* y = Identifier::create("y");
            List* arguments = new List(y);
            Apply* app1 = new Apply(fun1, arguments);
            std::stringstream ss;
            ss << app1;
            EXPECT_EQ("(fun (x) = x)(y)", ss.str());
        }
    }

}
