#include "map.h"

#include <iostream>
#include <fstream>
#include "utility.h"

DrawMap::DrawMap()
{
     //intialize the arrays
     //sets the outer borders
     for (int j = 0; j < 70; j++)
     {
          for (int i = 0; i < 90; i++)
          {
               map_array[j][i] = 219;
          }
     }
     //sets the inside to blanks
     for (int j = 1; j < 69; j++)
     {
          for (int i = 1; i < 89; i++)
          {
               map_array[j][i] = ' ';
          }
     }

     //Draw map compass
     map_array[3][6] = 'N';
     map_array[5][6] = '^';
     map_array[6][6] = '+';
     map_array[6][3] = 'W';
     map_array[6][7] = '>';
     map_array[6][5] = '<';
     map_array[6][9] = 'E';
     map_array[7][6] = 'v';
     map_array[9][6] = 'S';

     //draw captain's room since that is the only place the map can be found. (That way it shows up on map always.
     drawCaptainsQuarters(); 
}

void DrawMap::drawRoom(int roomID)
{
     switch (roomID)
     {
          case 1://poop deck
               drawPoopDeck();
               break;
          case 2://quarter deck
               drawQuarterDeck();
               break;
          case 3://Captain's Quarters
               drawCaptainsQuarters();
               break;
          case 4://forcastle deck
               drawForcastleDeck();
               break;
          case 5://main deck
               drawMainDeck();
               break;
          case 6://crow's nest
               drawCrowsNest();
               break;
          case 7://upper gun deck
               drawUpperGunDeck();
               break;
          case 8://middle gun deck
               drawMiddleGunDeck();
               break;
          case 9://galley
               drawGalley();
               break;
          case 10://officer area
               drawOfficersArea();
               break;
          case 11://lower gun deck
               drawLowerGunDeck();
               break;
          case 12://orlop deck
               drawOrlopDeck();
               break;
          case 13://hallway
               drawHallway();
               break;
          case 14://brig
               drawBrig();
               break;
          case 15://infirmary
               drawInfirmary();
               break;
          case 16://carpenter's office
               drawCarpentersWorkroom();
               break;
          case 17://the hold
               drawHold();
               break;
          default:
               if (debug)
               {
                    std::cout << " No room was drawn" << std::endl;
               }
               break;
     }
}

void DrawMap::drawDebugMap()
{
     //draw each room
     drawPoopDeck();
     drawQuarterDeck();
     drawMainDeck();
     drawForcastleDeck();
     drawCaptainsQuarters();
     drawForcastleDeck();
     drawCrowsNest();
     drawUpperGunDeck();
     drawMiddleGunDeck();
     drawOfficersArea();
     drawGalley();
     drawLowerGunDeck();
     drawOrlopDeck();
     drawCarpentersWorkroom();
     drawHallway();
     drawBrig();
     drawInfirmary();
     drawHold();
}



void DrawMap::writeMap()
{
     std::ofstream ofs;

     ofs.open("PirateRescueMap.txt");
     //ofs << "\xEF\xBB\xBF"; // UTF-8 BOM
     if (!ofs)//output file could not be opened
     {
          std::cout << " Error! Output file could not be opened." << std::endl;
          return;
     }
    //file open success
     
     drawDebugMap(); //Draw the entire map at once 

     //remove the extended ascii characters
     for (int x = 0; x < 70; x++)
     {
          for (int y = 0; y < 90; y++)
          {
               if (map_array[x][y] == 176)
               {
                    map_array[x][y] = '#';
               }
          }  
     }

     ofs << "                    PIRATE RESCUE MAP 1.0                     \n";
     ofs << "================================================================";

     //write to the file without the borders
     for (int x = 1; x < 69; x++)
     {
          for (int y = 1; y < 89; y++)
          {
               ofs << map_array[x][y];
          }
          ofs << "\n";
     }

     ofs.close();
     std::cout << " Game map has been saved to \"PirateRescueMap.txt\" and can be found in same directory as the PirateRescue.exe."<< std::endl;
     continue_fun();
}
























