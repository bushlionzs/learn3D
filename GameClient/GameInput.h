#pragma once

#include "GameSingleton.h"
#include "InputManager.h"
class GameInput :public GameSingleton<GameInput>
{
public:
	GameInput();
	~GameInput();

	void input(KeyCode _key);
};