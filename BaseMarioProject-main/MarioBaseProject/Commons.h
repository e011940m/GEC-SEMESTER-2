#pragma once

struct Vector2D
{
	float x;
	float y;

	Vector2D(float initial_x, float initial_y) // Argument Constructor
	{
		x = initial_x;
		y = initial_y;
	}
	Vector2D() // Default Constructor
	{
		x = 0;
		y = 0;
	}
	Vector2D(const Vector2D& rhs) // Copy Constructor
	{
		x = rhs.x;
		y = rhs.y;
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

enum FACING
{
	FACING_LEFT,
	FACING_RIGHT
};

struct Rect2D
{
	float x;
	float y;
	float width;
	float height;


	Rect2D(float x_pos, float y_pos, float width, float height)
	{
		x = x_pos;
		y = y_pos;
		this->width = width;
		this->height = height;
	}
};