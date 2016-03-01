#include "combat.h"
#include "utility.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric> //needed for mean calculation (accumulate())
#include <queue> // std::queue
#include <stack> // std::stack

void Combat::combat_sim(std::queue<Character *> player1_team, std::queue<Character *> player2_team, std::string team1, std::string team2, bool debug_mode)
{
    annotations = false;
    if (debug_mode)
    {
        annotations = true;
    }
    clear_screen();
    std::cout << std::endl << std::endl;
    std::cout << "Both teams enter the arena made of dirt walls and slate floor." << std::endl;
    std::cout << "It is decorated with patterned murals, skulls and inscriptions." << std::endl;
    std::cout << "Be wary of the flame jets, arrow traps and hidden spikes!" << std::endl;
    std::cout << std::endl;
    std::vector<int> team1_win_results; // player 1 results
    std::vector<int> team2_win_results; //player 2 results
    std::vector<Character *> player1_losers; //loser pile for player 1 fighters
    std::vector<Character *> player2_losers; //loser pile for player 2 fighters
    Character * player1;
    Character * player2;
    Character * temp; //used in calculations
    int round = 1; //counter variable to display current round number
    while (!player1_team.empty() && !player2_team.empty()) //keeps looping until one of the teams is out of fighters
    {
        player1 = &*player1_team.front();
        player2 = &*player2_team.front();
        //remove the fighters from the lineup
        player1_team.pop();
        player2_team.pop();
        int winner = 0;
        coin_flip(); //sets the bool flags for the current players turn
        winner = fight_loop(*player1, *player2);
        if (winner == 1) //if player 1 wins
        {
            std::cout << "Round "<<round <<": "<<player1->get_name() <<" wins the battle! Current points: "<<player1->points << std::endl;
            player1->recover_strength();
            player1->number_wins++;
            player1_team.push(player1); //return the fighter to the back of the line up
            player2_losers.push_back(player2); //put the loser into the loser pile
            team1_win_results.push_back(1);
            team2_win_results.push_back(0);
        }
        else if (winner == 2) //if player 2 wins
        {
            std::cout << "Round " << round << ": " << player2->get_name() << " wins the battle! Current points: " << player2->points << std::endl;
            player2->recover_strength();
            player2->number_wins++;
            player2_team.push(player2); //return the fighter to the back of the line up
            player1_losers.push_back(player1); //put the loser into the loser pile
            team1_win_results.push_back(0);
            team2_win_results.push_back(1);
        }
        else //Display error messaage if anything wierd happens
        {
            std::cout << "Error! A winner could not be determined!" << std::endl;
            continue_fun();
        }
        round++;
    }
    //calculations of the results
    while (!player1_team.empty()) //team 1: add the still alive players to the loser pile so we can calculate points
    {
        player1 = &*player1_team.front();
        player1_team.pop();
        player1_losers.push_back(player1);
    }
    while (!player2_team.empty()) //team 2: add the still alive players to the loser pile so we can calculate points
    {
        player2 = &*player2_team.front();
        player2_team.pop();
        player2_losers.push_back(player2);
    }
    int team1_points = 0;
    int team2_points = 0;
    int team1_wins = 0;
    int team2_wins = 0;
    for (unsigned int i = 0; i < player1_losers.size(); i++)
    {
        temp = &*player1_losers[i];
        team1_points += temp->points;
        team1_wins += temp->number_wins;
    }
    for (unsigned int i = 0; i < player2_losers.size(); i++)
    {
        temp = &*player2_losers[i];
        team2_points += temp->points;
        team2_wins += temp->number_wins;
    }
    player1_losers.insert(player1_losers.end(), player2_losers.begin(), player2_losers.end()); //put both vectors together to find top 3 characters
    Character * first_place = new Goblin;
    Character * second_place = new Goblin;
    Character * third_place = new Goblin;
    int largest_index = 0;
    for (unsigned int i = 0; i < player1_losers.size(); i++)
    {
        temp = &*player1_losers[i];
        if (temp->get_points() > first_place->get_points())
        {
            first_place = &*player1_losers[i];
            largest_index = i;
        }
    }
    player1_losers.erase(player1_losers.begin() + largest_index); //remove the 1st place character from the vector
    largest_index = 0;
    for (unsigned int i = 0; i < player1_losers.size(); i++)
    {
        temp = &*player1_losers[i];
        if (temp->get_points() > second_place->get_points())
        {
            second_place = &*player1_losers[i];
            largest_index = i;
        }
    }
    player1_losers.erase(player1_losers.begin() + largest_index); //remove the 2nd place character from the vector
    largest_index = 0;
    for (unsigned int i = 0; i < player1_losers.size(); i++)
    {
        temp = &*player1_losers[i];
        if (temp->get_points() > third_place->get_points())
        {
            third_place = &*player1_losers[i];
            largest_index = i;
        }
    }
    player1_losers.erase(player1_losers.begin() + largest_index); //remove the 3rd place character from the vector
    /*for (unsigned int i = 0; i < player1_losers.size(); i++)
     {
     temp = &*player1_losers[i];
     if (temp->get_points() > first_place->get_points())
     {
     first_place = &*player1_losers[i];
     }
     else if ((temp->get_points() > second_place->get_points()) && (temp->get_points() < first_place->get_points()))
     {
     second_place = &*player1_losers[i];
     }
     else if ((temp->get_points() > third_place->get_points()) && (temp->get_points() < second_place->get_points()) && (temp->get_points() < first_place->get_points()))
     {
     third_place = &*player1_losers[i];
     }
     }
     */
    std::cout << std::endl << std::endl << std::endl;
    std::cout << "The tournament comes to a bloody halt! One team has been completely eliminated!" << std::endl;
    std::cout << "It's time to head over to the awards ceramony!" << std::endl;
    continue_fun();
    clear_screen();
    std::cout << " "<< team1 << " "<< team2 << std::endl;
    std::cout << "==================== ==================== " << std::endl;
    std::cout << "Number of wins: " << team1_wins << " Number of wins: " << team2_wins << std::endl;
    std::cout << "Total # points: " << team1_points << " Total # points: " << team2_points << std::endl;
    std::cout << std::endl << std::endl << std::endl;
    if (team1_points > team2_points)
    {
        std::cout << "The winner is "<<team1 << std::endl;
    }
    else if (team1_points < team2_points)
    {
        std::cout << "The winner is "<<team2 << std::endl;
    }
    else if (team1_points == team2_points)
    {
        std::cout << "There was a tie!" << std::endl;
    }
    std::cout << std::endl << std::endl << std::endl;
    std::cout << "1st place: " << first_place->get_name() << " with " << first_place->number_wins << " wins and " << first_place->points << " points!" << std::endl;
    std::cout << std::endl;
    std::cout << "2nd place: " << second_place->get_name() << " with " << second_place->number_wins << " wins and " << second_place->points << " points!" << std::endl;
    std::cout << std::endl;
    std::cout << "3rd place: " << third_place->get_name() << " with " << third_place->number_wins << " wins and " << third_place->points << " points!" << std::endl;
    std::cout << std::endl;
    continue_fun();
}

