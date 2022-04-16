#pragma once
#include <ctime>

class GameTime {
	clock_t s_prevTick;
	float s_deltaTime;

public :
	GameTime();

	/// <summary>
	/// Ÿ�̸Ӹ� �ֽ�ȭ�Ѵ�.
	/// </summary>
	void UpdateTimer();

	/// <summary>
	/// ��Ÿ Ÿ�� (�����Ӱ� �ð�)�� ���Ѵ�.
	/// </summary>
	float GetDeltaTime();

	~GameTime();
};