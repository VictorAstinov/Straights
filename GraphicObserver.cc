#include "GraphicObserver.h"
#include "GameState.h"
#include "Commands.h"
#include <vector>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

Graphics::Graphics(GameState* s) : subject{s} {
  subject->attach(this);
}

void Graphics::notify(string cmd, Card c) {
  if (cmd == cmds::init) {
    init_players();
  }
  else if (cmd == cmds::startRound) {
    startRound();
  }
  else if (cmd == cmds::deck) {
    printDeck();
  }
  else if (cmd == cmds::notifyMove) {
    notifyMove();
  }
  else if (cmd == cmds::ragequit) {
    rageQuit();
  }
  else if (cmd == cmds::play) {
    play(c);
  }
  else if (cmd == cmds::discard) {
    discard(c);
  }
  else if (cmd == cmds::score) {
    printScore();
  }
  else if (cmd == cmds::invalid) {
    invalid_cmd();
  }
  else if (cmd == cmds::inv_play) {
    invalid_play();
  }
  else if (cmd == cmds::inv_discard) {
    invalid_disc();
  }
  else if (cmd == cmds::setvals) {
    setVals();
  }
  else if (cmd == cmds::best) {
    best(c);
  }
  else if (cmd == cmds::win) {
    printWinners();
  }
}

// these functions do nothing, but if a full implementation
// of graphics was done they'd do different things

void Graphics::init_players() {}

void Graphics::startRound() {}

void Graphics::notifyMove() {}

void Graphics::printDeck() {}

void Graphics::printScore() {}

void Graphics::rageQuit() {}

void Graphics::play(Card c) {}

void Graphics::discard(Card c) {}

void Graphics::invalid_cmd() {}

void Graphics::invalid_disc() {}

void Graphics::invalid_play() {}

void Graphics::setVals() {}

void Graphics::best(Card c) {}

// prints window, then closes after 10 seconds
void Graphics::printWinners() {
  using namespace chrono_literals;
  vector<int> winners = subject->getWinners();
  // check if difficulty is hard
  if (subject->getAIlevel() != Hard) {
    return;
  }
  // check for human winners
  int count = 0;
  for (int p : winners) {
    if (subject->getPlayerType(p) == Player::Human) {
      ++count;
    }
  }
  if (!count) {
    return;
  }
  const int center = 230;
  const int shift = 15;
  int offset = 20;
  Xwindow window;
  window.drawString(center, offset, "CONGRATULATIONS!");
  offset += shift;
  for (int player : winners) {
    if (subject->getPlayerType(player) == Player::Human) {
      string str{"Player"};
      str = str + to_string(player + 1) + " wins!";
      window.drawString(center, offset, str);
      offset += shift;
    }
  }
  this_thread::sleep_for(10s);
}

Graphics::~Graphics() {
  subject->detach(this);
}