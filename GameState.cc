#include "GameState.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "DefaultRules.h"
#include "Commands.h"
#include <vector>
#include <sstream>
#include <memory>
#include <string>
#include <algorithm>
#include <stdexcept>
using namespace std;

// default ctor
GameState::GameState(int seed) : deck{seed}, seed{seed}, players{}, rules{make_unique<DefaultRules>()}, table{} {
  table.resize(Suit::TOTAL_SUITS);
}

// ctor for loading from a save state
GameState::GameState(ifstream& setup) {
  table.resize(Suit::TOTAL_SUITS);
  rules = make_unique<DefaultRules>();
  string str;
  getline(setup, str);
  istringstream l{str};
  // set seed
  l >> seed;
  deck = Deck(seed);
  // init players
  for (int player = 0; player < 4; ++player) {
    for (int i = 0; i < 4; ++i) {
      getline(setup, str);
      istringstream line{str};
      if (i == 0) {
        char type;
        line >> type;
        init_player(type);
      }
      else if (i == 1) {
        int score;
        line >> score;
        players[player]->setScore(score);
      }
      else if (i == 2) {
        Card c;
        while (line >> c) {
          players[player]->addCard(c);
        }
      }
      else {
        Card c;
        vector<Card> disc;
        while (line >> c) {
          disc.emplace_back(c);
        }
        players[player]->getDiscards() = disc;
      }
    }
  }
  // init table
  for (int s = 0; s < Suit::TOTAL_SUITS; ++s) {
    getline(setup, str);
    istringstream line{str};
    Card c;
    while (line >> c) {
      table[s].push_back(c);
    }
  }
  // get current player
  getline(setup, str);
  istringstream cur_player{str};
  cur_player >> current_player;
  // get if its the first move
  getline(setup, str);
  istringstream first{str};
  int val;
  first >> val;
  first_move = val;
  // calc all legal moves for players
  int p = 0;
  for (auto& player : players) {
    player->getLegalMoves() = calcLegalMoves(p);
    ++p;
  }
  // get exit score
  getline(setup, str);
  istringstream score{str};
  score >> val;
  rules->setScore(val);
  // get start card
  getline(setup,str);
  istringstream s_card{str};
  Card start_c;
  s_card >> start_c;
  rules->setCard(start_c);
  // get card values
  vector<int> vals;
  getline(setup, str);
  istringstream card_vals{str};
  while (card_vals >> val) {
    vals.push_back(val);
  }
  rules->getWeights() = vals;
  // set AI dif
  getline(setup, str);
  istringstream ai{str};
  ai >> val;
  setAIdifficulty(val);
  // when loading from save need to increment the rng value of deck
  getline(setup, str);
  istringstream round_count{str};
  round_count >> shuffle_count;
  for (int i = 0; i < shuffle_count; ++i) {
    deck.shuffle();
  }
}

// initilize players
void GameState::init_player(char player_type) {
  if (player_type == 'h') {
    players.emplace_back(make_unique<HumanPlayer>());
  }
  else if (player_type == 'c') {
    players.emplace_back(make_unique<ComputerPlayer>(Default, seed));
  }
  else {
    throw invalid_argument{"wrong player"};
  }
}

int GameState::getSeed() const noexcept {
  return seed;
}

int GameState::getFirstMove() const noexcept {
  return first_move;
}
void GameState::dealCards() {
  int card_num = 0;
  for (auto& player : players) {
    for (int i = card_num; i < card_num + 13; ++i) {
      player->addCard(deck.getDeck()[i]);
    }
    card_num += 13;
  }
}

int GameState::getShuffles() const noexcept {
  return shuffle_count;
}

int GameState::startRound() {
  // make sure hands and table are empty
  for (auto& player : players) {
    player->clearHand();
  }
  for (auto& pile : table) {
    pile.clear();
  }
  // shuffle deck and deal
  deck.shuffle();
  ++shuffle_count;
  dealCards();
  first_move = true;
  notifyObservers(cmds::startRound);
  current_player = getStartingPlayer();
  return current_player;
}

void GameState::finishRound() {
  // clear table + players hands
  for (auto& player : players) {
    player->clearHand();
  }
  for (auto& pile : table) {
    pile.clear();
  }
}

int GameState::getStartingPlayer() {
  for (int i = 0; i < players.size(); ++i) {
    for (auto card : players[i]->getHand()) {
      if (card == rules->startCard())
      return i;
    }
  }
  // for some reason if start card is not in anyones hand, player 1 goes first
  // shouldnt be possible in default configs
  return 0;
}