void DrawMap::printMap()
{
     //print the map to the screen
     for (int j = 0; j < 70; j++)
     {
          for (int i = 0; i < 90; i++)
          {
               std::cout << map_array[j][i];
          }
          std::cout << std::endl;
     }
}

void DrawMap::drawPoopDeck()
{
     //Poop deck
     map_array[2][34] = 176;
     map_array[2][35] = 176;
     map_array[2][36] = 176;
     map_array[2][37] = 176;
     map_array[2][38] = 176;
     map_array[2][39] = 176;
     map_array[3][34] = 176;
     map_array[4][34] = 176;
     map_array[5][34] = 176;
     map_array[5][35] = 176;
     map_array[5][36] = 176;
     map_array[5][37] = 176;
     map_array[5][38] = 176;
     map_array[5][39] = 176;
     map_array[4][39] = 176;
     map_array[3][39] = 176;
     map_array[3][35] = 'P';
     map_array[3][36] = 'O';
     map_array[3][37] = 'O';
     map_array[3][38] = 'P';
     map_array[4][35] = 'D';
     map_array[4][36] = 'E';
     map_array[4][37] = 'C';
     map_array[4][38] = 'K';

     //Vertical arrow for the poop deck
     map_array[7][37] = '|';
     map_array[8][37] = '|';
     map_array[9][37] = '|';

}

void DrawMap::drawQuarterDeck()
{
     //Quarter deck
     map_array[11][33] = 176;
     map_array[11][34] = 176;
     map_array[11][35] = 176;
     map_array[11][36] = 176;
     map_array[11][37] = 176;
     map_array[11][38] = 176;
     map_array[11][39] = 176;
     map_array[11][40] = 176;
     map_array[11][41] = 176;
     map_array[12][33] = 176;
     map_array[13][33] = 176;
     map_array[12][41] = 176;
     map_array[13][41] = 176;
     map_array[14][33] = 176;
     map_array[14][34] = 176;
     map_array[14][35] = 176;
     map_array[14][36] = 176;
     map_array[14][37] = 176;
     map_array[14][38] = 176;
     map_array[14][39] = 176;
     map_array[14][40] = 176;
     map_array[14][41] = 176;
     map_array[12][34] = 'Q';
     map_array[12][35] = 'U';
     map_array[12][36] = 'A';
     map_array[12][37] = 'R';
     map_array[12][38] = 'T';
     map_array[12][39] = 'E';
     map_array[12][40] = 'R';
     map_array[13][35] = 'D';
     map_array[13][36] = 'E';
     map_array[13][37] = 'C';
     map_array[13][38] = 'K';

     //Vertical arrow for the quarter deck
     map_array[7][37] = '|';
     map_array[8][37] = '|';
     map_array[9][37] = '|';

     //Horizontal arrow for the quarter deck
     map_array[12][29] = '-';
     map_array[12][30] = '-';
     map_array[12][31] = '-';

     //Horizontal arrow for  quarter deck
     map_array[12][43] = '-';
     map_array[12][44] = '-';
     map_array[12][45] = '-';

     //Vertical arrow for the quarter deck
     map_array[16][37] = '|';
     map_array[17][37] = '|';
     map_array[18][37] = '|';



}

