#pragma once
#include <SDL.h>
#include <iostream>
#include "Character.h"

class Luigi : public Character
{
public:
	Luigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~Luigi();

	virtual void Update(float deltaTime, SDL_Event e);
};

