#pragma once

class Cell
{
	bool isAlive;

public:
	Cell();
	Cell(bool state);
	bool getState();
	void setState(bool &&newState);
};