int Combat::fight_loop(Character &player1, Character &player2)
{
    int winner = 0; // returns 1 for player 1 and 2 for player 2
    if (player1_turn)
    {
        if (annotations)
        {
            std::cout << std::endl << std::endl;
            std::cout << player1.get_name() << " makes the first strike!" << std::endl;
        }
    }
    if (player2_turn)
    {
        if (annotations)
        {
            std::cout << std::endl << std::endl;
            std::cout << player2.get_name() << " makes the first strike!" << std::endl;
        }
    }
    bool ply1_goblin = false;
    bool ply2_goblin = false;
    bool ply1_debuff = false; //if player 2 performs hamstring, player 1 has dmg reduced by half
    bool ply2_debuff = false;
    bool ply1_shadow = false;
    bool ply2_shadow = false;
    //point system for successful attacks, defends, and wins
    int attack_success = 2;
    int defend_success = 1;
    int win_success = 3;
    if (player1.get_creature_type() == 1) //flags player 1 as a goblin
    {
        ply1_goblin = true;
    }
    if (player2.get_creature_type() == 1) //flags player 2 as a goblin
    {
        ply2_goblin = true;
    }
    if (ply1_goblin && ply1_goblin) //If both are goblin, turns off the hamstring feature
    {
        ply1_goblin = false;
        ply2_goblin = false;
    }
    if (player1.get_creature_type() == 2)
    {
        ply1_shadow = true;
    }
    if (player2.get_creature_type() == 2)
    {
        ply2_shadow = true;
    }
    bool round_over = false;
    while (!round_over) //The combat loop
    {
        int damage_dealed = 0;
        if (player1_turn)
        {
            player1_turn = false;
            player2_turn = true;
            if (ply1_debuff)
            {
                damage_dealed = ((player2.defend(player1.attack())) / 2);
                if (annotations)
                {
                    std::cout << std::endl << std::endl;
                    std::cout << player1.get_name() << " is slowing down from " << player2.get_name() << "'s hamstring attack!" << std::endl;
                }
            }
            else
            {
                damage_dealed = (player2.defend(player1.attack()));
            }
            if (ply1_goblin)
            {
                if (player1.special_used())
                {
                    ply2_debuff = true;
                }
            }
            if (damage_dealed < 1)//attack failed
            {
                player2.points += defend_success; //add 1 point
                if (ply2_shadow)
                {
                    if (player2.special_used())
                    {
                        if (annotations)
                        {
                            std::cout << player2.get_name() << " is elsewhere and avoids " << player1.get_name() << "'s attack!" << std::endl;
                        }
                    }
                }
                else
                {
                    if (annotations)
                    {
                        std::cout << player2.get_name() << " successfully defends against " << player1.get_name() << "'s attack and no damage is taken!" << std::endl;
                    }
                }
            }
            else //attack succeeded
            {
                player1.points += attack_success; //add 2 points
                player2.current_strength_points = (player2.current_strength_points - damage_dealed);
                if (annotations)
                {
                    std::cout << player1.get_name() << " attacks " << player2.get_name() << " and deals " << damage_dealed << " damage!" << std::endl;
                }
                if (player2.current_strength_points < 1)
                {
                    if (annotations)
                    {
                        std::cout << player2.get_name() << " has been defeated by " << player1.get_name() << "!" << std::endl;
                        continue_fun();
                    }
                    player1.points += win_success; //add 3 points
                    winner = 1;
                    round_over = true;
                    break;
                }
                else
                {
                    if (annotations)
                    {
                        std::cout << player2.get_name() << " has " << player2.current_strength_points << " strength points remaining!" << std::endl;
                    }
                }
            }
        }
        if(player2_turn) //player 2 turn
        {
            player1_turn = true;
            player2_turn = false;
            if (ply2_debuff)
            {
                damage_dealed = ((player1.defend(player2.attack())) / 2);
                if (annotations)
                {
                    std::cout << player2.get_name() << " is slowing down from " << player1.get_name() << "'s hamstring attack!" << std::endl;
                }
            }
            else
            {
                damage_dealed = (player1.defend(player2.attack()));
            }
            if (ply2_goblin)
            {
                if (player2.special_used())
                {
                    ply1_debuff = true;
                }
            }
            if (damage_dealed < 1) //attack failed
            {
                player1.points += defend_success;
                if (ply1_shadow)
                {
                    if (player1.special_used())
                    {
                        if (annotations)
                        {
                            std::cout << player1.get_name() << " is elsewhere and avoids " << player2.get_name() << "'s attack!" << std::endl;
                        }
                    }
                }
                else
                {
                    if (annotations)
                    {
                        std::cout << player1.get_name() << " successfully defends against " << player2.get_name() << "'s attack and no damage is taken!" << std::endl;
                    }
                }
            }
            else //attack succeeded
            {
                player2.points += attack_success; //add 2 points
                player1.current_strength_points = (player1.current_strength_points - damage_dealed);
                if (annotations)
                {
                    std::cout << player2.get_name() << " attacks " << player1.get_name() << " and deals " << damage_dealed << " damage!" << std::endl;
                }
                if (player1.current_strength_points < 1)
                {
                    if (annotations)
                    {
                        std::cout << player1.get_name() << " has been defeated by " << player2.get_name() << "!" << std::endl;
                        continue_fun();
                    }
                    player2.points += win_success; //add 3 points
                    winner = 2;
                    round_over = true;
                    break;
                }
                else
                {
                    if (annotations)
                    {
                        std::cout << player1.get_name() << " has " << player1.current_strength_points << " strength points remaining!" << std::endl;
                    }
                }
            }
        }
        if (annotations)
        {
            continue_fun();
        }
    }
    return winner;
}

