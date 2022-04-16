#include "Game.h"
#include "../stdafx.h"

Game::Game(int sizeX, int sizeY, Input*& input)
	:sizeX(sizeX), sizeY(sizeY), input(input)
{
	screen = new char* [sizeY];
	for (int i = 0; i < sizeY; i++) {
		screen[i] = new char[sizeX];
		memset(screen[i], ' ', sizeX);
		screen[i][sizeX - 1] = '\0';
	}
}

bool Game::LoadFile(const char* filename)
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
}

char** Game::GetScreen() const
{
	return screen;
}

Game::~Game()
{
	for (int i = 0; i < sizeY; i++) {
		delete[] screen[i];
	}
	delete[] screen;
}
