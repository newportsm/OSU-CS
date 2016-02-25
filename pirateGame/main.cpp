/**********************************************************************
** Program Filename: PirateRescue
** Author: Juan C. Solis
** Date: 3/7/2015
** Description: Final project for CS162. A text adventue game about rescuing
** a friend from pirates. Features include: A map, linked strucure for all 
** the different rooms of the pirate ship. 
** Input: All input is from the user. 
** Output: Lots of text to the console depending on user input. 
**********************************************************************/
#include <iostream>
#include <time.h>

#include "utility.h"
#include "ship.h"
#include "game.h"
#include "player.h"
#include "map.h"
#include "npc.h"

void game_banner(); //Prints the main menu art and options

int main()
{
     srand((unsigned int)time(NULL)); // Seeds random number generator
     //system("mode 650"); //used to make the console screen full screen for Microsoft windows 

     bool quit_program = false;
     while (!quit_program) //main menu loop
     {
          int choice = 0;
          
          game_banner(); //displays the menu
          std::cout << std::endl << std::endl;
          choice = input_verify();

          switch (choice)
          {
               case 1: //Start
               {
                    Game start; //Declare the Game instance that will be the main driver for the entire game functions
                    bool validInput = false;
                    int mode = 0;

                    while (!validInput)
                    {
                         //Display the game difficulty options
                         clear_screen();
                         std::cout << " 1. Easy   - Start with increased health points, fully discovered map, a ranged weapon, and a longer time limit. " << std::endl;
                         std::cout << " 2. Normal - Spawn with map in inventory!" << std::endl;
                         std::cout << " 3. Hard   - Good luck!" << std::endl;
                         std::cout << " 4. Return to main menu" << std::endl;

                         std::cout << std::endl << std::endl;
                         std::cout << " Which mode do you want to play?" << std::endl;
                         std::cout << std::endl << std::endl;
                         mode = input_verify();

                         if ((mode == 1) || (mode == 2) || (mode == 3) || (mode == 4))
                         {
                              validInput = true;
                         }
                         else
                         {
                              std::cout << std::endl;
                              std::cout << " Invalid entry! Please try again." << std::endl;
                              continue_fun();
                         }
                    }

                    if (mode == 1)//easy
                    {
                         start.runGame(1);
                    }
                    else if (mode == 2)//normal
                    {
                         start.runGame(2);
                    }
                    else if (mode == 3)//hard
                    {
                         start.runGame(3);
                    }
                    else if (mode == 4)//return to main menu
                    {
                         break;
                    }

                    break;
               }
               case 2: //instructions
               {
                    clear_screen();
                    std::cout << "                                    MAIN GAME OBJECTIVES" << std::endl;
                    std::cout << " #################################################################################################" << std::endl;
                    std::cout << " ##                                                                                             ##" << std::endl;
                    std::cout << " ## Pirate Captain Scarr is currently docked at Pirate's Cove.                                  ##" << std::endl;
                    std::cout << " ##                                                                                             ##" << std::endl;
                    std::cout << " ## Step 1: Sneak onto his ship, \"The Night's Sadness\", as it sets sail.                        ##" << std::endl;
                    std::cout << " ##                                                                                             ##" << std::endl;
                    std::cout << " ## Step 2: Find \"Ham-Hands Hugo\" and rescue him.                                               ##" << std::endl;
                    std::cout << " ##                                                                                             ##" << std::endl;
                    std::cout << " ## Step 3: Try to sabotage the ship or something.                                              ##" << std::endl;
                    std::cout << " ##                                                                                             ##" << std::endl;
                    std::cout << " ## Step 4: Survive long enough for the Royal Navy's fleet to attack the Pirate Armada.         ##" << std::endl;
                    std::cout << " ##                                                                                             ##" << std::endl;
                    std::cout << " #################################################################################################" << std::endl;
                    std::cout << std::endl;
                    continue_fun();
                    break;
               }
               case 3: //Options
               {
                    bool quitOptions = false;
                    while (!quitOptions)
                    {
                         clear_screen();
                         std::cout << " 1. Write game map to file" << std::endl;
                         std::cout << " 2. Debug Mode -Dont be cheating!" << std::endl;
                         std::cout << " 3. Return to Main Menu" << std::endl;

                         int choice = 0;
                         std::cout << std::endl << std::endl;
                         choice = input_verify();


                         switch (choice)
                         {
                              case 1://write game map to txt file
                              {
                                   clear_screen();
                                   DrawMap map; //instance of map class
                                   map.writeMap(); //writes the map to the file
                                   break;
                              }

                              case 2://debug mode
                              {
                                   clear_screen();
                                   char choice;
                                   std::cout << " All items will be unlocked." << std::endl;
                                   std::cout << " Map will be fully discovered." << std::endl;
                                   std::cout << " Health points set to 600." << std::endl;
                                   std::cout << " Ranged and melee weapons equiped." << std::endl;
                                   std::cout << " Long countdown timers." << std::endl;
                                   std::cout << " Warning: Story line progression will not function correctly. Debug mode used for testing only!" << std::endl;
                                   std::cout << " Do you want to begin the game in Debug mode? (y/n): ";
                                   choice = getUserYN();

                                   if (choice == 'Y')
                                   {
                                        Game start;
                                        start.runGame(4);
                                   }

                                   break; //return to Options menu

                              }
                              case 3://return to main menu
                              {
                                   quitOptions = true;
                                   break;
                              }
                              default:
                              {
                                   clear_screen();
                                   std::cout << " Invalid entry! Only integers from 1-3 are allowed!" << std::endl;
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
                    std::cout << " Created by Juan C. Solis 2015 for a CS162 assignment." << std::endl;
                    std::cout << std::endl;
                    continue_fun();
                    break;
               }
               case 5: //exit the program
               {
                    std::cout << " Exit program has been selected." << std::endl;
                    quit_program = true;
                    break;
               }
               default:
               {
                    clear_screen();
                    std::cout << " Invalid entry! Only integers from 1-5 are allowed!" << std::endl;
                    continue_fun();
                    break;
               }
          }
     }

     return 0;
}



void game_banner()
{
     clear_screen();
     //art by Krzysztof Garus http://www.chris.com/ascii/index.php?art=transportation/nautical
     std::cout << "	             	                                   I" << std::endl;
     std::cout << "	                                                _.$I" << std::endl;
     std::cout << "	                                             _.$#$$I" << std::endl;
     std::cout << "	                                I            $._   I" << std::endl;
     std::cout << "	                                I            _.$   I" << std::endl;
     std::cout << "	                                I     ...:::\"\"\"    I" << std::endl;
     std::cout << "	                                I                  IU" << std::endl;
     std::cout << "	                                I                  ==" << std::endl;
     std::cout << "	                                IU                 IU" << std::endl;
     std::cout << "	                                ==           =======U=======" << std::endl;
     std::cout << "	                                IU           |      U      |" << std::endl;
     std::cout << "	                            =====U=====      |      U      |" << std::endl;
     std::cout << "	                            |    U    |     |       U       |" << std::endl;
     std::cout << "	                            |    U    |     |       U       |" << std::endl;
     std::cout << "	                           |     U     |   |        U        |" << std::endl;
     std::cout << "	                           |     U     |   |        U        |" << std::endl;
     std::cout << "	                          |      U      |  |        U        |         I" << std::endl;
     std::cout << "	                          |      U      | |         U         |    ---~I        //" << std::endl;
     std::cout << "	                         |       U       ||         U         | -=~ qp I       //|" << std::endl;
     std::cout << "	                         |       U       |         _U____      | }  >< I      // |" << std::endl;
     std::cout << "	                        |       _U___    |___----~~\\WWWW/~---__|/  ---~I     //  |" << std::endl;
     std::cout << "	                        |__---~~YYYYY---__|         U||         ~~~    I    //   |" << std::endl;
     std::cout << "	                                 U||    =============||============    I|| //    `." << std::endl;
     std::cout << "	                        ==========||====|            ||           |    ===//      |" << std::endl;
     std::cout << "	                        |         ||    |            ||           |    I||/       |" << std::endl;
     std::cout << "	                        |         ||    |            ZZ           |    /||        `." << std::endl;
     std::cout << "	                        |         ZZ    |            ZZ           |   //||         |" << std::endl;
     std::cout << "	                        |         ZZ    |            ||           |  // ||         |" << std::endl;
     std::cout << "	                 I      |         ||    |            ||           | //  ||         `." << std::endl;
     std::cout << "	              ===I===   |         ||    |            ||           |//   ||          |" << std::endl;
     std::cout << "	              |  I  |   |         ||    |            ||           //    ||          |" << std::endl;
     std::cout << "	              |  I  |   |         ||    |            ZZ          //_____||_-----~~~~~" << std::endl;
     std::cout << "	              |__I__|   |_________||____| ZZ / | || !!!!!!\\" << std::endl;
     std::cout << "	                .I                ||    |            ZZ           |     ||     ;  A I==+==" << std::endl;
     std::cout << "	                `bo.              ||    |____________||___________|   !!!!!!!!!    /" << std::endl;
     std::cout << "	                ===`bo.===        ||                 ||               ;   888    ,/" << std::endl;
     std::cout << "	                |     `boo.   TTTTTTTTT              ||   !!!!!!!!!!!!   A   A A I" << std::endl;
     std::cout << "	                |     &--`boo/        |______________LL   ;                 iiiiiii" << std::endl;
     std::cout << "	                |     (___        8888 !!!!!!!!!!!!!!!!---'8888888            /" << std::endl;
     std::cout << "	                |________\\                                                   /" << std::endl;
     std::cout << "	                          \\            []   []   []   []   []   []   []     /" << std::endl;
     std::cout << "	                           \\                                               =|\\" << std::endl;
     std::cout << "	                            \\                                             = ||" << std::endl;
     std::cout << "	              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
     std::cout << " ================================================================================================================" << std::endl;
     std::cout << " .########..####.########.....###....########.########....########..########..######...######..##.....##.########" << std::endl;
     std::cout << " .##.....##..##..##.....##...##.##......##....##..........##.....##.##.......##....##.##....##.##.....##.##......" << std::endl;
     std::cout << " .##.....##..##..##.....##..##...##.....##....##..........##.....##.##.......##.......##.......##.....##.##......" << std::endl;
     std::cout << " .########...##..########..##.....##....##....######......########..######....######..##.......##.....##.######.." << std::endl;
     std::cout << " .##.........##..##...##...#########....##....##..........##...##...##.............##.##.......##.....##.##......" << std::endl;
     std::cout << " .##.........##..##....##..##.....##....##....##..........##....##..##.......##....##.##....##.##.....##.##......" << std::endl;
     std::cout << " .##........####.##.....##.##.....##....##....########....##.....##.########..######...######...#######..########" << std::endl;
     std::cout << " ================================================================================================================" << std::endl;
     std::cout << "                                                 1. Start" << std::endl;
     std::cout << "                                                 2. Instructions" << std::endl;
     std::cout << "                                                 3. Options" << std::endl;
     std::cout << "                                                 4. Credits" << std::endl;
     std::cout << "                                                 5. Exit Program" << std::endl;
}