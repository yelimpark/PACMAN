#pragma once

class Player {
private :
	int playerX;
	int playerY;

	int xForce;
	int yForce;

	float timeAfterMove;
	float plyerSpeed;

	char playerSprite[3];

	bool isDead;

public :
	Player(const char * playerSprite);

	~Player();
};