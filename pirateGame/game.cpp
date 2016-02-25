#include "game.h"
#include "utility.h"
#include "map.h"

Game::Game()
{
     phase2 = false;
}

void Game::runGame(int mode)   //the main game driver
{
     //create instances of all the needed classes except npcs. 
     DrawMap Map;
     Player player1;
     Combat combat;
     Room* currentRoom;
     Room* shipMap[24];  //array to hold all the rooms of the ship
     Room* shipExit = buildShip(shipMap); //build the ship map

     //Had to put this here because the flip server wanted it here but visual studio did not need it here?
     player1.bandages = 0; 
     //game difficuties options as passed from the main menu
     if (mode == 1)//easy mode
     {
          timer = 220;
          player1.healthPoints = 300;
          player1.maxHealthPoints = 300;
          player1.equipWeapon(7);//equip pistol
          Map.drawDebugMap(); //Draw the entire map at once 
          player1.map = true; //allow the player to access the map option
     }
     else if (mode == 2)//normal mode
     {
          timer = 180;
          player1.healthPoints = 250;
          player1.maxHealthPoints = 250;
          player1.map = true;
     }
     else if (mode == 3)//hard mode
     {
          timer = 120;
     }
     else if (mode == 4) //debug mode 
     {
          timer = 220;
          player1.healthPoints = 600;
          player1.maxHealthPoints = 600;
          player1.equipWeapon(7);//equip pistol
          player1.equipWeapon(3);//equip buckler
          player1.equipWeapon(4);//equip cutlass
          Map.drawDebugMap();
          player1.map = true;
          player1.rope = true;
          player1.spyglass = true;
          player1.rope = true;
          player1.brigKey = true;
          player1.officerKey = true;
          player1.flintSteel = true;
          player1.cookies = true;
     }

     printIntro(player1); //dsiplay the intro story and get the player's name
     
     currentRoom = shipMap[6];

     deny_entry: //goto label for if the room is locked and player does not have the key

     //main game loop
     while (currentRoom != shipExit)
     {
          char nextChoice;
          Room* nextRoom = NULL;

          if (player1.map) //if player has the map in inventory
          {
               Map.drawRoom(currentRoom->roomID); //draws each room to the map as the player visits it
          }

          storyEventCheck(player1, *currentRoom, combat); //checks to see for any story line progression events

          while (nextRoom == NULL)
          {

               //check for player dead status
               if (player1.dead)
               {
                    gameOver(player1); //goto to the game over screen
                    return;
               }

               if (timer <= 0)
               {
                    if (!phase2)//initiate phase 2 
                    {
                         phase2 = true;
                         phaseMessage();//warn the player that ship is going to sink
                         timer = 80;
                    }
                    else
                    {
                         std::cout << std::endl << std::endl;
                         std::cout << " You did not make it off the ship in time." << std::endl;
                         continue_fun();
                         player1.setStatus(3); //set status of player to dead
                         gameOver(player1);
                         return;
                    }
               }


               if (player1.bleeding) //if the player has the bleeding debuff
               {
                    if (bleedMsgTimer == player1.moveCount)
                    {
                         clear_screen();
                         player1.healthPoints--; 
                         bleedMsgTimer = (player1.moveCount + 4); //will alert the player only every 4 moves 
                         std::cout << std::endl << std::endl;
                         std::cout << " You lose 1 health point due to bleeding. Apply a bandage!" << std::endl;
                         continue_fun();
                    }
                    else if (bleedMsgTimer < player1.moveCount)  //to make sure that the bleed timer msg gets enabled
                    {
                         bleedMsgTimer = (player1.moveCount + 1); 
                    } 
               }

               if (player1.healthy && player1.surgeonDead) //this is the passive regen buff after killing the surgeon
               {
                    player1.recoverHealth(2); //heals for 2 each move
               }

               clear_screen();
               displayGui(player1, *currentRoom); //print the game options and gui
               nextChoice = getUserChoice();

               if (nextChoice == 'N')
               {
                    nextRoom = currentRoom->North;
               }
               else if (nextChoice == 'E')
               {
                    nextRoom = currentRoom->East;
               }
               else if (nextChoice == 'S')
               {
                    nextRoom = currentRoom->South;
               }
               else if (nextChoice == 'W')
               {
                    nextRoom = currentRoom->West;
               }
               else if (nextChoice == 'X')//explore surroundings
               {
                    if (currentRoom->explorable) //check to see if the current room can even be explored
                    {
                         displayExploreGui(player1, *currentRoom);   //if it is, execute that specific room's options 
                    }
                    else //display error msg if room can not be explored
                    {
                         std::cout << " There is nothing of importance to explore in this area." << std::endl;
                         continue_fun();
                    }

                    continue; //skip back to start of loop to make sure timer does not get affected 
                    
               }
               else if (nextChoice == 'I') //check inventory
               {
                    player1.setInventoryStatus();  //sets the display labels for the different items depending if the player has them or not
                    displayInventoryGui(player1);//display the inventory
                    continue;
               }
               else if (nextChoice == 'M')//display the map
               {
                    if (player1.map) //checks to see if the player has actually found the map
                    {
                         clear_screen();
                         Map.printMap();
                         continue_fun();
                         player1.setScore(5); //add 5 to the player score
                    }
                    else
                    {
                         std::cout << std::endl << std::endl;
                         std::cout << " You do not have a map yet. Did you try searching the Captain's cabin?" << std::endl;
                         continue_fun();
                    }

                    continue; //skip back to start of loop to make sure timer does not get affected 
               }
               else if (nextChoice == 'H') //heal with a bandage
               {
                    if (player1.bandages >= 1)
                    {
                         if (player1.healthPoints + 10 <= player1.maxHealthPoints)
                         {
                              player1.recoverHealth(10);
                              player1.bandages--;
                              player1.setStatus(1); //stop bleeding and set status to healthy
                              std::cout << std::endl << std::endl;
                              std::cout << " You quickly apply a bandage and stop any bleeding!" << std::endl;
                              std::cout << " You recover 10 healthpoints." << std::endl;
                         }
                         else if (player1.healthPoints >= player1.maxHealthPoints)
                         {
                              std::cout << std::endl << std::endl;
                              std::cout << " You quickly apply a bandage and stop any bleeding!" << std::endl;
                              player1.setStatus(1); //stop bleeding and set status to healthy
                              player1.bandages--;
                         }
                         else
                         {
                              std::cout << std::endl << std::endl;
                              std::cout << " You quickly apply a bandage and stop any bleeding!" << std::endl;
                              std::cout << " You recover some healthpoints." << std::endl;
                              player1.recoverHealth(10);
                              player1.bandages--;
                              player1.setStatus(1); //stop bleeding and set status to healthy
                         }
                         continue_fun();
                    }
                    else
                    {
                         std::cout << std::endl << std::endl;
                         std::cout << " You do not have any bandages! Try finding some in the infirmary." << std::endl;
                         continue_fun();
                    }
                    continue;
               }
               else if (nextChoice == 'Q')//quit to main menu
               {
                    clear_screen();
                    char choice;
                    std::cout << " Are you sure you want to quit this game? (All progress will be lost!) (y/n): ";
                    choice = getUserYN();

                    if (choice == 'Y')
                    {
                         return;
                    }
                    else
                    {
                         continue;
                    }
               }

               if (nextRoom != NULL)
               {
                    bool roomLocked = roomCheck(player1, *nextRoom, combat); //checks to see that the room the user picked is not a currently locked room

                    if (roomLocked)//if the room is locked for now it will jump back to the start of the loop 
                    {
                         goto deny_entry;
                    }
               }
 
               if (nextRoom == NULL) //if the user enters any characters that are not allowed
               {
                    std::cout << std::endl << std::endl;
                    std::cout << " You can't do that! Try something different." << std::endl;
                    continue_fun();
               }
          }

         
     
          player1.setPreviousLocation(currentRoom->Label); //to help the player keep track of where they are
          currentRoom = nextRoom;

          timer -= 2; //decrease timer each time player moves to a new room
          player1.moveCount++; //currently used for bleed timers
     }

     //Winning message!
     gameOver(player1); 
     
     for (int i = 0; i < 24; i++)
     {
          delete(shipMap[i]);
     }
}

