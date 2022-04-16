#include "GameTime.h"

GameTime::GameTime()
	:s_prevTick(clock()), s_deltaTime(0.0f)
{
}

void GameTime::UpdateTimer()
{
	clock_t currentTick = clock();

	s_deltaTime = (currentTick - s_prevTick) / (float)CLOCKS_PER_SEC;

	s_prevTick = currentTick;
}

float GameTime::GetDeltaTime()
{
	return s_deltaTime;
}

GameTime::~GameTime()
{

}