void DrawMap::drawForcastleDeck()
{
     //Forcastle Deck
     map_array[11][17] = 176;
     map_array[11][18] = 176;
     map_array[11][19] = 176;
     map_array[11][20] = 176;
     map_array[11][21] = 176;
     map_array[11][22] = 176;
     map_array[11][23] = 176;
     map_array[11][24] = 176;
     map_array[11][25] = 176;
     map_array[11][26] = 176;
     map_array[11][27] = 176;
     map_array[12][17] = 176;
     map_array[13][17] = 176;
     map_array[12][27] = 176;
     map_array[13][27] = 176;
     map_array[14][17] = 176;
     map_array[14][18] = 176;
     map_array[14][19] = 176;
     map_array[14][20] = 176;
     map_array[14][21] = 176;
     map_array[14][22] = 176;
     map_array[14][23] = 176;
     map_array[14][24] = 176;
     map_array[14][25] = 176;
     map_array[14][26] = 176;
     map_array[14][27] = 176;
     map_array[12][18] = 'F';
     map_array[12][19] = 'O';
     map_array[12][20] = 'R';
     map_array[12][21] = 'C';
     map_array[12][22] = 'A';
     map_array[12][23] = 'S';
     map_array[12][24] = 'T';
     map_array[12][25] = 'L';
     map_array[12][26] = 'E';
     map_array[13][20] = 'D';
     map_array[13][21] = 'E';
     map_array[13][22] = 'C';
     map_array[13][23] = 'K';

     //Horizontal arrow for the forcastle deck
     map_array[12][29] = '-';
     map_array[12][30] = '-';
     map_array[12][31] = '-';


}

void DrawMap::drawCaptainsQuarters()
{
     //Captain's quarters
     map_array[11][47] = 176;
     map_array[11][48] = 176;
     map_array[11][49] = 176;
     map_array[11][50] = 176;
     map_array[11][51] = 176;
     map_array[11][52] = 176;
     map_array[11][53] = 176;
     map_array[11][54] = 176;
     map_array[11][55] = 176;
     map_array[11][56] = 176;
     map_array[11][57] = 176;
     map_array[12][47] = 176;
     map_array[13][47] = 176;
     map_array[12][57] = 176;
     map_array[13][57] = 176;
     map_array[14][47] = 176;
     map_array[14][48] = 176;
     map_array[14][49] = 176;
     map_array[14][50] = 176;
     map_array[14][51] = 176;
     map_array[14][52] = 176;
     map_array[14][53] = 176;
     map_array[14][54] = 176;
     map_array[14][55] = 176;
     map_array[14][56] = 176;
     map_array[14][57] = 176;
     map_array[12][48] = 'C';
     map_array[12][49] = 'A';
     map_array[12][50] = 'P';
     map_array[12][51] = 'T';
     map_array[12][52] = 'A';
     map_array[12][53] = 'I';
     map_array[12][54] = 'N';
     map_array[12][55] = '\'';
     map_array[12][56] = 'S';
     map_array[13][48] = 'Q';
     map_array[13][49] = 'U';
     map_array[13][50] = 'A';
     map_array[13][51] = 'R';
     map_array[13][52] = 'T';
     map_array[13][53] = 'E';
     map_array[13][54] = 'R';
     map_array[13][55] = 'S';

     //Horizontal arrow for Captain's quarters 
     map_array[12][43] = '-';
     map_array[12][44] = '-';
     map_array[12][45] = '-';


}