vector<deque<Card>>& GameState::getTable() noexcept {
  return table;
}

vector<Card>& GameState::getDeck() noexcept {
  return deck.getDeck();
}

AbstractPlayer* GameState::getPlayer(int player) noexcept {
  return players[player].get();
}

AbstractRules* GameState::getRules() noexcept {
  return rules.get();
}

int GameState::total_players() const noexcept {
  return players.size();
}

void GameState::notifyMove() {
  players[current_player]->getLegalMoves() = calcLegalMoves(current_player);
  notifyObservers(cmds::notifyMove);
}

vector<int> GameState::getWinners() const noexcept {
  // find min score
  int min_score = 0;
  bool first = true;
  vector<int> winners;
  for (auto& player : players) {
    if (first) {
      min_score = player->getScore();
      first = false;
    }
    if (player->getScore() < min_score) {
      min_score = player->getScore();
    }
  }
  // add all players with min score to vector
  for (int i = 0; i < players.size(); ++i) {
    if (players[i]->getScore() == min_score) {
      winners.push_back(i);
    }
  }
  return winners;
}

char GameState::getPlayerType(int player) const {
  return players[player]->getPlayerType();
}

int GameState::getCurrentPlayer() const noexcept {
  return current_player;
}

vector<Card> GameState::calcLegalMoves(int p) {
  vector<Card> moves;
  // if first move
  if (first_move) {
    moves.push_back(rules->startCard());
    return moves;
  }
  for (auto card : players[p]->getHand()) {
    int suit = card.getSuit();
    Card start_c{Rank::Seven, suit};
    auto pile = table[suit];
    if (pile.empty()) {
      if (card == start_c) {
        moves.push_back(card);
      }
      continue;
    }
    if (pile.front().getRank() - 1 == card.getRank() && pile.front().getSuit() == card.getSuit()) {
      moves.push_back(card);
    }
    else if (pile.back().getRank() + 1 == card.getRank() && pile.back().getSuit() == card.getSuit()) {
      moves.push_back(card);
    }
  }
  return moves;
}

vector<Card> GameState::getLegalMoves(AbstractPlayer* player) {
  return player->getLegalMoves();
}

int GameState::next_player() noexcept {
  current_player = (current_player + 1) % players.size();
  return current_player;
}

void GameState::makeMove(Card card, int player, bool discard) {
  // add check for valid human moves
  vector<Card> legal_moves = players[player]->getLegalMoves();
  if (players[player]->getPlayerType() == Player::Human) {
    if (discard) {
      // still legal moves
      if (!legal_moves.empty())  {
        notifyObservers(cmds::inv_discard);
        throw invalid_argument{"still_legal_moves"};
      }
      // discard card not in hand
      else if (find(players[player]->getHand().begin(), players[player]->getHand().end(), card) 
                == players[player]->getHand().end()) {
        notifyObservers(cmds::inv_play);
        throw invalid_argument{"illegal_card"};
      }
    }
    else {
      if (find(legal_moves.begin(), legal_moves.end(), card) == legal_moves.end()) {
        // Card was not a legal move
        notifyObservers(cmds::inv_play);
        throw invalid_argument{"illegal_play"};
      }
    }
  }
  players[player]->play(card, discard);
  // add card to table
  if (!discard) {
    int idx = card.getSuit();
    // insert at front
    if (card.getRank() < table[idx].front().getRank()) {
      table[idx].push_front(card);
    }
    // insert at back
    else {
      table[idx].push_back(card);
    }
    notifyObservers(cmds::play, card);
  }
  first_move = false;
  // make sure to notify after valid move is played
  if (discard) {
    notifyObservers(cmds::discard, card);
  }
}

bool GameState::checkDone() const noexcept {
  for (auto& player : players) {
    if (player->getScore() >= rules->exitScore()) {
      return true;
    }
  }
  return false;
}

bool GameState::roundDone() const noexcept {
  for (auto& player : players) {
    if (!player->getHand().empty()) {
      return false;
    }
  }
  return true;
}

// checks that a given card is in the deck, useful
// for checking valid input
bool GameState::checkValid(Card c) noexcept {
  for (auto card : deck.getDeck()) {
    if (card == c) {
      return true;
    }
  }
  return false;
}

void GameState::calcScores() {
  notifyObservers(cmds::score);
  for (auto& player : players) {
    int score = rules->calcScore(player->getDiscards());
    player->addScore(score);
  }
}

