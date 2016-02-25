#pragma once

#include <iostream>
#include <string>



class NPC
{
public:
     NPC();
     virtual ~NPC(){}
     virtual int attack() = 0;
     virtual int diceRoll(int numberRolls, int numberSides);
     std::string getName();
     int getHealth();
     int getMaxHealthPoints();
     int healthPoints;
     bool dead;
     std::string difficulty;
     int npcID;
     int getNpcID();


protected:
     std::string name;
     int maxHealthPoints;

};

class PirateCaptain : public NPC
{
public:
     PirateCaptain();
     int attack();
};

class PirateOfficer :public NPC
{
public:
     PirateOfficer();
     int attack();
};

class PirateQuarterMaster : public NPC
{
public:
     PirateQuarterMaster();
     int attack();
};

class PirateSurgeon : public NPC
{
public:
     PirateSurgeon();
     int attack();
};


class PirateSailor : public NPC
{
public:
     PirateSailor();
     int attack();
};

class PirateCook : public NPC
{
public:
     PirateCook();
     int attack();
};

class PirateWarden : public NPC
{
public:
     PirateWarden();
     int attack();
};