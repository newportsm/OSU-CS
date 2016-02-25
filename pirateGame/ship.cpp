#include "ship.h"
#include "utility.h"

Room::Room() //base class constructor
{
     roomID = 0;
     Label = "standard room";
     Description = "standard description";
     hintNorth   = "                                                                     ";
     hintEast    = "                                                                     ";
     hintSouth   = "                                                                     ";
     hintWest    = "                                                                     ";
     hintLocked  = "                                                                     ";
     hintExplore = "                                                                     ";
     explore1    = "                                                                     ";
     explore2    = "                                                                     ";
     explore3    = "                                                                     ";
     explorable = false;
     East = NULL;
     West = NULL;
     North = NULL;
     South = NULL;

}

bool Room::exploreRoom(Player &player1){ return true; } 

std::string Room::PrintDescription()
{
     return  Description;
}

std::string Room::getLabel()
{
     return Label;
}

poopDeck::poopDeck()
{
     roomID = 1;
     Label = "THE POOP DECK";
     Description = "The highest deck on the ship. This is where the \nsignal liuetenant hauls up flags to signal nearby vessels.";
     hintSouth = "(S) Take the stairs down to the quarter deck                         ";
     hintExplore = "(X) There is a Pirate Officer on this deck.                          ";
     explore1 = " 1. Ask the Pirate Officer for the key                               ";
     explore2 = " 2. Knock the Pirate Officer out                                     ";
     explore3 = " 3. Attempt to pick the Pirate Officer's pocket                      ";
     explorable = true;
}

bool poopDeck::exploreRoom(Player &player1)
{
     bool validInput = false;

     while (!validInput)
     {
          std::cout << std::endl;
          int choice = 0;

          choice = input_verify();

          switch (choice)
          {
          case 1://ask for the key

               clear_screen();

               if (!player1.officerKnockedOut)
               {
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##      You ask him if you could have the key to the wardroom...            ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    continue_fun();

                    std::cout << std::endl << std::endl << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##                           He says \"No\".                                  ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    
               }
               else
               {
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##                     You already knocked him out!...                      ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
               }

               validInput = true;
               break;

          case 2://knock him out
               clear_screen();

               if (!player1.officerKnockedOut)
               {
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##    You grab a nearby belaying pin... ( It's a solid wood bar)            ##" << std::endl;
                    std::cout << " ##                       You knock him out!                                 ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##    **Key to the officer's wardroom has been added to your inventory**    ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    player1.officerKnockedOut = true;
                    player1.officerKey = true;
                    player1.setScore(10); //add 10 to the player score
               }
               else
               {
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##                     You already knocked him out!...                      ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
               }
               
               validInput = true;
               break;

          case 3://pick pocket
               clear_screen();

               if (!player1.officerKnockedOut)
               {
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##      You move in closer to try to pick the key...                        ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    continue_fun();

                    std::cout << std::endl << std::endl << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##        He turns around and orders you to get to work!                    ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
               }
               else
               {
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##                     You already knocked him out!...                      ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
               }
               validInput = true;
               break;

          case 4://stop exploring
               return true;

          default://error msg
               std::cout << " Invalid entry! Only integers from 1-4 are allowed!" << std::endl;
               break;
          }
     }
     return false;
}

quarterDeck::quarterDeck()
{
     roomID = 2;
     Label = "THE QUARTER DECK";
     Description = "At the stern of the ship, the quarter deck is normally reserved for the officers.";
     hintNorth = "(N) Take the stairs up to the poop deck                              ";
     hintEast  = "(E) Door to the Captain's quarters                                   ";
     hintSouth = "(S) Stairs down to the main deck                                     ";
     hintWest  = "(W) Cross the gangway to the forcastle deck                          ";
}


captainDining::captainDining()
{
     roomID = 3;
     Label = "THE CAPTAIN'S DINING ROOM";
     Description = "This is where the Captain eats his meals alone. He can be no friend to his sailors or risk loosing their respect.";
     hintWest    = "(W) Take the door back to the hallway                                ";
     hintExplore = "(X) Explore your surroundings                                        ";
     explore1    = " 1. A bottle 'o 'spiced rum                                          ";
     explore2    = " 2. Half eaten dinner                                                ";
     explore3    = " 3. The Captain's bib                                                ";
     bib = false;
     explorable = true;
}

