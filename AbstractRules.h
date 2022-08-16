#ifndef ABSTRACT_RULES_H
#define ABSTRACT_RULES_H
#include "Deck.h"
#include <vector>

class AbstractRules {
  virtual int DoExitScore() = 0;
  virtual Card DoStartCard() = 0;
  virtual int DoCalcScore(std::vector<Card> discards) = 0;
  virtual std::vector<int>& DoGetWeights() = 0;
  virtual void DoSetScore(int s) = 0;
  virtual void DoSetCard(Card c) = 0;
  public:
  AbstractRules() = default;
  int exitScore();
  Card startCard();
  std::vector<int>& getWeights();
  void setScore(int s);
  void setCard(Card c);
  int calcScore(std::vector<Card> discards) noexcept;
  virtual ~AbstractRules() = default;
};
#endif