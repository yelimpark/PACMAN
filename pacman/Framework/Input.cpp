#include "Input.h"
#include "../stdafx.h"

Input::Input() 
{
}

bool isKeyDown(int32_t keyCode) {
	if (0x8000 & GetAsyncKeyState(keyCode)) {
		return true;
	}
	else {
		return false;
	}
}

void Input::UpdateInput()
{
	memcpy(s_prevKeyStates, s_currentKeyStates, sizeof(s_prevKeyStates));

	for (int32_t keyCode = 0; keyCode < 256; keyCode++) {
		if (isKeyDown(keyCode)) {
			s_currentKeyStates[keyCode] = true;
		}
		else {
			s_currentKeyStates[keyCode] = false;
		}
	}
}

bool Input::GetButtonDown(KeyCode keyCode)
{
	if (false == s_prevKeyStates[(char)keyCode] && s_currentKeyStates[(char)keyCode])
		return true;
	else
		return false;
}

bool Input::GetButtonUp(KeyCode keyCode)
{
	if (s_prevKeyStates[(char)keyCode] && false == s_currentKeyStates[(char)keyCode])
		return true;
	else
		return false;
}

bool Input::GetButton(KeyCode keyCode)
{
	if (s_prevKeyStates[(char)keyCode] && s_currentKeyStates[(char)keyCode])
		return true;
	else
		return false;
}

Input::~Input()
{
}