bool captainDining::exploreRoom(Player &player1)
{

     bool validInput = false;

     while (!validInput)
     {
          std::cout << std::endl;
          int choice = 0;

          choice = input_verify();

          switch (choice)
          {
               case 1://bottle of rum
                    clear_screen();

                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##         You pour yourself some spiced rum. Now you are drunk.            ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    player1.setStatus(4);
           
                    validInput = true;

                    break;

               case 2://half eaten dinner
                    clear_screen();

                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##  You realize you are quite hungry and decide to eat some dinner.         ##" << std::endl;
                    std::cout << " ##  It is delicious.                                                        ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##  However, you accidentally drop some of it on your shirt...              ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;

                    if (bib)//if the player is wearing a bib
                    {
                         std::cout << std::endl << std::endl << std::endl;
                         std::cout << "##############################################################################" << std::endl;
                         std::cout << "##                                                                          ##" << std::endl;
                         std::cout << "##         Good thing you were wearing that bib!                            ##" << std::endl;
                         std::cout << "##                                                                          ##" << std::endl;
                         std::cout << "##############################################################################" << std::endl;
                         player1.setScore(10); //add 10 to the player score
                    }
                    else
                    {
                         std::cout << std::endl << std::endl << std::endl;
                         std::cout << "##############################################################################" << std::endl;
                         std::cout << "##                                                                          ##" << std::endl;
                         std::cout << "##         If only you had been wearing a bib or something....              ##" << std::endl;
                         std::cout << "##                                                                          ##" << std::endl;
                         std::cout << "##############################################################################" << std::endl;
                    }
                    validInput = true;
                    break;

               case 3://captain's bib
                    clear_screen();

                    if (bib)
                    {
                         std::cout << "##############################################################################" << std::endl;
                         std::cout << "##                                                                          ##" << std::endl;
                         std::cout << "##                      You take the bib off.                               ##" << std::endl;
                         std::cout << "##                                                                          ##" << std::endl;
                         std::cout << "##############################################################################" << std::endl;
                         bib = false;
                    }
                    else
                    {
                         std::cout << "##############################################################################" << std::endl;
                         std::cout << "##                                                                          ##" << std::endl;
                         std::cout << "##                You put the bib on. It looks fantastic.                   ##" << std::endl;
                         std::cout << "##                                                                          ##" << std::endl;
                         std::cout << "##############################################################################" << std::endl;
                         bib = true;  
                         player1.setScore(10); //add 10 to the player score
                    }
                    validInput = true;
                    break;

               case 4://stop exploring
                    return true;

               default://error msg
                    std::cout << " Invalid entry! Only integers from 1-4 are allowed!" << std::endl;
                    break;
          }
     }

     return false;
}

captainCabin::captainCabin()
{
     roomID = 3;
     Label = "THE CAPTAIN'S CABIN";
     Description = "This is where the Captain sleeps, so he can be on hand quickly in an emergency. \nLuckily it's unlocked!";
     hintSouth   = "(S) Take the door back to the hallway                                ";
     hintExplore = "(X) Explore your surroundings                                        ";
     explore1    = " 1. A cabinet                                                        ";
     explore2    = " 2. A locked footlocker                                              ";
     explore3    = " 3. A desk                                                           ";
     explorable = true;
     lockerKey = false;

}

bool captainCabin::exploreRoom(Player &player1)
{

     bool validInput = false;

     while (!validInput)
     {
          std::cout << std::endl;
          int choice = 0;

          choice = input_verify();

          switch (choice)
          {
          case 1://cabinet
               clear_screen();

               std::cout << "##############################################################################" << std::endl;
               std::cout << "##                                                                          ##" << std::endl;
               std::cout << "##            You open the cabinet and find nothing useful.                 ##" << std::endl;
               std::cout << "##                                                                          ##" << std::endl;
               std::cout << "##############################################################################" << std::endl;
               validInput = true;
               break;

          case 2://footlocker
               clear_screen();

               if (!player1.mapFound)
               {
                    if (lockerKey)
                    {
                         std::cout << "##############################################################################" << std::endl;
                         std::cout << "##                                                                          ##" << std::endl;
                         std::cout << "##  The key works! You open the foot locker and find a blank map!           ##" << std::endl;
                         std::cout << "##   You can use this to keep track of the rooms you have been in.          ##" << std::endl;
                         std::cout << "##                                                                          ##" << std::endl;
                         std::cout << "##############################################################################" << std::endl;
                         std::cout << std::endl;
                         std::cout << "##############################################################################" << std::endl;
                         std::cout << "##                                                                          ##" << std::endl;
                         std::cout << "##            **Map has been added to your inventory**                      ##" << std::endl;
                         std::cout << "##                                                                          ##" << std::endl;
                         std::cout << "##############################################################################" << std::endl;
                         player1.map = true;
                         player1.mapFound = true;
                         player1.setScore(20); //add 20 to the player score
                    }
                    else
                    {
                         std::cout << "##############################################################################" << std::endl;
                         std::cout << "##                                                                          ##" << std::endl;
                         std::cout << "##          You try to open the footlocker, but it's no use.                ##" << std::endl;
                         std::cout << "##                                                                          ##" << std::endl;
                         std::cout << "##############################################################################" << std::endl;
                    }
               }
               else
               {
                    std::cout << "############################################" << std::endl;
                    std::cout << "##                                        ##" << std::endl;
                    std::cout << "##           It's empty now...            ##" << std::endl;
                    std::cout << "##                                        ##" << std::endl;
                    std::cout << "############################################" << std::endl;
               }

               
               validInput = true;
               break;

          case 3://desk
               clear_screen();

               if (!player1.mapFound)
               {
                    std::cout << "##############################################################################" << std::endl;
                    std::cout << "##                                                                          ##" << std::endl;
                    std::cout << "##           You go through the drawers and find a small key.               ##" << std::endl;
                    std::cout << "##               It might be able to open the footlocker.                   ##" << std::endl;
                    std::cout << "##                                                                          ##" << std::endl;
                    std::cout << "##############################################################################" << std::endl;
                    lockerKey = true;
                    player1.setScore(10); //add 10 to the player score
               }
               else
               {
                    std::cout << "##############################################################################" << std::endl;
                    std::cout << "##                                                                          ##" << std::endl;
                    std::cout << "##             You go through the drawers but it's empty now.               ##" << std::endl;
                    std::cout << "##               It might be able to open the footlocker.                   ##" << std::endl;
                    std::cout << "##                                                                          ##" << std::endl;
                    std::cout << "##############################################################################" << std::endl;
               }
               
               validInput = true;
               break;

          case 4://stop exploring
               return true;

          default://error msg

               std::cout << " Invalid entry! Only integers from 1-4 are allowed!" << std::endl;
               break;
          }

     }
     return false;
}

