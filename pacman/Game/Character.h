#pragma once

class Character {
private :
	int x;
	int y;

	int xForce;
	int yForce;

	float timeAfterMove;
	float speed;

	char sprite[3];

	char onWhat[3];

	bool isDead;

public :
	Character(int xForce, int yForce, float speed, const char* sprite);

	Character(int x, int y, int xForce, int yForce, float speed, const char* sprite);

	void SetPos(int x, int y);

	void SetForce(int x, int y);

	void SetSprite(const char* sprite);

	void SetOnWhat(const char* sprite);

	void Rotate90();

	void Dead();

	void UpdatePos();

	int GetPosX();
	
	int GetPosY();

	int GetXForce();

	int GetYForce();

	float AddTimeAfterMove(float dTime);

	float GetSpeed();

	char* GetSprite();

	char* GetOnWhat();

	bool GetIsDead();

	bool IsTimeToMove();

	~Character();
};