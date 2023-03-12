// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include "Player.h"
#include "Pack.h"
#include "Card.h"
#include <cassert>
#include <algorithm>
#include <fstream>

class Game{
    private:
        Pack card_pack;
        bool shuffle = false;
        int pts_to_win = 1;
        std::vector<Player*> players;
        int player_num = 4;

        int hand_number = 0;

        int team_1_score = 0;
        int team_2_score = 0;
        int team_1_tricks = 0;
        int team_2_tricks = 0;
        int team_made_trump = 0;


        Card upcard;
        std::string trump;

        Player* dealer;
        int dealer_index = 0;
        int lead_index = 0;
        bool winner_exists = false;
    public:
        Game(){}

        Game(Pack in_pack, bool in_shuffle, int in_pts_to_win, 
        std::vector<Player*> &in_players)
        : card_pack(in_pack), shuffle(in_shuffle), 
        pts_to_win(in_pts_to_win), players(in_players) {}

        void shuffle_pack(){
            card_pack.shuffle();
        }

        void begin_play(){
            dealer_index = 0;
            // for(int i = 0; i<24; ++i){
            //     std::cout<<card_pack.deal_one()<<"\n";
            // }
            begin_hand();
        }
        
        void begin_round(){

        }
        
        void begin_hand(){
            while(!winner_exists){
                std::cout<<"Hand "<< hand_number << "\n";
                std::cout<<players[dealer_index]->get_name() << " deals\n";
                lead_index = get_next_player(dealer_index);
                deal_cards();
                making_trump();
                for(int i = 0; i<5; ++i){
                    trick();
                }
                evaluate_tricks();
                print_score();
                check_winner();
                reset_tricks();
                dealer_index = get_next_player(dealer_index);
                hand_number++;
            }
            end_game();
        }

        void deal_cards(){
            card_pack.reset();
            if(shuffle) card_pack.shuffle();

            // std::cout<<"PACK :\n";
            // for(int i = 0; i<20;i++){
            //     std::cout<<card_pack.deal_one()<<"\n";
            // }
            // std::cout<<"\n";

            card_pack.reset();
            int curr_index = get_next_player(dealer_index);
            int deal_amount = 3;
            for(int i = 0; i<8; ++i){
                for(int k = 0; k<deal_amount; ++k){
                    Card dealt = card_pack.deal_one();
                    players[curr_index]->add_card(dealt);
                }
                if(i==3) deal_amount = 2;
                else if(deal_amount==3) deal_amount = 2;
                else if(deal_amount==2) deal_amount = 3;
                curr_index = get_next_player(curr_index);
            }
            upcard = card_pack.deal_one();
            std::cout<<upcard<<" turned up\n";
        }

        int get_next_player(int index){
            if(index==3) return 0;
            return index + 1;
        }

        bool making_trump(){
            int index = get_next_player(dealer_index);
            //ROUND 1
            for(int round = 1; round<3; ++round){
                for(int i = 0; i<4; ++i){
                    if(players[index]->make_trump(upcard, 
                    (index == dealer_index), round, trump)){
                        std::cout<< players[index]->get_name();
                        std::cout<< " orders up " << trump<< "\n";
                        if(round!=2) players[dealer_index]->add_and_discard(upcard);
                        if(index%2==0) team_made_trump = 1;
                        else team_made_trump = 2;
                        std::cout<<std::endl;
                        return true;
                    }
                    std::cout<< players[index]->get_name() << " passes\n";
                    index = get_next_player(index);
                }
            }
            return false;
        }

        void trick(){
            Card played_cards[4];
            Card led_card;
            int index = lead_index;

            led_card = players[index]->lead_card(trump);
            //std::cout<<"LED CARD: "<<led_card<<"\n";
            played_cards[index] = led_card;

            std::cout<<played_cards[index]<<" led by "
            <<players[index]->get_name()<<"\n";
            index = get_next_player(index);

            for(int i = 0; i<3; i++){
                played_cards[index] = (players[index]->play_card(led_card, trump));
                std::cout<<played_cards[index]<<" played by ";
                std::cout<<players[index]->get_name() << "\n";
                index = get_next_player(index);
            }

            Card max_card = played_cards[0];
            int max_index = 0;
            for(int i = 0; i<4; ++i){
                if(Card_less(max_card,played_cards[i],led_card,trump)){
                    max_index = i;
                    max_card = played_cards[i];
                }
            }
            std::cout<<players[max_index]->get_name()<<" takes the trick\n\n";
            lead_index = max_index;
            add_tricks(max_index);
        }