void Game::storyEventCheck(Player &player1, Room  &currentRoom, Combat &combat)
{

     if ((currentRoom.roomID == 9) && (!player1.cookieDead) && (player1.cookies)) //galley cookie event
     {
          clear_screen();
          std::cout << "##############################################################################" << std::endl;
          std::cout << "##                                                                          ##" << std::endl;
          std::cout << "##         You have been caught by the ship's cook, \"Cookie\"!               ##" << std::endl;
          std::cout << "##                                                                          ##" << std::endl;
          std::cout << "##############################################################################" << std::endl;
          std::cout << std::endl;
          continue_fun();

          NPC * Enemy;
          Enemy = new PirateCook();
          combat.combatSim(player1, *Enemy);
          delete Enemy;
     }


     if ((currentRoom.roomID == 15) && (!player1.surgeonDead) && (player1.surgeonFight)) // Infirmary surgeon battle event
     {
          clear_screen();
          std::cout << "##############################################################################" << std::endl;
          std::cout << "##                                                                          ##" << std::endl;
          std::cout << "##  Pirate Dr. Macon Read:                                                  ##" << std::endl;
          std::cout << "##                                                                          ##" << std::endl;
          std::cout << "##         \"AHA! I found the one who has been stealing my bandages!\"        ##" << std::endl;
          std::cout << "##                                                                          ##" << std::endl;
          std::cout << "##############################################################################" << std::endl;
          std::cout << std::endl;
          continue_fun();

          NPC * Enemy;
          Enemy = new PirateSurgeon();
          combat.combatSim(player1, *Enemy);
          delete Enemy;
     }
         

     if ((currentRoom.roomID == 14) && (!player1.hugoSaved)) // rescue hugo event
     {
          clear_screen();
          std::cout << "##############################################################################" << std::endl;
          std::cout << "##                                                                          ##" << std::endl;
          std::cout << "##                    You unlock the door to the brig.                      ##" << std::endl;
          std::cout << "##    You check the cells and find a badly beaten \"Ham-Hands Hugo\".         ##" << std::endl;
          std::cout << "##                                                                          ##" << std::endl;
          std::cout << "##############################################################################" << std::endl;
          std::cout << std::endl;
          continue_fun();
          clear_screen();

          std::cout << std::endl << " Ham-Hands Hugo: \"" <<player1.getName() <<", is it really you!?\" "<< std::endl;
          std::cout << std::endl << " Ham-Hands Hugo: \"I can't beleive it...\"" << std::endl;
          std::cout << std::endl << " " <<player1.getName()<< ": \"Believe it! Now get up! We need to get out of here!\"" << std::endl;
          std::cout << std::endl << " Ham-Hands Hugo: \"Aye! What did you do to the guard? I could sure use his boots.\"" << std::endl;
          std::cout << std::endl << " " << player1.getName() << ": \"What guard?\"" << std::endl;
          std::cout << std::endl;
          continue_fun();

          clear_screen();
          std::cout << " ##############################################################################" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##  Pirate Warden: \"WHO DARES RELEASE MY PRISONER?!?!?!\"                    ##" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##           \"We'll hang ye by the gibbet, ye mutinous sea dog...\"          ##" << std::endl;
          std::cout << " ##           \"Ye'll meet the rope's end for that, me bucko!\"                ##" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##############################################################################" << std::endl;
          std::cout << std::endl;
          continue_fun();

          NPC * Enemy;
          Enemy = new PirateWarden();
          combat.combatSim(player1, *Enemy);
          delete Enemy;
     }

     if ((currentRoom.roomID == 17) && (player1.hugoSaved) && (!player1.sabotageSet)) //the hold event before sabotage
     {
          clear_screen();
          std::cout << " ##############################################################################" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##  Ham-Hands Hugo explores a nearby weapons rack and arms himself.         ##" << std::endl;
          std::cout << " ## \"If you haven't already, arm yourself!\" (Explore your surroundings)      ##" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##   \"Also, let's set a fuse to these gun powder barrels.\"                  ##" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##############################################################################" << std::endl;
          std::cout << std::endl;
          continue_fun();

          if (player1.flintSteel) //if the player already has flint and steel in the inventory
          {
               clear_screen();
               std::cout << " ##############################################################################" << std::endl;
               std::cout << " ##                                                                          ##" << std::endl;
               std::cout << " ##       You and Hugo set up a long fuse to the gun powder barrels.         ##" << std::endl;
               std::cout << " ##                                                                          ##" << std::endl;
               std::cout << " ##        Better choose the weapons you want before you light it!           ##" << std::endl;
               std::cout << " ##        There will be no coming back here afterwards!                     ##" << std::endl;
               std::cout << " ##                                                                          ##" << std::endl;
               std::cout << " ##############################################################################" << std::endl;
               std::cout << std::endl;
               continue_fun();
               player1.sabotageSet = true;
          }
          else //tell the player where to find the flint and steeel
          {
               clear_screen();
               std::cout << " ##############################################################################" << std::endl;
               std::cout << " ##                                                                          ##" << std::endl;
               std::cout << " ##        It looks like your missing a way to light the fuse.               ##" << std::endl;
               std::cout << " ##                                                                          ##" << std::endl;
               std::cout << " ##     You can find a flint and steel in the galley's storage room!         ##" << std::endl;
               std::cout << " ##                                                                          ##" << std::endl;
               std::cout << " ##############################################################################" << std::endl;
               std::cout << std::endl;
               continue_fun();
          }
     }

     if ((currentRoom.roomID == 12) && (player1.sabotageSet) && (!player1.holdLocked)) //its time to lock the hold again and to start phase 2 if timer still has not
     {
          clear_screen();
          std::cout << " ##########################################################################################" << std::endl;
          std::cout << " ##                                                                                      ##" << std::endl;
          std::cout << " ##           You and Hugo light the fuse and run out to the orlop deck!                 ##" << std::endl;
          std::cout << " ##                                                                                      ##" << std::endl;
          std::cout << " ##      BOOOM! The gun powder barrels explode and you hear the hull creaking loudly.    ##" << std::endl;
          std::cout << " ##                                                                                      ##" << std::endl;
          std::cout << " ##      Everyone must have heard it. Looks like you will have to fight your way out!    ##" << std::endl;
          std::cout << " ##                                                                                      ##" << std::endl;
          std::cout << " ##      Make your way to the Crow's nest to figure out your escape route!               ##" << std::endl;
          std::cout << " ##                                                                                      ##" << std::endl;
          std::cout << " ##########################################################################################" << std::endl;
          std::cout << std::endl;
          player1.setScore(100); //add 100 to the player score
          player1.holdLocked = true; //lock the hold from entry since it's been blown up
          continue_fun();



          if (!phase2) //intiate phase 2
          {
               std::cout << std::endl << std::endl << std::endl;
               phase2 = true;
               timer = 80;
               std::cout << " ##################################################################" << std::endl;
               std::cout << " ##                                                              ##" << std::endl;
               std::cout << " ##      You hear cannon fire off in the distance.               ##" << std::endl;
               std::cout << " ##                                                              ##" << std::endl;
               std::cout << " ##      The full scale attack on the Pirate Armada has begun.   ##" << std::endl;
               std::cout << " ##                                                              ##" << std::endl;
               std::cout << " ##      It's time to get off the ship before it's too late!     ##" << std::endl;
               std::cout << " ##                                                              ##" << std::endl;
               std::cout << " ##################################################################" << std::endl;
               continue_fun();
          }
     }

     if ((currentRoom.roomID == 6) && (!player1.quarterMasterDead)) //crows nest access
     {
          clear_screen();
          std::cout << " ##############################################################################" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ## Pirate QuarterMaster Bernard the Pale:                                   ##" << std::endl;
          std::cout << " ##  \"Dance with Jack Ketch, ye grog-snarfing swab... Belay that talk!\"      ##" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##############################################################################" << std::endl;
          continue_fun();

          NPC * Enemy;
          Enemy = new PirateQuarterMaster();
          combat.combatSim(player1, *Enemy);
          delete Enemy;
     }

     if ((currentRoom.roomID == 7) || (currentRoom.roomID == 8) || (currentRoom.roomID == 11)) //the gun decks
     {
          if (phase2) //random chance of having to fight npcs
          {
               //1 out of 3 chance that npc attacks you
               int aggroChance = (int)(rand() % 5) + 1;

               if (aggroChance == 2)
               {
                    clear_screen();
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##                       Pirate sailor engages you!                         ##" << std::endl;
                    std::cout << " ##       \"We'll send ye to Davy Jones' locker, ye scalawag parrot...\"       ##" << std::endl;
                    std::cout << " ##                    \"Yo ho ho an' a bottle o' rum!\"                       ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    continue_fun();

                    NPC * Enemy;
                    Enemy = new PirateSailor();
                    combat.combatSim(player1, *Enemy);
                    delete Enemy;
               }             
          }
     }

     if ((currentRoom.roomID == 5) || (currentRoom.roomID == 7))//main and quarter deck
     {
          if (phase2) //random chance of having to fight npcs
          {
               //1 out of 3 chance that npc attacks you
               int aggroChance = (int)(rand() % 5) + 1;

               if (aggroChance == 2)
               {
                    clear_screen();
                    std::cout << " ##############################################################################" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##                   Pirate Officer engages you!                            ##" << std::endl;
                    std::cout << " ##  \"We'll rip and burn yer Jolly Roger, ye scrappy kraken... Blast ye!\"    ##" << std::endl;
                    std::cout << " ##                  \"Yo ho ho an' a bottle o' rum!\"                         ##" << std::endl;
                    std::cout << " ##                                                                          ##" << std::endl;
                    std::cout << " ##############################################################################" << std::endl;
                    continue_fun();

                    NPC * Enemy;
                    Enemy = new PirateOfficer();
                    combat.combatSim(player1, *Enemy);
                    delete Enemy;
               }
          }
     }
}


