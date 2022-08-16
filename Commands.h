#ifndef COMMANDS_H
#define COMMANDS_H
#include <string>
#include "Card.h"

// namespace for various commands to notify the view to output
// for different chages in state
namespace cmds {
  const extern std::string init;
  const extern std::string startRound;
  const extern std::string deck;
  const extern std::string notifyMove;
  const extern std::string ragequit;
  const extern std::string play;
  const extern std::string discard;
  const extern std::string score;
  const extern std::string invalid;
  const extern std::string win;
  const extern std::string inv_play;
  const extern std::string inv_discard;
  const extern std::string setvals;
  const extern std::string best;
  const extern int DONE;
  const extern int CONTINUE;
  const extern int ERROR;
  const extern Card p_holder;
}
#endif