#include "Card.h"
#include <iostream>
#include <string>
using namespace std;

Card::Card(int rank, int suit) : rank{rank}, suit{suit} {}

int Card::getSuit() const noexcept {
  return suit;
}

int Card::getRank() const noexcept {
  return rank;
}

void Card::setRank(int r) noexcept {
  rank = r;
}

void Card::setSuit(int s) noexcept {
  suit = s;
}

bool Card::operator==(const Card& other) const noexcept {
  return (rank == other.rank && suit == other.suit);
}

// fix
ostream& operator<<(ostream& out, const Card& card) {
  string suits{"CDHS"};
  string ranks{"!A23456789TJQK"}; // ! as placeholder for jokers
  if (card.getRank() == 0) {
    out << "JJ"; // joker
  }
  else {
    out << ranks[card.getRank()] << suits[card.getSuit()];
  }
  return out;
}

// fix later
istream& operator>>(istream& in, Card& card) {
  char r = 0, s = 0;
  in >> r >> s;
  if (r == 'J' && s == 'J') {
    card.setRank(0);
    card.setSuit(0);
  }
  else {
    string suits{"CDHS"};
    string ranks{"!A23456789TJQK"};
    for (int i = 0; i < Suit::TOTAL_SUITS; ++i) {
      if (suits[i] == s) {
        card.setSuit(i);
        break;
      }
    }
    for (int i = 1; i <= Rank::King; ++i) {
      if (ranks[i] == r) {
        card.setRank(i);
        break;
      }
    }
  }
  return in;
}