// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}


TEST(test_card_default_ctor) {
    Card c;
    ASSERT_EQUAL(Card::RANK_TWO, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit());
}

TEST(test_get_suit_trump) {
    Card c(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_EQUAL(c.get_suit("SUIT_SPADES"),c.get_suit());

    Card d(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(d.get_suit("SUIT_SPADES"), "SUIT_SPADES");

}

TEST(test_card_is_face) {
    Card c(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_EQUAL(c.is_face(),false);

    Card d(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(d.is_face(),true);   
}

TEST(test_is_right_bower) {
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(c.is_right_bower("SUIT_SPADES"), true);

    Card d(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(d.is_right_bower("SUIT_SPADES"), false);

    Card e(Card::RANK_TWO, Card::SUIT_SPADES);
    ASSERT_EQUAL(e.is_right_bower("SUIT_SPADES"), false);
}

TEST(test_is_left_bower) {
    Card c(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(c.is_left_bower("SUIT_SPADES"), true);

    Card d(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(d.is_left_bower("SUIT_SPADES"), false);
}

TEST(test_is_trump) {
    Card c(Card::RANK_THREE, Card::SUIT_CLUBS);
    ASSERT_EQUAL(c.is_trump("SUIT_CLUBS"), true);

    Card d(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_EQUAL(d.is_trump("SUIT_DIAMONDS"), false);

    Card e(Card::RANK_JACK, Card::SUIT_DIAMONDS);  // left bower
    ASSERT_EQUAL(e.is_trump("SUIT_HEARTS"), true); 
}

TEST(test_get_rank_weight) {
    ASSERT_EQUAL(true,true);
}

TEST(test_get_suit_weight) {
    ASSERT_EQUAL(true,true);
}


// Add more test cases here

TEST_MAIN()
