#ifndef SUBJECT_H
#define SUBJECT_H
#include "Card.h"
#include "Commands.h"
#include <vector>
#include <string>

class GameView;

class Subject {
  std::vector<GameView*> observers;
  public:
  void notifyObservers(std::string cmd, Card c = cmds::p_holder);
  void attach(GameView* o);
  void detach(GameView* o);
  virtual ~Subject() = default;
};
#endif