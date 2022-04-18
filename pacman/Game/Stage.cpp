#include "Stage.h"
#include "../stdafx.h"

Stage::Stage(int sizeX, int sizeY, Input*& input, GameTime* &gametime)
	:Game(sizeX, sizeY, input), ghostCount(0), cookieCount(1), score(0), gametime(gametime)
{
	player = new Character(1, 0, 0.3f, PLAYER_D);
	memset(ghostArr, NULL, sizeof(ghostArr));
}

void Stage::RewriteScreen(int i, int j, const char * sprite) {
	screen[i][j] = sprite[0];
	screen[i][j + 1] = sprite[1];
}

bool Stage::LoadFile(char* filename)
{
	std::ifstream ifs(filename);
	if (false == ifs.is_open()) return false;

	for (int i = 1; i < sizeY; ++i)
	{
		for (int j = 0; j < sizeX; j += 2) {

			char ch1 = 0;
			ifs.get(ch1);
			if (ch1 == '\n') break;
			if (ifs.eof()) break;
			
			char ch2 = 0;
			ifs.get(ch2);
			if (ch2 == '\n') break;
			if (ifs.eof()) break;

			if (ch1 == '#' && ch2 == '#') {
				RewriteScreen(i, j, WALL);
			}
			else if (ch1 == 'P' && ch2 == 'l') {
				RewriteScreen(i, j, PLAYER_D);
				player->SetPos(j, i);
			}
			else if (ch1 == '*' && ch2 == '*') {
				RewriteScreen(i, j, COOKIE);
				++cookieCount;
			}
			else if (ch1 == 'G' && ch2 == 'h') {
				RewriteScreen(i, j, GHOST);
				ghostArr[ghostCount] = new Character(j, i, 0, -1, 0.6f, GHOST);
				++ghostCount;
			}
		}
	}

	//int mapValue[24][64] = { };

	//for (int i = 0; i < 10; ++i)
	//{
	//	for (int j = 0; j < 10; ++j) {
	//		mapValue[i][j] = 9;
	//		//std::cout << mapValue[i][j] << " ";
	//	}
	//	//std::cout << std::endl;
	//}

	//mapValue[player->GetPosY()][player->GetPosX()] = 0;
	//FindWay(mapValue, player->GetPosY(), player->GetPosX(), 1);

	//for (int i = 1; i < 10; ++i)
	//{
	//	for (int j = 0; j < 10; ++j) {
	//		std::cout << mapValue[i][j] << " ";
	//	}
	//	std::cout << std::endl;
	//}
}

// 처음에 FindWay(mapValue, player->y, player->x, 1)
bool Stage::FindWay(int mapValue[][64], int i, int j, int distance) {

	if (screen[i - 1][j] != WALL[0] && mapValue[i - 1][j] > distance) {
		mapValue[i - 1][j] = distance;
		return FindWay(mapValue, i - 1, j, ++distance);
	}

	if (screen[i + 1][j] != WALL[0] && mapValue[i + 1][j] > distance) {
		mapValue[i + 1][j] = distance;
		return FindWay(mapValue, i + 1, j, ++distance);
	}

	if (screen[i][j - 2] != WALL[0] && mapValue[i][j - 2] > distance) {
		mapValue[i][j - 2] = distance;
		return FindWay(mapValue, i, j - 2, ++distance);
	}

	if (screen[i][j + 2] != WALL[0] && mapValue[i][j + 2] > distance) {
		mapValue[i][j + 2] = distance;
		return FindWay(mapValue, i, j + 2, ++distance);
	}

	return true;
}

void Stage::GhostMove(int idx)
{
	char nextPos = screen[ghostArr[idx]->GetPosY() + ghostArr[idx]->GetYForce()][ghostArr[idx]->GetPosX() + ghostArr[idx]->GetXForce()];

	if (nextPos == WALL[0]) {
		for (int i = 0; i < 4; i++) {
			ghostArr[idx]->Rotate90();
			nextPos = screen[ghostArr[idx]->GetPosY() + ghostArr[idx]->GetYForce()][ghostArr[idx]->GetPosX() + ghostArr[idx]->GetXForce()];
			if (nextPos != WALL[0]) break;
		}
	}

	RewriteScreen(ghostArr[idx]->GetPosY(), ghostArr[idx]->GetPosX(), ghostArr[idx]->GetOnWhat());

	ghostArr[idx]->UpdatePos();

	if (nextPos == COOKIE[0]) ghostArr[idx]->SetOnWhat(COOKIE);
	else if (nextPos == ' ') ghostArr[idx]->SetOnWhat("  ");

	RewriteScreen(ghostArr[idx]->GetPosY(), ghostArr[idx]->GetPosX(), ghostArr[idx]->GetSprite());
}

bool Stage::Move() {
	char nextPos = screen[player->GetPosY() + player->GetYForce()][player->GetPosX() + player->GetXForce()];

	switch (nextPos) {
	case WALL[0] :
		return false;

	case COOKIE[0] :
		--cookieCount;
		score += 1;
		screen[0][0] = score / 100 + '0';
		screen[0][1] = (score / 10) % 10 + '0';
		screen[0][2] = score % 10 + '0';
		break;

	case GHOST[0] :
		player->Dead();
		break;
	}

	RewriteScreen(player->GetPosY(), player->GetPosX(), "  ");

	player->UpdatePos();

	RewriteScreen(player->GetPosY(), player->GetPosX(), player->GetSprite());

	return true;
}

bool Stage::Update()
{
	if (input->GetButtonDown(KeyCode::ESC)) {
		return true;
	}
	else if (input->GetButtonDown(KeyCode::W)) {
		player->SetForce(0, -1);
		player->SetSprite(PLAYER_W);
	}
	else if (input->GetButtonDown(KeyCode::D)) {
		player->SetForce(1, 0);
		player->SetSprite(PLAYER_D);
	}
	else if (input->GetButtonDown(KeyCode::S)) {
		player->SetForce(0, 1);
		player->SetSprite(PLAYER_S);
	}
	else if (input->GetButtonDown(KeyCode::A)) {
		player->SetForce(-1, 0);
		player->SetSprite(PLAYER_A);
	}

	player->AddTimeAfterMove(gametime->GetDeltaTime());

	if (player->IsTimeToMove()) {
		Move();
	}

	int mapValue[24][64] = { -1 };

	for (int i = 0; i < ghostCount; i++) {
		ghostArr[i]->AddTimeAfterMove(gametime->GetDeltaTime());

		if (ghostArr[i]->IsTimeToMove()) {
			GhostMove(0);
		}
	}

	// 바뀐 정보로 맵 수정하기

	return false;
}

bool Stage::IsDead()
{
	return player->GetIsDead();
}

bool Stage::IsClear()
{
	return (cookieCount == 1);
}


Stage::~Stage()
{
	delete player;
	
	for (int i = 0; i < ghostCount; i++) {
		delete ghostArr[i];
	} 
}
