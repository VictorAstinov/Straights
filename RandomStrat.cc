#include "RandomStrat.h"
#include <random>
using namespace std;

RandomStrat::RandomStrat(int seed) : rng{seed} {}

Card RandomStrat::doGetMove(std::vector<Card>& legal_moves, bool discard) {
  return legal_moves[rng() % legal_moves.size()];
}
