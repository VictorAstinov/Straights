#include "HumanPlayer.h"
#include <vector>
#include <algorithm>
using namespace std;

HumanPlayer::HumanPlayer() : AbstractPlayer{} {}

void HumanPlayer::doPlay(Card& c, bool discard) {
  hand.erase(remove(hand.begin(), hand.end(), c), hand.end());
  if (discard) {
    discards.push_back(c);
  }
}

int HumanPlayer::doGetPlayerType() {
  return Human;
}