forcastleDeck::forcastleDeck()
{
     roomID = 4;
     Label = "THE FORCASTLE DECK";
     Description = "This raised deck covers the main deck at the bows of the ship. Many of the ships sails are controlled from here.";
     hintNorth = "(N) Hop in the small boat and lower it down to the sea               ";
     hintEast  = "(E) Cross the gangway to the quarter deck                            ";
}

mainDeck::mainDeck()
{
     roomID = 5;
     Label = "THE MAIN DECK";
     Description = "This deck is armed with a few cannons and in the middle is a large cargo hatch. ";
     hintNorth = "(N) Take the stairs up to the quarter deck                           ";
     hintSouth = "(S) Take the stairs down to the upper gun deck                       ";
     hintWest  = "(W) Climb up the main mast to the crow's nest                        ";
}

crowsNest::crowsNest()
{
     roomID = 6;
     Label = "THE CROW'S NEST";
     Description = "Located on the upper part of the main mast, the crow's nest is primarily used as a lookout point.";
     hintEast   = "(E) Climb down the main mast to go back to the main deck             ";
     hintExplore = "(X) Explore your surroundings                                        ";
     explore1    = " 1. A small chest                                                    ";
     explore2    = " 2. A book                                                           ";
     explore3    = " 3. Rope                                                             ";
     explorable = true;
}

bool crowsNest::exploreRoom(Player &player1)
{
     bool validInput = false;

     while (!validInput)
     {
          std::cout << std::endl;
          int choice = 0;

          choice = input_verify();

          switch (choice)
          {
          case 1://small chest
               clear_screen();

               if (!player1.spyglassFound)
               {
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##                 You open the chest and find a spyglass!                  ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;

                    std::cout << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##                **Spyglass has been added to your inventory**             ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    continue_fun();
                    clear_screen();
                    std::cout << " ################################################################################################" << std::endl;
                    std::cout << " ##                                                                                            ##" << std::endl;
                    std::cout << " ##    You use the spyglass and spot The Millenium Executioner coming up on the port side!     ##" << std::endl;
                    std::cout << " ##                                                                                            ##" << std::endl;
                    std::cout << " ##    Get to the forcastle deck and use the rope to lower the row boat into the sea!          ##" << std::endl;
                    std::cout << " ##                                                                                            ##" << std::endl;
                    std::cout << " ################################################################################################" << std::endl;
                    player1.spyglassFound = true;
                    player1.spyglass = true;
                    player1.setScore(100); //add 10 to the player score
               }
               else
               {
                    std::cout << " ################################################################################################" << std::endl;
                    std::cout << " ##                                                                                            ##" << std::endl;
                    std::cout << " ##    You use the spyglass and spot The Millenium Executioner coming up on the port side!     ##" << std::endl;
                    std::cout << " ##                                                                                            ##" << std::endl;
                    std::cout << " ##    Get to the forcastle deck and use the rope to lower the row boat into the sea!          ##" << std::endl;
                    std::cout << " ##                                                                                            ##" << std::endl;
                    std::cout << " ################################################################################################" << std::endl;
               }
        
               validInput = true;
               break;

          case 2://a book
               clear_screen();

               std::cout << " ##############################################################################" << std::endl;
               std::cout << " ##                                                                          ##" << std::endl;
               std::cout << " ##         You flip though the book...                                      ##" << std::endl;
               std::cout << " ##         You learn about international maritime signal flags.             ##" << std::endl;
               std::cout << " ##                                                                          ##" << std::endl;
               std::cout << " ##############################################################################" << std::endl;
               validInput = true;
               break;

          case 3://some rope
               clear_screen();

               if (!player1.ropeFound)
               {
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##                      You pick up the rope.                               ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##               **Rope has been added to your inventory**                  ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    player1.rope = true;
                    player1.ropeFound = true;
                    player1.setScore(10); //add 10 to the player score
               }
               else
               {
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##                      You already have some rope!                         ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
               }

               validInput = true;
               break;

          case 4://stop exploring
               return true;

          default://error msg

               std::cout << " Invalid entry! Only integers from 1-4 are allowed!" << std::endl;
               break;
          }
     }

     return false;
}

upperGunDeck::upperGunDeck()
{
     roomID = 7;
     Label = "THE UPPER GUN DECK";
     Description = "This deck is open to weather in the middle, on each side there are 15 cannons. 24-pounder cannons to be exact.";
     hintNorth = "(N) Take the stairs up to the main deck                              ";
     hintSouth = "(S) Take the stairs down to the middle gun deck                      ";

}

middleGunDeck::middleGunDeck()
{
     roomID = 8;
     Label = "THE MIDDLE GUN DECK";
     Description = "This deck is where most of the crew eats and sleeps. There are 14 cannons on each side. ";
     hintNorth = "(N) Take the stairs up to the upper gun deck                         ";
     hintWest  = "(W) Door the galley                                                  ";
     hintSouth = "(S) Take the stairs down to the lower gun deck                       ";
     hintEast  = "(E) Door to the officers' wardroom                                   ";
}

galley::galley()
{
     roomID = 9;
     Label = "THE GALLEY";
     Description = "This is where food is cooked and prepared.";
     hintEast  = "(E) Door to the middle gun deck                                      ";
     hintWest  = "(W) Go into the storage room                                         ";
}

