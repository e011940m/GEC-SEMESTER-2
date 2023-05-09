#pragma once
#include <SDL.h>
#include <iostream>
#include "Character.h"

using namespace std;

class Enemy : public Character
{
public:
	Enemy(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed);
	~Enemy();

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render();

	void TakeDamage();
	void Jump();

	bool GetInjured() { return m_injured; }

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;

	void FlipRightWayUp();

protected:
	bool m_alive;
};