        void end_game(){
            //for(int i = 0; i<int(players.size());++i){
                //delete players[i];
            //}
        }

        void add_points(int team_number, int points){
            if(team_number==1){
                std::cout<<players[0]->get_name()<<" and "
                << players[2]->get_name()<< " win the hand\n";
                team_1_score+=points;
            }
            else {
                std::cout<<players[1]->get_name()<<" and "<< players[3]->get_name()
                << " win the hand\n";
                team_2_score+=points;
            }
        }

        void check_winner(){
            if(team_1_score >= pts_to_win){
                std::cout<<players[0]->get_name()<<" and "
                << players[2]->get_name()<< " win!\n";
                winner_exists = true;
            } else if (team_2_score >= pts_to_win){
                std::cout<<players[1]->get_name()<<" and "
                << players[3]->get_name()<< " win!\n";
                winner_exists = true;
            }
        }

        void evaluate_tricks(){
            if(team_1_tricks == 5 && team_made_trump == 1){
                add_points(1,2);
                std::cout<<"march!\n";
            }
            else if(team_2_tricks == 5 && team_made_trump == 2){
                add_points(2,2);
                std::cout<<"march!\n";
            }
            else if(team_1_tricks>=3 && team_made_trump == 2){
                add_points(1,2);
                std::cout<<"euchred!\n";
            }
            else if(team_2_tricks>=3 && team_made_trump == 1){
                add_points(2,2);
                std::cout<<"euchred!\n";
            }
            else if(team_2_tricks > team_1_tricks){
                add_points(2,1);
            }
            else {
                add_points(1,1);
            }
        }

        void reset_tricks(){
            team_1_tricks = 0;
            team_2_tricks = 0;
        }
        void print_score(){
            std::cout<<players[0]->get_name()<<" and "<< players[2]->get_name()
            << " have "<< team_1_score<<" points\n";
            std::cout<<players[1]->get_name()<<" and "<< players[3]->get_name()
            << " have "<< team_2_score<<" points\n\n";
        }

        void add_tricks(int index){
            if(index%2==0) team_1_tricks++;
            else team_2_tricks++;
        }
     
};

struct name_strat {
    std::string name;
    std::string strat;
};

int failed() {
    std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << std::endl;
    return 1;
}

void init_players(std::vector<Player*> v){
    
}
int main(int argc, char* argv[]) {
    for(int i = 0; i<argc; ++i){
        std::cout<<argv[i]<<" ";
    }
    std::cout<<"\n";
    if(argc!=12) return failed();
    std::string input_file = argv[1];
    std::ifstream fin;
    fin.open(input_file);
    if (!fin.is_open()){
        std::cout << "Error opening " << input_file << "\n";
        return 1;
    }
    int pts_to_win = std::atoi(argv[3]);
    bool shuffle;

    std::string shuffle_arg = argv[2];

    if(shuffle_arg=="shuffle") shuffle=true;
    else if(shuffle_arg=="noshuffle") shuffle=false;
    else return failed();

    Pack p = Pack(fin);
    std::vector<Player*> in_players;

    in_players.push_back(Player_factory(argv[4],argv[5]));
    in_players.push_back(Player_factory(argv[6],argv[7]));
    in_players.push_back(Player_factory(argv[8],argv[9]));
    in_players.push_back(Player_factory(argv[10],argv[11]));

    Game main_game = Game(p, shuffle, pts_to_win, in_players);

    main_game.begin_play();
    for(int i = 0; i<int(in_players.size()); ++i){
        delete in_players[i];
    }
}
