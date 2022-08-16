#ifndef COMP_STRATEGY_H
#define COMP_STRATEGY_H
#include <vector>
#include "Card.h"

class CompStrategy {
  virtual Card doGetMove(std::vector<Card>& legal_moves, bool discard) = 0;
  public:
  Card getMove(std::vector<Card>& legal_moves, bool discard);
  virtual ~CompStrategy() = default;
};
#endif