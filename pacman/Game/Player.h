#pragma once

#define PLAYER_W "¡ã"
#define PLAYER_A "¢¸"
#define PLAYER_S "¡å"
#define PLAYER_D "¢º"

class Player {
protected :
	int playerX;
	int playerY;

	int xForce;
	int yForce;

	float timeAfterMove;
	float plyerSpeed;

	char playerSprite[3];

	bool isDead;

public :
	Player(int xForce, int yForce, float plyerSpeed, const char* playerSprite);

	Player(int playerX, int playerY, int xForce, int yForce, float plyerSpeed, const char * playerSprite);

	void TriggerDead();

	void GetIsDead();

	void SetPos(int x, int y);

	void SetForce(int x, int y);

	void Update(float dTime);

	void Move();

	int GetNextX();

	int GetNextY();

	void SetPlayerSprite(const char* playerSprite);

	~Player();
};