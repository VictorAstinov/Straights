#include "DefaultStrat.h"
#include <vector>
using namespace std;

// default strat is to play/discard first card
Card DefaultStrat::doGetMove(vector<Card>& legal_moves, bool discard) {
  return legal_moves[0];
}