bool Game::roomCheck(Player &player1, Room  &nextRoom, Combat &combat) //checks to see if the player has satisfied the conditions to enter the room
{
     if ((nextRoom.roomID == 10) && (!player1.officerKey)) //Wardroom and the player does not hold the officer key
     {
          clear_screen();
          std::cout << " ##############################################################################" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##           The Officer's wardroom and cabins are locked!                  ##" << std::endl;
          std::cout << " ##             Try to get the key from a Pirate officer.                    ##" << std::endl;
          std::cout << " ##            An officer was seen alone on the poop deck.                   ##" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##############################################################################" << std::endl;
          continue_fun();
          return true;
     }

     if ((nextRoom.roomID == 14) && (!player1.brigKey)) //the brig and no key
     {
          clear_screen();
          std::cout << " ##############################################################################" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##                 The door to the brig is locked!                          ##" << std::endl;
          std::cout << " ##       Try to find the key in one of the Pirate officer's cabin.          ##" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##############################################################################" << std::endl;
          continue_fun();
          return true;
     }

     if ((nextRoom.roomID == 17) && (!player1.carpenterAxe))//the hold and no axe
     {
          clear_screen();
          std::cout << " ########################################################################" << std::endl;
          std::cout << " ##                                                                    ##" << std::endl;
          std::cout << " ##                The door to the hold is locked!                     ##" << std::endl;
          std::cout << " ##             You don't have time to find the key.                   ##" << std::endl;
          std::cout << " ##      You grab a nearby carpenter's axe and hack at the door.       ##" << std::endl;
          std::cout << " ##                                                                    ##" << std::endl;
          std::cout << " ########################################################################" << std::endl;
          std::cout << std::endl << std::endl;
          std::cout << " ########################################################################" << std::endl;
          std::cout << " ##                                                                    ##" << std::endl;
          std::cout << " ##                     The lock breaks off!                           ##" << std::endl;
          std::cout << " ##             Now try opening the door to the hold.                  ##" << std::endl;
          std::cout << " ##                                                                    ##" << std::endl;
          std::cout << " ########################################################################" << std::endl;
          player1.carpenterAxe = true;
          player1.setScore(10); //add 10 to the player score
          continue_fun();
          return true;
     }

     if ((nextRoom.roomID == 20) && (!player1.rope) && (!phase2))//ship exit...must have rope and phase2 must be enabled
     {
          clear_screen();
          std::cout << " ##############################################################################" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##                 You still have a mission to complete!                    ##" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##############################################################################" << std::endl;
          continue_fun();
          return true;
     }


     if ((nextRoom.roomID == 6) && (!phase2))//Crow's nest
     {
          clear_screen();
          std::cout << " ##############################################################################" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##    Pirate QuarterMaster Bernard the Pale: \"Get back to work you swab!\"   ##" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##############################################################################" << std::endl;
          continue_fun();
          return true;
     }

     if ((nextRoom.roomID == 17) && (player1.holdLocked))//lock the hold since sabotage happened
     {
          clear_screen();
          std::cout << " ##############################################################################" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##            There is no hold since it has been sabotaged!                 ##" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##############################################################################" << std::endl;
          continue_fun();
          return true;
     }

     if ((nextRoom.roomID == 4) && (phase2) && (!player1.captainDead)) //phase 2 captain fight before being able to escape!
     {
          clear_screen();
          std::cout << " ##############################################################################" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##            Pirate Captain Rupert Scarr stands in your way.               ##" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##                  You will have to defeat him first.                      ##" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##############################################################################" << std::endl;

          char choice;
          std::cout << std::endl << " Are you ready to battle the Pirate Captain? (y/n) :";

          choice = getUserYN();

          if (choice == 'Y')
          {
               NPC * Enemy;
               Enemy = new PirateCaptain();
               combat.combatSim(player1, *Enemy);
               delete Enemy;

               if (player1.captainDead)
               {
                    return false;
               }
               else
               {
                    return true;
               }
          }
          if (choice == 'N')
          {
               std::cout << std::endl << " Right! You better make sure you are at full health and totally ready!" << std::endl;
               continue_fun();
               return true;
          }
     }

     if ((nextRoom.roomID == 20) && (!player1.rope) && (phase2)) //need the rope to escape off the ship
     {
          clear_screen();
          std::cout << " ##############################################################################" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##          You need Rope to be able to lower the small boat!               ##" << std::endl;
          std::cout << " ##                 Look for some at the Crow's Nest!                        ##" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##############################################################################" << std::endl;
          continue_fun();
          return true;
     }

     return false;
}

