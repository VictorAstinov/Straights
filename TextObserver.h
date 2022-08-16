#ifndef TEXT_OBSERVER_H
#define TEXT_OBSERVER_H
#include "GameView.h"

class GameState;

class TextObserver : public GameView {
  GameState* subject;
  template <typename T> void printCards(const T& cards);
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
  TextObserver(GameState* s);
  ~TextObserver();
};
#endif