#include "prefixModule.h"

#include <gtest.h>

TEST(PrefixModule, can_create_module) {
    normalArith str = "2 + 2";
    ASSERT_NO_THROW(PrefixModule god(str));
}

TEST(PrefixModule, can_give_normal) {
    normalArith str = "2 + 2";
    PrefixModule god(str);
    ASSERT_NO_THROW(god.get_normal());
}

TEST(PrefixModule, give_normal_correctly) {
    normalArith str = "2 + 2";
    PrefixModule god(str);
    EXPECT_EQ(str, god.get_normal());
}

TEST(PrefixModule, can_give_prefix) {
    normalArith str = "2 + 2";
    PrefixModule god(str);
    ASSERT_NO_THROW(god.get_prefix());
}

TEST(PrefixModule, algo_works_easy) {
    normalArith str = "2 + 2";
    PrefixModule god(str);
    prefixArith ans = "22+";
    EXPECT_EQ(ans, god.get_prefix());
}

TEST(PrefixModule, algo_works_normal) {
    normalArith str = "2 + 2 * 3";
    PrefixModule god(str);
    prefixArith ans = "223*+";
    EXPECT_EQ(ans, god.get_prefix());
}

TEST(PrefixModule, algo_works_medium) {
    normalArith str = "9 + 5 * (4 + 3 / 5) - 2";
    PrefixModule god(str);
    prefixArith ans = "95435/+*2-+";
    EXPECT_EQ(ans, god.get_prefix());
}

TEST(PrefixModule, algo_works_hard) {
    normalArith str = "9 + 5 * (4 + 3 * 5 ^ 4) - 2";
    PrefixModule god(str);
    prefixArith ans = "954354^*+*2-+";
    EXPECT_EQ(ans, god.get_prefix());
}

TEST(PrefixModule, step_push_works) {
    normalArith str = "2 + 2 * 3";
    PrefixModule god(str);
    ASSERT_NO_THROW(god.step_push());
}

TEST(PrefixModule, step_push_works_correctly_1_step) {
    normalArith str = "2 + 2 * 3";
    PrefixModule god(str);
    EXPECT_EQ(god.step_push(), 2 * 3);
}

TEST(PrefixModule, step_push_works_correctly_2_plus_step) {
    normalArith str = "2 + 2 * 3 - 1";
    PrefixModule god(str);
    EXPECT_EQ(god.step_push(), 2 * 3);
    EXPECT_EQ(god.step_push(), 2 * 3 - 1);
}

TEST(PrefixModule, calculate_works) {
    normalArith str = "9 + 5 * (4 + 3 * 5) - 2";
    PrefixModule god(str);
    ASSERT_NO_THROW(god.calculate());
}

TEST(PrefixModule, calculate_works_correctly) {
    normalArith str = "9 + 5 * (4 + 3 * 5) - 2";
    PrefixModule god(str);
    EXPECT_EQ(god.calculate(), 9 + 5 * (4 + 3 * 5) - 2);
}