void Combat::coin_flip()
{
    int coin_flip = rand() % 2; //50% chance of either 0 or 1
    if (coin_flip == 0) //Player 1 attacks first
    {
        player1_turn = true;
        player2_turn = false;
    }
    else //player 2 attacks first
    {
        player1_turn = false;
        player2_turn = true;
    }
}

void Combat::balance_stats()
{
    clear_screen();
    std::cout << "This will test every possible pairing and write the results to \"CharacterBalanceStats.txt\"." << std::endl;
    std::cout << "Both fighters will get first strike an equal amount of times." << std::endl;
    std::ofstream ofs;
    ofs.open("CharacterBalanceStats.txt");
    int number_sims = 0;
    std::cout << "Please enter how many simulations you would like to perform." << std::endl;
    number_sims = input_verify();
    Character * player1;
    Character * player2;
    //goblin vs goblin
    std::cout << "Simulating Goblins vs Goblins..." << std::endl;
    std::string h1 = "Goblins vs Goblins";
    player1 = new Goblin();
    player2 = new Goblin();
    print_stats(h1, ofs, *player1, *player2, number_sims);
    std::cout << "Goblins vs Goblins...Complete!" << std::endl;
    //barb vs barb
    std::cout << "Simulating Barbarians vs Barbarians..." << std::endl;
    std::string h2 = "Barbarians vs Barbarians";
    player1 = new Barbarian();
    player2 = new Barbarian();
    print_stats(h2, ofs, *player1, *player2, number_sims);
    std::cout << "Barbarians vs Barbarians...Complete!" << std::endl;
    //reptile vs reptile
    std::cout << "Simulating Reptile People vs Reptile People..." << std::endl;
    std::string h3 = "Reptile People vs Reptile People";
    player1 = new Reptile_people();
    player2 = new Reptile_people();
    print_stats(h3, ofs, *player1, *player2, number_sims);
    std::cout << "Reptile People vs Reptile People...Complete!" << std::endl;
    //blue men vs blue men
    std::cout << "Simulating Blue Men vs Blue Men..." << std::endl;
    std::string h4 = "Blue Men vs Blue Men";
    player1 = new Blue_men();
    player2 = new Blue_men();
    print_stats(h4, ofs, *player1, *player2, number_sims);
    std::cout << "Blue Men vs Blue Men...Complete" << std::endl;
    //shadow vs shadow
    std::cout << "Simulating The Shadow vs The Shadow..." << std::endl;
    std::string h5 = "The Shadow vs The Shadow";
    player1 = new Shadow();
    player2 = new Shadow();
    print_stats(h5, ofs, *player1, *player2, number_sims);
    std::cout << "The Shadow vs The Shadow...Complete!" << std::endl;
    //goblin vs barb
    std::cout << "Simulating Goblins vs Barbarians... " << std::endl;
    std::string h6 = "Goblins vs Barbarians ";
    player1 = new Goblin();
    player2 = new Barbarian();
    print_stats(h6, ofs, *player1, *player2, number_sims);
    std::cout << "Goblins vs Barbarians...Complete!" << std::endl;
    //goblin vs reptile
    std::cout << "Simulating Goblins vs Reptile People..." << std::endl;
    std::string h7 = "Goblins vs Reptile People";
    player1 = new Goblin();
    player2 = new Reptile_people();
    print_stats(h7, ofs, *player1, *player2, number_sims);
    //goblin vs blue men
    std::cout << "Simulating Goblins vs Blue Men..." << std::endl;
    std::string h8 = "Goblins vs Blue Men";
    player1 = new Goblin();
    player2 = new Blue_men();
    print_stats(h8, ofs, *player1, *player2, number_sims);
    std::cout << "Goblins vs Blue Men...Complete!" << std::endl;
    //goblin vs shadow
    std::cout << "Simulating Goblins vs The Shadow..." << std::endl;
    std::string h9 = "Goblins vs The Shadow";
    player1 = new Goblin();
    player2 = new Shadow();
    print_stats(h9, ofs, *player1, *player2, number_sims);
    std::cout << "Goblins vs The Shadow...Complete!" << std::endl;
    //barb vs reptile
    std::cout << "Simulating Barbarians vs Reptile People..." << std::endl;
    std::string h10 = "Barbarians vs Reptile People";
    player1 = new Barbarian();
    player2 = new Reptile_people();
    print_stats(h10, ofs, *player1, *player2, number_sims);
    std::cout << "Barbarians vs Reptile People...Complete!" << std::endl;
    //barb vs blue men
    std::cout << "Simulating Barbarians vs Blue Men..." << std::endl;
    std::string h11 = "Barbarians vs Blue Men";
    player1 = new Barbarian();
    player2 = new Blue_men();
    print_stats(h11, ofs, *player1, *player2, number_sims);
    std::cout << "Barbarians vs Blue Men...Complete!" << std::endl;
    //barb vs shadow
    std::cout << "Simulating Barbarians vs The Shadow.." << std::endl;
    std::string h12 = "Barbarians vs The Shadow";
    player1 = new Barbarian();
    player2 = new Shadow();
    print_stats(h12, ofs, *player1, *player2, number_sims);
    std::cout << "Barbarians vs The Shadow...Complete!" << std::endl;
    //reptile vs blue men
    std::cout << "Simulating Reptile People vs Blue Men..." << std::endl;
    std::string h13 = "Reptile People vs Blue Men";
    player1 = new Reptile_people();
    player2 = new Blue_men();
    print_stats(h13, ofs, *player1, *player2, number_sims);
    std::cout << "Reptile People vs Blue Men...Complete!" << std::endl;
    //reptile vs shadow
    std::cout << "Simulating Reptile People vs The Shadow..." << std::endl;
    std::string h14 = "Reptile People vs The Shadow";
    Reptile_people *myReptile6 = new Reptile_people();
    Shadow *myShadow5 = new Shadow();
    print_stats(h14, ofs, *player1, *player2, number_sims);
    std::cout << "People vs The Shadow...Complete!" << std::endl;
    //blue men vs shadow
    std::cout << "Simulating Blue Men vs The Shadow..." << std::endl;
    std::string h15 = "Blue Men vs The Shadow";
    player1 = new Blue_men();
    player2 = new Shadow();
    print_stats(h15, ofs, *player1, *player2, number_sims);
    std::cout << "Blue Men vs The Shadow...Complete!" << std::endl;
    ofs.close();
    std::cout << std::endl << std::endl;
    std::cout << "All results have been saved to \"CharacterBalanceStats.txt\"." << std::endl;
    continue_fun();
}