void DrawMap::drawMainDeck()
{
     //main deck
     map_array[20][34] = 176;
     map_array[20][35] = 176;
     map_array[20][36] = 176;
     map_array[20][37] = 176;
     map_array[20][38] = 176;
     map_array[20][39] = 176;
     map_array[21][34] = 176;
     map_array[22][34] = 176;
     map_array[21][39] = 176;
     map_array[22][39] = 176;
     map_array[23][34] = 176;
     map_array[23][35] = 176;
     map_array[23][36] = 176;
     map_array[23][37] = 176;
     map_array[23][38] = 176;
     map_array[23][39] = 176;
     map_array[21][35] = 'M';
     map_array[21][36] = 'A';
     map_array[21][37] = 'I';
     map_array[21][38] = 'N';
     map_array[22][35] = 'D';
     map_array[22][36] = 'E';
     map_array[22][37] = 'C';
     map_array[22][38] = 'K';

     //Vertical arrow for main deck
     map_array[25][37] = '|';
     map_array[26][37] = '|';
     map_array[27][37] = '|';

     //Horizontal arrow for main deck
     map_array[21][30] = '-';
     map_array[21][31] = '-';
     map_array[21][32] = '-';



}
void DrawMap::drawCrowsNest()
{
     //crows nest
     map_array[20][21] = 176;
     map_array[20][22] = 176;
     map_array[20][23] = 176;
     map_array[20][24] = 176;
     map_array[20][25] = 176;
     map_array[20][26] = 176;
     map_array[20][27] = 176;
     map_array[20][28] = 176;
     map_array[21][21] = 176;
     map_array[22][21] = 176;
     map_array[21][28] = 176;
     map_array[22][28] = 176;
     map_array[23][21] = 176;
     map_array[23][22] = 176;
     map_array[23][23] = 176;
     map_array[23][24] = 176;
     map_array[23][25] = 176;
     map_array[23][26] = 176;
     map_array[23][27] = 176;
     map_array[23][28] = 176;
     map_array[21][22] = 'C';
     map_array[21][23] = 'R';
     map_array[21][24] = 'O';
     map_array[21][25] = 'W';
     map_array[21][26] = '\'';
     map_array[21][27] = 'S';
     map_array[22][23] = 'N';
     map_array[22][24] = 'E';
     map_array[22][25] = 'S';
     map_array[22][26] = 'T';

     //Horizontal arrow for Crow's nest
     map_array[21][30] = '-';
     map_array[21][31] = '-';
     map_array[21][32] = '-';

}

void DrawMap::drawUpperGunDeck()
{
     //Upper gun deck
     map_array[29][30] = 176;
     map_array[29][31] = 176;
     map_array[29][32] = 176;
     map_array[29][33] = 176;
     map_array[29][34] = 176;
     map_array[29][35] = 176;
     map_array[29][36] = 176;
     map_array[29][37] = 176;
     map_array[29][38] = 176;
     map_array[29][39] = 176;
     map_array[29][40] = 176;
     map_array[29][41] = 176;
     map_array[29][42] = 176;
     map_array[29][43] = 176;
     map_array[29][44] = 176;
     map_array[29][45] = 176;
     map_array[30][30] = 176;
     map_array[30][45] = 176;
     map_array[31][30] = 176;
     map_array[31][31] = 176;
     map_array[31][32] = 176;
     map_array[31][33] = 176;
     map_array[31][34] = 176;
     map_array[31][35] = 176;
     map_array[31][36] = 176;
     map_array[31][37] = 176;
     map_array[31][38] = 176;
     map_array[31][39] = 176;
     map_array[31][40] = 176;
     map_array[31][41] = 176;
     map_array[31][42] = 176;
     map_array[31][43] = 176;
     map_array[31][44] = 176;
     map_array[31][45] = 176;
     map_array[30][31] = 'U';
     map_array[30][32] = 'P';
     map_array[30][33] = 'P';
     map_array[30][34] = 'E';
     map_array[30][35] = 'R';
     map_array[30][37] = 'G';
     map_array[30][38] = 'U';
     map_array[30][39] = 'N';
     map_array[30][41] = 'D';
     map_array[30][42] = 'E';
     map_array[30][43] = 'C';
     map_array[30][44] = 'K';

     //Vertical arrow for upper gun deck
     map_array[25][37] = '|';
     map_array[26][37] = '|';
     map_array[27][37] = '|';

     //Vertical arrow for upper gun deck
     map_array[33][37] = '|';
     map_array[34][37] = '|';
     map_array[35][37] = '|';


}

