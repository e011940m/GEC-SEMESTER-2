#include "Luigi.h"
#include "Character.h"
#include "Texture2D.h"
#include "constants.h"

using namespace std;

Luigi::Luigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{

}
Luigi::~Luigi()
{

}

void Luigi::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
			break;
		case SDLK_a:
			//m_position.x = -1;
			m_moving_left = true;
			break;
		case SDLK_d:
			//m_position.x = 1;
			m_moving_right = true;
			break;
		case SDLK_SPACE:
			Jump();
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
			break;
		case SDLK_LEFT:
			//m_position.x = -1;
			m_moving_left = false;
			break;
		case SDLK_RIGHT:
			//m_position.x = 1;
			m_moving_right = false;
			break;
		}
	}

	Character::Update(deltaTime, e);
}

