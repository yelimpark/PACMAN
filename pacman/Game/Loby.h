#pragma once
#include "Game.h"

class Loby : public Game{
private:

public:
	Loby(int sizeX, int sizeY, Input*& input);

	bool Update();

	virtual ~Loby();
};