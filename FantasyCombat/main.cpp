#include <iostream>
#include "combat.h"
#include "characters.h"
#include "utility.h"

#include <string>
#include <fstream>
#include <queue> // std::queue
#include <cstdlib>
#include <time.h>

void game_banner()
{
    clear_screen();
    std::cout << "=====================================================" << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << " .-." << std::endl; // Art found on http://www.chris.com/ascii/index.php?art=objects/swords
    std::cout << " {{@}}" << std::endl;
    std::cout << " <> 8@8" << std::endl;
    std::cout << " .::::. 888" << std::endl;
    std::cout << " @\\\\/W\\/\\/W\\//@ 8@8" << std::endl;
    std::cout << " \\\\/^\\/\\/^\\// _ )8( _" << std::endl;
    std::cout << " \\_O_<>_O_/ (@)__/8@8\\__(@)" << std::endl;
    std::cout << " ____________________ `~\"-=):(=-\"~`" << std::endl;
    std::cout << " |<><><> | | <><><>| |.|" << std::endl;
    std::cout << " |<> | | <>| |D|" << std::endl;
    std::cout << " |<> | | <>| |'|" << std::endl;
    std::cout << " |<> .--------. <>| |.|" << std::endl;
    std::cout << " | | () | | |O|" << std::endl;
    std::cout << " |_____| (O\\/O) |_____| |'|" << std::endl;
    std::cout << " | \\ /\\ / | |.|" << std::endl;
    std::cout << " |------\\ \\/ /------| |O|" << std::endl;
    std::cout << " | '.__.' | |'|" << std::endl;
    std::cout << " | | | | |.|" << std::endl;
    std::cout << " : | | : |M|" << std::endl;
    std::cout << " \\<> | | <>/ |'|" << std::endl;
    std::cout << " \\<> | | <>/ |.|" << std::endl;
    std::cout << " \\<> | | <>/ | |" << std::endl;
    std::cout << " `\\<> | | <>/' |'|" << std::endl;
    std::cout << " `-.| |.-` \\ /" << std::endl;
    std::cout << " \"--\" ^" << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << "Welcome to the Fantasy Combat Tournament!" << std::endl;
    std::cout << "=====================================================" << std::endl;
}

void display_character_list()
{
    std::cout << "1. Goblin " << std::endl;
    std::cout << "2. Barbarian" << std::endl;
    std::cout << "3. Reptilian" << std::endl;
    std::cout << "4. Blue Men" << std::endl;
    std::cout << "5. The Shadow" << std::endl;
}

bool character_selection()
{
    display_character_list();
    std::cout << "6. RETURN to Main Menu" << std::endl;
    int choice = 0;
    choice = input_verify();
    switch (choice)
    {
        case 1: //Goblin
        {
            std::cout << std::endl << std::endl;
            std::cout << "You have chosen the Goblin!" << std::endl;
            std::cout << "He has fiery red hair, a kind smile, a short build and green skin. " << std::endl;
            std::cout << "One of his hobbies is collecting oddities. He is agile and not very honest." << std::endl;
            std::cout << "His favorite sin is envy. " << std::endl;
            continue_fun();
            break;
        }
        case 2: //Barbarian
        {
            std::cout << std::endl << std::endl;
            std::cout << "You have chosen the Barbarian!" << std::endl;
            std::cout << "He has a solid build and short light brown hair. He is annoyed by autumn, members of the same sex, and irony." << std::endl;
            std::cout << "He is graceful and not very smart. He loves creepy crawly things, fancy parties, and romanticized outlaws." << std::endl;
            std::cout << "His favorite sin is sloth. " << std::endl;
            continue_fun();
            break;
        }
        case 3: //Reptilian
        {
            std::cout << std::endl << std::endl;
            std::cout << "You have chosen the Reptilian!" << std::endl;
            std::cout << "He has pasty tough skin and short grey hair. He dislikes complete honesty, spring, and mysticism." << std::endl;
            std::cout << "His favorite sin is gluttony. One of his hobbies is brawling." << std::endl;
            std::cout << "He loves get rich quick schemes and any sort of aristocracy. " << std::endl;
            continue_fun();
            break;
        }
        case 4: //Blue Men
        {
            std::cout << std::endl << std::endl;
            std::cout << "You have chosen the Blue men!" << std::endl;
            std::cout << "They are small, fast, tough and famed for their overpowering numbers and clever tactics." << std::endl;
            std::cout << "Each unit contains 3 Blue men. They have a highly informal chain of command, with ranks based on merit. " << std::endl;
            std::cout << "At the moment, they are short on supplies. " << std::endl;
            continue_fun();
            break;
        }
        case 5: //The Shadow
        {
            std::cout << std::endl << std::endl;
            std::cout << "You have chosen The Shadow!" << std::endl;
            std::cout << "He has dark brown hair, haunted features, a broad build and moss green eyes." << std::endl;
            std::cout << "One of his hobbies is following politics. He hates obscure trivia, winter, and sappy romantic things." << std::endl;
            std::cout << "His favorite sin is wrath. " << std::endl;
            continue_fun();
            break;
        }
        case 6: //return to main menu
        {
            return true;
            break;
        }
        default:
        {
            std::cout << "Invalid entry! Only integers from 1-6 are allowed!" << std::endl;
            continue_fun();
            break;
        }
    }
    return false;
}

