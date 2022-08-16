#include "AbstractRules.h"
using namespace std;

int AbstractRules::exitScore() {
  return DoExitScore();
}

Card AbstractRules::startCard() {
  return DoStartCard();
}

int AbstractRules::calcScore(vector<Card> discards) noexcept {
  return DoCalcScore(discards);
}

std::vector<int>& AbstractRules::getWeights() {
  return DoGetWeights();
}

void AbstractRules::setScore(int s) {
  DoSetScore(s);
}

void AbstractRules::setCard(Card c) {
  DoSetCard(c);
}