#pragma once
#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "Texture2D.h"

using namespace std;

class Texture2D;

class Character2
{
protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;

	bool m_moving_left;
	bool m_moving_right;
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

	float m_collision_radius;

public:
	Character2(SDL_Renderer* renderer, string imagePath, Vector2D start_position);
	~Character2();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();

	float GetCollisionRadius();

private:
	FACING m_facing_direction;
};
