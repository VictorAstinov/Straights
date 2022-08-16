#include "AbstractPlayer.h"
#include <vector>
#include <deque>
#include <algorithm>
#include "Card.h"
using namespace std;

AbstractPlayer::AbstractPlayer() {}

void AbstractPlayer::play(Card &c, bool discard) {
  doPlay(c, discard);
}

void AbstractPlayer::clearHand() {
  hand.clear();
  discards.clear();
  legal_moves.clear();
}

void AbstractPlayer::addCard(Card c) {
  hand.push_back(c);
}

vector<Card>& AbstractPlayer::getDiscards() {
  return discards;
}

vector<Card>& AbstractPlayer::getHand() {
  return hand;
}

vector<Card>& AbstractPlayer::getLegalMoves() {
  return legal_moves;
}

int AbstractPlayer::getScore() const noexcept {
  return score;
}

void AbstractPlayer::setScore(int s) noexcept {
  score = s;
}

int AbstractPlayer::getPlayerType() noexcept {
  return doGetPlayerType();
}

void AbstractPlayer::addScore(int s) {
  score += s;
}