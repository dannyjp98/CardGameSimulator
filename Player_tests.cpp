// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    Player * bob = Player_factory("Bob", "Human");
    ASSERT_EQUAL("Bob", bob->get_name());

    delete bob;
    delete alice;
}

// Add more tests here
TEST(test_player_creation) {
  // Create a Human player
  Player * human = Player_factory("Joe", "Human");
  ostringstream oss1;
  oss1 << * human;

  ASSERT_EQUAL(oss1.str(), "Joe");

  // Create a Simple player
  Player * alice = Player_factory("Alice", "Simple");
  ostringstream oss2;
  oss2 << *alice;
  ASSERT_EQUAL(oss2.str(), "Alice");

  // Clean up players that were created using Player_factory()
  delete human;
  delete alice;
}

// Tests 2 facecards of trump suit => True
TEST(test_robot_make_trump_1) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

  // Bob makes tump
  Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
  string trump;
  bool orderup_r1 = bob->make_trump(
    nine_hearts,    // Upcard
    false,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

ASSERT_TRUE(orderup_r1);
ASSERT_EQUAL(trump, Card::SUIT_HEARTS);

  delete bob;
}

// Tests one facecard
TEST(test_robot_make_trump_2) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));

  Card up_card(Card::RANK_NINE, Card::SUIT_HEARTS);
  string trump;

  bool orderup_r1 = bob->make_trump(
    up_card,    // Upcard
    false,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );
ASSERT_FALSE(orderup_r1);

    bool orderup_r2 = bob->make_trump(
    up_card,    // Upcard
    false,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );
ASSERT_FALSE(orderup_r2);
  delete bob;
}

// Tests trump card face card and left bower => True 
TEST(test_robot_make_trump_3) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

  // Bob makes tump
  Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
  string trump;
  bool orderup_r1 = bob->make_trump(
    nine_hearts,    // Upcard
    false,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

ASSERT_TRUE(orderup_r1);
ASSERT_EQUAL(trump, Card::SUIT_HEARTS);

  delete bob;
}

//Tests 1 trump facecard
TEST(test_robot_make_trump_4) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

    // Bob makes tump
    Card up_card(Card::RANK_NINE, Card::SUIT_HEARTS);
    string trump;
    bool orderup_r1 = bob->make_trump(up_card, false, 1, trump);

    ASSERT_TRUE(orderup_r1);
    ASSERT_EQUAL(trump, Card::SUIT_HEARTS);
    delete bob;
}

//Tests 0 trump facecards
TEST(test_robot_make_trump_5) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));

  // Bob makes tump
  Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
  string trump;
  bool orderup_r1 = bob->make_trump(
    nine_hearts,    // Upcard
    false,         
    1,              // First round
    trump           // Suit ordered up (if any)
  );

    ASSERT_FALSE(orderup_r1);

    bool orderup_r2 = bob->make_trump(
    nine_hearts,    // Upcard
    false,        
    2,             
    trump           // Suit ordered up (if any)
  );

ASSERT_FALSE(orderup_r2);
  delete bob;
}

//Tests 1 same color facecards
TEST(test_robot_make_trump_6) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));

  // Bob makes tump
  Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
  string trump;
  bool orderup_r1 = bob->make_trump(
    nine_hearts,    // Upcard
    false,         
    1,              // First round
    trump           // Suit ordered up (if any)
  );

    ASSERT_FALSE(orderup_r1);

    bool orderup_r2 = bob->make_trump(
    nine_hearts,    // Upcard
    false,        
    2,             
    trump           // Suit ordered up (if any)
  );

ASSERT_TRUE(orderup_r2);
ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);

  delete bob;
}

TEST(test_robot_screw_dealer) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));

  // Bob makes tump
  Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
  string trump;
  bool orderup_r1 = bob->make_trump(
    nine_hearts,    // Upcard
    true,         
    1,              // First round
    trump           // Suit ordered up (if any)
  );

    ASSERT_FALSE(orderup_r1);

    bool orderup_r2 = bob->make_trump(
    nine_hearts,    // Upcard
    true,        
    2,             
    trump           // Suit ordered up (if any)
  );

ASSERT_TRUE(orderup_r2);
ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);

  Card nine_clubs(Card::RANK_NINE, Card::SUIT_CLUBS);
    bool orderup_r3 = bob->make_trump(
    nine_clubs,    // Upcard
    true,        
    2,             
    trump           // Suit ordered up (if any)
  );

ASSERT_TRUE(orderup_r3);
ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}

TEST(test_robot_lead_card_1) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));

  // Bob adds a card to his hand and discards one card
  // bob->add_and_discard(
  //   Card(Card::RANK_KING, Card::SUIT_SPADES) // upcard
  // );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card correct_card(Card::RANK_QUEEN, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, correct_card); //check led card

  Card card_led_2 = bob->lead_card(Card::SUIT_HEARTS);
  Card correct_card_2(Card::RANK_TEN, Card::SUIT_CLUBS);
  ASSERT_EQUAL(card_led_2, correct_card_2); //check led card
  delete bob;
}

TEST(test_robot_lead_card_2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card correct_card(Card::RANK_JACK, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, correct_card); //check led card

  delete bob;
}

TEST(test_robot_lead_card_3) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card correct_card(Card::RANK_JACK, Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_led, correct_card); //check led card

  delete bob;
}

TEST(test_robot_lead_card_4) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card correct_card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
  ASSERT_EQUAL(card_led, correct_card); //check led card

  delete bob;
}

TEST(test_robot_play_card_1) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card led_card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    led_card,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_TEN, Card::SUIT_SPADES));

  Card card_played2 = bob->play_card(
    led_card,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played2, Card(Card::RANK_TEN, Card::SUIT_CLUBS));
  delete bob;
}

TEST(test_robot_play_card_2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

bob->add_and_discard(
    Card(Card::RANK_JACK, Card::SUIT_HEARTS) // upcard
  );
  // Bob plays a card
  Card led_card(Card::RANK_TEN, Card::SUIT_HEARTS);
  Card card_played = bob->play_card(
    led_card, 
    "Diamonds"
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_KING, Card::SUIT_SPADES));
  delete bob;
}

TEST(test_robot_play_card_3) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card led_card(Card::RANK_NINE, Card::SUIT_SPADES);
  Card card_played = bob->play_card(
    led_card,  // Nine of Diamonds is led
    "Spades"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_ACE, Card::SUIT_SPADES));
  delete bob;
}

TEST(test_robot_play_card_4) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card led_card(Card::RANK_NINE, Card::SUIT_SPADES);
  Card card_played = bob->play_card(
    led_card,  // Nine of Diamonds is led
    "Spades"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_SPADES));
  delete bob;
}

TEST(test_robot_play_card_5) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card led_card(Card::RANK_NINE, Card::SUIT_SPADES);
  Card card_played = bob->play_card(
    led_card,  // Nine of Diamonds is led
    "Spades"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_CLUBS));
  delete bob;
}

TEST(test_robot_play_card_6) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card led_card(Card::RANK_NINE, Card::SUIT_SPADES);
  Card card_played = bob->play_card(
    led_card,  // Nine of Diamonds is led
    "Spades"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_SPADES));
  delete bob;
}

TEST_MAIN()
