#pragma once
#include "GameScreen.h"
#include "Commons.h"
#include "LevelMap.h"
#include "SDL.h"
#include "Mario.h"
#include "Luigi.h"
#include "Texture2D.h"
#include "PowBlock.h"
#include "Collisions.h"
#include "Enemy.h"
#include <vector>

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* m_background_texture;

	LevelMap* m_level_map;

	bool SetUpLevel();

	void SetLevelMap();

	PowBlock* m_pow_block;
	Mario* my_character;
	Luigi* my_character2;

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateEnemy(Vector2D position, FACING direction, float speed);
	vector<Enemy*> m_enemies;

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();
	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void UpdatePOWBlock();
};