wardroom::wardroom()
{
     roomID = 10;
     Label = "THE WARDROOM";
     Description = "Located at the stern of the ship, this room serves as the dining/living room for the officers. ";
     hintNorth   = "(N) Door to officer's cabin #1                                       ";
     hintEast    = "(E) Door to officer's cabin #2                                       ";
     hintSouth   = "(S) Door to officer's cabin #3                                       ";
     hintWest    = "(W) Door to middle gun deck                                          ";
}

officerCabin::officerCabin()
{
     roomID = 10;
     Label = "AN OFFICER'S CABIN";
     Description = "The sleeping quarters for an officer.";
     hintExplore = "(X) Explore your surroundings                                        ";
     explore1    = " 1. Check the cabinet                                                ";
     explore2    = " 2. Check the desk                                                   ";
     explore3    = " 3. Check under the bed                                              ";
     explorable = true;
}

bool officerCabin::exploreRoom(Player &player1)
{
     bool validInput = false;

     while (!validInput)
     {
          std::cout << std::endl;
          int choice = 0;

          choice = input_verify();

          switch (choice)
          {
          case 1://check the cabinet
               clear_screen();

               std::cout << " ##############################################################################" << std::endl;
               std::cout << " ##                                                                          ##" << std::endl;
               std::cout << " ##                    You check the cabinet...nothing.                      ##" << std::endl;
               std::cout << " ##                                                                          ##" << std::endl;
               std::cout << " ##############################################################################" << std::endl;
               validInput = true;
               break;

          case 2://check the desk
               clear_screen();

               std::cout << " ##############################################################################" << std::endl;
               std::cout << " ##                                                                          ##" << std::endl;
               std::cout << " ##                  You check the desk...nothing.                           ##" << std::endl;
               std::cout << " ##                                                                          ##" << std::endl;
               std::cout << " ##############################################################################" << std::endl;
               validInput = true;
               break;

          case 3://check under the bed
               clear_screen();
               if ((Label == "OFFICER'S CABIN # 2") && (!player1.brigKey))
               {
                    std::cout << "               || " << std::endl;
                    std::cout << "            ||/||___                ||" << std::endl;
                    std::cout << "            || /`   )____________ _ /|" << std::endl;
                    std::cout << "            ||/___ //_/_/_/_/_/_/||/ |" << std::endl;
                    std::cout << "            ||(___)/_/_/_/_/_/_/_||  |" << std::endl;
                    std::cout << "            ||     |_|_|_|_|_|_|_|| /|" << std::endl;
                    std::cout << "            ||     | | | | | | | ||/||" << std::endl;
                    std::cout << "            ||~~~~~~~~~~~~~~~~~~~||" << std::endl;
                    std::cout << "            ||                   ||" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##        You check under the bed...and find the key to the brig!           ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##         **Key to the Brig has been added to your inventory**             ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    player1.brigKey = true;
                    player1.setScore(10); //add 10 to the player score
               }
               else
               {
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##                 You check under the bed...nothing.                       ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
               }
               validInput = true;
               break;

          case 4://stop exploring
               return true;

          default://error msg

               std::cout << " Invalid entry! Only integers from 1-4 are allowed!" << std::endl;
               break;
          }
     }
     return false;
}

lowerGunDeck::lowerGunDeck()
{
     roomID = 11;
     Label = "THE LOWER GUN DECK";
     Description = "There are 15 cannons on each side. Lots of hammocks lay hung from the beams of this deck.";
     hintNorth = "(N) Stairs to the middle gun deck                                    ";
     hintSouth = "(S) Stairs to the orlop deck                                         ";
}

orlopDeck::orlopDeck()
{
     roomID = 12;
     Label = "THE ORLOP DECK";
     Description = "This deck overlaps the hold and is primarily used for storage and offices for some of the ship's crew.";
     hintNorth = "(N) Take the stairs up to the lower gun deck                         ";
     hintEast  = "(E) Door to the carpenters' workroom                                 ";
     hintSouth = "(S) Take the stairs down to the hold                                 ";
     hintWest  = "(W) Door leading to a hallway                                        ";
}

hallway::hallway()
{
     Label = "A HALLWAY";
     Description = "Just your standard corridor.";
}

theBrig::theBrig()
{
     roomID = 14;
     Label = "THE BRIG";
     Description = "The cells where prisoners are held. There is no light or sanitation. It's not a good place to be.";
     hintSouth   = "(S) Door back to the hallway                                         ";
}


infirmary::infirmary()
{
     roomID = 15;
     Label = "THE INFIRMARY";
     Description = "The ship's sick bay. Mostly used to treat gunshot and splinter wounds. Also to amputate limbs. ";
     hintEast    = "(E) Door back to the hallway                                         ";
     hintExplore = "(X) Explore your surroundings                                        ";
     explore1    = " 1. Medical cabinet                                                  ";
     explore2    = " 2. Check the barrel                                                 ";
     explore3    = " 3. Chest                                                            ";
     explorable = true;
}

