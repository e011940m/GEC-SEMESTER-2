#pragma once

struct Vector2D
{
	float x;
	float y;
	float initial_x;
	float initial_y;

	Vector2D()
	{
		x = initial_x;
		y = initial_y;

	}
};

enum SCREENS
{
	SCREEN_INTRO,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};