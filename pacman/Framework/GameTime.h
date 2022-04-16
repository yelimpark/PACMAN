#pragma once
#include <ctime>

class GameTime {
	clock_t s_prevTick;
	float s_deltaTime;

public :
	GameTime();

	/// <summary>
	/// 타이머를 최신화한다.
	/// </summary>
	void UpdateTimer();

	/// <summary>
	/// 델타 타임 (프레임간 시간)을 구한다.
	/// </summary>
	float GetDeltaTime();

	~GameTime();
};