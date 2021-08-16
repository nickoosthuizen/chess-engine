#include <gtest/gtest.h>

#include "perft.h"

TEST(perftTests, initialBoard) {
  Board b;
  ASSERT_EQ(perft(1, b), 20);
  ASSERT_EQ(perft(2, b), 400);
  ASSERT_EQ(perft(3, b), 8902);
  ASSERT_EQ(perft(4, b), 197281);
  ASSERT_EQ(perft(5, b), 4865609);
}

TEST(perftTests, kiwipeteBoard) {
  Board b("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 10");
  ASSERT_EQ(perft(1, b), 48);
  ASSERT_EQ(perft(2, b), 2039);
  ASSERT_EQ(perft(3, b), 97862);
  ASSERT_EQ(perft(4, b), 4085603);
}