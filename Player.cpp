#include <iostream>
#include <string>
#include <array>
#include <vector>
#include "Player.h"
#include <cassert>
#include <algorithm>

class SimplePlayer: public Player {
  private:
    const std::string player_name;
    //std::array<Card, MAX_HAND_SIZE> hand;
    std::vector<Card> hand;
    int next = 0;

  public:
    SimplePlayer(const std::string name) : player_name(name) {}

    void add_card(const Card &c) override {
      assert(next<=MAX_HAND_SIZE);
      hand.push_back(c);
      next++;
    }

    const std::string& get_name() const override {
      return player_name;
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override {
      if(round==0){
        order_up_suit = upcard.get_suit();
        return true;
      }
      return false;
    }
    void add_and_discard(const Card &upcard) override {
      hand.pop_back();
      hand.push_back(upcard);
    }
    Card lead_card(const std::string &trump) override {
      Card lead;
      bool found_non_trump = false;
      for(Card c : hand){
        if(!c.is_trump(trump)){
          if(!found_non_trump) lead = c;
          else if(Card_less(lead, c, trump)) lead = c;
        }
      }
      //No non-trump found
      if(!found_non_trump) {
        lead = hand[0];
        for(Card c : hand){
          if(Card_less(lead, c, trump)) lead = c;
        }
      }
      return lead;
    }

    Card play_card(const Card &led_card, const std::string &trump) override {
      Card card_to_play;
      bool card_picked = false;
      for(Card c : hand){
        if(c.get_suit() == led_card.get_suit() && c > card_to_play){
          card_to_play = c;
          card_picked = true;
        }
      }
      //No card of same suit
      if(!card_picked){
        card_to_play = hand[0];
        for(Card c : hand){
          if(Card_less(c, card_to_play,trump)) card_to_play = c;
        }
      }

      return card_to_play;
    }
     
};

class HumanPlayer: public Player {
  private:
    const std::string player_name;
    //std::array<Card, MAX_HAND_SIZE> hand;
    std::vector<Card> hand;
    int next = 0;

  public:
    HumanPlayer(const std::string name) : player_name(name) {}

    void add_card(const Card &c) override {
      assert(next<=MAX_HAND_SIZE);
      hand.push_back(c);
      next++;
    }

    const std::string& get_name() const override {
      return player_name;
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override {
      print_hand();
      if(round==0){
        order_up_suit = upcard.get_suit();
        return true;
      }
      return false;
    }
    void add_and_discard(const Card &upcard) override {
      hand.pop_back();
      hand.push_back(upcard);
    }
    Card lead_card(const std::string &trump) override {
      Card lead;
      bool found_non_trump = false;
      for(Card c : hand){
        if(!c.is_trump(trump)){
          if(!found_non_trump) lead = c;
          else if(Card_less(lead, c, trump)) lead = c;
        }
      }
      //No non-trump found
      if(!found_non_trump) {
        lead = hand[0];
        for(Card c : hand){
          if(Card_less(lead, c, trump)) lead = c;
        }
      }
      return lead;
    }

    Card play_card(const Card &led_card, const std::string &trump) override {
      Card card_to_play;
      bool card_picked = false;
      for(Card c : hand){
        if(c.get_suit() == led_card.get_suit() && c > card_to_play){
          card_to_play = c;
          card_picked = true;
        }
      }
      //No card of same suit
      if(!card_picked){
        card_to_play = hand[0];
        for(Card c : hand){
          if(Card_less(c, card_to_play,trump)) card_to_play = c;
        }
      }

      return card_to_play;
    }

    void print_hand() const{
      //std::sort(hand.begin(),hand.end());
      for(Card c : hand){
        std::cout<<c<<std::endl;
      }
    }
     
};

Player * Player_factory(const std::string &name, const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  // Repeat for each other type of Player
  if (strategy == "Human") {
    // The "new" keyword dynamically allocates an object.
    return new HumanPlayer(name);
  }
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
  os<<p.get_name();
  return os;
}