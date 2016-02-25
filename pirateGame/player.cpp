#include "player.h"

Player::Player()
{
     score = 0;
     healthPoints = 100;
     maxHealthPoints = 100;
     status = "Healthy";
     dead = false;
     bleeding = false;
     healthy = true;
     drunk = false;
     previousLocation = "Grappling hook entrance! No one notices you as you throw the grappling hook into the sea. ";
     bandages = 0;
     map = false;
     spyglass = false;
     rope = false;
     brigKey = false;
     officerKey = false;
     flintSteel = false;
     cookies = false;
     carpenterAxe = false;
     fists = true;
     pegLeg = false;
     buckler = false;
     cutlass = false;
     sailorsKnife = false;
     scimitar = false;
     flintlockPistol = false;
     grenadoes = false;
     meleeWeaponName = "Fists                                                         ";
     rangedWeaponName = "None                                                          ";
     bandages = 0;

     
     //storyline progression
     moveCount = 0;
     hugoSaved = false;
     cookieDead = false;
     surgeonDead = false;
     surgeonFight = false;
     sabotageSet = false;
     holdLocked = false;
     quarterMasterDead = false;
     captainDead = false;
     officerKnockedOut = false;
     mapFound = false;
     spyglassFound = false;
     ropeFound = false;
     
}

void Player::recoverHealth(int num)
{
     if ((healthPoints + num) <= maxHealthPoints)
     {
          healthPoints += num;
     }
     else
     {
          int healAmount = ((maxHealthPoints) - (healthPoints));
          healthPoints += healAmount;

     }
}

int Player::diceRoll(int numberRolls, int numberSides)
{
     int result = 0;
     for (int i = 0; i < numberRolls; i++)
     {
          result += (rand() % numberSides) + 1;
     }
     return result;
}

int Player::getScore()
{
     return score;
}

void Player::setScore(int num)
{
     this->score += num;
}

void Player::equipWeapon(int choice)
{

     switch (choice)
     {
          case 1://fists 2H
               fists = true;
               pegLeg = false;
               buckler = false;
               cutlass = false;
               sailorsKnife = false;
               scimitar = false;
               meleeWeaponName = "Fists                                                         ";

               break;

          case 2://pegleg 2H
               fists = false;
               pegLeg = true;
               buckler = false;
               cutlass = false;
               sailorsKnife = false;
               scimitar = false;
               meleeWeaponName = "Someone's Wooden Pegleg                                       ";

               break;

          case 3://buckler 1H + cutlass or knife
               fists = false;
               pegLeg = false;
               buckler = true;
               scimitar = false;

               break;

          case 4://cutlass 1H
               fists = false;
               pegLeg = false;
               cutlass = true;
               sailorsKnife = false;
               scimitar = false;
               meleeWeaponName = "Cutlass                                                       ";
               
               break;

          case 5://sailor's knife
               fists = false;
               pegLeg = false;
               cutlass = false;
               sailorsKnife = true;
               scimitar = false;
               meleeWeaponName = "Sailor's Knife                                                ";

               break;

          case 6://scimitar 2H
               fists = false;
               pegLeg = false;
               buckler = false;
               cutlass = false;
               sailorsKnife = false;
               scimitar = true;
               meleeWeaponName = "Scimitar                                                      ";

               break;

          case 7://flintlock pistol
               flintlockPistol = true;
               grenadoes = false;
               rangedWeaponName = "Flintlock Pistol                                              ";

               break;

          case 8://grenados
               flintlockPistol = false;
               grenadoes = true;
               rangedWeaponName = "Grenados                                                      ";

               break;
          default://error

               std::cout << "ERROR: Weapon equiped failure!" << std::endl;
               break;
     }

     if ((buckler) && (cutlass))
     {
          meleeWeaponName = "Cutlass and Buckler                                           ";
     }
     else if ((buckler) && (sailorsKnife))
     {
          meleeWeaponName = "Sailor's Knife and Buckler                                    ";
     }
}

int Player::meleeAttack()
{
     int attackDamage = 0;

     if (fists)
     {
          attackDamage = diceRoll(2, 3);
     }

     if (pegLeg)
     {
          attackDamage = diceRoll(4, 5);
     }

     if (buckler)
     {
          attackDamage += diceRoll(1, 5);
     }

     if (cutlass)
     {
          attackDamage += diceRoll(3,8);
     }

     if (sailorsKnife)
     {
          attackDamage += diceRoll(2,12);
     }

     if (scimitar)
     {
          attackDamage = diceRoll(4, 10);
     }

     return attackDamage;

}

