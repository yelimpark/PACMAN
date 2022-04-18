#include "Stage.h"
#include "../stdafx.h"

Stage::Stage(int sizeX, int sizeY, Input*& input, GameTime* &gametime)
	:Game(sizeX, sizeY, input), cookieCount(0), gametime(gametime)
{
	player = new Player(0, 1, 0.5f, PLAYER_D);
}

void Stage::RewriteScreen(int i, int j, const char * sprite) {
	screen[i][j] = sprite[0];
	screen[i][j + 1] = sprite[1];
}

bool Stage::LoadFile(char* filename)
{
	std::ifstream ifs(filename);
	if (false == ifs.is_open()) return false;

	for (size_t i = 1; i < sizeY; ++i)
	{
		for (size_t j = 0; j < sizeX; j += 2) {

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
			}
			else if (ch1 == 'G' && ch2 == 'o') {
				RewriteScreen(i, j, GHOST);
			}
		}
	}
}

void Stage::UpdatePos(int x, int y, const char* playerSprite)
{

	if (nextPos == '#') {
		return;
	}

	screen[playerY][playerX] = ' ';
	screen[playerY][playerX + 1] = ' ';

	playerX += 2 * x;
	playerY += y;

	screen[playerY][playerX] = playerSprite[0];
	screen[playerY][playerX + 1] = playerSprite[1];
}

bool Stage::Move() {
	char nextPos = screen[player->GetNextY()][player->GetNextX()];

	switch (nextPos) {
	case '#' :
		return false;

	case COOKIE[0] :
		++cookieCount;
		screen[0][0] = cookieCount / 100 + '0';
		screen[0][1] = (cookieCount / 10) % 10 + '0';
		screen[0][2] = cookieCount % 10 + '0';
		return true;

	case GHOST[0] :
		isDead = true;
	}

	return true;
}

bool Stage::Update()
{
	if (input->GetButtonDown(KeyCode::ESC)) {
		return true;
	}
	else if (input->GetButtonDown(KeyCode::W)) {
		player->SetForce(0, 1);
		player->SetPlayerSprite(PLAYER_W);
	}
	else if (input->GetButtonDown(KeyCode::D)) {
		player->SetForce(1, 0);
		player->SetPlayerSprite(PLAYER_D);
	}
	else if (input->GetButtonDown(KeyCode::S)) {
		player->SetForce(0, -1);
		player->SetPlayerSprite(PLAYER_S);
	}
	else if (input->GetButtonDown(KeyCode::A)) {
		player->SetForce(-1, 0);
		player->SetPlayerSprite(PLAYER_A);
	}

	player->Update(gametime->GetDeltaTime());




	// 유령도?
	// timeAfterMove 더해주기
	// plyerSpeed보다 커지면 0으로 초기화하고 이동 함 시켜주기

	// 바뀐 정보로 맵 수정하기

	return false;
}
//
//bool Stage::IsClear()
//{
//    return isDead;
//}

Stage::~Stage()
{
}
