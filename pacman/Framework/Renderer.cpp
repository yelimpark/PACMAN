#include "Renderer.h"
#include "../stdafx.h"

static HANDLE s_consolHandle;

void Renderer::clear() {
	for (size_t i = 0; i < screenSizeY; i++) {
		memset(screen[i], ' ', screenSizeX);
		screen[i][screenSizeX - 1] = '\0';
	}
}

Renderer::Renderer(int screenSizeX, int screenSizeY)
	:screenSizeX(screenSizeX), screenSizeY(screenSizeY)
{
	screen = new char * [screenSizeY];

	for (int i = 0; i < screenSizeY; i++) {
		screen[i] = new char[screenSizeX];
	}

	clear();
}

bool Renderer::InitializeRenderer()
{
	s_consolHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	if (INVALID_HANDLE_VALUE == s_consolHandle) {
		return false;
	}

	system("mode con cols=65 lines=25 | title PACMAN");

	return true;
}

void Renderer::Render(char* screenInput[])
{
	const static COORD initialPos = { 0, 0 };
	const static CONSOLE_CURSOR_INFO info = { 100, false };

	SetConsoleCursorPosition(s_consolHandle, initialPos);
	SetConsoleCursorInfo(s_consolHandle, &info);

	for (size_t i = 0; i < screenSizeY; i++) {
		memcpy(screen[i], screenInput[i], screenSizeX);
		std::cout << screen[i] << std::endl;
	}

	clear();
}

Renderer::~Renderer()
{
	for (int i = 0; i < screenSizeY; i++) {
		delete [] screen[i];
	}
	delete[] screen;
}

