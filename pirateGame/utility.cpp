#include "utility.h"

#include <iostream>
#include <string>
#include <sstream>
#include <limits>


/**********************************************************************
** Function: input_verify()
** Description: Only integers are allowed as it prints error message to user if not correct and ask them to try again.
** By using this function with switch statements in which the user has to only enter the specified choice, i limit incorrect input from breaking the game.
** Parameters: none
**********************************************************************/
int input_verify()
{
     int choice = 0;
     std::string sn;
     std::stringstream ssn;
     std::cout << " Enter the number of your selection:";
     std::getline(std::cin, sn);
     ssn << sn;
     ssn >> choice;
     if (choice < 1)
     {
          std::cout << " Invalid input! Please enter integer values greater than 0 only." << std::endl;
          choice = input_verify();
     }
     return choice;
}

/**********************************************************************
** Function: void continue_fun()
** Description: Will pause game and ask user to press enter to continue
** Parameters: none
**********************************************************************/
void continue_fun()
{
     std::cout << std::endl << std::endl << std::endl;
     std::cout << " Press ENTER to continue... " << std::flush;
     std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
}
/**********************************************************************
** Function: void clear_screen()
** Description: Clears the screen by printing 300 blank lines
** Parameters: none
**********************************************************************/
void clear_screen()
{
     for (int i = 0; i < 300; i++)
     {
          std::cout << std::endl;
     }
}

char getUserChoice()
{
     char userInput[] = { 'N', 'E', 'S', 'W', 'X', 'I', 'Q', 'A', 'R', 'U', 'M', 'O', 'H', 'Y' };
     char choice;

     bool validInput = false;

     while (!validInput)
     {
          std::cout << " What will you do? : ";
          choice = std::getchar();
          std::cin.ignore(1000, '\n');

          for (int i = 0; i < 14; i++)
          {
               if (toupper(choice) == userInput[i])
               {
                    choice = toupper(choice);
                    validInput = true;
                    break;
               }
          }
          if (!validInput)
          {
               std::cout << " Invalid entry: Please try again." << std::endl;
          }
     }

     return choice;
}

char getUserYN()
{
     char choice;
     choice = std::getchar();
     std::cin.ignore(1000, '\n');

     while ((choice != 'y' && choice != 'n') && (choice != 'Y' && choice != 'N'))
     {
          std::cout << std::endl;
          std::cout << " Please enter \"y\" or \"n\" :" ;

          choice = std::getchar();
          std::cin.ignore(1000, '\n');
     }

     if (toupper(choice) == 'Y')
     {
          choice = toupper(choice);
     }
     else if (toupper(choice) == 'N')
     {
          choice = toupper(choice);
     }

     return choice;
}