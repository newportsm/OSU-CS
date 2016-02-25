#include "combat.h"
#include "utility.h"
#include "npc.h"

#include <iostream>
#include <string>

void Combat::combatSim(Player &player1, NPC &Enemy)
{
     annotations = true;
     bool battleOver = false;
     rangeTimer = 1;
     round = 1;
     twoHandTimer = 1;

     while (!battleOver)
     {
          char choice;

          coinFlip();

          //check ranged weapon status
          if (rangeTimer == round) //ranged weapon is ready to use
          {
               rangedCooldown = false;
          }

          if (twoHandTimer == round) //2H weapon is ready to use
          {
               twoHandCooldown = false;
          }

          combatMenu(player1, Enemy); 
          choice = getUserChoice();

          if (choice == 'O') //options
          {
               toggleAnnotations();
               continue;
          }
          else if (choice == 'A') //attack
          {
               if (!annotations)
               {
                    std::cout << std::endl << std::endl;
                    std::cout << " You decide to fight!" << std::endl;
               }

               fightLoop(player1, Enemy); //fight loop for the two fighters will run twice 
               round++;
               continue_fun();
          }
          else if (choice == 'H')
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
          else if (choice == 'R')
          {
               std::cout << std::endl << std::endl;
               std::cout << " You run away." << std::endl;
               std::cout <<" "<<Enemy.getName() << " will regain his health and await your return." << std::endl;
               battleOver = true;
               break;
          }
          else
          {
               std::cout << std::endl << std::endl;
               std::cout << std::endl << " Invalid option! Try something else. " << std::endl;
               continue_fun();
               continue;
          }

          if (player1.dead)
          {
               battleOver = true;
          }

          if (Enemy.dead)
          {
               std::cout << std::endl;
               std::cout << std::endl << " You have gained valuable combat expierence! You gain +5 health and raise your max health points by 10!" << std::endl;
               player1.healthPoints += 5;
               player1.maxHealthPoints += 10;
               player1.setScore(10); //add 10 to the player score

               if (Enemy.getNpcID() == 6) //Cookie
               {
                    player1.cookieDead = true;
                    player1.healthPoints += 10;
                    player1.maxHealthPoints += 5;
                    player1.setScore(50); //add 10 to the player score
                    std::cout << std::endl;
                    std::cout << std::endl << " You loot the cook's kitchen and eat a hearty stew!" << std::endl;
                    std::cout << std::endl << " You gain +10 health and raise your max health points by 5!" << std::endl;
               }

               if (Enemy.getNpcID() == 4) //Doctor event
               {
                    player1.surgeonDead = true;
                    player1.healthPoints += 10;
                    player1.maxHealthPoints += 5;
                    player1.setScore(100); //add 100 to the player score
                    std::cout << std::endl;
                    std::cout << std::endl << " Dr. Macon Read drops a vial of unknown liquid!" << std::endl;
                    std::cout << std::endl << " You decide to drink it and you start to feel a little strange..." << std::endl;
                    std::cout << std::endl << " You are now able to passively regenerate +2 health points when in a \"healthy\" state." << std::endl;
                    std::cout << std::endl << " You also gain +10 health and raise your max health points by 5!" << std::endl;
               }

               if (Enemy.getNpcID() == 7) //warden event 
               {
                    clear_screen();

                    player1.hugoSaved = true;
                    player1.setScore(100); //add 100 to the player score
                    std::cout << std::endl << " You pick up the warden's keys and unlock Ham-Hands Hugo's cell." << std::endl;
                    std::cout << std::endl << " Ham-Hands Hugo: \"Nice one, " << player1.getName() << "!\" " << std::endl;
                    std::cout << std::endl << " Ham-Hands Hugo: \"I'll just take these boots...\"" << std::endl;
                    std::cout << std::endl << " Ham-Hands Hugo: \"Let's go down to the hold for some weapons.\"" << std::endl;
                    std::cout << std::endl << " Ham-Hands Hugo: \"There is also tons of gun powder down there for us to \"use\" in some way or another.\"" << std::endl;
                    std::cout << std::endl;
               }

               if (Enemy.getNpcID() == 3)//quartermaster
               {
                    player1.setScore(200); //add 200 to the player score
                    player1.recoverHealth(200); //recover 200 hp or if less recover full health
                    player1.quarterMasterDead = true;
               }

               if (Enemy.getNpcID() == 1) //pirate captain
               {
                    player1.captainDead = true;
                    player1.setScore(500); //add 500 to the player score
                    std::cout << std::endl << " Now you can get to the forcastle deck and escape!" << std::endl;
               }
    
               battleOver = true;
          } 
     }
     continue_fun();
}


