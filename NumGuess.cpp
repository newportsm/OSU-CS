/*
Author:             Sarah Newport
Date Created:       12 October 2014
Last Modification:  12 October 2014
File name:          NumGuess.cpp
Overview:
    This program is a number guessing game for two players. Player 1 inputs a secret number and Player 2 has four guesses to get it right.
Input: Secret number, guessed number, Yes or No if the user wants to play again
Output: Adjusted range after failed guesses, updated number of guesses left, congratulations if Player 2 guesses correctly, repeat the game if users input Yes
*/

#include <iostream>
using namespace std;

int main()

{
    char PlayAgain = 'Y';
    while (PlayAgain == 'Y')
    {
    
        int SecretNum; //number to be inputted by Player 1
        int Number; // number that Player 2 guesses with
        int Guesses = 0; // number of guesses Player 2 has
    
    
        cout << "Welcome to the Number Guessing Game! \n";
        cout << "Player 1 please pick a secret number to be guessed by Player 2 between 1 - 20. \n";
        cin >> SecretNum;
        cout<< string(50, '\n'); //to clear the screen so that Player 2 can't see the number
    
        cout << "Hello Player 2, you have 4 guesses to get the correct number. \n";
        cout << "Please guess your first number in the range of 1 to 20. \n";
        cin >> Number; // first guess of Player 2
        Guesses++;
        
        while (Guesses < 4)
        {
            if (Number == SecretNum)
                {
                    cout << "Congratulations!! You guessed the correct number " << SecretNum << ".\n";
                    break;
                }
            
            else if (Number > SecretNum)
                {
                    cout << "Your number guess is a little on the high side, try guessing in the range of 1 - ";
                    cout << (Number - 1) << ". You have used " << Guesses++ << " guess, try again! \n";
                    cin >> Number;
                
                }
            
            else if (Number < SecretNum)
                {
                    cout << "Your number guess is a little on the low side, try guessing in the range of ";
                    cout << (Number + 1) << " - 20. You have used " << Guesses++ << " guess, try again! \n";
                    cin >> Number;
                
                }
            
            else if (Guesses == 4)
                {
                    cout << "Wrong again. You don't have any guesses left. \n";
                    cout << "The secret number was " << SecretNum << ". \n";
                }
            
        }
            cout << "Do you wish the play the game again?\n";
            cout << "Please type Y (Yes) or N (No). \n";
            cin >> PlayAgain;
            
    }
             

             
    return 0;
}
