#include "Deck.h"
#include "Card.h"
#include <vector>
#include <algorithm>
#include <random>


// move these somewhere

Deck::Deck(int seed) : deck{}, rng{seed} {
  // add all cards to the deck. needs to be changed
  for (int s = 0; s < Suit::TOTAL_SUITS; ++s) {
    for (int r = 1; r <= Rank::King; ++r) {
      deck.emplace_back(r,s);
    }
  }
}

void Deck::shuffle() {
  std::shuffle(deck.begin(), deck.end(), rng);
}

std::vector<Card>& Deck::getDeck() noexcept {
  return deck;
}

int Deck::deckSize() const noexcept {
  return deck.size();
}