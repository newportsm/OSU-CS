/*
Author:                     Sarah Newport
Date Created:               7 November 2014
Last Modification Date:     7 November 2014
Filename:                   grades.cpp

Overview:                   A program that acts a histogram for grades of a quiz. Teacher inputs grades to recieve
                            histogram data.
Input:                      quiz grades for students
Output:                     histogram data for each score 0 - 5
*/

#include <iostream>

using namespace std;

int Histogram (int, int); //declare histogram function

int main () {
    
    int ClassSize; // class size
    int Grades[6]; // array for grades
    int x; //counter
    
    cout << "How many student's took the quiz?" << endl;
    cin >> ClassSize;
    
    
    int Scores[ClassSize]; // scores the students got
    cout << "Please enter each student's grade followed by enter." << endl;
    for (x = 0; x < ClassSize; x++) {
        cin >> Scores[x]; // user enters in all grades

    }
    
    Histogram (int Grades[6], int Scores[ClassSize]); // call to Histogram function
    
    return 0;

}

int Histogram (int Grades[6], int Scores[ClassSize]) {
        
    if (Scores[x] == 0)
        Grades[0]++;
    if (Scores[x] == 1)
        Grades[1]++;
    if (Scores[x] == 2)
        Grades[2]++;
    if (Scores[x] == 3)
        Grades[3]++;
    if (Scores[x] == 4)
        Grades[4]++;
    else (Scores[x] == 5)
        grades[5]++;
    
    cout << "Here's your class Histogram:" << endl;
    cout << Grades[0] << " grade(s) of 0" << endl;
    cout << Grades[1] << " grade(s) of 1" << endl;
    cout << Grades[2] << " grade(s) of 2" << endl;
    cout << Grades[3] << " grade(s) of 3" << endl;
    cout << Grades[4] << " grade(s) of 4" << endl;
    cout << Grades[5] << " grade(s) of 5" << endl;
    
    
}