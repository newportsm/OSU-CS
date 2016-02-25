#pragma once

#include "ship.h"
#include "player.h"
#include "combat.h"
#include "npc.h"

class Game
{
public:
     Game();
     void runGame(int mode); //main game driver 

private:
     void printIntro(Player &player1); //prints the intro story and gets the user's name
     void displayGui(Player player1, Room currentRoom);
     void displayExploreGui(Player &player1, Room  &currentRoom);
     void displayInventoryGui(Player &player1);
     void phaseMessage(); //prints the phase 2 entered message to the user
     int timer; //coutdown clock
     bool phase2;
     void gameOver(Player &player1);
     int bleedMsgTimer;
     void storyEventCheck(Player &player1, Room  &currentRoom, Combat &combat); //checks to see if any story line progression functions
     bool roomCheck(Player &player1, Room  &nextRoom, Combat &combat); //checks to see if the room is currently locked
};

