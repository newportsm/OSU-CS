#pragma once

class DrawMap
{
public:
     DrawMap();                                  //constructor for the map array
     void drawDebugMap();                       //will draw the whole map if debug mode is enabled
     void printMap();                          //will print the current map to the screen
     void drawRoom(int roomID);                //will draw the visited room on the map

     void writeMap();                      //write game map to a txt file 

private:
     unsigned char map_array[70][90]; //unsigned to allow for use of the ascii characters for the borders of the map
     bool debug;
     //functions for drawing each room
     void drawPoopDeck();
     void drawQuarterDeck();
     void drawForcastleDeck();
     void drawCaptainsQuarters();
     void drawMainDeck();
     void drawCrowsNest();
     void drawUpperGunDeck();
     void drawMiddleGunDeck();
     void drawOfficersArea();
     void drawGalley();
     void drawLowerGunDeck();
     void drawOrlopDeck();
     void drawCarpentersWorkroom();
     void drawHallway();
     void drawBrig();
     void drawInfirmary();
     void drawHold();
};

