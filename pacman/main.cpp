#include "stdafx.h"
#include "Framework/GameFramwork.h"

int main() {
	GameFramwork gameFramework;

	if (false == gameFramework.Initialize())
	{
		puts("������ �ε��ϴ� �� ������ ������ϴ�.");

		return 1;
	}

	return gameFramework.Run();
}