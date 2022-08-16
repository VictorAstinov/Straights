#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H
#include <vector>
#include <memory>
#include "AbstractPlayer.h"
#include "CompStrategy.h"

static const std::vector<int> empty;

class ComputerPlayer : public AbstractPlayer {
  std::unique_ptr<CompStrategy> strategy;
  Card getMove(bool discard);
  void doPlay(Card& c, bool discard = false) override;
  int doGetPlayerType() override;
  public:
  explicit ComputerPlayer(int dif = 0, int seed = 0, std::vector<int> values = empty);
};
#endif