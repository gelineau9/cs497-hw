#include <gtest/gtest.h>

#include <test/PlxTestFixture.hpp>

#include <plx/data/HashTable.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    class Identifier_Test : public PlxTestFixture {};

    TEST_F(Identifier_Test, CreateInstance) {
        Identifier* identifier1 = Identifier::create("Abc");
        EXPECT_TRUE(identifier1->isA(TypeId::E_IDENTIFIER));
        EXPECT_EQ("Identifier", identifier1->typeName());
        Identifier* identifier2 = Identifier::create("Abc");
        // This asserts that both identifiers are the same object
        ASSERT_EQ(identifier1, identifier2);
        HashCode hashCode1;
        EXPECT_TRUE(identifier1->hashCode(hashCode1));
        HashCode hashCode2;
        EXPECT_TRUE(identifier2->hashCode(hashCode2));
        EXPECT_NE(0, hashCode1);
        EXPECT_NE(0, hashCode2);
        EXPECT_EQ(hashCode1, hashCode2);
        Identifier* identifier3 = Identifier::create("Def");
        HashCode hashCode3;
        EXPECT_TRUE(identifier3->hashCode(hashCode3));
        EXPECT_NE(hashCode1, hashCode3);
        EXPECT_NE(hashCode2, hashCode3);
    }


    TEST_F(Identifier_Test, Eval) {
        Evaluator* etor = new Evaluator();
        Identifier* abc = Identifier::create("abc");
        Integer* i100 = new Integer(100);
        etor->bind(abc, i100);
        Object* value = abc->eval(etor);
        EXPECT_EQ(i100, value);
    }



    TEST_F(Identifier_Test, EvalUnbound) {
        Evaluator* etor = new Evaluator();
        Identifier* abc = Identifier::create("abc");
        EXPECT_THROW(abc->eval(etor), Array*);
    }


    TEST_F(Identifier_Test, ShowOn) {
        {
            std::stringstream ss;
            Identifier* ident1 = Identifier::create("abc");
            ss << ident1;
            EXPECT_EQ("abc", ss.str());
        }
        {
            std::stringstream ss;
            Identifier* ident1 = Identifier::create("def");
            ss << ident1;
            EXPECT_EQ("def", ss.str());
        }
    }

}
