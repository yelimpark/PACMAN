#pragma once
#include "Game.h"

class Menu : public Game {
private:
	int cursorX;
	int cursorY;

	void MoveCursor(int x, int y);
public:
	Menu(int sizeX, int sizeY, Input*& input);

	bool LoadFile(const char* filename);

	bool Update();

	int GetStageNum() const;

	virtual ~Menu();
};