/*
 Author:                            Sarah Newport
 Date Created:                      15 November 2014
 Last Modification Date:            16 November 2014
 Filename:                          tictactoe.cpp
 Overview:                          A tictactoe game using a 2d array.
 Input:                             user enters a row and column intersection for their move
 Output:                            game winner
 */

#include <iostream>
#include <cstring>
#include <stdlib.h>
using namespace std;

void blank_board(char board[][4], int size); //declare blank board function
bool player_turn(char board[][4], int size, bool &player_1); //function for player turns and moves
bool win_check_X(char board[][4], int size, int &wins_1); //function to check X wins
bool win_check_O(char board[][4], int size, int &wins_2); // function to check 0 wins
bool tie_check(char board[][4], int size);

int main (int argc, char* argv[])
{
    int games;              //number of games that wish to be played
    int played = 0;         //number of games played
    int wins_1 = 0;         //number of wins for player 1
    int wins_2 = 0;         //number of wins for player 2
    char board[4][4];       //tic tac toe board
    int size = 4;           //size of array row
    bool player_1;          //bool value to help switch turns
    bool over_X;            //bool value to tell if X won a game
    bool over_O;            //bool value to tell if O won a game
    bool tie;               //is game tied
    
    //if no command line entered default number of games to 1
    if(argc == 1)
        games = 1;
    
    //if command line entered, games equals number entered by user
    else
        games = atoi(argv[1]);
    
    do
    {
        cout << "It's time to play Tic Tac Toe! Please enter your moves "
        << "in coordinate form." << endl;
        
        blank_board(board, size);
        
        if(played % 2 == 0)
        {
            cout << "Player 1, you are 'X' and will be going first.\n";
            player_1 = true;
        }
        
        else
        {
            cout << "Player 2, you are 'O' and will be going first.\n";
            player_1 = false;
        }
        
        do
        {
            
            player_1 = player_turn(board, size, player_1);
            over_X = win_check_X(board, size, wins_1);
            over_O = win_check_O(board, size, wins_2);
            tie = tie_check(board, size);
            
        }while((over_X == false) && (over_O == false) && (tie == false));
        
        if(over_X == true)
            cout << "Player 1 has won the game.\n";
        if(over_O == true)
            cout << "Player 2 has won the game.\n";
        if(tie == true)
            cout << "That game was a tie.\n";
        
        played++;
        
    }while(played < games);
    
    cout << "Player 1 has won " << wins_1 << " games." << endl;
    cout << "Player 2 has won " << wins_2 << " games." << endl;
    
    if(wins_1 > wins_2)
        cout << "Player 1 is the overall victor.\n";
    if(wins_2 > wins_1)
        cout << "Player 2 is the overall victor.\n";
    if(wins_1 == wins_2)
        cout << "The end result is a tie.\n";
    
    return 0;
}

void blank_board(char board[][4], int size) // function to display board and updated moves
{
    board[0][0] = ' ';
    board[0][1] = '1';
    board[0][2] = '2';
    board[0][3] = '3';
    board[1][0] = '1';
    board[2][0] = '2';
    board[3][0] = '3';
    
    board[1][1] = '.';
    board[2][1] = '.';
    board[3][1] = '.';
    board[1][2] = '.';
    board[2][2] = '.';
    board[3][2] = '.';
    board[1][3] = '.';
    board[2][3] = '.';
    board[3][3] = '.';
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << board[i][j] << " ";
        }
        
        cout << endl;
    }
}

