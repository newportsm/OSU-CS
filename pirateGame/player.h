#pragma once

#include <iostream>
#include <string>
#include <sstream>

class Player
{
public:
     Player();
     ~Player(){}

     //getters and setters
     std::string getName();
     int getHealth();
     int getMaxHealthPoints();
     void setName();
     std::string getPreviousLocation();
     void setPreviousLocation(std::string currentRoomLabel);
     std::string getStatus();
     void setStatus(int num);
     int getScore();
     void setScore(int num);
     
     //combat functions
     void equipWeapon(int choice);
     int meleeAttack();
     int rangedAttack();
     int defend();
     int diceRoll(int numberRolls, int numberSides);  //Performs a roll based on how many die and number of sides for each die 
     void recoverHealth(int num);

     //inventory
     void setInventoryStatus();
     int bandages;
     bool map;
     std::string mapOption(); //returns the correct menu option for map depending if player has found the map
     bool spyglass;
     bool rope;
     bool brigKey;
     bool officerKey;
     bool flintSteel;
     bool cookies;
     bool bleeding;
     bool healthy;
     bool drunk;
     bool dead;
     bool carpenterAxe;
     std::string meleeWeaponName;
     std::string rangedWeaponName;
     std::string slot1;
     std::string slot2;
     std::string slot3;
     std::string slot4;
     std::string slot5;
     std::string slot6;
     std::string slot7;
     std::string slot8;

     //stats
     int healthPoints;
     int maxHealthPoints;

     //melee weapons
     bool fists;
     bool pegLeg; //1H
     bool buckler; //small shield
     bool cutlass; //1H
     bool scimitar; //2H
     bool sailorsKnife; //1H

     //ranged weapons
     bool grenadoes;
     bool flintlockPistol;

     //story progression
     int moveCount;
     bool cookieDead;
     bool surgeonDead;
     bool surgeonFight;
     bool hugoSaved;
     bool sabotageSet;
     bool holdLocked;
     bool quarterMasterDead;
     bool captainDead;
     bool officerKnockedOut;
     bool mapFound;
     bool spyglassFound;
     bool ropeFound;

private:
     std::string name;
     int score;
     std::string previousLocation;
     std::string status;
};