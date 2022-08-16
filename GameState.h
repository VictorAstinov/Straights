#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <vector>
#include <memory>
#include <deque>
#include <iostream>
#include <fstream>
#include "Deck.h"
#include "subject.h"
#include "AbstractPlayer.h"
#include "AbstractRules.h"

class GameState : public Subject {
  Deck deck;
  int seed;
  std::vector<std::unique_ptr<AbstractPlayer>> players;
  std::unique_ptr<AbstractRules> rules;
  std::vector<std::deque<Card>> table;
  int current_player = 0;
  bool first_move = true;
  int ai_dif = CompLevels::Default;
  int shuffle_count = 0;
  void dealCards();
  bool checkValid(Card c) noexcept;
  public:
  explicit GameState(int seed);
  explicit GameState(std::ifstream& setup);
  // getters and setters
  char getPlayerType(int player) const;
  int getCurrentPlayer() const noexcept;
  std::vector<std::deque<Card>>& getTable() noexcept;
  std::vector<Card> getLegalMoves(AbstractPlayer* player);
  AbstractPlayer* getPlayer(int player) noexcept;
  std::vector<Card>& getDeck() noexcept;
  AbstractRules* getRules() noexcept;
  std::vector<int> getWinners() const noexcept;
  int getAIlevel() const noexcept;
  int getSeed() const noexcept;
  int getFirstMove() const noexcept;
  int getStartingPlayer();
  int getShuffles() const noexcept;
  void setValues(std::vector<int>& vals) noexcept;
  void setAIdifficulty(int level) noexcept;
  void setScore(int s) noexcept;
  void setCard(Card c);
  int total_players() const noexcept;
  // actual methods
  void init_player(char player_type);
  int startRound();
  void finishRound();
  void makeMove(Card card, int player, bool discard = false);
  int next_player() noexcept;
  void calcScores();
  std::vector<Card> calcLegalMoves(int p);
  bool checkDone() const noexcept;
  bool roundDone() const noexcept;
  void notifyMove();
  void rageQuit(int player) noexcept;
  void bestMove() noexcept;
};
#endif