void Combat::fightLoop(Player &player1, NPC &Enemy)
{
     bool rangedUsed = false;
     bool twoHandUsed = false;
     if (annotations)
     {
          if (playerTurn)
          {
               std::cout << std::endl << std::endl;
               std::cout <<" "<< player1.getName() << " strikes first! " << std::endl;           
          }

          if (npcTurn)
          {

               std::cout << std::endl << std::endl;
               std::cout << " " << Enemy.getName() << " strikes first!" << std::endl;
          }
     }

     if (player1.bleeding)
     {
          player1.healthPoints--;
          if (annotations)
          {
               std::cout << std::endl << std::endl;
               std::cout << " You lose 1 health point due to bleeding." << std::endl;
          }
     }

     for (int i = 0; i < 2; i++) //loop for each character to take 1 turn
     {
          int damageDealt = 0;

          //player's turn
          if (playerTurn)
          {
               playerTurn = false;
               npcTurn = true;

               //deal damage
               if ((player1.grenadoes) || (player1.flintlockPistol)) //player has a ranged weapon
               {
                    if (!rangedCooldown) //ranged weapon is ready
                    {
                         damageDealt = player1.rangedAttack();
                         rangedCooldown = true;
                         rangedUsed = true;

                         if (player1.flintlockPistol)
                         {
                              rangeTimer = (round + 3);
                         }
                         else//grenadoes
                         {
                              rangeTimer = (round + 5);
                         }
                    }
                    else//ranged weapon is still on cooldown
                    {
                         if ((player1.scimitar) || (player1.pegLeg))
                         {
                              if (!twoHandCooldown)
                              {
                                   damageDealt = player1.meleeAttack();
                                   twoHandCooldown = true;
                                   twoHandUsed = true;
                                   twoHandTimer = (round + 2);
                              }
                              else
                              {
                                   if (annotations)
                                   {
                                        std::cout << std::endl;
                                        std::cout << std::endl << " You prepare for a powerful swing of your two-handed weapon." << std::endl;                                    
                                   }
                              }
                         }
                         else
                         {
                              damageDealt = player1.meleeAttack();
                         }
                    }
               }
               else if ((!player1.grenadoes) && (!player1.flintlockPistol)) //player does not have any ranged weapons equiped
               {

                    if ((player1.scimitar) || (player1.pegLeg))
                    {
                         if (!twoHandCooldown)
                         {
                              damageDealt = player1.meleeAttack();
                              twoHandCooldown = true;
                              twoHandUsed = true;
                              twoHandTimer = (round + 2);
                         }
                         else
                         {
                              if (annotations)
                              {
                                   std::cout << std::endl;
                                   std::cout << std::endl << " You prepare for a powerful swing of your two-handed weapon." << std::endl;
                              }
                         }
                    }
                    else
                    {
                         damageDealt = player1.meleeAttack();
                    }
               }


               if (damageDealt >= 1)
               {
                    //1 out of 5 chance that npc defends
                    int npcDefense = (int)(rand() % 5) + 1;

                    if (npcDefense == 1) //the npc parries your attaack
                    {
                         if (annotations)
                         {
                              std::cout << std::endl;
                              std::cout << std::endl << " Your attack on " << Enemy.getName() << " misses! No damage is done." << std::endl;
                         }
                    }
                    else
                    {
                         Enemy.healthPoints -= damageDealt;
                         if (annotations)
                         {
                              std::cout << std::endl;
                              std::cout << std::endl << " You attack " << Enemy.getName() << " and deal (" << damageDealt << ") damage!" << std::endl;
                         }
                    }

               }

               if (player1.buckler) //if player has the buckler than we can the special chance to perform additional strikes
               {
                    int additionalStrike = 0;

                    if (player1.sailorsKnife)
                    {
                         //1 out of 3 chance for additional strike
                         additionalStrike = (int)(rand() % 3) + 1;
                    }
                    else //cutlass
                    {
                         //1 out of 5 chance for additional strike
                         additionalStrike = (int)(rand() % 5) + 1;
                    }
                    
                    damageDealt = 0;
                    if (additionalStrike == 2)
                    {
                         damageDealt = player1.meleeAttack();
                         Enemy.healthPoints -= damageDealt;
                         if (annotations)
                         {
                              std::cout << std::endl;
                              std::cout << std::endl << " You see an opening and make an additional strike!" << std::endl;
                              std::cout << std::endl << " You deal ("<<damageDealt <<") more damage!" << std::endl;
                         }
                    }
               }

               if (annotations && rangedUsed)
               {
                    if (!player1.hugoSaved)
                    {
                         std::cout << std::endl;
                         std::cout << std::endl << " It will take some time for your ranged weapon to be reloaded." << std::endl;
                    }
                    else
                    {
                         std::cout << std::endl;
                         std::cout << std::endl << " You give your ranged weapon to \"Ham-Hands Hugo\" to reload for you." << std::endl;
                    }
                    
               }

               if (Enemy.healthPoints < 1)
               {
                    if (annotations)
                    {
                         std::cout << std::endl;
                         std::cout << " You have defeated " << Enemy.getName() << "!" << std::endl;
                    }

                    Enemy.dead = true;
                    return;
               }
          }
          else if (npcTurn)//npc turn
          {
               playerTurn = true;
               npcTurn = false;

               //deal damage
               int damageDealt = ((Enemy.attack()) - (player1.defend()));

               if (damageDealt < 1)//attack failed
               {
                    if (annotations)
                    {
                         std::cout << std::endl;
                         std::cout << std::endl << " You block " << Enemy.getName() << "'s attack with your weapon and he deals no damage!" << std::endl;
                    }
               }
               else
               {
                    //1 out of 6 chance that npc attack misses
                    int missChance = (int)(rand() % 6) + 1;

                    if (missChance == 2)
                    {
                         if (annotations)
                         {
                              std::cout << std::endl;
                              std::cout << std::endl << " " << Enemy.getName() << " misses his attack on you and deals no damage!" << std::endl;
                         }
                    }
                    else
                    {
                         player1.healthPoints -= damageDealt;
                         if (annotations)
                         {
                              std::cout << std::endl;
                              std::cout << std::endl << " " << Enemy.getName() << " deals (" << damageDealt << ") damage to you!" << std::endl;
                         }
                         //1 out of 15 chance for bleeding debuff
                         int bleedChance = (int)(rand() % 15) + 1;
                         damageDealt = 0;
                         if (bleedChance == 1) 
                         {
                              player1.setStatus(2); //sets the bleeding status
                              player1.healthPoints--;
                              if (annotations)
                              {
                                   std::cout << std::endl;
                                   std::cout << " You are bleeding and will lose 1 health point each turn." << std::endl;
                                   std::cout << " Apply a bandage to stop the bleeding!" << std::endl;
                              }
                         }
                    }

                    if (player1.healthPoints < 1)
                    {
                         if (annotations)
                         {
                              std::cout << std::endl;
                              std::cout << " You have been defeated by " << Enemy.getName() << " and are now dead!" << std::endl;
                         }

                         player1.dead = true; //set player to dead so that the game loop in game.cpp can trigger the game over functions
                         return;
                    }
               }
          }
     }
}