void display_main_menu()
{
    game_banner();
    std::cout << "1. Instructions" << std::endl;
    std::cout << "2. Start" << std::endl;
    std::cout << "3. Options" << std::endl;
    std::cout << "4. Credits" << std::endl;
    std::cout << "5. Exit program" << std::endl;
}

int main()
{
    srand((unsigned int)time(NULL)); // Seeds random number generator
    bool debug_mode = false;
    bool quit_program = false;
    while (!quit_program) //main menu loop
    {
        display_main_menu();
        int choice = 0;
        choice = input_verify();
        switch (choice)
        {
            case 1: //Instructions
            {
                bool exit_menu = false;
                while (!exit_menu)
                {
                    clear_screen();
                    std::cout << "Welcome to the Fantasy Combat Tournament! Each player will take turns forming their team's lineup." << std::endl;
                    std::cout << "Each player sends 1 fighter to battle each other. The winning fighter will return to the back of the line to fight again." << std::endl;
                    std::cout << "Points are what determine the winning team. Each fighter will earn 2 points for a successful attack, 1 point for a successful defend, " << std::endl;
                    std::cout << "and 3 points for winning a match. Once an entire team is eliminated, an awards ceremony will be held in honor of the winning team! " << std::endl;
                    std::cout << "The 1st, 2nd, and 3rd place fighters will also be announced." << std::endl;
                    std::cout << std::endl << std::endl;
                    std::cout << "Please select a character for more information." << std::endl;
                    exit_menu = character_selection();
                }
                break;
            }
            case 2: // start
            {
                clear_screen();
                std::queue<Character *> player1_team;
                std::queue<Character *> player2_team;
                Combat new_game;
                Character * player1;
                Character * player2;
                std::cout << "Welcome to the Fantasy Combat Tournament! Each player will take turns forming their team's lineup." << std::endl;
                std::cout << "Each player sends 1 fighter to battle each other. The winning fighter will return to the back of the line to fight again." << std::endl;
                std::cout << "Points are what determine the winning team. Each fighter will earn 2 points for a successful attack, 1 point for a successful defend " << std::endl;
                std::cout << "and 3 points for winning a match. Once an entire team is eliminated, an awards ceremony will be held in honor of the winning team! " << std::endl;
                std::cout << "The 1st, 2nd, and 3rd place fighters will also be announced." << std::endl;
                std::cout << "Good luck!" << std::endl;
                continue_fun();
                bool valid_name = false;
                std::string team1 = "";
                std::string team2 = "";
                while (!valid_name)
                {
                    std::cout << std::endl << std::endl;
                    std::cout << "Player 1, Please enter the name of your team: ";
                    getline(std::cin, team1);
                    if (team1.length() <= 0)
                    {
                        std::cout << "Invalid entry! Try again. " << std::endl;
                    }
                    else
                    {
                        valid_name = true;
                    }
                }
                valid_name = false;
                while (!valid_name)
                {
                    std::cout << std::endl << std::endl;
                    std::cout << "Player 2, Please enter the name of your team: ";
                    getline(std::cin, team2);
                    if (team2.length() <= 0)
                    {
                        std::cout << "Invalid entry! Try again. " << std::endl;
                    }
                    else
                    {
                        valid_name = true;
                    }
                }
                bool valid_number = false;
                int number_fighters = 0;
                while (!valid_number) //there has to be at least 3 players per team for the 3rd place result to work
                {
                    std::cout << std::endl << std::endl;
                    std::cout << "How many fighters will be on each team?" << std::endl;
                    number_fighters = input_verify();
                    if (number_fighters < 3)
                    {
                        std::cout << std::endl << "There has to be at least 3 fighters per team. Please try again." << std::endl;
                    }
                    else
                    {
                        valid_number = true;
                    }
                }
                //Player 1 forms his lineup
                for (int i = 0; i < number_fighters; i++)
                {
                    bool valid_input = false;
                    while (!valid_input)
                    {
                        int player_choice = 0;
                        std::cout << std::endl << std::endl;
                        display_character_list();
                        std::cout << std::endl << std::endl;
                        std::cout << "Player 1, please select your fighter #" << i + 1 << std::endl;
                        player_choice = input_verify();
                        if (player_choice == 1)//Goblin
                        {
                            player1 = new Goblin();
                            player1->set_name(team1);
                            player1_team.push(player1);
                            valid_input = true;
                        }
                        else if (player_choice == 2)//Barb
                        {
                            player1 = new Barbarian();
                            player1->set_name(team1);
                            player1_team.push(player1);
                            valid_input = true;
                        }
                        else if (player_choice == 3)//Reptile
                        {
                            player1 = new Reptile_people();
                            player1->set_name(team1);
                            player1_team.push(player1);
                            valid_input = true;
                        }
                        else if (player_choice == 4)//Blue men
                        {
                            player1 = new Blue_men();
                            player1->set_name(team1);
                            player1_team.push(player1);
                            valid_input = true;
                        }
                        else if (player_choice == 5)//The shadow
                        {
                            player1 = new Shadow();
                            player1->set_name(team1);
                            player1_team.push(player1);
                            valid_input = true;
                        }
                        else
                        {
                            std::cout << "Invalid choice! Try again." << std::endl;
                        }
                    }
                }
                std::cout << std::endl << std::endl;
                std::cout << "Excellent. The fighters for team " << team1 <<" have been chosen and await their battle!"<< std::endl;
                std::cout << "It is now time for "<<team2 <<" to select their line up of fighters." << std::endl;
                continue_fun();
                //Player 2 forms his lineup
                for (int i = 0; i < number_fighters; i++)
                {
                    bool valid_input = false;
                    while (!valid_input)
                    {
                        int player_choice = 0;
                        display_character_list();
                        std::cout << std::endl << std::endl;
                        std::cout << "Player 2, please select your fighter #" << i + 1 << std::endl;
                        player_choice = input_verify();
                        if (player_choice == 1)//Goblin
                        {
                            player2 = new Goblin();
                            player2->set_name(team2);
                            player2_team.push(player2);
                            valid_input = true;
                        }
                        else if (player_choice == 2)//Barb
                        {
                            player2 = new Barbarian();
                            player2->set_name(team2);
                            player2_team.push(player2);
                            valid_input = true;
                        }
                        else if (player_choice == 3)//Reptile
                        {
                            player2 = new Reptile_people();
                            player2->set_name(team2);
                            player2_team.push(player2);
                            valid_input = true;
                        }
                        else if (player_choice == 4)//Blue men
                        {
                            player2 = new Blue_men();
                            player2->set_name(team2);
                            player2_team.push(player2);
                            valid_input = true;
                        }
                        else if (player_choice == 5)//The shadow
                        {
                            player2 = new Shadow();
                            player2->set_name(team2);
                            player2_team.push(player2);
                            valid_input = true;
                        }
                        else
                        {
                            std::cout << "Invalid choice! Try again." << std::endl;
                        }
                    }
                }
                std::cout << std::endl << std::endl;
                std::cout << "Excellent. The fighters for team " << team2 << " have been chosen and await their battle!" << std::endl;
                continue_fun();
                new_game.combat_sim(player1_team, player2_team, team1, team2, debug_mode);
                break;
            }
            case 3: //options
            {
                bool exit_menu = false;
                while (!exit_menu)
                {
                    clear_screen();
                    std::cout << "1. Debug Mode ON " << std::endl;
                    std::cout << "2. Debug Mode OFF" << std::endl;
                    std::cout << "3. Write character balance stats to file" << std::endl;
                    std::cout << "4. RETURN to Main Menu" << std::endl;
                    int choice = 0;
                    choice = input_verify();
                    switch (choice)
                    {
                        case 1://debug mode ON
                        {
                            debug_mode = true;
                            std::cout << "Battle annotations will now be displayed." << std::endl;
                            continue_fun();
                            break;
                        }
                        case 2: //DEBUG mode OFF
                        {
                            debug_mode = false;
                            std::cout << "Battle annotations will not be displayed." << std::endl;
                            continue_fun();
                            break;
                        }
                        case 3: // Write balance stats to file
                        {
                            Combat stats;
                            stats.balance_stats();
                            break;
                        }
                        case 4: //return to main menu
                        {
                            exit_menu = true;
                            break;
                        }
                        default:
                        {
                            std::cout << "Invalid entry! Only integers from 1-4 are allowed!" << std::endl;
                            continue_fun();
                            break;
                        }
                    }
                }
                break;
            }
            case 4: //Credits
            {
                clear_screen();
                std::cout << "Created by Juan C. Solis 2015 for a CS162 assignment." << std::endl;
                std::cout << "Special thanks to Paul Williams for debugging help." << std::endl;
                std::cout << std::endl;
                continue_fun();
                break;
            }
            case 5: //exit the program
            {
                std::cout << "Exit program has been selected." << std::endl;
                quit_program = true;
                break;
            }
            default:
            {
                std::cout << "Invalid entry! Only integers from 1-5 are allowed!" << std::endl;
                continue_fun();
                break;
            }
        }
    }
    return 0;
}