bool player_turn(char board[][4], int size, bool &player_1) // function for user to enter moves
{
    int row;
    int col;
    
    if(player_1 == true)
    {
        cout << "Player 1, please enter your move: "; // prompt player one to enter move
        cin >> row;
        cin >> col;
        
        while(board[row][col] != '.')
        {
            cout << "That space has already been taken.\n"; //notify player that move is taken
            cout << "Player 1, please enter another move: "; // player 1 must enter new move
            cin >> row;
            cin >> col;
        }
        
        board[row][col] = 'X'; // enter X onto chosen space
        
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                cout << board[i][j] << " ";
            }
            
            cout << endl;
        }
        
        return false;
        
    }
    
    if(player_1 == false)
    {
        cout << "Player 2, please enter your move: "; //prompt player 2 to enter move
        cin >> row;
        cin >> col;
        
        while(board[row][col] != '.')
        {
            cout << "That space has already been taken.\n"; // notify player 2 that space is taken
            cout << "Player 2, please enter another move: ";
            cin >> row;
            cin >> col;
        }
        
        board[row][col] = 'O'; // enter 0 onto chosen space
        
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                cout << board[i][j] << " ";
            }
            
            cout << endl;
            
        }
        
        return true;
    }
}

bool win_check_X(char board[][4], int size, int &wins_1) // function to check for a win for X
{
    if (board[1][1] == 'X' && board[2][2] == 'X' && board[3][3] == 'X')
    {
        wins_1++;
        return true;
    }
    
    else if (board[3][1] == 'X' && board[2][2] == 'X' && board[1][3] == 'X')
    {
        wins_1++;
        return true;
    }
    
    else if (board[1][1] == 'X' && board[1][2] == 'X' && board[1][3] == 'X')
    {
        wins_1++;
        return true;
    }
    
    else if (board[1][2] == 'X' && board[2][2] == 'X' && board[3][2] == 'X')
    {
        wins_1++;
        return true;
    }
    
    else if (board[1][3] == 'X' && board[2][3] == 'X' && board[3][3] == 'X')
    {
        wins_1++;
        return true;
    }
    
    else if (board[2][1] == 'X' && board[2][2] == 'X' && board[2][3] == 'X')
    {
        wins_1++;
        return true;
    }
    
    else if (board[3][1] == 'X' && board[3][2] == 'X' && board[3][3] == 'X')
    {
        wins_1++;
        return true;
    }
    
    else if (board[1][1] == 'X' && board[2][1] == 'X' && board[3][1] == 'X')
    {
        wins_1++;
        return true;
    }
    
    else
        return false;
}

bool win_check_O(char board[][4], int size, int &wins_2) //function to check for wins for 0
{
    if (board[1][1] == 'O' && board[2][2] == 'O' && board[3][3] == 'O')
    {
        wins_2++;
        return true;
    }
    
    else if (board[3][1] == 'O' && board[2][2] == 'O' && board[1][3] == 'O')
    {
        wins_2++;
        return true;
    }
    
    else if (board[1][1] == 'O' && board[1][2] == 'O' && board[1][3] == 'O')
    {
        wins_2++;
        return true;
    }
    
    else if (board[1][2] == 'O' && board[2][2] == 'O' && board[3][2] == 'O')
    {
        wins_2++;
        return true;
    }
    
    else if (board[1][3] == 'O' && board[2][3] == 'O' && board[3][3] == 'O')
    {
        wins_2++;
        return true;
    }
    
    else if (board[2][1] == 'O' && board[2][2] == 'O' && board[2][3] == 'O')
    {
        wins_2++;
        return true;
    }
    
    else if (board[3][1] == 'O' && board[3][2] == 'O' && board[3][3] == 'O')
    {
        wins_2++;
        return true;
    }
    
    else if (board[1][1] == 'O' && board[2][1] == 'O' && board[3][1] == 'O')
    {
        wins_2++;
        return true;
    }
    
    else
        return false;
}

bool tie_check(char board[][4], int size)
{
    
    if (board[1][1] != '.' && board[1][2] != '.' && board[1][3] == '.'
        && board[2][1] != '.' && board[2][2] != '.' && board[2][3] == '.'
        && board[3][1] != '.' && board[3][2] != '.' && board[3][3] == '.')
    {
        return true;
    }
    
    return false;
}

