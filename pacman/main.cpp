#include "stdafx.h"
#include "Framework/GameFramwork.h"

int main() {
	GameFramwork gameFramework;

	if (false == gameFramework.Initialize())
	{
		puts("게임을 로딩하는 데 문제가 생겼습니다.");

		return 1;
	}

	return gameFramework.Run();
}