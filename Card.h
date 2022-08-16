#ifndef CARD_H
#define CARD_H
#include <iostream>

enum Suit{Club, Diamond, Heart, Spade, TOTAL_SUITS};
enum Rank{Joker, Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King};

// change to enums
class Card {
  short int rank;
  short int suit;
  public:
  explicit Card(int rank = 0, int suit = 0);
  int getSuit() const noexcept;
  int getRank() const noexcept;
  void setRank(int r) noexcept;
  void setSuit(int s) noexcept;
  bool operator==(const Card& other) const noexcept;
};


std::istream& operator>>(std::istream& in, Card& card);
std::ostream& operator<<(std::ostream& out, const Card& card);

#endif