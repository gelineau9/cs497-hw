#include <gtest/gtest.h>

#include <test/PlxTestFixture.hpp>

#include <plx/data/Array.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/expr/Let.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    class Let_Test : public PlxTestFixture {};

    TEST_F(Let_Test, CreateInstance) {
        Let* let1 = new Let(GLOBALS->EmptyTriple());
        EXPECT_TRUE(let1->isA(TypeId::E_LET));
        EXPECT_EQ("Let", let1->typeName());
    }

    TEST_F(Let_Test, Eval_Evaluator) {
        Identifier* identX = Identifier::create("x");
        Integer* i100 = new Integer(100);
        Let* let1 = new Let(new Triple(identX, i100));
        Evaluator* etor = new Evaluator();
        Object* value = etor->evalExpr(let1);
        EXPECT_EQ(GLOBALS->NilObject(), value);
        value = etor->lookup(identX);
        EXPECT_EQ(i100, value);
    }

    // TEST_F(Let_Test, Eval_MatchFailure_Evaluator) {
    //     Evaluator* etor = new Evaluator();
    //     Integer* i100 = new Integer(100);
    //     Integer* i200 = new Integer(200);
    //     Let* let1 = new Let(new Triple(i100, i200));
    //     ASSERT_THROW(etor->evalExpr(let1), Array*);
    // }
    //COMMENTED AS PER INSTRUCTIONS

    TEST_F(Let_Test, ShowOn) {
        Identifier* x = Identifier::create("x");
        Identifier* y = Identifier::create("y");
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        Let* let1 = new Let(new Triple(x, i100, new Triple(y, i200)));
        std::stringstream ss;
        ss << let1;
        EXPECT_EQ("let x=100, y=200", ss.str());
    }

}