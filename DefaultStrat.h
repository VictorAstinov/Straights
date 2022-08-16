#ifndef DEFAULT_STRAT_H
#define DEFAULT_STRAT_H
#include "CompStrategy.h"
#include <vector>

class DefaultStrat : public CompStrategy {
  Card doGetMove(std::vector<Card>& legal_moves, bool discard) override;
};
#endif