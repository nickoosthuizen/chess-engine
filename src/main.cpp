#include <iostream>
#include <getopt.h>
#include <string>

#include "board.h"
#include "moveGen.h"
#include "perft.h"

struct args {
  std::string fen;
  int depth;
};

struct args parseArgs(int argc, char *argv[]);

int main(int argc, char *argv[]) {
  struct args passed = parseArgs(argc, argv);

  Board b;
  if (passed.fen != "") {
    b = Board(passed.fen);
  }

  if (-1 < passed.depth) {
    unsigned int numNodes = perft(passed.depth, b);
    std::cout << "The number of nodes generated was: " << numNodes << std::endl;
  }
  return 0;
}

struct args parseArgs(int argc, char *argv[]) {
  const char *opstring = "fp";
  struct option longOpts[3] = {{"fen", required_argument, nullptr, 'f'},
                               {"perft", required_argument, nullptr, 'p'},
                               {0, 0, 0, 0}};
  opterr = 0;

  struct args passed = {"", -1};

  int currentOpt;
  while ((currentOpt = getopt_long(argc, argv, opstring, longOpts, nullptr)) != -1) {
    switch(currentOpt) {
      case 'f':
        passed.fen = optarg;
        break;
      case 'p':
        passed.depth = atoi(optarg);
        break;
      case '?':
        break;
    }
  }

  return passed;
}