bool infirmary::exploreRoom(Player &player1)
{

     bool validInput = false;

     while (!validInput)
     {
          std::cout << std::endl;
          int choice = 0;

          choice = input_verify();

          switch (choice)
          {
          case 1://medical cabinet
               clear_screen();
               player1.surgeonFight = true;
               if (player1.bandages < 10)
               {
                    player1.bandages += 5;
                   
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##     You look through the medical cabinet and find some bandages!         ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << std::endl;

                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##       **Bandages(5) has been added to your inventory**                   ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
               }
               else if (player1.bandages >= 10)
               {
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##               **There are no more bandages**                             ##" << std::endl;
                    std::cout << " ##  You will have to come back later when the Surgeon has restocked them.   ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    
               }
           
               validInput = true;
               break;

          case 2://barrel
          {
               clear_screen();

               std::cout << " ##############################################################################" << std::endl;
               std::cout << " ##                                                                          ##" << std::endl;
               std::cout << " ##         You dig through the barrel and find a wooden peg leg.            ##" << std::endl;
               std::cout << " ##                                                                          ##" << std::endl;
               std::cout << " ##############################################################################" << std::endl;

               bool validChoice = false;

               while (!validChoice)
               {
                    char choice;

                    std::cout << " Do you want to equip peg leg as your 2 handed melee weapon? (y/n): ";
                    choice = getUserYN();

                    if (choice == 'Y')
                    {
                         player1.equipWeapon(2); //equips wooden peg leg as weapon
                         validChoice = true;
                    }
                    else if (choice == 'N')
                    {
                         validChoice = true;
                    }

               }

               validInput = true;
               break;
          }
          case 3://chest
               clear_screen();

               std::cout << " ##############################################################################" << std::endl;
               std::cout << " ##                                                                          ##" << std::endl;
               std::cout << " ##        You open the chest and find nothing useful.                       ##" << std::endl;
               std::cout << " ##                                                                          ##" << std::endl;
               std::cout << " ##############################################################################" << std::endl;
               validInput = true;
               break;

          case 4://stop exploring
               return true;

          default://error msg
               std::cout << " Invalid entry! Only integers from 1-4 are allowed!" << std::endl;
               break;
          }
     }

     return false;
}

carpentersOffice::carpentersOffice()
{
     roomID = 16;
     Label = "THE CARPENTERS' WORKROOM";
     Description = "A room full of important tools to keep the ship afloat. ";
     hintWest    = "(W) Door back to the orlop deck                                      ";
}


theHold::theHold()
{
     roomID = 17;
     Label = "THE HOLD";
     Description = "Located at the very bottom of the ship, the hold is a giant warehouse. ";
     hintNorth   = "(N) Take stairs back to the orlop deck                               ";
     hintExplore = "(X) Explore your surroundings                                        ";
     explore1    = " 1. Weapon rack                                                      ";
     explore2    = " 2. Look through barrels                                             ";
     explore3    = " 3. Barrel of gunpowder                                              ";
     explorable = true;
}

