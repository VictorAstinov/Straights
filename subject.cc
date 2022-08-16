#include "subject.h"
#include "GameView.h"
#include "Commands.h"
#include <vector>

void Subject::attach(GameView* o) {
  observers.emplace_back(o);
}

void Subject::detach(GameView* o) {
  for (auto it = observers.begin(); it != observers.end();) {
    if (*it == o) {
      it = observers.erase(it);
    }
    else {
      ++it;
    }
  }
}

void Subject::notifyObservers(std::string cmd, Card c) {
  for (auto &o : observers) {
    o->notify(cmd, c);
  }
}