#include "Enemy.h"
#include "Texture2D.h"
#include "constants.h"

Enemy::Enemy(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed) : Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_injured = false;

	m_alive = true;

	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();
}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	if (!m_injured)
	{
		if (m_facing_direction == FACING_LEFT)
		{
			m_moving_left = true;
			m_moving_right = false;
		}
		else if (m_facing_direction == FACING_RIGHT)
		{
			m_moving_right = true;
			m_moving_left = false;
		}
	}
	else
	{
		m_moving_right = false;
		m_moving_left = false;

		m_injured_time -= deltaTime;

		if (m_injured_time <= 0.0)
			FlipRightWayUp();
	}
}
void Enemy::Render()
{
	//hold left pos
	int left = 0.0f;

	//if injured move left of spritesheet
	if (m_injured)
		left = m_single_sprite_w;

	//get sptie portion to draw
	SDL_Rect portion_of_sprite = { left,0,m_single_sprite_w,m_single_sprite_h };

	//determine where to draw
	SDL_Rect destRect{ (int)(m_position.x),(int)(m_position.y),m_single_sprite_w,m_single_sprite_h };

	//draw facing correct direction
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void Enemy::TakeDamage()
{
	m_injured = true;
	m_injured_time = INJURED_TIME;
	Jump();
}
void Enemy::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE_SMALL;
		m_jumping = true;
		m_can_jump = false;
	}
}

void Enemy::FlipRightWayUp()
{
	if (m_facing_direction = FACING_LEFT)
	{
		FACING_RIGHT;
	}
	
	if(m_facing_direction = FACING_RIGHT)
	{
		FACING_LEFT;
	}

	m_injured = false;
	Jump();

}
