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

// game 수정
// 1.loby랑 엔딩 하는일이 똑같음
// 2. 파일 이름을 ... game으로 로비 엔딩 퉁칠거면 그대로 아니면 안으로 넣어야 하는데
// 둘다 게임으로 퉁치면 이름이 좀 애매한가...? 

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

			// 예외처리 고민해보기
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
