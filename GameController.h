#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <sstream>
#include "GameState.h"
#include "GameView.h"


class GameController {
  GameState* state;
  std::istream& in;
  std::ostringstream& log;
  bool saved;
  std::vector<std::unique_ptr<GameView>> observers;
  void initPlayers();
  void save();
  void computerMove(int current_player);
  public:
  GameController(GameState* state, std::istream& in, std::ostringstream& log, bool s = false);
  int playGame();
};
#endif