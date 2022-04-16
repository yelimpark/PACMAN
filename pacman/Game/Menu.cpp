#include "Menu.h"
#include "../stdafx.h"

void Menu::MoveCursor(int x, int y)
{
	if (screen[cursorY + y][cursorX] == '#')
		return;

	screen[cursorY][cursorX] = ' ';
	cursorY += y;
	screen[cursorY][cursorX] = '*';
}

Menu::Menu(int sizeX, int sizeY, Input*& input)
	:Game(sizeX, sizeY, input), cursorX(0), cursorY(0)
{
}

bool Menu::LoadFile(const char* filename)
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
			if (ch == '*') {
				cursorX = j;
				cursorY = i;
			}

			screen[i][j] = ch;
		}
	}
}

bool Menu::HandleInput()
{
	if (input->GetButtonDown(KeyCode::W)) {
		MoveCursor(0, -1);
	}
	else if (input->GetButtonDown(KeyCode::S)) {
		MoveCursor(0, 1);
	}
	else if (input->GetButtonDown(KeyCode::SPACE) || input->GetButtonDown(KeyCode::ENTER)) {
		return true;
	}
	return false;
}

Menu::~Menu()
{
}

int Menu::GetStageNum() const
{
	return cursorY - 8;
}
