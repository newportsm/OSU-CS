#pragma once

#include <iostream>
#include <string>

#include "player.h"
#include "combat.h"

//room superclass
class Room
{
public:
     Room(); //constructor
     virtual ~Room() {} //deconstructor
     std::string PrintDescription(); //the string variable for each room description that will appear in the main game menu gui

     std::string getLabel();    //will print the label of each room
     virtual bool exploreRoom(Player &player1); //this will execute the explore surroundings options for any rooms that can
     bool explorable;  //tells the main game driver if the room can even be explored


     int roomID;  //used for managing storyline events and phases
     std::string Label;
     std::string Description;
     std::string hintNorth;
     std::string hintEast;
     std::string hintSouth;
     std::string hintWest;
     std::string hintLocked;
     std::string hintExplore;
     std::string explore1;
     std::string explore2;
     std::string explore3;

     Room * East;
     Room * West;
     Room * North;
     Room * South;

};

class poopDeck :public Room
{
public:
     poopDeck();
     bool exploreRoom(Player &player1);
};


class quarterDeck :public Room
{
public:
     quarterDeck();
};

class captainDining :public Room
{
public:
     captainDining();
     bool exploreRoom(Player &player1);
private:
     bool bib;
};

class captainCabin :public Room
{
public:
     captainCabin();
     bool exploreRoom(Player &player1);

private:
     bool lockerKey;
};

class forcastleDeck :public Room
{
public:
     forcastleDeck();
};


class mainDeck :public Room
{
public:
     mainDeck();
};

class crowsNest :public Room
{
public:
     crowsNest();
     bool exploreRoom(Player &player1);
};

class upperGunDeck :public Room
{
public:
     upperGunDeck();
};

class middleGunDeck :public Room
{
public:
     middleGunDeck();
};

class galley :public Room
{
public:
     galley();
};

class wardroom :public Room
{
public:
     wardroom();
};

class officerCabin :public Room
{
public:
     officerCabin();
     bool exploreRoom(Player &player1);
};

class lowerGunDeck :public Room
{
public:
     lowerGunDeck();
};

class orlopDeck :public Room
{
public:
     orlopDeck();
};

class hallway :public Room
{
public:
     hallway();
};

class theBrig :public Room
{
public:
     theBrig();
};

class infirmary :public Room
{
public:
     infirmary();

     bool exploreRoom(Player &player1);
};

class carpentersOffice :public Room
{
public:
     carpentersOffice();
};

class theHold :public Room
{
public:
     theHold();
 
     bool exploreRoom(Player &player1);
};

class storageRoom :public Room
{
public:
     storageRoom();
     bool exploreRoom(Player &player1);
};

class exitRoom :public Room
{
public:
     exitRoom();
};

Room * buildShip(Room** shipMap); //Builds the entire ship map