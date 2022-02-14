#include "Pack.h"
#include <string>
#include <vector>

Pack::Pack() {
    int index = 0;
    for(auto suit : SUIT_NAMES_BY_WEIGHT){
        for(auto rank : RANK_NAMES_BY_WEIGHT){
            Card c(rank,suit);
            cards[index] = c;
            index++;
        }
    }
}

Pack::Pack(std::istream& pack_input) {
    int index = 0;
    while(pack_input){
        std::string rank, filler, suit;
        pack_input>>rank>>filler>>suit;
        Card c(rank,suit);
        cards[index] = c;
        index++;
    }
}

Card Pack::deal_one(){
    Card c = cards[next];
    next++;
    return c;
}

void Pack::reset() {
    next = 0;
}

void Pack::shuffle() {
    std::array<Card, PACK_SIZE> new_stack = cards;
    for(int i = 0; i < PACK_SIZE; i+=2){
        Card temp;
        new_stack[i] = cards[PACK_SIZE-i];
        new_stack[i+1] = cards[i];
    }
    cards = new_stack;
    reset();
}

bool Pack::empty() const{
    if(next==PACK_SIZE-1)
        return true;
    return false;
}