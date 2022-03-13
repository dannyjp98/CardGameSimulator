// Project UID 1d9f47bfc76643019cfbf037641defe1

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

  public:
    SimplePlayer(const std::string name) : player_name(name) {}

    void add_card(const Card &c) override {
      hand.push_back(c);
      //std::cout<<"ADDED CARD"<<c<<"\n";
    }

    
    void remove_card(int index){
      hand.erase(hand.begin()+index);
    }

    void remove_card(Card card_to_remove){
      int index = 0;
      for(int i = 0; i<int(hand.size()); ++i){
        if(hand[i]==card_to_remove){
          index = i;
        }
      }
      remove_card(index);
    }


    const std::string& get_name() const override {
      return player_name;
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override {
      //ROUND 0
      if(round==1){ //|| round==2){
        order_up_suit = upcard.get_suit();
        int num_face_trumps = 0;
        for(Card c : hand){
          if((c.is_trump(order_up_suit) && c.is_face()) ||
          c.is_left_bower(order_up_suit) || c.is_right_bower(order_up_suit)) {
            num_face_trumps++;
          }
        }
        if(num_face_trumps>=2){
            return true;
        }
      }
    //ROUND 2
      if(round==2){
        order_up_suit = Suit_next(upcard.get_suit());
        if(is_dealer){
          return true;
        }
        int num_face_trumps = 0;
        for(Card c : hand){
          if((c.is_trump(order_up_suit) && c.is_face()) ||
          c.is_left_bower(order_up_suit) || c.is_right_bower(order_up_suit)) {
            num_face_trumps++;
          }
        }
        if(num_face_trumps>=1){
            return true;
        }
      }
      return false;
    }
    void add_and_discard(const Card &upcard) override {
      std::string trump = upcard.get_suit();
      hand.push_back(upcard);
      int index_of_lowest = 0;
      for(unsigned i = 0; i<hand.size(); i++){
        if(Card_less(hand[i], hand[index_of_lowest], trump)){
          index_of_lowest = i;
        }
      }
      //std::cout<<"Removing: "<<hand[index_of_lowest]<<"\n";
      hand.erase(hand.begin()+index_of_lowest);
    }

    //Pick highest non-trump. If only trumps, pick highest trump.
    Card lead_card(const std::string &trump) override {
      std::vector<Card> temp = hand;
      std::sort(temp.begin(),temp.end());
      //Check non-trumps
      for(int i = temp.size()-1; i>=0; i--){
        //std::cout<<temp[i]<<"\n";
        if(!temp[i].is_trump(trump)){
          remove_card(temp[i]);
          return temp[i];
        }
      }
      //Check trumps with bower exceptions
      Card highest_card = temp[0];
      for(int i = temp.size()-1; i>=0; i--){
        //std::cout<<temp[i]<<"\n";
        if(Card_less(highest_card, temp[i], trump)){
          highest_card = temp[i];
        }
      }
      remove_card(highest_card);
      return highest_card;
      //Card lead;
      // bool found_non_trump = false;
      // for(Card c : hand){
      //   if(!c.is_trump(trump)){
      //     if(!found_non_trump) lead = c;
      //     else if(Card_less(lead, c, trump)) lead = c;
      //   }
      // }
      // //No non-trump found
      // if(!found_non_trump) {
      //   lead = hand[0];
      //   for(Card c : hand){
      //     if(Card_less(lead, c, trump)) lead = c;
      //   }
      // }
      //return lead;
    }

    Card play_card(const Card &led_card, const std::string &trump) override {

      // std::cout<<"PRINTING HAND. SIZE: "<<hand.size()<<"\n";
      // for(int i = 0; i< int(hand.size()); ++i){
      //   std::cout<<hand[i]<<"\n";
      // }

      Card card_to_play;
      bool card_picked = false;

      for(int i = 0; i< int(hand.size()); ++i){
        if(hand[i].get_suit(trump) == led_card.get_suit(trump)){
          if(!card_picked){
            card_to_play = hand[i];
            card_picked = true;
          } else if (Card_less(card_to_play,hand[i], led_card, trump)){
            card_to_play = hand[i];
          }
        }
      }
      //No card of same suit
      if(!card_picked){
        card_to_play = hand[0];
        for(int i = 0; i< int(hand.size()); ++i){
          //std::cout<<c<<"\n";
          if(Card_less(hand[i], card_to_play, led_card, trump)){
            //std::cout<<"TRUE"<<card_to_play<<"\n";
            card_to_play = hand[i];
          }
        }
      }
      //std::cout<<card_to_play.get_rank()<<"\n";
      remove_card(card_to_play);
      return card_to_play;
    }
     
};

class HumanPlayer: public Player {
  private:
    const std::string player_name;
    //std::array<Card, MAX_HAND_SIZE> hand;
    std::vector<Card> hand;

  public:
    HumanPlayer(const std::string name) : player_name(name) {}

    void add_card(const Card &c) override {
      hand.push_back(c);
      std::sort(hand.begin(), hand.end());
    }

    void remove_card(int index){
      hand.erase(hand.begin()+index);
    }

    const std::string& get_name() const override {
      return player_name;
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override {
      print_hand();
      std::cout<<"Human player "<<get_name()<< ", please enter a suit, or \"pass\":\n";
      std::string input;
      std::cin>>input;
      if(input=="pass"){
        //std::cout<<get_name()<<" passes\n";
        return false;
      }
      order_up_suit = input;
      //std::cout<<get_name()<<" orders up "<<order_up_suit<<"\n";
      return true;
    }
    void add_and_discard(const Card &upcard) override {
      print_hand();
      std::cout<<"Discard upcard: [-1]\n";
      std::cout<<"Human player "<<get_name()<<", please select a card to discard:\n";
      int discard_index;
      std::cin>>discard_index;
      if(discard_index != -1){
        hand.erase(hand.begin()+discard_index);
        add_card(upcard);
      }
    }
    Card lead_card(const std::string &trump) override {
      print_hand();
      int index;
      std::cout<<"Human player "<<get_name()<<", please select a card:\n";
      std::cin>>index;
      //std::cout<<hand[index]<<" led by "<<get_name()<<"\n";
      Card card_to_play = hand[index];
      remove_card(index);
      return card_to_play;
    }

    Card play_card(const Card &led_card, const std::string &trump) override {
      print_hand();
      int index;
      std::cout<<"Human player "<<get_name()<<", please select a card:\n";
      std::cin>>index;
      //std::cout<<hand[index]<<" played by "<<get_name()<<"\n";
      Card card_to_play = hand[index];
      remove_card(index);
      return card_to_play;
    }

    void print_hand() const{
      //std::sort(hand.begin(), hand.end());
      //std::vector<Card> temp = hand;
      for(int i = 0; i<int(hand.size()); i++){
        std::cout<<"Human player "<<get_name()
        <<"'s hand: ["<<i<<"] "<<hand[i]<<std::endl;
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