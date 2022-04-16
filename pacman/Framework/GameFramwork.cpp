#include "GameFramwork.h"
#include "../stdafx.h"

GameFramwork::GameFramwork()
	:gameStatus(GameStatus::LOBY), level(StageLevel::STAGE_01), gameStageSizeX(64), gameStageSizeY(24),
	renderer(nullptr), input(nullptr), gametime(nullptr),
	loby(nullptr), menu(nullptr), stage(nullptr)
{
	renderer = new Renderer(gameStageSizeX, gameStageSizeY);
	gametime = new GameTime();
	input = new Input();

	loby = new Loby(gameStageSizeX, gameStageSizeY, input);
	menu = new Menu(gameStageSizeX, gameStageSizeY, input);
	stage = new Stage(gameStageSizeX, gameStageSizeY, input);
}

// game ����
// 1.loby�� ���� �ϴ����� �Ȱ���
// 2. ���� �̸��� ... game���� �κ� ���� ��ĥ�Ÿ� �״�� �ƴϸ� ������ �־�� �ϴµ�
// �Ѵ� �������� ��ġ�� �̸��� �� �ָ��Ѱ�...? 

bool GameFramwork::Initialize()
{
	if (renderer->InitializeRenderer() == false) return false;
	if (loby->LoadFile("../Game/textfile/Loby.txt") == false) return false;
	if (menu->LoadFile("../Game/textfile/Menu.txt") == false) return false;

	return true;
}

void GameFramwork::update() {
	switch (gameStatus)
	{
	case GameStatus::LOBY:
		if (loby->HandleInput())
			gameStatus = GameStatus::MENU;
		break;
	case GameStatus::MENU:
		if (menu->HandleInput()) {
			level = (StageLevel)menu->GetStageNum();
			char path[MAX_PATH] = { 0 };
			sprintf_s(path, sizeof(path), "../Stage/Stage%02d.txt", (int32_t)level);

			// ����ó�� ����غ���
			if (stage->LoadFile(path) == false) return;

			gameStatus = GameStatus::STAGE;
		}
		break;
	case GameStatus::STAGE:
		stage->HandleInput();
		break;
	case GameStatus::END:
		break;
	default:
		break;
	}
}

void GameFramwork::render() {
	switch (gameStatus)
	{
	case GameStatus::LOBY:
		renderer->Render(loby->GetScreen());
		break;

	case GameStatus::MENU:
		renderer->Render(menu->GetScreen());
		break;

	case GameStatus::STAGE:
		renderer->Render(stage->GetScreen());
		break;

	case GameStatus::END:
		//RenderMap(GetMap());
		break;

	default:
		break;
	}
}

int32_t GameFramwork::Run()
{
	while (true)
	{
		gametime->UpdateTimer();
		input->UpdateInput();
		update();
		render();

		if (stage->IsClear()) break;
		if (gameStatus == GameStatus::TERMINATE) break;
	}

	return 0;
}

GameFramwork::~GameFramwork()
{
}
