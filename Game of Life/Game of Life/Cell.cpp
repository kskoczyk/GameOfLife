#include "Cell.h"

void Cell::setState(bool &&newState)
{
	isAlive = newState;
}

Cell::Cell()
{

}

Cell::Cell(bool state)
{
	isAlive = state;
}

bool Cell::getState()
{
	return isAlive;
}
