#include <gtest/gtest.h>

#include "perft.h"

// Testing the positions listed on perft results at 
// https://www.chessprogramming.org/Perft_Results

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

TEST(perftTests, position3) {
  Board b("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 15");
  ASSERT_EQ(perft(1, b), 14);
  ASSERT_EQ(perft(2, b), 191);
  ASSERT_EQ(perft(3, b), 2812);
  ASSERT_EQ(perft(4, b), 43238);
  ASSERT_EQ(perft(5, b), 674625);
}

TEST(perftTests, position4) {
  Board b("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
  ASSERT_EQ(perft(1, b), 6);
  ASSERT_EQ(perft(2, b), 264);
  ASSERT_EQ(perft(3, b), 9467);
  ASSERT_EQ(perft(4, b), 422333);
}

TEST(perftTests, position5) {
  Board b("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8 ");
  ASSERT_EQ(perft(1, b), 44);
  ASSERT_EQ(perft(2, b), 1486);
  ASSERT_EQ(perft(3, b), 62379);
  ASSERT_EQ(perft(4, b), 2103487);
}

TEST(perftTests, position6) {
  Board b("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10 ");
  ASSERT_EQ(perft(1, b), 46);
  ASSERT_EQ(perft(2, b), 2079);
  ASSERT_EQ(perft(3, b), 89890);
  ASSERT_EQ(perft(4, b), 3894594);
}