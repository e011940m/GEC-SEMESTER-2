#pragma once
#include <SDL.h>
#include <iostream>
#include "Character.h"

class Mario : public Character
{
public:
	Mario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~Mario();

	virtual void Update(float deltaTime, SDL_Event e);
};

