#include "CompStrategy.h"
#include <vector>

Card CompStrategy::getMove(std::vector<Card>& legal_moves, bool discard) {
  return doGetMove(legal_moves, discard);
}