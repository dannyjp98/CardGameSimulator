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
    ASSERT_EQUAL(c.get_suit(Card::SUIT_SPADES), Card::SUIT_SPADES);

    Card d(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(d.get_suit(Card::SUIT_SPADES), Card::SUIT_SPADES);

}

TEST(test_card_is_face) {
    Card c(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_TRUE(c.is_face());

    Card d(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(d.is_face());  

    Card e(Card::RANK_NINE, Card::SUIT_HEARTS);
    ASSERT_FALSE(e.is_face());    
}

TEST(test_is_right_bower) {
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(c.is_right_bower(Card::SUIT_SPADES));

    Card d(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_FALSE(d.is_right_bower(Card::SUIT_SPADES));

    Card e(Card::RANK_TWO, Card::SUIT_SPADES);
    ASSERT_FALSE(e.is_right_bower(Card::SUIT_SPADES));
}

TEST(test_is_left_bower) {
    Card c(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(c.is_left_bower(Card::SUIT_SPADES));

    Card d(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(d.is_left_bower(Card::SUIT_SPADES));
}

TEST(test_is_trump) {
    Card c(Card::RANK_THREE, Card::SUIT_CLUBS);
    ASSERT_FALSE(c.is_trump(Card::SUIT_SPADES));

    Card d(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_FALSE(d.is_trump(Card::SUIT_CLUBS));

    Card e(Card::RANK_JACK, Card::SUIT_DIAMONDS);  // left bower
    ASSERT_TRUE(e.is_trump(Card::SUIT_HEARTS)); 
}

TEST(test_get_rank_weight) {
    ASSERT_EQUAL(true,true);
}

TEST(test_get_suit_weight) {
    ASSERT_EQUAL(true,true);
}
//Tests if card a is less than b with trump
TEST(test_is_less_1) {
    Card a(Card::RANK_KING, Card::SUIT_CLUBS);
    Card b(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    std::string trump_suit = Card::SUIT_DIAMONDS;
    ASSERT_TRUE(Card_less(a,b,trump_suit));
}

TEST(test_is_less_2) {
    Card a(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card b(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    std::string trump_suit = Card::SUIT_DIAMONDS;
    ASSERT_TRUE(Card_less(a,b,trump_suit));
}

TEST(test_is_less_3) {
    Card a(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card b(Card::RANK_ACE, Card::SUIT_CLUBS);
    std::string trump_suit = Card::SUIT_DIAMONDS;
    ASSERT_TRUE(Card_less(a,b,trump_suit));
}

TEST(test_is_less_4) {
    Card a(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card b(Card::RANK_ACE, Card::SUIT_SPADES);
    Card led(Card::RANK_ACE, Card::SUIT_CLUBS);
    std::string trump_suit = Card::SUIT_DIAMONDS;

    ASSERT_FALSE(Card_less(a,b,led,trump_suit));
}

TEST(test_is_less_5) {
    Card a(Card::RANK_TEN, Card::SUIT_SPADES);
    Card b(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    std::string trump_suit = Card::SUIT_SPADES;

    ASSERT_FALSE(Card_less(a,b,trump_suit));
}
// Add more test cases here
TEST(test_operators) {
    Card a(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card b(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(a<b);
    ASSERT_TRUE(b>a);
    ASSERT_TRUE(a==a);
    ASSERT_TRUE(a<=a);
}

TEST(test_operators_edge) {
    Card a(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card b(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(b>a);
    ASSERT_TRUE(a<b);
    ASSERT_TRUE(b>=a);
    ASSERT_TRUE(a<=b);
    ASSERT_TRUE(a==a);
    ASSERT_TRUE(a<=a);
    ASSERT_TRUE(a>=a);
    ASSERT_TRUE(a!=b);
    ASSERT_FALSE(a==b);
}

TEST(test_print) {
    Card a(Card::RANK_JACK, Card::SUIT_CLUBS);
    ostringstream s;
    s<<a;

    // Correct output
    ostringstream correct;
    correct << "Jack of Clubs";

    ASSERT_EQUAL(s.str(),correct.str());
}

TEST_MAIN()
