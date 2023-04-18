#include "Character2.h"
#include "Texture2D.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>


Character2::Character2(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map)
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

	m_current_level_map = map;
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
	//collision pos variables
	int centralX_position = (int)(m_position.x + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;

	//gravity
	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		m_can_jump = true;
	}

	//deal with jumping first
	if (m_jumping)
	{
		//adjust pos
		m_position.y -= m_jump_force * deltaTime;

		//reduce jumpf
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		//is jumpf 0
		if (m_jump_force <= 0.0f)
			m_jumping = false;
	}

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
	default:;
	}

}

void Character2::AddGravity(float deltaTime)
{
	if (m_position.y + 64 <= SCREEN_HEIGHT)
	{
		m_position.y += GRAVITY * deltaTime;
	}
	else
	{
		m_can_jump = true;
	}
}

void Character2::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
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
	m_facing_direction = FACING_LEFT;
	m_position.x -= MOVEMENTSPEED * deltaTime;
}
void Character2::MoveRight(float deltaTime)
{
	m_facing_direction = FACING_RIGHT;
	m_position.x += MOVEMENTSPEED * deltaTime;
}

float Character2::GetCollisionRadius()
{
	return m_collision_radius;
}