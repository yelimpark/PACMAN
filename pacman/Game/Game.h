#pragma once
#include <stdbool.h>
#include "../Framework/Input.h"

class Game {
protected:
	char** screen;
	int sizeX;
	int sizeY;
	Input* input;

public:
	Game(int sizeX, int sizeY, Input * &input);

	virtual bool LoadFile(const char * filename);

	char** GetScreen() const;

	virtual bool HandleInput() = 0;

	virtual ~Game();
};