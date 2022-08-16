#ifndef DEFAULT_RULES_H
#define DEFAULT_RULES_H
#include "AbstractRules.h"
#include <vector>

class DefaultRules : public AbstractRules {
  virtual int DoExitScore() override;
  virtual Card DoStartCard() override;
  virtual int DoCalcScore(std::vector<Card> discards) override;
  virtual std::vector<int>& DoGetWeights() override;
  virtual void DoSetScore(int s) override;
  virtual void DoSetCard(Card c) override;
  Card start_card;
  int exit_score;
  std::vector<int> weights;
  public:
  DefaultRules();
};
#endif