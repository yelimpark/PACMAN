#include "../stdafx.h"
#include "Character.h"

Character::Character(int xForce, int yForce, float speed, const char* sprite)
	:x(0), y(0), xForce(xForce * 2), yForce(yForce), timeAfterMove(0.0f), speed(speed), isDead(false)
{
	strcpy_s(this->sprite, sizeof(this->sprite), sprite);
	strcpy_s(onWhat, sizeof(onWhat), "  ");
}

Character::Character(int x, int y, int xForce, int yForce, float speed, const char* sprite)
	: x(x), y(y), xForce(xForce * 2), yForce(yForce), timeAfterMove(0.0f), speed(speed), isDead(false)
{
	strcpy_s(this->sprite, sizeof(this->sprite), sprite);
	strcpy_s(onWhat, sizeof(onWhat), "  ");
}

void Character::SetPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Character::SetForce(int x, int y)
{
	xForce = x * 2;
	yForce = y;
}

void Character::SetSprite(const char* sprite)
{
	strcpy_s(this->sprite, sizeof(this->sprite), sprite);
}

void Character::SetOnWhat(const char* sprite)
{
	strcpy_s(onWhat, sizeof(onWhat), sprite);
}

void Character::Rotate90()
{
	if (xForce == 0 && yForce == -1) {
		SetForce(1, 0);
	}
	else if (xForce == 2 && yForce == 0) {
		SetForce(0, 1);
	}
	else if (xForce == 0 && yForce == 1) {
		SetForce(-1, 0);
	}
	else {
		SetForce(0, -1);
	}
}

void Character::Dead()
{
	isDead = true;
}

void Character::UpdatePos()
{
	SetPos(x + xForce, y + yForce);
}

int Character::GetPosX()
{
	return x;
}

int Character::GetPosY()
{
	return y;
}

int Character::GetXForce()
{
	return xForce;
}

int Character::GetYForce()
{
	return yForce;
}

float Character::AddTimeAfterMove(float dTime)
{
	return timeAfterMove += dTime;
}

float Character::GetSpeed()
{
	return speed;
}

char* Character::GetSprite()
{
	return sprite;
}

char* Character::GetOnWhat()
{
	return onWhat;
}

bool Character::GetIsDead()
{
	return isDead;
}

bool Character::IsTimeToMove()
{
	if (timeAfterMove > speed) {
		timeAfterMove = 0;
		return true;
	}
	return false;
}

Character::~Character()
{
}
