#include <iostream>
#include <string>
#include <array>
#include "Player.h"
#include <cassert>


class SimplePlayer: public Player {
  private:
    const std::string player_name;
    std::array<Card, MAX_HAND_SIZE> hand;

  public:
    SimplePlayer(const std::string name) : player_name(name) {}

    void add_card(const Card &c) override {

    }

    const std::string& get_name() const override {
      return player_name;
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override {
      return true;
    }
    void add_and_discard(const Card &upcard) override {

    }
    Card lead_card(const std::string &trump) override {

    }

    Card play_card(const Card &led_card, const std::string &trump) override {

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
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
  os<<p.get_name();
}