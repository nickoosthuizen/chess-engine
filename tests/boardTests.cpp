#include <gtest/gtest.h>
#include <string>

#include "board.h"
#include "constants.h"
#include "Move.h"
#include "utilFunctions.h"

TEST(boardTests, defaultConstructor) {
  Board b;
  EXPECT_EQ(b.getAllPieces(), WHITE_START | BLACK_START);
  EXPECT_EQ(b.getEmptySquares(), 0x0000FFFFFFFF0000);
  EXPECT_EQ(b.getBByColor(white), WHITE_START);
  EXPECT_EQ(b.getBByColor(black), BLACK_START);
  EXPECT_EQ(b.getBByPiece(rooks), ROOK_START);
  EXPECT_EQ(b.getBByPiece(kings), KING_START);
  EXPECT_EQ(b.getBByPieceAndColor(queens, white), QUEEN_START & WHITE_START);
  EXPECT_EQ(b.getBByPieceAndColor(kings, black), KING_START & BLACK_START);
}

TEST(boardTests, fenConstructor) {
  std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board defaultConstructor;
  Board fenConstructor(fen);
  EXPECT_EQ(defaultConstructor, fenConstructor);
}

TEST(boardTests, makeMove) {
  Board b;
  b.makeMove(Move(squareToPos("h2"), squareToPos("h4"), DOUBLE_PAWN));
  std::string fen = "rnbqkbnr/pppppppp/8/8/7P/8/PPPPPPP1/RNBQKBNR b KQkq h3 0 1";
  EXPECT_EQ(Board(fen), b);
  b.makeMove(Move(squareToPos("b8"), squareToPos("a6"), REGULAR));
  fen = "r1bqkbnr/pppppppp/n7/8/7P/8/PPPPPPP1/RNBQKBNR w KQkq - 1 2";
  EXPECT_EQ(Board(fen), b);
}

TEST(boardTests, unMakeMove) {
  // Ordinary pawn pushes
  Board b;
  b.makeMove(Move(squareToPos("h2"), squareToPos("h4"), DOUBLE_PAWN));
  b.unMakeMove();
  EXPECT_EQ(b, Board());
  b.makeMove(Move(squareToPos("h2"), squareToPos("h4"), DOUBLE_PAWN));
  b.makeMove(Move(squareToPos("b8"), squareToPos("a6"), REGULAR));
  b.unMakeMove();
  std::string h2h4b8a6 = "rnbqkbnr/pppppppp/8/8/7P/8/PPPPPPP1/RNBQKBNR b KQkq h3 0 1";
  EXPECT_EQ(b, Board(h2h4b8a6));
  b.unMakeMove();
  EXPECT_EQ(b, Board());

  // Pawn capture
  b.makeMove(Move(squareToPos("e2"), squareToPos("e4"), DOUBLE_PAWN));
  std::string e2e4 = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1";
  EXPECT_EQ(b, Board(e2e4));
  b.makeMove(Move(squareToPos("d7"), squareToPos("d5"), DOUBLE_PAWN));
  std::string e2e4d7d5 = "rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 2";
  EXPECT_EQ(b, Board(e2e4d7d5));
  b.makeMove(Move(squareToPos("e4"), squareToPos("d5"), CAPTURE));
  std::string e2e4d7d5e4d5 = "rnbqkbnr/ppp1pppp/8/3P4/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 2";
  EXPECT_EQ(b, Board(e2e4d7d5e4d5));
  b.unMakeMove();
  EXPECT_EQ(b, Board(e2e4d7d5));
  b.unMakeMove();
  EXPECT_EQ(b, Board(e2e4));
  b.unMakeMove();
  EXPECT_EQ(b, Board());
}

TEST(boardTests, enPassatCapture) {
  std::string startFen = "rnbqkbnr/p1pppp1p/8/1p4p1/7N/8/PPPPPPPP/RNBQKB1R w KQkq g6 0 3";
  Move epCapture(squareToPos("h4"), squareToPos("g6"), EP_CAPTURE);
  Board b(startFen);
  b.makeMove(epCapture);
  std::string capturedFen = "rnbqkbnr/p1pppp1p/6N1/1p6/8/8/PPPPPPPP/RNBQKB1R b KQkq - 0 3";
  EXPECT_EQ(b, Board(capturedFen));
  b.unMakeMove();
  EXPECT_EQ(b, Board(startFen));
}

TEST(boardTests, boardToFen) {
  Board b;
  EXPECT_EQ(b.toFen(), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  b = Board("r1bqkbnr/pppppppp/n7/8/7P/8/PPPPPPP1/RNBQKBNR w KQkq - 1 2");
  EXPECT_EQ(b.toFen(), "r1bqkbnr/pppppppp/n7/8/7P/8/PPPPPPP1/RNBQKBNR w KQkq - 1 2");
  b = Board("rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 2");
  EXPECT_EQ(b.toFen(), "rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 2");
}

TEST(boardTests, castlingMakeUnMake) {
  Board b("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 10");
  b.makeMove(Move(squareToPos("h1"), squareToPos("g1"), REGULAR));
  EXPECT_EQ(b, Board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K1R1 b Qkq - 1 10"));
  b.makeMove(Move(squareToPos("e8"), squareToPos("c8"), Q_CASTLE));
  EXPECT_EQ(b, Board("2kr3r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K1R1 w Q - 2 11"));
  b.unMakeMove();
  EXPECT_EQ(b, Board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K1R1 b Qkq - 1 10"));
  b.unMakeMove();
  EXPECT_EQ(b, Board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 10"));
}

TEST(boardTests, promotionTests) {
  Board b("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/1PN2Q1P/P1PBBPp1/R3K2R b KQkq - 0 11");
  Board verify("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/1PN2Q1P/P1PBBPp1/R3K2R b KQkq - 0 11");
  b.makeMove(Move(squareToPos("g2"), squareToPos("g1"), KN_PRMT));
  EXPECT_EQ(b, Board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/1PN2Q1P/P1PBBP2/R3K1nR w KQkq - 0 12"));
  b.unMakeMove();
  EXPECT_EQ(b, verify);
  b.makeMove(Move(squareToPos("g2"), squareToPos("g1"), B_PRMT));
  EXPECT_EQ(b, Board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/1PN2Q1P/P1PBBP2/R3K1bR w KQkq - 0 12"));
  b.unMakeMove();
  EXPECT_EQ(b, verify);
  b.makeMove(Move(squareToPos("g2"), squareToPos("g1"), R_PRMT));
  EXPECT_EQ(b, Board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/1PN2Q1P/P1PBBP2/R3K1rR w KQkq - 0 12"));
  b.unMakeMove();
  EXPECT_EQ(b, verify);
  b.makeMove(Move(squareToPos("g2"), squareToPos("g1"), Q_PRMT));
  EXPECT_EQ(b, Board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/1PN2Q1P/P1PBBP2/R3K1qR w KQkq - 0 12"));
  b.unMakeMove();
  EXPECT_EQ(b, verify);
}