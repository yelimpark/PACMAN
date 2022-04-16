#include "Stage.h"
#include "../stdafx.h"

Stage::Stage(int sizeX, int sizeY, Input*& input)
    :Game(sizeX, sizeY, input), playerX(1), playerY(1),
	cookieCount(0), isDead(false)
{
}

void Stage::RewriteScreen()
{
	screen[playerY][playerX] = PLAYER_D[0];
	screen[playerY][playerX + 1] = PLAYER_D[1];

	for (int i = 0; i < sizeY; ++i)
	{
		for (int j = 0; j < sizeX; ++j) {
			if (screen[i][j] == '*' && screen[i][j + 1] == '*') {
				screen[i][j] = COOKIE[0];
				screen[i][j + 1] = COOKIE[1];
			}
			else if (screen[i][j] == 'G' && screen[i][j + 1] == 'o') {
				screen[i][j] = GHOST[0];
				screen[i][j + 1] = GHOST[1];
			}
		}
	}
}

bool Stage::LoadFile(char* filename)
{
	std::ifstream ifs(filename);
	if (false == ifs.is_open()) return false;

	for (size_t i = 0; i < sizeY; ++i)
	{
		for (size_t j = 0; j < sizeX; ++j) {
			char ch;
			ifs.get(ch);

			if (ch == '\n') break;
			if (ifs.eof()) break;

			screen[i][j] = ch;
		}
	}

	RewriteScreen();
}

void Stage::UpdatePos(int x, int y, const char* playerSprite)
{
	char nextPos = screen[playerY + y][playerX + x * 2];

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

bool Stage::Move(int x, int y, const char* playerSprite) {

	UpdatePos(x, y, playerSprite);

	char nextPos = screen[playerY + y][playerX + x*2];

	switch (nextPos) {
	case '#' :
		return false;

	case COOKIE[0] :
		++cookieCount;
		return true;

	case GHOST[0] :
		isDead = true;
	}

	return true;
}

bool Stage::HandleInput()
{
	if (input->GetButtonDown(KeyCode::W)) {
		Move(0, -1, PLAYER_W);
	}
	else if (input->GetButtonDown(KeyCode::D)) {
		Move(1, 0, PLAYER_D);
	}
	else if (input->GetButtonDown(KeyCode::S)) {
		Move(0, 1, PLAYER_S);
	}
	else if (input->GetButtonDown(KeyCode::A)) {
		Move(-1, 0, PLAYER_A);
	}
	else if (input->GetButtonDown(KeyCode::ESC)) {
		return true;
	}
	return false;
}

bool Stage::IsClear()
{
    return isDead;
}

Stage::~Stage()
{
}
