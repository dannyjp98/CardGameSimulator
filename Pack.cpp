#include "Pack.h"
#include <string>
#include <vector>

Pack::Pack() {
    int index = 0;
    for(std::string suit : SUIT_NAMES_BY_WEIGHT){
        for(std::string rank : RANK_NAMES_BY_WEIGHT){
            if(rank==Card::RANK_NINE || rank==Card::RANK_TEN ||
            rank==Card::RANK_JACK || rank==Card::RANK_QUEEN ||
            rank==Card::RANK_KING || rank==Card::RANK_ACE) {
            Card c(rank,suit);
            cards[index] = c;
            //std::cout<<suit<<rank<<std::endl;
            index++;
            }
        }
    }
    next = 0;
}

Pack::Pack(std::istream& pack_input) {
    int index = 0;
    std::string rank, filler, suit;
    while(pack_input>>rank>>filler>>suit){
        //std::cout<<suit<<rank<<std::endl;
        Card c(rank,suit);
        cards[index] = c;
        index++;
    }
    next = 0;
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
    std::array<Card, PACK_SIZE> new_stack;
    for(int x = 0; x < 7; x++){
        int index = 0;
        for(int i = 0; i < PACK_SIZE/2; i++){
            // std::cout<<cards[PACK_SIZE/2+i]<<std::endl;
            // std::cout<<cards[i]<<std::endl;
            // std::cout<<index<<std::endl;
            new_stack[index] = cards[PACK_SIZE/2+i];
            index++;
            new_stack[index] = cards[i];
            index++;
        }
        cards = new_stack;
    }
    reset();
}

bool Pack::empty() const{
    std::cout<<next<<std::endl;
    if(next>=PACK_SIZE) return true;
    return false;
}