#include <gtest/gtest.h>

#include "utilFunctions.h"

TEST(bitToSquareTests, basic) {
  EXPECT_EQ(bitToSquare(0x0100000000000000), "h8");
  EXPECT_EQ(bitToSquare(0x0400000000000000), "f8");
  EXPECT_EQ(bitToSquare(0x0000800000000000), "a6");
  EXPECT_EQ(bitToSquare(0x0000000000000008), "e1");
}