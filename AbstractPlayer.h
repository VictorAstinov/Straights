#ifndef ABSTRACT_PLAYER_H
#define ABSTRACT_PLAYER_H
#include <vector>
#include <deque>
#include "Card.h"

enum Player{Human, Computer};
enum CompLevels{Default, Random, Hard};

class AbstractPlayer {
  protected:
  std::vector<Card> hand;
  std::vector<Card> legal_moves;
  std::vector<Card> discards;
  int score = 0;
  virtual void doPlay(Card& card, bool discard = false) = 0;
  virtual int doGetPlayerType() = 0;
  public:
  AbstractPlayer();
  virtual ~AbstractPlayer() = default;
  void addCard(Card c);
  void clearHand();
  void play(Card& c, bool discard = false);
  std::vector<Card>& getHand();
  std::vector<Card>& getDiscards();
  std::vector<Card>& getLegalMoves();
  int getScore() const noexcept;
  void setScore(int s) noexcept;
  int getPlayerType() noexcept;
  void addScore(int s);
};
#endif