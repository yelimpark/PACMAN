#include "Loby.h"
#include "../stdafx.h"

Loby::Loby(int sizeX, int sizeY, Input*& input)
	:Game(sizeX, sizeY, input)
{

}

bool Loby::Update()
{
	return (input->GetButtonDown(KeyCode::SPACE) || input->GetButtonDown(KeyCode::ENTER));
}

Loby::~Loby()
{

}
