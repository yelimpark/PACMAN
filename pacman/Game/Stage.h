#pragma once
#include "Game.h"

#define COOKIE "¨¬"
#define GHOST "£¦"
#define PLAYER_W "¡ã"
#define PLAYER_A "¢¸"
#define PLAYER_S "¡å"
#define PLAYER_D "¢º"
#define WALL '#';

class Stage : public Game {
private:
	int playerX;
	int playerY;
	int cookieCount;
	bool isDead;
	
	void UpdatePos(int x, int y, const char* playerSprite);

	void RewriteScreen();

	bool Move(int x, int y, const char* playerSprite);

public:
	Stage(int sizeX, int sizeY, Input*& input);

	bool LoadFile(char* filename);

	bool HandleInput();

	bool IsClear();

	virtual ~Stage();
};