bool theHold::exploreRoom(Player &player1)
{
     bool validInput = false;

     while (!validInput)
     {
          std::cout << std::endl;
          int choice = 0;

          choice = input_verify();

          switch (choice)
          {
               case 1://weapons rack
               {

                    clear_screen();

                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##                 It's time to arm yourself to the teeth!                  ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    continue_fun();

                    bool doneEquiping = false;
                    while (!doneEquiping)
                    {
                         clear_screen();
                         int weaponChoice = 0;

                         std::cout << "                                  WEAPONS RACK       " << std::endl;
                         std::cout << " ##############################################################################" << std::endl;
                         std::cout << " ##                                                                          ##" << std::endl;
                         std::cout << " ## CURRENT EQUIPED WEAPONS:                                                 ##" << std::endl;
                         std::cout << " ##                                                                          ##" << std::endl;
                         std::cout << " ##    Melee:  " << player1.meleeWeaponName << "##" << std::endl;
                         std::cout << " ##                                                                          ##" << std::endl;
                         std::cout << " ##    Ranged: " << player1.rangedWeaponName << "##" << std::endl;
                         std::cout << " ##                                                                          ##" << std::endl;
                         std::cout << " ## OPTIONS:                                                                 ##" << std::endl;
                         std::cout << " ##                                                                          ##" << std::endl;
                         std::cout << " ##    Melee:                                                                ##" << std::endl;
                         std::cout << " ##                                                                          ##" << std::endl;
                         std::cout << " ##         1: Someone's Wooden Peg Leg                                      ##" << std::endl;
                         std::cout << " ##                                                                          ##" << std::endl;
                         std::cout << " ##         2: Buckler + Cutlass                                             ##" << std::endl;
                         std::cout << " ##                                                                          ##" << std::endl;
                         std::cout << " ##         3: Buckler + Sailor's Knife                                      ##" << std::endl;
                         std::cout << " ##                                                                          ##" << std::endl;
                         std::cout << " ##         4: Scimitar                                                      ##" << std::endl;
                         std::cout << " ##                                                                          ##" << std::endl;
                         std::cout << " ##    Ranged:                                                               ##" << std::endl;
                         std::cout << " ##                                                                          ##" << std::endl;
                         std::cout << " ##         5: Flintlock Pistol                                              ##" << std::endl;
                         std::cout << " ##                                                                          ##" << std::endl;
                         std::cout << " ##         6: Grenadoes                                                     ##" << std::endl;
                         std::cout << " ##                                                                          ##" << std::endl;
                         std::cout << " ##############################################################################" << std::endl;
                         std::cout << std::endl << std::endl << std::endl;
                         std::cout << " Choose an option for information about the weapon." << std::endl;
                         weaponChoice = input_verify();

                         switch (weaponChoice)
                         {
                              case 1://peg leg
                              {
                                   char choice;

                                   clear_screen();
                                   std::cout << std::endl << " This Peg leg is a great blunt weapon that deals some moderate damage." ;
                                   std::cout << std::endl << " However, it is heavy and requires two hands to wield." << std::endl;
                                   std::cout << std::endl << " It also does not offer much value to defense." << std::endl;
                                   std::cout << std::endl << std::endl << std::endl;

                                   std::cout << std::endl << " Do you want to equip the peg leg as your melee weapon? (y/n) :" ;
                                   
                                   choice = getUserYN();
                                   
                                   if (choice == 'Y')
                                   {
                                        player1.equipWeapon(2);
                                        std::cout << std::endl << std::endl << std::endl;
                                        std::cout << std::endl << " Someone's Wooden Peg Leg has been equiped!" << std::endl;
                                   }
                                   
                                   break;
                              }
                              case 2: //bucker + cutlass
                              {
                                   char choice;

                                   clear_screen();
                                   std::cout << std::endl << " The Buckler, a small shield, is a simple yet effective weapon when combined with a sword." << std::endl;
                                   std::cout << std::endl << " The Cutlass is a short, thick sabre, with a sharpened slight curve. " << std::endl;
                                   std::cout << std::endl << " This combo will allow you to perform additional strikes in one turn!" << std::endl;
                                   std::cout << std::endl << " This combo will also grant you a better defensive value. " << std::endl;
                                   std::cout << std::endl << std::endl << std::endl;

                                   std::cout << std::endl << " Do you want to equip the Buckler and Cutlass as your melee weapons? (y/n) :" ;

                                   choice = getUserYN();

                                   if (choice == 'Y')
                                   {
                                        player1.equipWeapon(3);
                                        player1.equipWeapon(4);
                                        std::cout << std::endl << std::endl << std::endl;
                                        std::cout << std::endl << " Buckler and Cutlass has been equiped! You are now a \"SwashBuckler\"!" ;
                                   }

                                   break;
                              }
                              case 3: // buckler + sailor's knife
                              {
                                   char choice;

                                   clear_screen();
                                   std::cout << std::endl << " The Buckler, a small shield, is a simple yet effective weapon when combined with the knife." << std::endl;
                                   std::cout << std::endl << " The Sailor's Knife is just your standard small blade. It is useful for combat in tight spaces." << std::endl;
                                   std::cout << std::endl << " This combo will allow you to perform the most additional strikes in one turn than any other weapon. !" << std::endl;
                                   std::cout << std::endl << " However, the Sailor's Knife deals less damage than the Cutlass. " << std::endl;
                                   std::cout << std::endl << " This combo will also grant you a better defensive value. " << std::endl;
                                   std::cout << std::endl << std::endl << std::endl;

                                   std::cout << std::endl << " Do you want to equip the Buckler and Sailor's Knife as your melee weapons? (y/n) :" ;

                                   choice = getUserYN();

                                   if (choice == 'Y')
                                   {
                                        player1.equipWeapon(3);
                                        player1.equipWeapon(5);
                                        std::cout << std::endl << std::endl << std::endl;
                                        std::cout << std::endl << " Buckler and Sailor's Knife has been equiped! You are now a \"SwashBuckler\"!" << std::endl;
                                   }

                                   break;
                              }
                              case 4: //scimitar
                              {
                                   char choice;

                                   clear_screen();
                                   std::cout << std::endl << " The Scimitar is a deeply curved blade that almost forms a half circle." << std::endl;
                                   std::cout << std::endl << " Due to it's heavy weight, it requires two hands to wield and can be slow." << std::endl;
                                   std::cout << std::endl << " However, it does considerable damage!" << std::endl;
                                   std::cout << std::endl << " It also provides a good amount of defense in parry value." << std::endl;
                                   std::cout << std::endl << std::endl << std::endl;

                                   std::cout << std::endl << " Do you want to equip the Scimitar as your melee weapon? (y/n) : ";

                                   choice = getUserYN();

                                   if (choice == 'Y')
                                   {
                                        player1.equipWeapon(6);
                                        std::cout << std::endl << std::endl << std::endl;
                                        std::cout << std::endl << " The Scimitar has been equiped!" << std::endl;
                                   }

                                   break;
                              }
                              case 5://flintlock pistol
                              {
                                   char choice;

                                   clear_screen();
                                   std::cout << std::endl << " The flintlock Pistol is the dominant form of personal fire arms these days." << std::endl;
                                   std::cout << std::endl << " It deals an incredible amount of damage but has a reloading cooldown of 3 turns." << std::endl;
                                   std::cout << std::endl << std::endl << std::endl;

                                   std::cout << std::endl << " Do you want to equip the Flintlock Pistol as your ranged weapon? (y/n) :" ;

                                   choice = getUserYN();

                                   if (choice == 'Y')
                                   {
                                        player1.equipWeapon(7);
                                        std::cout << std::endl << std::endl << std::endl;
                                        std::cout << std::endl << " The Flintlock Pistol has been equiped!" << std::endl;
                                   }
                                   break;
                              }
                              case 6://grenados
                              {
                                   char choice;

                                   clear_screen();
                                   std::cout << std::endl << " The Grenadoe is a round cast iron hollow ball filled with gunpowder, and grape shot." << std::endl;
                                   std::cout << std::endl << " The cooldown is 5 turns but is useful for taking down tough enemies." << std::endl;
                                   std::cout << std::endl << " Be sure to take cover before use!" << std::endl;
                                   std::cout << std::endl << std::endl << std::endl;

                                   std::cout << std::endl << " Do you want to equip Grenadoes as your ranged weapon? (y/n) :" ;

                                   choice = getUserYN();

                                   if (choice == 'Y')
                                   {
                                        player1.equipWeapon(8);
                                        std::cout << std::endl << std::endl << std::endl;
                                        std::cout << std::endl << " Grenadoes have been equiped!" << std::endl;
                                   }
                                   break;
                              }

                              default:
                              {
                                   clear_screen();
                                   std::cout << " Invalid entry! Only integers from 1-7 are allowed!" << std::endl;
                                   continue_fun();
                                   break;
                              }
                         }

                         char choice;
                         std::cout << std::endl << std::endl << std::endl;
                         std::cout << std::endl << " Do you want to equip another weapon? (y/n) :";

                         choice = getUserYN();

                         if (choice == 'Y')
                         {
                              continue;
                         }
                         else if (choice == 'N')
                         {
                              doneEquiping = true;
                              return true;
                         }
                    }

                    validInput = true;
                    break;
               }

               case 2://look through barrels
               {
                    clear_screen();

                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##         You dig through the barrels and find nothing useful.             ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;

                    validInput = true;
                    break;
               }

               case 3://barrel of gunpowder
               {
                    clear_screen();

                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##           You find barrels of gunpowder. How dangerous...                ##" << std::endl;
                    std::cout << " ##               This could be useful for sabotage.                         ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    validInput = true;
                    break;
               }

               case 4://stop exploring
               {
                    return true;
               }
               default://error msg
               {
                    std::cout << " Invalid entry! Only integers from 1-4 are allowed!" << std::endl;
                    break;
               }
          }
     }

     return false;
}


