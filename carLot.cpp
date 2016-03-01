/*
 Author:                        Sarah Newport
 Date Created:                  22 November 2014
 Last Modification Date:        23 November 2014
 Filename:                      carlot.cpp
 Overview: 
    A program that allows a user to enter information on when cars are sold and at what price. It will give the user an inventory of the cars available for sale and profits for specific months.
 
 Input: menu choice of 1 -4, information on car - sale price, date sold.
 
 Output: inventory of cars, profits for specific months
 */

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

//date specified for user input
struct Date
{
    int day;
    int month;
    int year;
};

struct Car
{
    string make;                                                              //car make
    string model;                                                                  //car model
    int year;                                                                    //year car made
    Date datePurchased;                                                                     //date car purchased by lot
    double purchasePrice;                                                           //price car purchased for by lot
    bool isSold;                                                                            //was car sold
    Date dateSold;                                                                          //date car was sold
    double salePrice;                                                                       //price car sold for
};

void carInfo(vector<Car>& carVect, int count);           //function to add car details to list (vector)
void lotInv(vector<Car>& carVect, int count);            //lists the lots current inventory(all non-sold)
void profitMonth(vector<Car>& carVect, int count);       //calculates a profit based on month and year selected

int main()
{
    vector<Car> carVect;                                                            //vector of structs of Car, lot inventory tracker
    int menu;                                                                                       //menu selection input
    int count;                                                                                      //positional tracker
    
    do
    {
        cout << "Please view the allowable menu options.\n";
        cout << "1. Add Entry - Input of car info.\n";
        cout << "2. List - Lists current invetory on site.\n";
        cout << "3. Profit - Displays profit for a given month/year.\n";
        cout << "4. Exit - Terminates Program.\n";
        cout << "Please enter a menu choice 1 - 4: " << endl;
        cin >> menu;
        cin.ignore();
        
        //verify that valid menu choice is selected.
        while ((menu > 4) || (menu < 1))
        {
            cin.clear();
            cout << "ERROR" << endl;
            cout << "Please enter a choice between 1 and 4: ";
            cin >> menu;
            cin.ignore();
        }
        
        switch (menu)
        {
            case 1:
                carInfo(carVect, count);
                count++;
                break;
                
            case 2:
                lotInv(carVect, count);
                break;
                
            case 3:
                profitMonth(carVect, count);
                break;
                
            case 4:
                return(0);
                
        }
    }while(1);
    
    return 0;
}

