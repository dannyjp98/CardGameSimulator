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
Card::Card() {
  rank = RANK_TWO;
  suit = SUIT_SPADES;
}

Card::Card(const std::string &rank_in, const std::string &suit_in) {
  rank = rank_in;
  suit = suit_in;
}
string Card::get_rank() const {
  return rank;
}

string Card::get_suit() const {
  return suit;
}

string Card::get_suit(const std::string &trump) const {
  
}

 bool Card::is_face() const {
   if(get_rank() == RANK_JACK || RANK_QUEEN || RANK_KING) {
     return true;
   }
   return false;
 }

 //REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the trump suit
  bool Card::is_right_bower(const std::string &trump) const{
    if(get_rank() == RANK_JACK && get_suit(trump) == trump) {
      return true;
    }
    return false;
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the next suit
  bool Card::is_left_bower(const std::string &trump) const {
    
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if the card is a trump card.  All cards of the trump
  // suit are trump cards.  The left bower is also a trump card.
  bool Card::is_trump(const std::string &trump) const {
    if(get_suit() == trump) {
      return true;
    }
    else if(is_left_bower(trump)) {
      return true;
    }
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
