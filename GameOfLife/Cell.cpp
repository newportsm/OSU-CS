/*
 Author:                    Sarah Newport
 Date Created:              12 January 2015
 Last Edited:               18 January 2015
 Filename:                  Cell.cpp
 Overview:                  create cells for the game
 Input:
 Output:
 */

#include <stdio.h>
#include "Cell.h"

Cell::Cell() {};
//A cell is one item on our gameBoard

Cell::Cell(CellState initState)
{
    state = initState;
}

//Getters and setters
CellState Cell::GetNextState()
{
    return nextState;
}

CellState Cell::GetState()
{
    return state;
}

void Cell::Increment()
{
    state = nextState;
}

void Cell::SetNextState(CellState setState)
{
    nextState = setState;
}