#include "Commands.h"

namespace cmds {
  const std::string init{"init"};
  const std::string startRound{"startRound"};
  const std::string deck{"deck"};
  const std::string notifyMove{"notifyMove"};
  const std::string ragequit{"ragequit"};
  const std::string play{"play"};
  const std::string discard{"discard"};
  const std::string score{"score"};
  const std::string invalid{"Invalid Command"};
  const std::string win{"win"};
  const std::string inv_play{"inv_play"};
  const std::string inv_discard{"inv_disc"};
  const std::string load{"load"};
  const std::string setvals{"setvals"};
  const std::string best{"best"};
  const int DONE{0};
  const int CONTINUE{1};
  const int ERROR{2};
  const Card p_holder{0,0};
}