void Game::displayGui(Player player1, Room  currentRoom)
{
     std::string healOption;
     
     std::cout << " Name: " << player1.getName() << std::endl;
     std::cout << std::endl;
     std::cout << " Health Points: " << player1.getHealth() << "/"<<player1.getMaxHealthPoints()<<"     Status: "<< player1.getStatus() << std::endl;
     std::cout << std::endl;

     if (!phase2)
     {
          std::cout << " Pocketwatch: Time remaining until full scale attack: " << timer << " minutes." << std::endl;
     }
     else
     {
          std::cout << " Pocketwatch: Time remaining until ship sinks: " << timer << " minutes." << std::endl;
     }


     if (player1.bandages >= 1) //if player has at least one bandage
     {
          healOption = " (H) Heal yourself or stop bleeding by applying a bandage              ";
     }
     else
     {
          healOption = "                                                                       ";
     }

     std::cout << std::endl;
     std::cout << " Previous Location: " << player1.getPreviousLocation() << std::endl;
     std::cout << std::endl;
     std::cout << " Current Location:  " << currentRoom.Label << std::endl;
     std::cout << std::endl;
     std::cout << " Location Description: " << currentRoom.PrintDescription() << std::endl;
     std::cout << std::endl << std::endl;
     std::cout << "                              " << currentRoom.Label  << std::endl;
     std::cout << " ##############################################################################" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ## Movement:                                                                ##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##    " <<currentRoom.hintNorth <<" ##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##    " << currentRoom.hintEast << " ##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##    " << currentRoom.hintSouth << " ##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##    " << currentRoom.hintWest << " ##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ## Actions:                                                                 ##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##   "<<healOption <<"##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##    " << currentRoom.hintExplore << " ##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##    " << player1.mapOption() <<" ##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##    (I) Check inventory                                                   ##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##    (Q) Quit to main menu                                                 ##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##############################################################################" << std::endl;
     std::cout << std::endl;
}


