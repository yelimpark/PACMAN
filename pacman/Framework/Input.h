#pragma once

enum class KeyCode {
	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
	SPACE = ' ',
	ENTER = '\n',
	ESC = 27
};

class Input {
private :
	bool s_currentKeyStates[256] = {false};
	bool s_prevKeyStates[256] = {false};

public :
	Input();

	void UpdateInput();

	bool GetButtonDown(KeyCode keyCode);

	bool GetButtonUp(KeyCode keyCode);

	bool GetButton(KeyCode keyCode);

	~Input();
};