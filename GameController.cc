#include "GameController.h"
#include "AbstractPlayer.h"
#include "TextObserver.h"
#include "GraphicObserver.h"
#include "Commands.h"
#include "Card.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>
using namespace std;

GameController::GameController(GameState* state, istream& in, ostringstream& log, bool s) : state{state}, in{in}, log{log}, saved{s} {}

void GameController::initPlayers() {
  // initialze players
  int i = state->total_players();
  for (; i < 4; ++i) {
    while(true) {
      state->notifyObservers(cmds::init);
      char player;
      in >> player;
      if (in.eof() || in.fail()) {
        exit(cmds::ERROR); // fail to initilize, immediately quit
      }
      // handle error here
      try {
        state->init_player(player);
        break;
      }
      catch (invalid_argument &e) {
        state->notifyObservers(cmds::invalid);;
      }
    } 
  }
}

void GameController::save() {
  // clear save contents
  log.str("");
  // save seed
  log << state->getSeed() << endl;
  // save player info
  for (int i = 0; i < state->total_players(); ++i) {
    if (state->getPlayerType(i) == Player::Human) {
      log << 'h' << endl;
    }
    else {
      log << 'c' << endl;
    }
    log << state->getPlayer(i)->getScore() << endl;
    for (auto c : state->getPlayer(i)->getHand()) {
      log << c << " ";
    }
    log << endl;
    for (auto c : state->getPlayer(i)->getDiscards()) {
      log << c << " ";
    }
    log << endl;
  }
  // save table info
  for (int i = 0; i < Suit::TOTAL_SUITS; ++i) {
    for (auto c : state->getTable()[i]) {
      log << c << " ";
    }
    log << endl;
  }
  // save current player
  log << state->getCurrentPlayer() << endl;
  // save if first move
  log << state->getFirstMove() << endl;
  // log exit score
  log << state->getRules()->exitScore() << endl;
  // log start card
  log << state->getRules()->startCard() << endl;
  // log card values
  for (auto val : state->getRules()->getWeights()) {
    log << val << " ";
  }
  log << endl;
  // log AI difficulty
  log << state->getAIlevel() << endl;
  // log shuffle count so that same shuffles arent reproduced
  log << state->getShuffles() << endl;
}


void GameController::computerMove(int current_player) {
  Card card; // computer will calculate the card to play
  AbstractPlayer* comp = state->getPlayer(current_player);
  if (comp->getLegalMoves().empty()) {
    state->makeMove(card, current_player, true);
  }
  else {
    state->makeMove(card, current_player);
  }
}


int GameController::playGame() {
  // save the current save file
  save();
  // add the textObserver
  observers.emplace_back(make_unique<TextObserver>(state));
  initPlayers();
  // play game
  // conditionally start round based on if the game was loaded from a save
  if (!saved) {
    state->startRound();
  } 
  while (true) {
    int current_player = state->getCurrentPlayer();
    // progress through each players turn
    while (!state->roundDone()) { 
      // check if human or computer
      state->notifyMove();
      while (true) {
        if (state->getPlayerType(current_player) == Player::Computer) {
          computerMove(current_player);
          // computer player doesnt have an execpetion handler on purpose
          // the computer should always play a valid move, if it doesnt
          // then thats a problem
          break;
        }
        else {
          string cmd;
          in >> cmd;
          try {
            if (cmd == "deck") {
              // print deck
              state->notifyObservers(cmds::deck);
            }
            else if (cmd == "play" || cmd == "discard") {
              Card card; 
              in >> card;
              // error will be thrown if invalid move
              if (cmd == "play") {
                state->makeMove(card, current_player);
              }
              else {
                state->makeMove(card, current_player, true);
              }
              break;
            }
            else if (cmd == "quit") {
              // quit
              return cmds::DONE;
            }
            else if (cmd == "ragequit") {
              // handle rage quits, computer makes a move right after NEEDS FIX
              state->rageQuit(current_player);
              computerMove(current_player);
              break;
            }
            else if (cmd == "set_score") {
              // set exit score
              int score;
              in >> score;
              state->setScore(score);
            }
            else if (cmd == "set_card") {
              // set start card for next round
              Card c;
              in >> c;
              try {
                state->setCard(c);
              }
              catch (out_of_range &e) {
                state->notifyObservers(cmds::invalid);
              }
            }
            else if (cmd == "set_values") {
              // set card values
              state->notifyObservers(cmds::setvals);
              vector<int> vals;
              for (int i = 0; i < Rank::King; ++i) {
                int val;
                in >> val;
                vals.push_back(val);
              }
              state->setValues(vals);
            }
            else if (cmd == "best_move") {
              // prints the best card to play
              state->bestMove();
            }
            else if (cmd == "set_AI") {
              // set AI difficulty
              in >> cmd;
              if (cmd == "default") {
                // default
                state->setAIdifficulty(Default); 
              }
              else if (cmd == "random") {
                // random
                state->setAIdifficulty(Random);
              }
              else if (cmd == "hard") {
                // hard
                state->setAIdifficulty(Hard);
              }
              else {
                state->notifyObservers(cmds::invalid);
              }
            }
            else if (cmd == "i_won") {
              observers.emplace_back(make_unique<Graphics>(state));
            }
            else if (cmd == "save") {
              save();
            }
            else if (in.eof() || in.fail()) {
              // end of file / in fail catch
              if (in.eof()) {
                return cmds::DONE;
              }
              else {
                return cmds::ERROR;
              }
            }
            else {
              // invalid command catchall
              state->notifyObservers(cmds::invalid);
            }
          }
          catch (invalid_argument &e) {
            // state will notify observers of exceptions automatically
          }
        }
      }
      current_player = state->next_player();
    }
    state->calcScores();
    state->finishRound();
    if (state->checkDone()) {
      break;
    }
    state->startRound();
  }
  state->notifyObservers(cmds::win);
  return cmds::DONE;
}