#include "DefaultRules.h"
using namespace std;

static const int START_SCORE = 80;
static const Card START_CARD{Rank::Seven, Suit::Spade};


DefaultRules::DefaultRules() : AbstractRules{}, start_card{START_CARD}, exit_score{START_SCORE} {
  // fill vector with default weights
  for (int i = 0; i<= Rank::King; ++i) {
    weights.push_back(i);
  }
}

int DefaultRules::DoExitScore() {
  return exit_score;
}

Card DefaultRules::DoStartCard() {
  return start_card;
}

vector<int>& DefaultRules::DoGetWeights() {
  return weights;
}

void DefaultRules::DoSetScore(int s) {
  exit_score = s;
}

void DefaultRules::DoSetCard(Card c) {
  start_card = c;
}

int DefaultRules::DoCalcScore(vector<Card> discards) {
  int sum = 0;
  for (auto card : discards) {
    sum += weights[card.getRank()];
  }
  return sum;
}


