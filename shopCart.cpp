/*
 Author:                            Sarah Newport
 Date Created:                      20 November 2014
 Last Modification Date:            23 November 2014
 Filename:                          shopCart.cpp
 Overview:
    A program that works as a shopping cart where a user can add items, see the content of said items, see the total price, and choice to quit.
 Input: user command for menu choice (1-4), product name, price of item, and quantity.
 Output: displays of list of all items and individual prices and quantities. outputs a total for the cost of everything before sales tax.
    */



#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


struct Item
{
    string name;
    double price;
    int quantity;
};

void addItem (Item shoppingCart[], const int array, int count);
void listCart(Item shoppingCart[], const int array, int count);
void finalTotal(Item shoppingCart[], const int array, int count);

int main ()
{
    const int array = 100;          //size of cart array
    int menu;                                       //menu selection input
    Item shoppingCart[array];       //array to hold all items
    int count = 0;                          //keeps track of shopping cart position additions
    
    do
    {
        cout << "Please view the allowable options with your cart.\n";
        cout << "1. Add - Allows addition of item to cart.\n";
        cout << "2. List - Lists contents of current cart; including price and quantity.\n";
        cout << "3. Total - Displays current final total w/o sales tax.\n";
        cout << "4. Quit Program.\n";
        cout << "Please enter a menu choice 1 - 4: " << endl;
        cin >> menu;
        
        while ((menu > 4) && (menu < 1))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "ERROR" << endl;
            cout << "Please be sure to enter a number between 1 and 4.";
            cin >> menu;
        }
        
        switch (menu)
        {
            case 1:
                addItem(shoppingCart, array, count);
                count++;
                break;
                
            case 2:
                listCart(shoppingCart, array, count);
                break;
                
            case 3:
                finalTotal(shoppingCart, array, count);
                break;
                
            case 4:
                return(0);
                
        }
        
    }while(1);
    
    return 0;
}

void addItem (Item shoppingCart[], const int array, int count)
{
    
    cout << "\nPlease enter the details of the item to be added to your cart.\n";
    cout << "Product name: ";
    getline(cin, shoppingCart[count].name);
    cin.ignore(256, '\n');
    
    cout << "Price: ";
    cin >> shoppingCart[count].price;
    
    cout << "Quantity: ";
    cin >> shoppingCart[count].quantity;
    
    cout << "\n\n";
    
}

void listCart(Item shoppingCart[], const int array, int count)
{
    cout << setw(15) << left << "Product" << "\t" <<" Price" << "\t" << right << " Quantity" << endl;
    
    for(int i = 0; i < count; i++)
    {
        cout << setw(15) << left << shoppingCart[i].name
        << "\t" << " $" << showpoint << setprecision(2) << fixed << shoppingCart[i].price
        << "\t" << " " << right << shoppingCart[i].quantity << endl;
        cout << "\n";
    }
}

void finalTotal(Item shoppingCart[], const int array, int count )
{
    double currentTotal;
    
    for(int i = 0; i < count; i++)
    {
        currentTotal += (shoppingCart[i].price * shoppingCart[i].quantity);
    }
    
    cout << "Your current total is " << showpoint << setprecision(2) << currentTotal << "." << endl;
    cout << endl;
}


