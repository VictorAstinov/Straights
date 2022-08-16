#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H
#include "AbstractPlayer.h"

class HumanPlayer : public AbstractPlayer {
  void doPlay(Card& c, bool discard = false) override;
  int doGetPlayerType() override;
  public:
  HumanPlayer();
};
#endif