storageRoom::storageRoom()
{
     Label = "A STORAGE ROOM";
     Description = "Just your standard storage room. ";
     hintEast    = "(E) Door back to the galley                                          ";
     hintExplore = "(X) Explore your surroundings                                        ";
     explore1    = " 1. Moldy bread                                                      ";
     explore2    = " 2. Flint and steel                                                  ";
     explore3    = " 3. Spice containers                                                 ";
     explorable = true;
}

bool storageRoom::exploreRoom(Player &player1)
{
     bool validInput = false;

     while (!validInput)
     {
          std::cout << std::endl;
          int choice = 0;

          choice = input_verify();

          switch (choice)
          {
          case 1://moldy bread
               clear_screen();

               std::cout << " ##############################################################################" << std::endl;
               std::cout << " ##                                                                          ##" << std::endl;
               std::cout << " ##                    You decide to not eat it.                             ##" << std::endl;
               std::cout << " ##                                                                          ##" << std::endl;
               std::cout << " ##############################################################################" << std::endl;
               std::cout << std::endl;
               std::cout << " ##############################################################################" << std::endl;
               std::cout << " ##                                                                          ##" << std::endl;
               std::cout << " ##                     You find a Sailor's knife!                           ##" << std::endl;
               std::cout << " ##                                                                          ##" << std::endl;
               std::cout << " ##############################################################################" << std::endl;

               std::cout << std::endl << " Do you want to equip the Sailor's Knife as your melee weapon? (y/n) :" ;

               choice = getUserYN();

               if (choice == 'Y')
               {
                    player1.equipWeapon(5);
                    std::cout << std::endl << std::endl << std::endl;
                    std::cout << std::endl << " Sailor's Knife has been equiped!" << std::endl;
               }

               validInput = true;
               break;

          case 2://flint and steel
               clear_screen();

               if (!player1.flintSteel)
               {
                    std::cout << "##############################################################################" << std::endl;
                    std::cout << "##                                                                          ##" << std::endl;
                    std::cout << "##        You pick up the flint and steel. This could be useful.            ##" << std::endl;
                    std::cout << "##                                                                          ##" << std::endl;
                    std::cout << "##############################################################################" << std::endl;
                    std::cout << std::endl;
                    std::cout << "##############################################################################" << std::endl;
                    std::cout << "##                                                                          ##" << std::endl;
                    std::cout << "##           **Flint and steel has been added to your inventory**           ##" << std::endl;
                    std::cout << "##                                                                          ##" << std::endl;
                    std::cout << "##############################################################################" << std::endl;
                    player1.flintSteel = true;
                    player1.setScore(10); //add 10 to the player score
               }
               else
               {
                    std::cout << "##############################################################################" << std::endl;
                    std::cout << "##                                                                          ##" << std::endl;
                    std::cout << "##               You already have the flint and steel.                      ##" << std::endl;
                    std::cout << "##                                                                          ##" << std::endl;
                    std::cout << "##############################################################################" << std::endl;
               }

               

               validInput = true;
               break;

          case 3://spice containers
               clear_screen();

               std::cout << "##############################################################################" << std::endl;
               std::cout << "##                                                                          ##" << std::endl;
               std::cout << "##  You look through the containers and decide to take some cookies.        ##" << std::endl;
               std::cout << "##                                                                          ##" << std::endl;
               std::cout << "##############################################################################" << std::endl;
               std::cout << std::endl;
               std::cout << "##############################################################################" << std::endl;
               std::cout << "##                                                                          ##" << std::endl;
               std::cout << "##            **Cookies have been added to your inventory**                 ##" << std::endl;
               std::cout << "##                                                                          ##" << std::endl;
               std::cout << "##############################################################################" << std::endl;
               player1.cookies = true;
               validInput = true;
               break;

          case 4://stop exploring
               return true;

          default://error msg

               std::cout << "Invalid entry! Only integers from 1-4 are allowed!" << std::endl;
               break;
          }
     }

     return false;
}

