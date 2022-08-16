#include "ComputerPlayer.h"
#include "DefaultStrat.h"
#include "RandomStrat.h"
#include "HardStrat.h"
#include <vector>
#include <algorithm>
using namespace std;

ComputerPlayer::ComputerPlayer(int dif, int seed, vector<int> values) : AbstractPlayer{}, strategy{make_unique<DefaultStrat>()} {
  if (dif == Random) {
    strategy = make_unique<RandomStrat>(seed);
  }
  else if (dif == Hard) {
    strategy = make_unique<HardStrat>(values);
  }
  else {
    strategy = make_unique<DefaultStrat>();
  }
}


void ComputerPlayer::doPlay(Card& c, bool discard) {
  c = getMove(discard);
  hand.erase(remove(hand.begin(), hand.end(), c), hand.end());
  if (discard) {
    discards.push_back(c);
  }
}

Card ComputerPlayer::getMove(bool discard) {
  if (discard) {
    return strategy->getMove(hand, discard);
  }
  else {
    return strategy->getMove(legal_moves, discard);
  }
}

int ComputerPlayer::doGetPlayerType() {
  return Computer;
}
