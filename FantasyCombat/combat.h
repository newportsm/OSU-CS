#pragma once

#include "characters.h"
#include <vector>
#include <queue> // std::queue

class Combat
{
public:
    void combat_sim(std::queue<Character *> player1_team, std::queue<Character *> player2_team, std::string team1, std::string team2, bool debug_mode);
    int fight_loop(Character &player1, Character &player2); //main fight rotation returns the winner
    void balance_stats(); //writes all the character balance stats to a text file
    void print_stats(std::string header, std::ofstream& ofs, Character &player1, Character &player2, int number_sims);
    void coin_flip();
    bool annotations;
private:
    bool player1_turn;
    bool player2_turn;
    int player1_wins;
    int player2_wins;
};