void DrawMap::drawMiddleGunDeck()
{
     //Middle gun deck
     map_array[37][29] = 176;
     map_array[37][30] = 176;
     map_array[37][31] = 176;
     map_array[37][32] = 176;
     map_array[37][33] = 176;
     map_array[37][34] = 176;
     map_array[37][35] = 176;
     map_array[37][36] = 176;
     map_array[37][37] = 176;
     map_array[37][38] = 176;
     map_array[37][39] = 176;
     map_array[37][40] = 176;
     map_array[37][41] = 176;
     map_array[37][42] = 176;
     map_array[37][43] = 176;
     map_array[37][44] = 176;
     map_array[37][45] = 176;
     map_array[38][29] = 176;
     map_array[38][45] = 176;
     map_array[39][29] = 176;
     map_array[39][30] = 176;
     map_array[39][31] = 176;
     map_array[39][32] = 176;
     map_array[39][33] = 176;
     map_array[39][34] = 176;
     map_array[39][35] = 176;
     map_array[39][36] = 176;
     map_array[39][37] = 176;
     map_array[39][38] = 176;
     map_array[39][39] = 176;
     map_array[39][40] = 176;
     map_array[39][41] = 176;
     map_array[39][42] = 176;
     map_array[39][43] = 176;
     map_array[39][44] = 176;
     map_array[39][45] = 176;
     map_array[38][30] = 'M';
     map_array[38][31] = 'I';
     map_array[38][32] = 'D';
     map_array[38][33] = 'D';
     map_array[38][34] = 'L';
     map_array[38][35] = 'E';
     map_array[38][37] = 'G';
     map_array[38][38] = 'U';
     map_array[38][39] = 'N';
     map_array[38][41] = 'D';
     map_array[38][42] = 'E';
     map_array[38][43] = 'C';
     map_array[38][44] = 'K';

     //Vertical arrow for middle gun deck
     map_array[33][37] = '|';
     map_array[34][37] = '|';
     map_array[35][37] = '|';

     //Vertical arrow for middle gun deck
     map_array[41][37] = '|';
     map_array[42][37] = '|';
     map_array[43][37] = '|';

     //Horizontal arrow for middle gun deck
     map_array[38][25] = '-';
     map_array[38][26] = '-';
     map_array[38][27] = '-';

     //Horizontal arrow for middle gun deck
     map_array[38][47] = '-';
     map_array[38][48] = '-';
     map_array[38][49] = '-';




}

void DrawMap::drawOfficersArea()
{
     //Officer's area
     map_array[36][51] = 176;
     map_array[36][52] = 176;
     map_array[36][53] = 176;
     map_array[36][54] = 176;
     map_array[36][55] = 176;
     map_array[36][56] = 176;
     map_array[36][57] = 176;
     map_array[36][58] = 176;
     map_array[36][59] = 176;
     map_array[36][60] = 176;
     map_array[37][51] = 176;
     map_array[38][51] = 176;
     map_array[39][51] = 176;
     map_array[40][51] = 176;
     map_array[37][60] = 176;
     map_array[38][60] = 176;
     map_array[39][60] = 176;
     map_array[40][60] = 176;
     map_array[41][51] = 176;
     map_array[41][52] = 176;
     map_array[41][53] = 176;
     map_array[41][54] = 176;
     map_array[41][55] = 176;
     map_array[41][56] = 176;
     map_array[41][57] = 176;
     map_array[41][58] = 176;
     map_array[41][59] = 176;
     map_array[41][60] = 176;
     map_array[37][52] = 'O';
     map_array[37][53] = 'F';
     map_array[37][54] = 'F';
     map_array[37][55] = 'I';
     map_array[37][56] = 'C';
     map_array[37][57] = 'E';
     map_array[37][58] = 'R';
     map_array[37][59] = 'S';
     map_array[38][52] = 'W';
     map_array[38][53] = 'A';
     map_array[38][54] = 'R';
     map_array[38][55] = 'D';
     map_array[38][56] = 'R';
     map_array[38][57] = 'O';
     map_array[38][58] = 'O';
     map_array[38][59] = 'M';
     map_array[39][54] = 'A';
     map_array[39][55] = 'N';
     map_array[39][56] = 'D';
     map_array[40][53] = 'C';
     map_array[40][54] = 'A';
     map_array[40][55] = 'B';
     map_array[40][56] = 'I';
     map_array[40][57] = 'N';
     map_array[40][58] = 'S';



     //Horizontal arrow for officers area
     map_array[38][47] = '-';
     map_array[38][48] = '-';
     map_array[38][49] = '-';


}

