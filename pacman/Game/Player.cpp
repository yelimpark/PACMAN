#include "Player.h"
#include "../stdafx.h"

Player::Player(int xForce, int yForce, float plyerSpeed, const char* playerSprite)
	:playerX(0), playerY(0), xForce(xForce), yForce(yForce), timeAfterMove(0.0f), plyerSpeed(plyerSpeed), isDead(false)
{
	strcpy_s(this->playerSprite, sizeof(this->playerSprite), playerSprite);
}

Player::Player(int playerX, int playerY, int xForce, int yForce, float plyerSpeed, const char* playerSprite)
	:playerX(playerX), playerY(playerY), xForce(xForce), yForce(yForce), timeAfterMove(0.0f), plyerSpeed(plyerSpeed), isDead(false)
{
	strcpy_s(this->playerSprite, sizeof(this->playerSprite), playerSprite);
}

void Player::TriggerDead()
{
	isDead = true;
}

void Player::GetIsDead()
{
	return isDead;
}

void Player::SetPos(int x, int y)
{
	playerX = x;
	playerY = y;
}

void Player::SetForce(int x, int y)
{
	xForce = x * 2;
	yForce = y;
}

void Player::Update(float dTime)
{
	timeAfterMove += dTime;
}

void Player::Move()
{
	if (timeAfterMove > plyerSpeed) {
		SetPos(playerX + xForce, playerY + yForce);
	}
}

int Player::GetNextX() {
	return playerX + xForce;
}

int Player::GetNextY()
{
	return playerY + yForce;
}

void Player::SetPlayerSprite(const char* playerSprite)
{
	strcpy_s(this->playerSprite, sizeof(this->playerSprite), playerSprite);
}

Player::~Player()
{
}
