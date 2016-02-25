#pragma once

#include "player.h"
#include "npc.h"

class Combat
{
public:
     void combatSim(Player &player1, NPC &Enemy); //The main loop for all combat and handling of storyline events
     void fightLoop(Player &player1, NPC &Enemy);  // fight rotation returns the winner
     void coinFlip();  //sets the bool flags for the current players turn
     void combatMenu(Player &player1, NPC &Enemy); //the fight gui and options
     void toggleAnnotations();
     std::string attackOption(Player player1); //displays to the menu if the ranged weapon is loaded or not

private:
     int round; //keeps track of the round number for setting timers on different weapons
     bool rangedCooldown;
     bool twoHandCooldown;
     int rangeTimer; //timer for when ranged weapon is ready to fire
     int twoHandTimer; //timer for 2h weapons cooldowns
     bool annotations;
     bool playerTurn;
     bool npcTurn;


};