void Combat::print_stats(std::string header, std::ofstream& ofs, Character &player1, Character &player2, int number_sims)
{
    annotations = false;
    std::vector<int> ply1_results; // player 1 results
    std::vector<int> ply2_results; //player 2 results
    player1_turn = true;
    player2_turn = false;
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < number_sims; i++)
        {
            int winner = 0;
            winner = fight_loop(player1, player2);
            if (winner == 1) //if player 1 wins
            {
                ply1_results.push_back(1);
                ply2_results.push_back(0);
            }
            else if(winner == 2) //if player 2 wins
            {
                ply1_results.push_back(0);
                ply2_results.push_back(1);
            }
            //reset the values for the next round
            player1.reset();
            player2.reset();
        }
        //alternate the attacking player
        player1_turn = false;
        player2_turn = true;
    }
    double player1_mean = ((accumulate(ply1_results.begin(), ply1_results.end(), 0) / double(ply1_results.size())) * 100);
    double player2_mean = ((accumulate(ply2_results.begin(), ply2_results.end(), 0) / double(ply2_results.size())) * 100);
    ofs << header << '\n';
    ofs << "--------------------------" << '\n';
    ofs << number_sims << " battles each as the attacking player: " << '\n';
    ofs << player1.get_name() << " wins: " << player1_mean << "%" << '\n';
    ofs << player2.get_name() << " wins: " << player2_mean << "%" << '\n';
    ofs << '\n';
}