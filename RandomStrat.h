#ifndef RANDOM_STRAT_H
#define RANDOM_STRAT_H
#include <vector>
#include <random>
#include "CompStrategy.h"

class RandomStrat : public CompStrategy {
  Card doGetMove(std::vector<Card>& legal_moves, bool discard) override;
  std::default_random_engine rng;
  public:
  explicit RandomStrat(int seed);
  ~RandomStrat() = default;
};
#endif