void Game::displayExploreGui(Player &player1, Room  &currentRoom)
{
     bool done = false;

     while (!done)
     {

          clear_screen();
          std::cout << "                       EXPLORING THE SURROUNDINGS" << std::endl;
          std::cout << " ##############################################################################" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ## You take a look around and see...                                        ##" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##    " << currentRoom.explore1 << " ##" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##    " << currentRoom.explore2 << " ##" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##    " << currentRoom.explore3 << " ##" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##    (4) Stop Exploring                                                    ##" << std::endl;
          std::cout << " ##                                                                          ##" << std::endl;
          std::cout << " ##############################################################################" << std::endl;
          std::cout << std::endl;

          std::cout << " What do you want to interact with?" << std::endl;
          done = currentRoom.exploreRoom(player1);
          player1.setScore(5); //add 5 to the player score

          if (!done)
          {
               continue_fun();
          }
     }
}

void Game::displayInventoryGui(Player &player1)
{
     player1.setInventoryStatus();
     clear_screen();
     std::cout << "                               CURRENT INVENTORY" << std::endl;
     std::cout << " ##############################################################################" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ## You find a place to hide and look inside your bag...                     ##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ## WEAPONS:                                                                 ##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##    Melee:  " <<player1.meleeWeaponName << "##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##    Ranged: " <<player1.rangedWeaponName << "##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ## ITEMS:                                                                   ##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##    Slot 1: " <<player1.slot1 << "##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##    Slot 2: " << player1.slot2 << "##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##    Slot 3: " << player1.slot3 << "##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##    Slot 4: " << player1.slot4 << "##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##    Slot 5: " << player1.slot5 << "##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##    Slot 6: " << player1.slot6 << "##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##    Slot 7: " << player1.slot7 << "##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##    Slot 8: " << player1.slot8 << "##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##############################################################################" << std::endl;
     std::cout << std::endl;
     continue_fun();
}