void GameState::setValues(vector<int>& vals) noexcept {
  vals.insert(vals.begin(), 0); // placeholder value
  rules->getWeights() = vals;
}

void GameState::rageQuit(int player) noexcept {
  // notify observers
  notifyObservers(cmds::ragequit);
  unique_ptr<AbstractPlayer> comp = make_unique<ComputerPlayer>(Default, seed);
  if (ai_dif == Hard) {
    // set all hard AIs with the current card values
    comp = make_unique<ComputerPlayer>(ai_dif, seed, rules->getWeights());
  }
  comp->getHand() = players[player]->getHand();
  comp->getDiscards() = players[player]->getDiscards();
  comp->setScore(players[player]->getScore());
  comp->getLegalMoves() = players[player]->getLegalMoves();
  players[player] = move(comp);
}

void GameState::bestMove() noexcept {
  auto& player = players[current_player];
  auto hand = player->getHand();
  Card c;
  if (player->getLegalMoves().empty()) {
    // best discard will be to discard the lowest value available
    // that limits opponents the most
    int min = INT32_MAX;
    for (auto card : player->getHand()) {
      int sum = 0;
      // sevens can never be discarded
      if (card.getRank() < Rank::Seven) {
        // discarding cuts off legal plays below that card
        // i.e discard a 6 means that 5,4,3,2,A must also be discarded
        for (auto other : player->getHand()) {
          if (other.getRank() < card.getRank() && other.getSuit() == card.getSuit()) {
            sum += rules->getWeights()[other.getRank()];
          }
        }
        sum += rules->getWeights()[card.getRank()];
      }
        // same as above
        // i.e discard an 8 means that 9,T,J,Q,K must also be discarded
      else if (card.getRank() > Rank::Seven) {
        for (auto other : player->getHand()) {
          if (other.getRank() > card.getRank() && other.getSuit() == card.getSuit()) {
            sum += rules->getWeights()[other.getRank()];
          }
        }
        sum += rules->getWeights()[card.getRank()];
      }
      if (sum < min) {
        min = sum;
        c = card;
      }
    }
  }
  else {
    // best legal move will be to play the highest value available
    // that allows for continuation
    // dont add the card in question to the sum, as it will never be discarded
    // since its currently a legal move
    int max = INT32_MIN;
    for (auto card : player->getLegalMoves()) {
      int sum = 0;
      if (card.getRank() < Rank::Seven) {
        for (auto other : player->getHand()) {
          if (other.getRank() < card.getRank() && other.getSuit() == card.getSuit()) {
            sum += rules->getWeights()[other.getRank()];
          }
        }
      }
      else if (card.getRank() > Rank::Seven) {
        for (auto other : player->getHand()) {
          if (other.getRank() > card.getRank() && other.getSuit() == card.getSuit()) {
            sum += rules->getWeights()[other.getRank()];
          }
        }
      }
      else {
        // 7s should be played as late as possible depending on 
        // the values of the cards of that suit in you hand
        // i.e if you have the 7C and you have a lot of high ranked clubs
        // play it, else hold it
        for (auto other : player->getHand()) {
          if (other.getSuit() == card.getSuit() && !(other == card)) {
            sum += rules->getWeights()[other.getRank()]; 
          }
        }
      }
      if (sum > max) {
        max = sum;
        c = card;
      }
    }
  }
  // notify which card to play
  notifyObservers(cmds::best, c);
}

void GameState::setScore(int s) noexcept {
  // score can be nonpositive, just means game will always end after
  // the round
  rules->setScore(s);
}

int GameState::getAIlevel() const noexcept {
  return ai_dif;
}

void GameState::setAIdifficulty(int level) noexcept {
  for (int i = 0; i < players.size(); ++i) {
    if (players[i]->getPlayerType() == Player::Computer) {
      unique_ptr<AbstractPlayer> comp = make_unique<ComputerPlayer>(level, seed);
      if (level == Hard) {
        // set all hard AIs with the current card values
        comp = make_unique<ComputerPlayer>(level, seed, rules->getWeights());
      }
      comp->getHand() = players[i]->getHand();
      comp->getDiscards() = players[i]->getDiscards();
      comp->setScore(players[i]->getScore());
      comp->getLegalMoves() = players[i]->getLegalMoves();
      players[i] = move(comp);
    }
  }
  ai_dif = level;

}

void GameState::setCard(Card c) {
  // scan deck for card
  if (!checkValid(c)) {
    throw out_of_range{"card_not_in_deck"};
  }
  // set start card
  rules->setCard(c);
}
