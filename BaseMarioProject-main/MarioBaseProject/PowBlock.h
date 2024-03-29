#pragma once
#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "LevelMap.h"
#include "Texture2D.h"


class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* map);
	~PowBlock();
	virtual void Render();
	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight()); }
	virtual void TakeHit();
	bool IsAvailable(){return m_num_hits_left > 0;}

private:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	LevelMap* m_level_map;

	float m_single_sprite_w;
	float m_single_sprite_h;
	float m_num_hits_left;
};

