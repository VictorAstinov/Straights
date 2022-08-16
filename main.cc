#include "GameController.h"
#include "GameState.h"
#include "Commands.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

// main will handle cmd-line parsing
int main(int argc, char** argv) {
  int seed = std::chrono::system_clock::now().time_since_epoch().count();
  bool saved = false;
  std::string log{"log.txt"};
  if (argc > 1) {
    for (int i = 1; i < argc; ++i) {
      if (std::string(argv[i]) == "--seed") {
        try {
          seed = std::stoi(std::string(argv[i + 1]));
          ++i;
        }
        catch (std::out_of_range &e) {
          // invalid seed
          std::cerr << e.what() << std::endl;
          return 2;
        }
        catch (std::invalid_argument &e) {
          // invalid seed
          std::cerr << e.what() << std::endl;
          return 2;
        }
      }
      else if (std::string(argv[i]) == "--save") {
        log = argv[i + 1];
        ++i;
        saved = true;
      }
    }
  }
  std::ostringstream buffer;
  std::ifstream save{log};
  int result;
  if (saved) {
    if (save.fail()) {
      std::cerr << "Error: Save state is unreadable!" << std::endl;
      return 10;
    }
    GameState state(save);
    GameController save_state(&state, std::cin, buffer, saved);
    result = save_state.playGame();
  }
  else {
    GameState state(seed);
    GameController game(&state, std::cin, buffer);
    result = game.playGame();
  }
  std::ofstream new_save{log};
  new_save << buffer.str();
  return result;
}