void Game::printIntro(Player &player1) //entire intro story
{
     clear_screen();
     
     std::cout << " Ahoy thar!" << std::endl;
     std::cout << std::endl;
     std::cout << " You find yourself aboard the Royal Navy's flagship, The Millenium Executioner." << std::endl;
     std::cout << std::endl;
     std::cout << " As a cabin boy, you serve Admiral Quincy Hawkins and his officers. Currently, you await outside the wardroom as they strategize." << std::endl;
     std::cout << std::endl;

     continue_fun();
     std::cout << std::endl << std::endl << std::endl;
     std::cout << " Weeks ago, the famous Captain Rupert Scarr turned traitor and joined the Pirate Armada, taking his ship and crew with him... " << std::endl << std::endl;
     std::cout << " You overhear the officers mention that Pirate Captain Scarr is holding \"Ham-Hands Hugo\" hostage!" << std::endl << std::endl;
     std::cout << " \"Ham-Hands Hugo\", also known as \"Hugo Sanchez\", holds vital information about the Spanish Treasure Fleet. " << std::endl << std::endl;
     std::cout << " He also happens to be your best friend." << std::endl << std::endl;

     continue_fun();
     std::cout << std::endl << std::endl << std::endl;

     std::cout << " Upon hearing this news, You burst into the wardroom and request to take part in his rescue." << std::endl << std::endl;
     std::cout << " After much convincing, Admiral Hawkins awknowleges your resolve." << std::endl << std::endl;
     std::cout << " He also believes that due to your remarkable ability of being unremarkable... you could be useful." << std::endl << std::endl;
     std::cout << " You are to report to the Marine Commander. How exciting!" << std::endl << std::endl;

     continue_fun();
     clear_screen();
     std::cout << std::endl << std::endl << std::endl;
     std::cout << " You meet with Commander Ronny Jones..." << std::endl << std::endl;
     std::cout << std::endl;

     player1.setName();
     std::cout << std::endl << std::endl;
     std::cout << std::endl  << std::endl;
     std::cout << " Commander Ronny Jones:\"Right. Okay, "<<player1.getName()<<", this is the situation...\"" << std::endl;
     std::cout << std::endl << std::endl;


     std::cout << " #################################################################################################" << std::endl;
     std::cout << " ##                                                                                             ##" << std::endl;
     std::cout << " ## Pirate Captain Scarr is currently docked at Pirate's Cove.                                  ##" << std::endl;
     std::cout << " ##                                                                                             ##" << std::endl;
     std::cout << " ## Step 1: We send you alone into Pirate's Cove, where you will sneak onto his ship,           ##" << std::endl;
     std::cout << " ##         \"The Night's Sadness\", as it sets sail.                                             ##" << std::endl;
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

     std::cout << std::endl << std::endl;
     std::cout << " The time is now. You are ready to prove yourself." << std::endl << std::endl;
     std::cout << " Commander Ronny Jones gives you a grappling hook, a small pack, and a pocketwatch." << std::endl << std::endl;
     std::cout << " Commander Ronny Jones:\"The pocketwatch will help you know when the major assault will commence.\"" << std::endl << std::endl;
     std::cout << " Commander Ronny Jones:\"Stay Sharp and good Luck!\"" << std::endl << std::endl;
     continue_fun();
}

