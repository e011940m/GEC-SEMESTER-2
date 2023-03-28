#include "Character2.h"
#include "Texture2D.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>


Character2::Character2(SDL_Renderer* renderer, string imagePath, Vector2D start_position)
{
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load background texture" << std::endl;;
	}
	m_moving_left = false;
	m_moving_right = false;

	m_collision_radius = 15.0f;
}

Character2::~Character2()
{
	m_renderer = nullptr;
}

void Character2::Render()
{
	m_texture->Render(m_position, SDL_FLIP_NONE);

	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
}

void Character2::Update(float deltaTime, SDL_Event e)
{
	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}

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
	default:;
	}

}

void Character2::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D Character2::GetPosition()
{
	return m_position;
}

void Character2::MoveLeft(float deltaTime)
{
	FACING_LEFT;
	m_position.x -= 1;
}
void Character2::MoveRight(float deltaTime)
{
	FACING_RIGHT;
	m_position.x += 1;
}

float Character2::GetCollisionRadius()
{
	return m_collision_radius;
}