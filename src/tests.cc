#include <gtest/gtest.h>
#include "biginteger.hpp"

TEST(SanityCheck, TrueIsTrue) {
    EXPECT_TRUE(true);
}

TEST(Constructure, DefaultConstructure) {
    BigInteger x();
    EXPECT_EQ(x, 0);
}
