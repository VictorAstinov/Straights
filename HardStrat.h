#ifndef HARD_STRAT_H
#define HARD_STRAT_H
#include "CompStrategy.h"
#include <vector>

class HardStrat : public CompStrategy {
  std::vector<int> card_weights;
  Card doGetMove(std::vector<Card>& legal_moves, bool discard) override;
  public:
  HardStrat();
  explicit HardStrat(std::vector<int> weights);
  ~HardStrat() = default;
};
#endif