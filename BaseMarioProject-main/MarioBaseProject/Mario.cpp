#include "Mario.h"
#include "Character.h"
#include "Texture2D.h"
#include "constants.h"

using namespace std;

Mario::Mario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{

}
Mario::~Mario()
{

}

void Mario::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
			break;
		case SDLK_LEFT:
			m_moving_left = true;
			break;
		case SDLK_RIGHT:
			m_moving_right = true;
			break;
		case SDLK_UP:
			Jump();
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
			break;
		case SDLK_LEFT:
			m_moving_left = false;
			break;
		case SDLK_RIGHT:
			m_moving_right = false;
			break;
		}
	}

	Character::Update(deltaTime, e);
}