void Combat::coinFlip()  //sets the bool flags for the current players turn
{
     int flipCoin = rand() % 2; //50% chance of either 0 or 1
     if (flipCoin == 0) //Player attacks first
     {
          playerTurn = true;
          npcTurn = false;
     }
     else //NPC attacks first
     {
          playerTurn = false;
          npcTurn = true;
     }
}

void Combat::combatMenu(Player &player1, NPC &Enemy)
{
     clear_screen();
     std::cout << " " << player1.getName() << std::endl;
     std::cout << std::endl;
     std::cout << " Health Points: " << player1.getHealth() << "/" << player1.getMaxHealthPoints() << "     Status: " << player1.getStatus() << std::endl;
     std::cout << std::endl;
     std::cout << " Melee weapon: "<< player1.meleeWeaponName << std::endl;
     std::cout << " Ranged weapon: "<< player1.rangedWeaponName << std::endl;
     std::cout << std::endl << std::endl << std::endl;

     std::cout << " ===========================================================" << std::endl;

     std::cout << std::endl << std::endl << std::endl;
     std::cout << " " << Enemy.getName() << std::endl;
     std::cout << std::endl;
     std::cout << " Health Points: " << Enemy.getHealth() << "/" << Enemy.getMaxHealthPoints() << "     Difficulty: " << Enemy.difficulty << std::endl;
     std::cout << std::endl;
     std::cout << std::endl << std::endl << std::endl;

     std::cout << "                           ENGAGED IN PIRATE COMBAT " << std::endl;
     std::cout << " ##############################################################################" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##  Round #: " << round << "                                                             ##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ## Actions:                                                                 ##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##   (O) Options                                                            ##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##   "<< attackOption(player1)<< "##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##   (H) Heal yourself by applying a bandage (Can also stop bleeding)       ##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##   (R) Run away                                                           ##" << std::endl;
     std::cout << " ##                                                                          ##" << std::endl;
     std::cout << " ##############################################################################" << std::endl;
     std::cout << std::endl;
}

std::string Combat::attackOption(Player player1)
{
     if (player1.grenadoes || player1.flintlockPistol)
     {
          if (!rangedCooldown) //ranged weapon is not ready
          {
               return "(A) Attack with ranged weapon!                                         ";
          }
          else
          {
               return "(A) Attack with melee! (Ranged weapon still reloading)                 ";
          }

     }
     else //no ranged weapon
     {
          return "(A) Attack with melee!                                                 ";
     }
}

void Combat::toggleAnnotations()
{
     clear_screen();
     std::cout << " 1. Battle annotations ON " << std::endl;
     std::cout << " 2. Battle annotations OFF" << std::endl;
     std::cout << std::endl << std::endl << std::endl;
     int choice = 0;
     choice = input_verify();
     switch (choice)
     {
          case 1://display annotations mode ON
          {
               annotations = true;
               std::cout << std::endl << std::endl << std::endl;
               std::cout << " Battle annotations will now be displayed." << std::endl;
               continue_fun();
               break;
          }
          case 2: //display annotations mode OFF
          {
               annotations = false;
               std::cout << std::endl << std::endl << std::endl;
               std::cout << " Battle annotations will NOT be displayed." << std::endl;
               continue_fun();
               break;
          }
          default:
          {
               std::cout << std::endl << std::endl << std::endl;
               std::cout << " Invalid entry! Only integers from 1-2 are allowed!" << std::endl;
               continue_fun();
               break;
          }
     }
}