int Player::rangedAttack()
{
     int attackDamage;

     if (flintlockPistol)
     {
          attackDamage = diceRoll(3,15);
     }

     if (grenadoes)
     {
          attackDamage = diceRoll(3,10);
     }

     return attackDamage;
}

int Player::defend()
{
     int defensePower = 0;

     if ((buckler && scimitar) || (buckler && sailorsKnife))
     {
          defensePower = diceRoll(4, 6);
     }
     else if (scimitar)
     {
          defensePower = diceRoll(3, 8);
     }
     else if (fists || sailorsKnife || pegLeg)
     {
          defensePower = diceRoll(2, 6);
     }
     else
     {
          defensePower = diceRoll(2, 3);
     }

     return defensePower;
}

void Player::setName()
{
     bool valid_name = false;
     while (!valid_name)
     {
          std::cout << std::endl << std::endl;
          std::cout << " Commander Ronny Jones:\"Boy, What is your name?\" : ";
          getline(std::cin, name);
          if (name.length() <= 0)
          {
               std::cout << " Invalid entry! Try again. " << std::endl;
          }
          else
          {
               valid_name = true;
          }
     }
}

void Player::setPreviousLocation(std::string currentRoomLabel)
{
     this->previousLocation = currentRoomLabel;
}

void Player::setStatus(int num)
{
     switch (num)
     {
          case 1://Healthy
               healthy = true;
               bleeding = false;
               drunk = false;
               status = "Healthy";

               break;

          case 2://Bleeding
               bleeding = true;
               healthy = false;
               status = "BLEEDING";
               break;

          case 3://dead
               dead = true;
               bleeding = false;
               healthy = false;
               status = "DEAD";
               break;

          case 4://Drunk
               drunk = true;
               healthy = false;
               bleeding = false;
               status = "DRUNK";
               break;

          default://error

               std::cout << " ERROR: status set failure!" << std::endl;
               break;
     }
}

std::string Player::getName()
{
     return name;
}

int Player::getHealth()
{
     return healthPoints;
}

int Player::getMaxHealthPoints()
{
     return maxHealthPoints;
}

std::string Player::getPreviousLocation()
{
     return previousLocation;
}

std::string Player::getStatus()
{
     return status;
}

void Player::setInventoryStatus()
{
     std::ostringstream oss;
     oss << bandages;

     //slot1
     if (bandages == 0)
     {
          slot1 = "Empty                                                         ";
     }
     else if (bandages >= 1 && bandages <= 9)
     {
          // std::string bandage = std::to_string(static_cast<long long>(bandages));
          slot1 = "BANDAGES (";
          slot1 += oss.str();
          slot1 += ")                                                  ";
     }
     else if (bandages >= 10)
     {
          // std::string bandage = std::to_string(static_cast<long long>(bandages));
          slot1 = "BANDAGES (";
          slot1 += oss.str();
          slot1 += ")                                                 ";
     }
     //slot2
     if (!map)
     {
          slot2 = "Empty                                                         ";
     }
     else
     {
          slot2 = "MAP                                                           ";
     }
     //slot3
     if (!spyglass)
     {
          slot3 = "Empty                                                         ";
     }
     else
     {
          slot3 = "SPYGLASS                                                      ";
     }

     //slot4
     if (!rope)
     {
          slot4 = "Empty                                                         ";
     }
     else
     {
          slot4 = "ROPE                                                          ";
     }

     //slot5
     if (!brigKey)
     {
          slot5 = "Empty                                                         ";
     }
     else
     {
          slot5 = "KEY TO THE BRIG                                               ";
     }

     //slot6
     if (!officerKey)
     {
          slot6 = "Empty                                                         ";
     }
     else
     {
          slot6 = "KEY TO THE OFFICERS' WARDROOM                                 ";
     }

     //slot7
     if (!flintSteel)
     {
          slot7 = "Empty                                                         ";
     }
     else
     {
          slot7 = "FLINT AND STEEL                                               ";
     }

     //slot8
     if (!cookies)
     {
          slot8 = "Empty                                                         ";
     }
     else
     {
          slot8 = "COOKIES                                                       ";
     }
}

std::string Player::mapOption()
{
     if (map)
     {
          return "(M) Check Map                                                        ";
     }
     else
     {
          return "                                                                     ";
     }
}
