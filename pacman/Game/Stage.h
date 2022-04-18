#pragma once
#include "Game.h"
#include "Player.h"
#include "../Framework/GameTime.h"

#define WALL "¢Ì"
#define COOKIE "¨¬"
#define GHOST "£¦"

class Stage : public Game {
private:
	Player * player;

	GameTime* gametime;

	int cookieCount;
	
	void RewriteScreen(int i, int j, const char* sprite);

	bool Move();

public:
	Stage(int sizeX, int sizeY, Input*& input, GameTime*& gametime);

	bool LoadFile(char* filename);

	bool Update();

	//bool IsClear();

	virtual ~Stage();
};