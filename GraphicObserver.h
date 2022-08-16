#ifndef GRAPH_OBSERVER_H
#define GRAPH_OBSERVER_H
#include "GameView.h"
#include "window.h"
#include "Commands.h"

class GameState;

// not having a window class as an attribute since
// this class will be implemeted just for printing
// which human players won, however a full implementation
// would have one
class Graphics : public GameView {
  GameState* subject;
  void init_players() override;
  void startRound() override;
  void notifyMove() override;
  void printDeck() override;
  void printScore() override;
  void rageQuit() override;
  void play(Card c) override;
  void discard(Card c) override;
  void invalid_cmd() override;
  void invalid_disc() override;
  void invalid_play() override;
  void printWinners() override;
  void setVals() override;
  void best(Card c) override;
  public:
  void notify(std::string cmd, Card c = cmds::p_holder) override;
  Graphics(GameState* s);
  ~Graphics();
};
#endif