void DrawMap::drawGalley()
{
     //galley
     map_array[37][16] = 176;
     map_array[37][17] = 176;
     map_array[37][18] = 176;
     map_array[37][19] = 176;
     map_array[37][20] = 176;
     map_array[37][21] = 176;
     map_array[37][22] = 176;
     map_array[37][23] = 176;
     map_array[38][16] = 176;
     map_array[38][23] = 176;
     map_array[39][16] = 176;
     map_array[39][17] = 176;
     map_array[39][18] = 176;
     map_array[39][19] = 176;
     map_array[39][20] = 176;
     map_array[39][21] = 176;
     map_array[39][22] = 176;
     map_array[39][23] = 176;
     map_array[38][17] = 'G';
     map_array[38][18] = 'A';
     map_array[38][19] = 'L';
     map_array[38][20] = 'L';
     map_array[38][21] = 'E';
     map_array[38][22] = 'Y';

     //Horizontal arrow for galley
     map_array[38][25] = '-';
     map_array[38][26] = '-';
     map_array[38][27] = '-';

}

void DrawMap::drawLowerGunDeck()
{
     //LOWER GUN DECK
     map_array[45][30] = 176;
     map_array[45][31] = 176;
     map_array[45][32] = 176;
     map_array[45][33] = 176;
     map_array[45][34] = 176;
     map_array[45][35] = 176;
     map_array[45][36] = 176;
     map_array[45][37] = 176;
     map_array[45][38] = 176;
     map_array[45][39] = 176;
     map_array[45][40] = 176;
     map_array[45][41] = 176;
     map_array[45][42] = 176;
     map_array[45][43] = 176;
     map_array[45][44] = 176;
     map_array[45][45] = 176;
     map_array[46][30] = 176;
     map_array[46][45] = 176;
     map_array[47][30] = 176;
     map_array[47][31] = 176;
     map_array[47][32] = 176;
     map_array[47][33] = 176;
     map_array[47][34] = 176;
     map_array[47][35] = 176;
     map_array[47][36] = 176;
     map_array[47][37] = 176;
     map_array[47][38] = 176;
     map_array[47][39] = 176;
     map_array[47][40] = 176;
     map_array[47][41] = 176;
     map_array[47][42] = 176;
     map_array[47][43] = 176;
     map_array[47][44] = 176;
     map_array[47][45] = 176;
     map_array[46][31] = 'L';
     map_array[46][32] = 'O';
     map_array[46][33] = 'W';
     map_array[46][34] = 'E';
     map_array[46][35] = 'R';
     map_array[46][37] = 'G';
     map_array[46][38] = 'U';
     map_array[46][39] = 'N';
     map_array[46][41] = 'D';
     map_array[46][42] = 'E';
     map_array[46][43] = 'C';
     map_array[46][44] = 'K';


     //Vertical arrow for lower gun deck
     map_array[49][37] = '|';
     map_array[50][37] = '|';
     map_array[51][37] = '|';

     //Vertical arrow for lower gun deck
     map_array[41][37] = '|';
     map_array[42][37] = '|';
     map_array[43][37] = '|';

}