void Game::phaseMessage()
{
     clear_screen();

     std::cout << " ################################################################################" << std::endl;
     std::cout << " ##                                                                            ##" << std::endl;
     std::cout << " ##            BOOOOOOOOOOM! You hear the sound of heavy cannon fire.          ##" << std::endl;
     std::cout << " ##                                                                            ##" << std::endl;
     std::cout << " ##            The full scale attack on the Pirate Armada has begun.           ##" << std::endl;
     std::cout << " ##                                                                            ##" << std::endl;
     std::cout << " ##            It's time to get off the ship before it's too late!             ##" << std::endl;
     std::cout << " ##                                                                            ##" << std::endl;
     std::cout << " ##                                                                            ##" << std::endl;
     std::cout << " ##            Fight your way to the crow's nest to try and spot               ##" << std::endl;
     std::cout << " ##            which direction the rescue ship is coming from.                 ##" << std::endl;
     std::cout << " ##                                                                            ##" << std::endl;
     std::cout << " ################################################################################" << std::endl;

     continue_fun();
}





void Game::gameOver(Player &player1)
{
     clear_screen();
     if (player1.dead)
     {
          std::cout << "                           uuuuuuu" << std::endl;
          std::cout << "                       uu$$$$$$$$$$$uu" << std::endl;
          std::cout << "                    uu$$$$$$$$$$$$$$$$$uu" << std::endl;
          std::cout << "                   u$$$$$$$$$$$$$$$$$$$$$u" << std::endl;
          std::cout << "                  u$$$$$$$$$$$$$$$$$$$$$$$u" << std::endl;
          std::cout << "                 u$$$$$$$$$$$$$$$$$$$$$$$$$u" << std::endl;
          std::cout << "                 u$$$$$$$$$$$$$$$$$$$$$$$$$u" << std::endl;
          std::cout << "                 u$$$$$$\"   \"$$$\"   \"$$$$$$u" << std::endl;
          std::cout << "                 \"$$$$\"      u$u       $$$$\"" << std::endl;
          std::cout << "                  $$$u       u$u       u$$$" << std::endl;
          std::cout << "                  $$$u      u$$$u      u$$$" << std::endl;
          std::cout << "                   \"$$$$uu$$$   $$$uu$$$$\"" << std::endl;
          std::cout << "                    \"$$$$$$$\"   \"$$$$$$$\"" << std::endl;
          std::cout << "                      u$$$$$$$u$$$$$$$u" << std::endl;
          std::cout << "                       u$\"$\"$\"$\"$\"$\"$u" << std::endl;
          std::cout << "            uuu        $$u$ $ $ $ $u$$       uuu" << std::endl;
          std::cout << "           u$$$$        $$$$$u$u$u$$$       u$$$$" << std::endl;
          std::cout << "            $$$$$uu      \"$$$$$$$$$\"     uu$$$$$$" << std::endl;
          std::cout << "          u$$$$$$$$$$$uu    \"\"\"\"\"    uuuu$$$$$$$$$$" << std::endl;
          std::cout << "          $$$$\"\"\"$$$$$$$$$$uuu   uu$$$$$$$$$\"\"\"$$$\"" << std::endl;
          std::cout << "           \"\"\"      \"\"$$$$$$$$$$$uu \"\"$\"\"\"" << std::endl;
          std::cout << "                     uuuu \"\"$$$$$$$$$$uuu" << std::endl;
          std::cout << "            u$$$uuu$$$$$$$$$uu \"\"$$$$$$$$$$$uuu$$$" << std::endl;
          std::cout << "            $$$$$$$$$$\"\"\"\"           \"\"$$$$$$$$$$$\"" << std::endl;
          std::cout << "             \"$$$$$\"                      \"\"$$$$\"\"" << std::endl;
          std::cout << "               $$$\"                         $$$$\"" << std::endl;
          std::cout << std::endl;
          std::cout << "                           GAME OVER" << std::endl;
          std::cout << std::endl << std::endl << std::endl;

          std::cout << "            Ye be in Davy Jones' treasure chest!" << std::endl;  
          std::cout << std::endl << "           Number of points:  " << player1.getScore() << std::endl;
     }
     else
     {
          

          std::cout << " You row like you've never rowed before hoping to not get hit by any stray cannon balls." << std::endl;
          std::cout << " Finally, you make it aboard the millennium executioner...   " << std::endl;
          std::cout << std::endl << std::endl;
          continue_fun();
          std::cout << std::endl << std::endl;
          std::cout << " Due to the success of your mission and the defeat of Pirate Captain Rupert Scarr," << std::endl;
          std::cout << " the Royal Navy was able to severly cripple the Pirate Armada." << std::endl;
          std::cout << " Admiral Quincy Hawkins rewards your bravery by promoting you to Captain "<<player1.getName() <<"!"<< std::endl;
          std::cout << std::endl << std::endl;
          continue_fun();

          std::cout << std::endl << std::endl;

          if (player1.hugoSaved)
          {
               std::cout << " You now find yourself aboard your very own ship, with Ham-Hands Hugo as your second in command." << std::endl;
          }
          else
          {
               std::cout << " You now find yourself aboard your very own ship. If only you had been able to save Ham-Hands Hugo..." << std::endl;
               std::cout << " Instead you have Clam-Hands Claudio as your second in command.." << std::endl;
          }
          std::cout << " Now it is time to venture off into the Seven Seas and forge your legend!" << std::endl;
          continue_fun();
          std::cout <<" "<<player1.getName()<< ", your total score was: " << player1.getScore() << std::endl;
          std::cout << " Congrats!" << std::endl;
     }

     continue_fun();
}