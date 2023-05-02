#include "GameScreenLevel1.h"
#include <iostream>
#include "Mario.h"
#include "Luigi.h"

Mario* my_character;
Luigi* my_character2;

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
}

void GameScreenLevel1::UpdatePOWBlock()
{
	
}