void DrawMap::drawOrlopDeck()
{
     //Orlop deck
     map_array[53][32] = 176;
     map_array[53][33] = 176;
     map_array[53][34] = 176;
     map_array[53][35] = 176;
     map_array[53][36] = 176;
     map_array[53][37] = 176;
     map_array[53][38] = 176;
     map_array[53][39] = 176;
     map_array[53][40] = 176;
     map_array[53][41] = 176;
     map_array[53][42] = 176;
     map_array[53][43] = 176;
     map_array[54][32] = 176;
     map_array[54][43] = 176;
     map_array[55][32] = 176;
     map_array[55][33] = 176;
     map_array[55][34] = 176;
     map_array[55][35] = 176;
     map_array[55][36] = 176;
     map_array[55][37] = 176;
     map_array[55][38] = 176;
     map_array[55][39] = 176;
     map_array[55][40] = 176;
     map_array[55][41] = 176;
     map_array[55][42] = 176;
     map_array[55][43] = 176;
     map_array[54][33] = 'O';
     map_array[54][34] = 'R';
     map_array[54][35] = 'L';
     map_array[54][36] = 'O';
     map_array[54][37] = 'P';
     map_array[54][39] = 'D';
     map_array[54][40] = 'E';
     map_array[54][41] = 'C';
     map_array[54][42] = 'K';

     //Vertical arrow for orlop deck
     map_array[49][37] = '|';
     map_array[50][37] = '|';
     map_array[51][37] = '|';

     //Vertical arrow for orlop deck
     map_array[57][37] = '|';
     map_array[58][37] = '|';
     map_array[59][37] = '|';


     //Horizontal arrow for orlop deck
     map_array[54][28] = '-';
     map_array[54][29] = '-';
     map_array[54][30] = '-';

     //Horizontal arrow for orlop deck
     map_array[54][45] = '-';
     map_array[54][46] = '-';
     map_array[54][47] = '-';


}

void DrawMap::drawCarpentersWorkroom()
{
     //CARPENTERS WORKROOM
     map_array[52][49] = 176;
     map_array[52][50] = 176;
     map_array[52][51] = 176;
     map_array[52][52] = 176;
     map_array[52][53] = 176;
     map_array[52][54] = 176;
     map_array[52][55] = 176;
     map_array[52][56] = 176;
     map_array[52][57] = 176;
     map_array[52][58] = 176;
     map_array[52][59] = 176;
     map_array[53][49] = 176;
     map_array[54][49] = 176;
     map_array[53][59] = 176;
     map_array[54][59] = 176;
     map_array[55][49] = 176;
     map_array[55][50] = 176;
     map_array[55][51] = 176;
     map_array[55][52] = 176;
     map_array[55][53] = 176;
     map_array[55][54] = 176;
     map_array[55][55] = 176;
     map_array[55][56] = 176;
     map_array[55][57] = 176;
     map_array[55][58] = 176;
     map_array[55][59] = 176;
     map_array[53][50] = 'C';
     map_array[53][51] = 'A';
     map_array[53][52] = 'R';
     map_array[53][53] = 'P';
     map_array[53][54] = 'E';
     map_array[53][55] = 'N';
     map_array[53][56] = 'T';
     map_array[53][57] = 'E';
     map_array[53][58] = 'R';
     map_array[54][50] = 'W';
     map_array[54][51] = 'O';
     map_array[54][52] = 'R';
     map_array[54][53] = 'K';
     map_array[54][55] = 'R';
     map_array[54][56] = 'O';
     map_array[54][57] = 'O';
     map_array[54][58] = 'M';

     //Horizontal arrow for carpenter's workroom
     map_array[54][45] = '-';
     map_array[54][46] = '-';
     map_array[54][47] = '-';

}

void DrawMap::drawHallway()
{
     //the hallway
     map_array[52][21] = 176;
     map_array[52][22] = 176;
     map_array[52][23] = 176;
     map_array[52][24] = 176;
     map_array[52][25] = 176;
     map_array[52][26] = 176;
     map_array[53][21] = 176;
     map_array[54][21] = 176;
     map_array[53][26] = 176;
     map_array[54][26] = 176;
     map_array[55][21] = 176;
     map_array[55][22] = 176;
     map_array[55][23] = 176;
     map_array[55][24] = 176;
     map_array[55][25] = 176;
     map_array[55][26] = 176;
     map_array[53][22] = 'H';
     map_array[53][23] = 'A';
     map_array[53][24] = 'L';
     map_array[53][25] = 'L';
     map_array[54][22] = 'W';
     map_array[54][23] = 'A';
     map_array[54][24] = 'Y';



     //Vertical arrow for the hallway
     map_array[48][24] = '|';
     map_array[49][24] = '|';
     map_array[50][24] = '|';


     //Horizontal arrow for the hallway
     map_array[54][17] = '-';
     map_array[54][18] = '-';
     map_array[54][19] = '-';

     //Horizontal arrow for hallway
     map_array[54][28] = '-';
     map_array[54][29] = '-';
     map_array[54][30] = '-';

}

