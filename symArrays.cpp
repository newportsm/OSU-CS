/*
 Author:                    Sarah Newport
 Date Created:              15 November 2015
 Last Modification Date:    16 November 2015
 Filename:                  symArrays.cpp
 Overview:                  A program to determine is a line of arrays is symmetric or not.
 Input:                     Integers
 Output:                    If the line is symmetric or not.
 */

#include <iostream>
#include <cstring>
#include <stdlib.h>
using namespace std;


bool sym_1 (int array_1[], int size_1);
bool sym_2 (int array_2[], int size_2);
bool sym_3 (int array_3[], int size_3);

int main(int argc, char* argv[])
{
    int size_1; //size of first array
    int size_2; // size of second array
    int size_3; // size of third array
    int* array_1; //first array to be entered
    int* array_2; //second array to be entered
    int* array_3; //third array to be entered
    char peek; // to ensure that user is still entering information
    
    
    size_1 = atoi(argv[1]);
    size_2 = atoi(argv[2]);
    size_3 = atoi(argv[3]);
    
    array_1 = new int[size_1];
    array_2 = new int[size_2];
    array_3 = new int[size_3];
    
    do{
        //prompt user to enter first array
        cout << "\nPlease enter an array consisting of " << size_1 << " integers, each separated by a space: ";
        
        for (int i = 0; i < size_1; i++)
        {
            cin >> array_1[i];
        }
        
        peek = cin.peek();
        
    }while(peek == '\n');
    
    //prompt user for second array
    cout << "\nPlease enter an array consisting of " << size_2 << " integers, each separated by a space: ";
    
    for (int i = 0; i < size_2; i++)
    {
        cin >> array_2[i];
    }
    
    //prompt user for third array
    cout << "\nPlease enter an array consisting of " << size_3 << " integers, each separated by a space: ";
    
    for (int i = 0; i < size_3; i++)
    {
        cin >> array_3[i];
    }
    
    if(sym_1(array_1, size_1))
    {
        cout << "\nArray 1 was symmetric." << endl;
    }
    
    else
    {
        cout << "\nArray 1 was not symmetric." << endl;
    }
    
    if(sym_2(array_2, size_2))
    {
        cout << "\nArray 2 was symmetric." << endl;
    }
    
    else
    {
        cout << "\nArray 2 was not symmetric." << endl;
    }
    
    if(sym_3(array_3, size_3))
    {
        cout << "\nArray 3 was symmetric." << endl;
    }
    
    else
    {
        cout << "\nArray 3 was not symmetric." << endl;
    }
    
    delete [] array_1;
    delete [] array_2;
    delete [] array_3;
    
    return 0;
}

bool sym_1 (int array_1[], int size_1) //bool function to check first array
{
    for (int i = 0; i <= ((size_1)/2); ++i)
    {
        if(array_1[i] != array_1[size_1 - (1 + i)])
        {
            return false;
        }
    }
    
    return true;
}

bool sym_2 (int array_2[], int size_2) // bool function to check second array
{
    for (int i = 0; i <= ((size_2)/2); ++i)
    {
        if(array_2[i] != array_2[size_2 - (1 + i)])
        {
            return false;
        }
    }
    
    return true;
}

bool sym_3 (int array_3[], int size_3)// bool function to check third array
{
    for (int i = 0; i <= ((size_3)/2); ++i)
    {
        if(array_3[i] != array_3[size_3 - (1 + i)])
        {
            return false;
        }
    }
    
    return true;
}

