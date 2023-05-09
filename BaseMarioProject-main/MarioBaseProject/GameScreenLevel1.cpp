#include "GameScreenLevel1.h"
#include <iostream>
#include "Mario.h"
#include "Luigi.h"
#include "Enemy.h"

using namespace std;

Mario* my_character;
Luigi* my_character2;
Enemy* m_enemies;

GameScreenLevel1::~GameScreenLevel1() 
{
	delete m_background_texture;
	m_background_texture = nullptr;

	delete my_character;
	my_character = nullptr;

	delete my_character2;
	my_character2 = nullptr;

	delete m_level_map;
	m_level_map = nullptr;

	delete m_pow_block;
	m_pow_block = nullptr;

	for (int i = 0; i < m_enemies.size(); i++)
	{
		delete m_enemies[i];
	}
	m_enemies.clear();
}
GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	
}
void GameScreenLevel1::Update(float deltaTime, SDL_Event e) 
{
	//update character
	my_character->Update(deltaTime, e);
	my_character2->Update(deltaTime, e);

	/*if (Collisions::Instance()->Circle(my_character, my_character2))
	{
		cout << "Circle hit!" << endl;
	}*/

	if (Collisions::Instance()->Box(my_character->GetCollisionBox(), my_character2->GetCollisionBox()))
	{
		cout << "Box hit!" << endl;
	}

	UpdateEnemies(deltaTime, e);
}

void GameScreenLevel1::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(0.0f, 0.0f), SDL_FLIP_NONE);
	
	my_character->Render();
	my_character2->Render();
	m_pow_block->Render();

	//dar enemeies
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}
}

bool GameScreenLevel1::SetUpLevel()
{
	SetLevelMap();

	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture" << std::endl;
		return false;
	}


	//set up player character
	my_character = new Mario(m_renderer, "Images/Mario.png", Vector2D(64.0f, 330.0f),m_level_map);
	my_character2 = new Luigi(m_renderer, "Images/Luigi.png", Vector2D(100.0f, 330.0f), m_level_map);

	m_pow_block = new PowBlock(m_renderer, m_level_map);
}

void  GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
										{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
										{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };
	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);

	CreateEnemy(Vector2D (150,32),FACING_RIGHT, KOOPA_SPEED);
	CreateEnemy(Vector2D (325, 32), FACING_LEFT, KOOPA_SPEED);
}

void GameScreenLevel1::UpdatePOWBlock()
{
	
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//check if enemy is on bottom row of tiles
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				//is enemy off screen left or right side
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f))m_enemies[i]->SetAlive(false);
			}
			//update
			m_enemies[i]->Update(deltaTime, e);

			//check collision
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collison if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], my_character))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						//kill mario
					}
				}
				if (Collisions::Instance()->Circle(m_enemies[i], my_character2))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						//kill mario
					}
				}
			}

			//if the enemy is dead - ready to delete
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}
		//remove dead enemies
		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateEnemy(Vector2D position, FACING direction, float speed)
{

	Enemy* Koopa = new Enemy(m_renderer, "Images/Koopa.png", position, m_level_map, direction, speed);
	m_enemies.push_back(Koopa);
}