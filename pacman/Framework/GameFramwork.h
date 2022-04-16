#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "Renderer.h"
#include "../Game/Loby.h"
#include "../Game/Menu.h"
#include "../Game/Stage.h"
#include "Input.h"
#include "GameTime.h"

enum class GameStatus
{
	LOBY,
	MENU,
	STAGE,
	END,
	TERMINATE
};

enum class StageLevel
{
	STAGE_01 = 1,
	STAGE_02,
	STAGE_03,
	STAGE_04,
	STAGE_05,
	STAGE_MAX
};

class GameFramwork {
private:
	GameStatus gameStatus;
	StageLevel level;

	int gameStageSizeX;
	int gameStageSizeY;

	Renderer* renderer;
	GameTime* gametime;
	Input* input;

	Loby* loby;
	Menu* menu;
	Stage* stage;

	void update();

	void render();

public:
	GameFramwork();

	bool Initialize();

	int32_t Run();

	~GameFramwork();
};

