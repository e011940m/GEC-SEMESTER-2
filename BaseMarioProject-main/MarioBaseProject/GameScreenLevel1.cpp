#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "Character2.h"
#include "Collisions.h"


class Character;
Character* my_character;

class Character2;
Character2* my_character2;



GameScreenLevel1::~GameScreenLevel1() 
{
	delete m_background_texture;
	m_background_texture = nullptr;

	delete my_character;
	my_character = nullptr;

	delete my_character2;
	my_character2 = nullptr;
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

	/*if (Collisions::Instance()->Circle())
	{
		cout << "Circle hit!" << endl;
	}

	if (Collisions::Instance()->Box())
	{
		cout << "Box hit!" << endl;
	}*/
}

void GameScreenLevel1::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(0.0f, 0.0f), SDL_FLIP_NONE);
	
	my_character->Render();
	my_character2->Render();
}

bool GameScreenLevel1::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp"))
	{
		std::cout << "Failed to load background texture" << std::endl;
		return false;
	}


	//set up player character
	my_character = new Character(m_renderer, "Images/Mario.png", Vector2D(64.0f, 330.0f));
	my_character2 = new Character2(m_renderer, "Images/Luigi.png", Vector2D(100.0f, 330.0f));
}