void carInfo(vector<Car>& carVect, int count)
{
    char sold;                                              //was car sold
    
    //create element in vector for next inventory piece
    carVect.push_back(Car());
    
    cout << "Make: ";
    getline(cin, carVect[count].make);
    
    cout << "Model: ";
    getline(cin, carVect[count].model);
    
    cout << "Year: ";
    cin >> carVect[count].year;
    cin.ignore();
    
    
    cout << "Month of purchase (1 - 12): ";
    cin >> carVect[count].datePurchased.month;
    
    //validates that a correct number for month is entered
    while(carVect[count].datePurchased.month > 12 || carVect[count].datePurchased.month < 1)
    {
        cin.clear();
        cout << "ERROR" << endl;
        cout << "Please be sure to enter a valid numeric month.\n";
        cout << "Month: ";
        cin >> carVect[count].datePurchased.month;
        cin.ignore();
    }
    
    //enter the day for February
    if(carVect[count].datePurchased.month == 2)
    {
        cout << "Day (1-28): ";
        cin >> carVect[count].datePurchased.day;
        cin.ignore();
        
        while(carVect[count].datePurchased.day > 28 || carVect[count].datePurchased.day < 1)
        {
            cin.clear();
            cout << "ERROR" << endl;
            cout << "Please be sure to enter a valid date for February (1-28).\n";
            cout << "Day: ";
            cin >> carVect[count].datePurchased.day;
            cin.ignore();
        }
    }
    
    //enter the day for any month with 30 days
    else if(carVect[count].datePurchased.month == 4 || carVect[count].datePurchased.month == 6
            || carVect[count].datePurchased.month == 9 || carVect[count].datePurchased.month == 11)
    {
        cout << "Day (1-30): ";
        cin >> carVect[count].datePurchased.day;
        cin.ignore();
        
        while(carVect[count].datePurchased.day > 30 || carVect[count].datePurchased.day < 1)
        {
            cin.clear();
            cout << "ERROR" << endl;
            cout << "Please be sure to enter a valid date for the given month (1-30).\n";
            cout << "Day: ";
            cin >> carVect[count].datePurchased.day;
            cin.ignore();
        }
    }
    
    //enter the day for any month with 31 days
    else
    {
        cout << "Day (1-31): ";
        cin >> carVect[count].datePurchased.day;
        cin.ignore();
        
        while(carVect[count].datePurchased.day > 31 || carVect[count].datePurchased.day < 1)
        {
            cin.clear();
            cout << "ERROR" << endl;
            cout << "Please be sure to enter a valid date for the given month (1-31).\n";
            cout << "Day: ";
            cin >> carVect[count].datePurchased.day;
            cin.ignore();
        }
    }
    
    //year of purchase
    cout << "Year: ";
    cin >> carVect[count].datePurchased.year;
    cin.ignore();
    
    
    cout << "Price purchased: ";
    cin >> carVect[count].purchasePrice;
    cin.ignore();
    
    cout << "Has this vehicle been sold? (Y/N): ";
    cin >> sold;
    
    if(sold == 'Y' || sold == 'y')
    {
        carVect[count].isSold = true;
    }
    
    if(!(sold == 'Y' || sold == 'y'))
    {
        carVect[count].isSold = false;
    }
    
    cout << carVect[count].isSold << endl;
    
    if(carVect[count].isSold == true)
    {
        cout << "Month of sale (1 - 12): ";
        cin >> carVect[count].dateSold.month;
        
        //validates that a correct number for month is entered
        while(carVect[count].dateSold.month > 12 || carVect[count].dateSold.month < 1)
        {
            cin.clear();
            cout << "ERROR" << endl;
            cout << "Please be sure to enter a valid numeric month.\n";
            cout << "Month: ";
            cin >> carVect[count].dateSold.month;
            cin.ignore();
        }
        
        //enter the day for February
        if(carVect[count].dateSold.month == 2)
        {
            cout << "Day (1-28): ";
            cin >> carVect[count].dateSold.day;
            cin.ignore();
            
            while(carVect[count].dateSold.day > 28 || carVect[count].dateSold.day < 1)
            {
                cin.clear();
                cout << "ERROR" << endl;
                cout << "Please be sure to enter a valid date for February (1-28).\n";
                cout << "Day: ";
                cin >> carVect[count].dateSold.day;
                cin.ignore();
            }
        }
        
        //enter the day for any month with 30 days
        else if(carVect[count].dateSold.month == 4 || carVect[count].dateSold.month == 6
                || carVect[count].dateSold.month == 9 || carVect[count].dateSold.month == 11)
        {
            cout << "Day (1-30): ";
            cin >> carVect[count].dateSold.day;
            cin.ignore();
            
            while(carVect[count].dateSold.day > 30 || carVect[count].dateSold.day < 1)
            {
                cin.clear();
                cout << "ERROR" << endl;
                cout << "Please be sure to enter a valid date for the given month (1-30).\n";
                cout << "Day: ";
                cin >> carVect[count].dateSold.day;
                cin.ignore();
            }
        }
        
        //enter the day for any month with 31 days
        else
        {
            cout << "Day (1-31): ";
            cin >> carVect[count].dateSold.day;
            cin.ignore();
            
            while(carVect[count].dateSold.day > 31 || carVect[count].dateSold.day < 1)
            {
                cin.clear();
                cout << "ERROR" << endl;
                cout << "Please be sure to enter a valid date for the given month (1-31).\n";
                cout << "Day: ";
                cin >> carVect[count].dateSold.day;
                cin.ignore();
            }
        }
        
        //year of sale
        cout << "Year: ";
        cin >> carVect[count].dateSold.year;
        cin.ignore();
        
        cout << "Sale price: ";
        cin >> carVect[count].salePrice;
        cin.ignore();
    }
    
    cout << "\n\n";
    
}



void lotInv(vector<Car>& carVect, int count)
{
    cout << "Current lot inventory" << endl;
    cout << setw(15) << left << "Make" << "\t\t" <<"Model" << "\t\t" << "Year" << "\t\t" << "Purchase Date"
    << "\t\t" << "Purchase Price" <<       endl;
    
    for(int i = 0; i < carVect.size(); i++)
    {
        //only display cars that were NOT sold
        if(carVect[i].isSold == false)
        {
            cout << setw(15) << left << carVect[i].make << "\t\t" << carVect[i].model << "\t\t"
            << carVect[i].year << "\t\t" << carVect[i].datePurchased.month << "/"
            << carVect[i].datePurchased.day << "/" << carVect[i].datePurchased.year
            << "\t\t" << "$" << showpoint << setprecision(2) << fixed << carVect[i].purchasePrice << endl;
            
            cout << endl;
        }
    }
}

void profitMonth(vector<Car>& carVect, int count)
{
    int Pmonth;                                             //month selected to chart profits
    int Pyear;                                              //year selected to chart profits
    double Ppurchase;                               //adds up total purchase amounts for that month/year
    double Psold;                                   //adds up all sold prices for month/year
    double profits;                                 //calculated profits
    
    cout << "Generate a profit report based on date.\n";
    cout << "Month: ";
    cin >> Pmonth;
    cin.ignore();
    cout << "Year: ";
    cin >> Pyear;
    cin.ignore();
    
    for(int i = 0; i < carVect.size(); i++)
    {
        Ppurchase += carVect[i].purchasePrice;
        
        //parse vector based on month
        if(carVect[i].dateSold.month == Pmonth)
        {
            //parse vector based on year
            if(carVect[i].dateSold.year == Pyear)
            {
                Psold += carVect[i].salePrice;
            }
        }
        
    }
    
    profits = Psold - Ppurchase;    //calculated profits (sales - overhead)
    
    cout << "Total Profits for given month/year: " << endl;
    cout << "$" << showpoint << setprecision(2) << fixed << profits << endl;

}

