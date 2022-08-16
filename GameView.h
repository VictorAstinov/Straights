#ifndef GAME_VIEW_H
#define GAME_VIEW_H
#include "Card.h"
#include "Commands.h"
#include <string>


class GameView {
  virtual void init_players() = 0;
  virtual void startRound() = 0;
  virtual void notifyMove() = 0;
  virtual void printDeck() = 0;
  virtual void printScore() = 0;
  virtual void rageQuit() = 0;
  virtual void play(Card c) = 0;
  virtual void discard(Card c) = 0;
  virtual void invalid_cmd() = 0;
  virtual void invalid_disc() = 0;
  virtual void invalid_play() = 0;
  virtual void printWinners() = 0;
  virtual void setVals() = 0;
  virtual void best(Card c) = 0;
  public:
  virtual void notify(std::string cmd, Card c = cmds::p_holder) = 0;
  virtual ~GameView() = default;
};
#endif