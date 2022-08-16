#include "TextObserver.h"
#include "GameState.h"
#include <vector>
#include <deque>
#include <iostream>
#include <string>
#include "Commands.h"
using namespace std;

TextObserver::TextObserver(GameState* s) : subject{s} {
  subject->attach(this);
}

template <typename T> void TextObserver::printCards(const T& cards) {
  for (auto c : cards) {
    cout <<" " << c;
  }
}

void TextObserver::notify(string cmd, Card c) {
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

void TextObserver::init_players() {
  int player = subject->total_players() + 1;
  cout << "Is Player" << player << " a human (h) or a computer (c)?" << endl;
}

void TextObserver::startRound() {
  int p = subject->getStartingPlayer() + 1;
  cout << "A new round begins. It's Player" << p << "'s turn to play." << endl;
}

void TextObserver::notifyMove() {
  vector<deque<Card>> table = subject->getTable();
  cout << "Cards on the table:" << endl;
  cout << "Clubs:";
  printCards(table[Suit::Club]);
  cout << endl;
  cout << "Diamonds:";
  printCards(table[Suit::Diamond]);
  cout << endl;
  cout << "Hearts:";
  printCards(table[Suit::Heart]);
  cout << endl;
  cout << "Spades:";
  printCards(table[Suit::Spade]);
  cout << endl;
  AbstractPlayer* player = subject->getPlayer(subject->getCurrentPlayer());
  cout << "Your hand:";
  printCards(player->getHand());
  cout << endl;
  cout << "Legal plays:";
  printCards(subject->getLegalMoves(player));
  cout << endl;
}

void TextObserver::printDeck() {
  vector<Card>& deck = subject->getDeck();
  for (int i = 1; i <= deck.size(); ++i) {
    if (i % 13 == 0) {
      cout << deck[i -1] << endl;
    }
    else {
      cout << deck[i - 1] << " ";
    }
  }
}

void TextObserver::rageQuit() {
  int player = subject->getCurrentPlayer() + 1;
  cout << "Player " << player << " ragequits." << " A computer will now take over." << endl; 
}

void TextObserver::play(Card c) {
  cout << "Player" << subject->getCurrentPlayer() + 1 << " plays " << c << "." << endl;
}

void TextObserver::discard(Card c) {
  cout << "Player" << subject->getCurrentPlayer() + 1 << " discards " << c << "." << endl;
}

void TextObserver::printScore() {
  for (int i = 0; i < subject->total_players(); ++i) {
    AbstractPlayer* player = subject->getPlayer(i);
    cout << "Player" << i + 1 <<"'s discards:";
    printCards(player->getDiscards());
    cout << endl;
    int disc_score = subject->getRules()->calcScore(player->getDiscards());
    cout << "Player" << i + 1 <<"'s score: " << player->getScore() << " + ";
    cout << disc_score << " = " << disc_score + player->getScore() << endl;
  }
}


void TextObserver::invalid_cmd() {
  cout << "Invalid command" << endl;
}

void TextObserver::invalid_play() {
  cout << "This is not a legal play." << endl;
}

void TextObserver::invalid_disc() {
  cout << "You have a legal play. You may not discard." << endl;
}

void TextObserver::printWinners() {
  vector<int> winners = subject->getWinners();
  for (int player : winners) {
    cout << "Player" << player + 1 << " wins!" << endl;
  }
}


void TextObserver::setVals() {
  cout << "Enter values in order of: A 2 3 4 5 6 7 8 9 T J Q K" << endl;
}

void TextObserver::best(Card c) {
  auto player = subject->getPlayer(subject->getCurrentPlayer());
  auto hand = player->getLegalMoves();
  cout << "Best card to " << (hand.empty() ? "discard" : "play") << " is: " << c << endl;
}
TextObserver::~TextObserver() {
  subject->detach(this);
}