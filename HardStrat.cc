#include "HardStrat.h"
using namespace std;

HardStrat::HardStrat() {
  // fill with default weights
  for (int i = 0; i <= Rank::King; ++i) {
    card_weights.push_back(i);
  }
}

// set with proper weights
HardStrat::HardStrat(vector<int> weights) {
  card_weights = weights;
}


Card HardStrat::doGetMove(std::vector<Card>& legal_moves, bool discard) {
  if (discard) {
    // discard with min value
    int min = card_weights[legal_moves[0].getRank()]; // first card will have min value
    int idx = 0;
    for (int i = 0; i < legal_moves.size(); ++i) {
      if (card_weights[legal_moves[i].getRank()] < min) {
        min = card_weights[legal_moves[i].getRank()];
        idx = i;
      }
    }
    return legal_moves[idx];
  }
  else {
    // play with max values
    int max = card_weights[legal_moves[0].getRank()]; // first card will have max value
    int idx = 0;
    for (int i = 0; i < legal_moves.size(); ++i) {
      if (card_weights[legal_moves[i].getRank()] > max) {
        max = card_weights[legal_moves[i].getRank()];
        idx = i;
      }
    }
    return legal_moves[idx];
  }
}