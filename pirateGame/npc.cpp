#include "npc.h"


NPC::NPC(){}

int NPC::getHealth()
{
     return healthPoints;
}


int NPC::getMaxHealthPoints()
{
     return maxHealthPoints;
}


std::string NPC::getName()
{
     return name;
}

int NPC::diceRoll(int numberRolls, int numberSides)
{
     int result = 0;
     for (int i = 0; i < numberRolls; i++)
     {
          result += (rand() % numberSides) + 1;
     }
     return result;
}

int NPC::getNpcID()
{
     return npcID;
}

PirateCaptain::PirateCaptain()
{
     npcID = 1;
     name = "Pirate Captain Rupert Scarr";
     dead = false;
     healthPoints = 300;
     maxHealthPoints = 300;
     difficulty = " Very Hard";

}

int PirateCaptain::attack()
{
     return diceRoll(3, 12);
}

PirateOfficer::PirateOfficer()
{
     npcID = 2;
     name = "Pirate Officer";
     dead = false;
     healthPoints = 120;
     maxHealthPoints = 120;
     difficulty = "Medium";
}

int PirateOfficer::attack()
{
     return diceRoll(2, 10);
}

PirateQuarterMaster::PirateQuarterMaster()
{
     npcID = 3;
     name = "Pirate QuarterMaster Bernard the Pale";
     dead = false;
     healthPoints = 220;
     maxHealthPoints = 220;
     difficulty = "Hard";
}

int PirateQuarterMaster::attack()
{
     return diceRoll(2, 15);
}

PirateSurgeon::PirateSurgeon()
{
     npcID = 4;
     name = "Pirate Dr. Macon Read";
     dead = false;
     healthPoints = 80;
     maxHealthPoints = 80;
     difficulty = "Normal";
}

int PirateSurgeon::attack()
{
     return diceRoll(3, 6);
}

PirateSailor::PirateSailor()
{
     npcID = 5;
     name = "Pirate Sailor";
     dead = false;
     healthPoints = 100;
     maxHealthPoints = 100;
     difficulty = "Easy";

}

int PirateSailor::attack()
{
     return diceRoll(2, 5);
}

PirateCook::PirateCook()
{
     npcID = 6;
     name = "Cookie the Pirate cook";
     dead = false;
     healthPoints = 40;
     maxHealthPoints = 40;
     difficulty = "Easy";
}

int PirateCook::attack()
{
     return diceRoll(2, 5);
}

PirateWarden::PirateWarden()
{
     npcID = 7;
     name = "Warden Hanley 'Cruelty' Granger";
     dead = false;
     healthPoints = 60;
     maxHealthPoints = 60;
     difficulty = "Easy";
}

int PirateWarden::attack()
{
     return diceRoll(2, 5);
}