exitRoom::exitRoom()
{
     roomID = 20;
     Label = "A TINY ROW BOAT";
     Description = "You use the rope to repair the lowering mechanism of the escape boat and get in.";
     hintNorth = "(N) Row towards The Millenium Executioner                            ";
}

Room * buildShip(Room** shipMap)
{
     Room* shipExit = new Room();


     shipMap[0] = new poopDeck();
     shipMap[1] = new quarterDeck();
     shipMap[2] = new forcastleDeck();
     shipMap[3] = new hallway();
     shipMap[4] = new captainCabin();
     shipMap[5] = new captainDining();
     shipMap[6] = new mainDeck();
     shipMap[7] = new crowsNest();
     shipMap[8] = new upperGunDeck();
     shipMap[9] = new middleGunDeck();
     shipMap[10] = new galley();
     shipMap[11] = new storageRoom();
     shipMap[12] = new wardroom();
     shipMap[13] = new officerCabin();
     shipMap[14] = new officerCabin();
     shipMap[15] = new officerCabin();
     shipMap[16] = new lowerGunDeck();
     shipMap[17] = new orlopDeck();
     shipMap[18] = new hallway();
     shipMap[19] = new theBrig();
     shipMap[20] = new infirmary();
     shipMap[21] = new carpentersOffice();
     shipMap[22] = new theHold();
     shipMap[23] = new exitRoom();
     shipMap[24] = shipExit;

     //The poop deck
     shipMap[0]->South = shipMap[1];

     //The quarter deck
     shipMap[1]->North = shipMap[0];
     shipMap[1]->East = shipMap[3];
     shipMap[1]->South = shipMap[6];
     shipMap[1]->West = shipMap[2];

     //The forcastle deck
     shipMap[2]->East = shipMap[1];
     shipMap[2]->North = shipMap[23];

     //The hallway #1
     shipMap[3]->North = shipMap[4];
     shipMap[3]->East = shipMap[5];
     shipMap[3]->West = shipMap[1];
     shipMap[3]->hintWest  = "(W) Door to the quarter deck                                         ";
     shipMap[3]->hintNorth = "(N) Take the stairs up to the Captain's cabin                        ";
     shipMap[3]->hintEast  = "(E) Door to the Captain's dining room                                ";

     //The captain's quarters
     shipMap[4]->South = shipMap[3];

     //The captain's dining room
     shipMap[5]->West = shipMap[3];

     //The main deck
     shipMap[6]->North = shipMap[1];
     shipMap[6]->South = shipMap[8];
     shipMap[6]->West = shipMap[7];

     //The crow's nest
     shipMap[7]->East = shipMap[6];

     //The upper gun deck
     shipMap[8]->North = shipMap[6];
     shipMap[8]->South = shipMap[9];

     //The middle gun deck
     shipMap[9]->North = shipMap[8];
     shipMap[9]->East = shipMap[12];
     shipMap[9]->South = shipMap[16];
     shipMap[9]->West = shipMap[10];

     //The galley
     shipMap[10]->East = shipMap[9];
     shipMap[10]->West = shipMap[11];

     //The storage room
     shipMap[11]->East = shipMap[10];

     //The Wardroom
     shipMap[12]->North = shipMap[14];
     shipMap[12]->East = shipMap[13];
     shipMap[12]->South = shipMap[15];
     shipMap[12]->West = shipMap[9];

     //The officerCabin 2
     shipMap[13]->West = shipMap[12];
     shipMap[13]->Label = "OFFICER'S CABIN # 2";
     shipMap[13]->hintWest = "(W) Door to the wardroom                                             ";

     //The officerCabin 1
     shipMap[14]->South = shipMap[12];
     shipMap[14]->Label = "OFFICER'S CABIN # 1";
     shipMap[14]->hintSouth = "(S) Door to the wardroom                                             ";

     //The officerCabin 3
     shipMap[15]->North = shipMap[12];
     shipMap[15]->Label = "OFFICER'S CABIN # 3";
     shipMap[15]->hintNorth = "(N) Door to the wardroom                                             ";

     //The lower gun deck
     shipMap[16]->North = shipMap[9];
     shipMap[16]->South = shipMap[17];

     //The orlop deck
     shipMap[17]->North = shipMap[16];
     shipMap[17]->East = shipMap[21];
     shipMap[17]->South = shipMap[22];
     shipMap[17]->West = shipMap[18];

     //the hallway #2
     shipMap[18]->North = shipMap[19];
     shipMap[18]->East = shipMap[17];
     shipMap[18]->West = shipMap[20];
     shipMap[18]->roomID = 13;
     shipMap[18]->hintNorth = "(N) Door to the brig                                                 ";
     shipMap[18]->hintWest  = "(W) Door to the infirmary                                            ";
     shipMap[18]->hintEast  = "(E) Door to orlop deck                                               ";

     //the brig
     shipMap[19]->South = shipMap[18];

     // the infirmary
     shipMap[20]->East = shipMap[18];

     //the carpenters office
     shipMap[21]->West = shipMap[17];

     // the hold
     shipMap[22]->North = shipMap[17];

     //ship exit
     shipMap[23]->North = shipMap[24];

     return shipExit;
}


