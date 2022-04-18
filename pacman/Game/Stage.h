#pragma once
#include "Game.h"
#include "Character.h"
#include "../Framework/GameTime.h"

#define WALL "¢Ì"
#define COOKIE "¨¬"
#define GHOST "£¦"

#define PLAYER_W "¡ã"
#define PLAYER_A "¢¸"
#define PLAYER_S "¡å"
#define PLAYER_D "¢º"

class Stage : public Game {
private:
	GameTime* gametime;

	Character* player;

	Character* ghostArr[5];
	int ghostCount;

	int cookieCount;
	int score;
	
	void RewriteScreen(int i, int j, const char* sprite);

	bool FindWay(int mapValue[][64], int i, int j, int distance);

	void GhostMove(int idx);

	bool Move();

public:
	Stage(int sizeX, int sizeY, Input*& input, GameTime*& gametime);

	bool LoadFile(char* filename);

	bool Update();

	bool IsDead();

	bool IsClear();

	virtual ~Stage();
};