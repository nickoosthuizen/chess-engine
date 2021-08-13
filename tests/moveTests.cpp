#include <gtest/gtest.h>
#include <stdint.h>

#include "Move.h"
#include "constants.h"

TEST(moveTests, initialization) {
  uint16_t from = 1;
  uint16_t to = 24;
  Move m(from, to, REGULAR);
  EXPECT_EQ(m.getFrom(), from);
  EXPECT_EQ(m.getTo(), to);
  EXPECT_EQ(m.getFlag(), REGULAR);
}