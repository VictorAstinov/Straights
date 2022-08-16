#ifndef DECK_H
#define DECK_H
#include <vector>
#include <random>
#include "Card.h"

class Deck {
  std::vector<Card> deck;
  std::default_random_engine rng;
  public:
  explicit Deck(int seed = 0);
  void shuffle();
  std::vector<Card>& getDeck() noexcept;
  int deckSize() const noexcept;
};
#endif