void DrawMap::drawBrig()
{
     //the brig
     map_array[45][21] = 176;
     map_array[45][22] = 176;
     map_array[45][23] = 176;
     map_array[45][24] = 176;
     map_array[45][25] = 176;
     map_array[45][26] = 176;
     map_array[46][21] = 176;
     map_array[46][26] = 176;
     map_array[47][21] = 176;
     map_array[47][22] = 176;
     map_array[47][23] = 176;
     map_array[47][24] = 176;
     map_array[47][25] = 176;
     map_array[47][26] = 176;
     map_array[46][22] = 'B';
     map_array[46][23] = 'R';
     map_array[46][24] = 'I';
     map_array[46][25] = 'G';

     //Vertical arrow for the brig
     map_array[48][24] = '|';
     map_array[49][24] = '|';
     map_array[50][24] = '|';

}

void DrawMap::drawInfirmary()
{
     //The infirmary
     map_array[53][6] = 176;
     map_array[53][7] = 176;
     map_array[53][8] = 176;
     map_array[53][9] = 176;
     map_array[53][10] = 176;
     map_array[53][11] = 176;
     map_array[53][12] = 176;
     map_array[53][13] = 176;
     map_array[53][14] = 176;
     map_array[53][15] = 176;
     map_array[53][16] = 176;
     map_array[54][6] = 176;
     map_array[54][16] = 176;
     map_array[55][6] = 176;
     map_array[55][7] = 176;
     map_array[55][8] = 176;
     map_array[55][9] = 176;
     map_array[55][10] = 176;
     map_array[55][11] = 176;
     map_array[55][12] = 176;
     map_array[55][13] = 176;
     map_array[55][14] = 176;
     map_array[55][15] = 176;
     map_array[55][16] = 176;
     map_array[54][7] = 'I';
     map_array[54][8] = 'N';
     map_array[54][9] = 'F';
     map_array[54][10] = 'I';
     map_array[54][11] = 'R';
     map_array[54][12] = 'M';
     map_array[54][13] = 'A';
     map_array[54][14] = 'R';
     map_array[54][15] = 'Y';

     //Horizontal arrow for the infirmary
     map_array[54][17] = '-';
     map_array[54][18] = '-';
     map_array[54][19] = '-';

}

void DrawMap::drawHold()
{
     //The hold
     map_array[61][33] = 176;
     map_array[61][34] = 176;
     map_array[61][35] = 176;
     map_array[61][36] = 176;
     map_array[61][37] = 176;
     map_array[61][38] = 176;
     map_array[61][39] = 176;
     map_array[61][40] = 176;
     map_array[61][41] = 176;
     map_array[61][42] = 176;
     map_array[62][33] = 176;
     map_array[62][42] = 176;
     map_array[63][33] = 176;
     map_array[63][34] = 176;
     map_array[63][35] = 176;
     map_array[63][36] = 176;
     map_array[63][37] = 176;
     map_array[63][38] = 176;
     map_array[63][39] = 176;
     map_array[63][40] = 176;
     map_array[63][41] = 176;
     map_array[63][42] = 176;
     map_array[62][34] = 'T';
     map_array[62][35] = 'H';
     map_array[62][36] = 'E';
     map_array[62][38] = 'H';
     map_array[62][39] = 'O';
     map_array[62][40] = 'L';
     map_array[62][41] = 'D';

     //vertical arrow for the hold
     map_array[57][37] = '|';
     map_array[58][37] = '|';
     map_array[59][37] = '|';

}
