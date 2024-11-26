#include "postfix.h"
#include <gtest.h>

TEST(Calc, test_constructor){
    EXPECT_NO_THROW(Calc a("(12-2)*34+2"));
}
TEST(Calc, test_postfixed){
    Calc a("(12-2)*34+2");
    EXPECT_NO_THROW(a.postfixed());
}

TEST(Calc, test_postfixed_correct){
    Calc a("(12-2)*34+2");
    EXPECT_EQ(a.postfixed(), "12 2 - 34 * 2 + ");
}

TEST(Calc, test_calculate){
    Calc a("(12-2)*34+2");
    a.postfixed();
    EXPECT_NO_THROW(a.calculate());
}

TEST(Calc, test_calculate_correct){
    Calc a("(12-2)*34+2");
    a.postfixed();
    EXPECT_EQ(342,a.calculate());
}