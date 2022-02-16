// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
using namespace std;
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
Card::Card() : rank(RANK_TWO), suit(SUIT_SPADES) {}

Card::Card(const std::string &rank_in, const std::string &suit_in) 
: rank(rank_in), suit(suit_in) {}

string Card::get_rank() const {
  return rank;
}

string Card::get_suit() const {
  return suit;
}

string Card::get_suit(const std::string &trump) const {
  if(is_left_bower(trump)) return trump;
  return get_suit();
}

 bool Card::is_face() const {
   std::cout << get_rank() << endl;
   if(get_rank() == RANK_JACK || get_rank() == RANK_QUEEN 
   || get_rank() == RANK_KING) {
     return true;
   }
   return false;
 }

 //REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the trump suit
  bool Card::is_right_bower(const std::string &trump) const{
    if(get_rank() == RANK_JACK && get_suit() == trump) {
      return true;
    }
    return false;
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the next suit
  bool Card::is_left_bower(const std::string &trump) const {
    if(get_rank() == RANK_JACK && get_suit() == Suit_next(trump)) return true;
    return false;
    // if(get_rank() == RANK_JACK && ((trump == SUIT_CLUBS && get_suit() == SUIT_SPADES)
    // || (trump == SUIT_SPADES && get_suit() == SUIT_CLUBS)
    // || (trump == SUIT_DIAMONDS && get_suit() == SUIT_HEARTS)
    // || (trump == SUIT_HEARTS && get_suit() == SUIT_DIAMONDS))) {
    //   return true;
    // }
    // return false;
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if the card is a trump card.  All cards of the trump
  // suit are trump cards.  The left bower is also a trump card.
  bool Card::is_trump(const std::string &trump) const {
    if(get_suit(trump) == trump) {
      return true;
    }
    return false;
  }


int get_rank_weight(const Card &c){
  for(int i = 0; i<=NUM_RANKS; i++){
    if(RANK_NAMES_BY_WEIGHT[i]==c.get_rank()){
      return i;
    }
  }
  return -1;
}

int get_suit_weight(const Card &c){
  for(int i = 0; i<=NUM_SUITS; i++){
    if(SUIT_NAMES_BY_WEIGHT[i]==c.get_suit()){
      return i;
    }
  }
  return -1;
}

bool operator<(const Card &lhs, const Card &rhs) {
  if(get_rank_weight(lhs)<get_rank_weight(rhs)){
    return true;
  }
  if(get_rank_weight(lhs)==get_rank_weight(rhs)){
    if(get_suit_weight(lhs)<get_suit_weight(rhs)){
      return true;
    }
  }
  return false;
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs) {
  if(lhs==rhs) return true;
  return lhs<rhs;
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs) {
  if(get_rank_weight(lhs)>get_rank_weight(rhs)){
    return true;
  }
  if(get_rank_weight(lhs)==get_rank_weight(rhs)){
    if(get_suit_weight(lhs)>get_suit_weight(rhs)){
      return true;
    }
  }
  return false;
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs){
  if(lhs==rhs) return true;
  return lhs>rhs;
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs){
  if(get_rank_weight(lhs)==get_rank_weight(rhs) &&
  get_suit_weight(lhs)==get_suit_weight(rhs)){
    return true;
  }
  return false;
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs){
  return !(lhs==rhs);
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit) {
  if(suit == Card::SUIT_SPADES) return Card::SUIT_CLUBS;
  if(suit == Card::SUIT_CLUBS) return Card::SUIT_SPADES;
  if(suit == Card::SUIT_DIAMONDS) return Card::SUIT_HEARTS;
  if(suit == Card::SUIT_HEARTS) return Card::SUIT_DIAMONDS;
  return "asdasdasd";
  }

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card){
  os << card.get_rank() << " of " << card.get_suit();
  return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump){
  return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump){
  return false;
}
// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
