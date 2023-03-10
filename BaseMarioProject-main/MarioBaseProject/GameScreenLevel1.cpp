#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"

GameScreenLevel1::~GameScreenLevel1() 
{
	m_background_texture = nullptr;
}
GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	
}
void GameScreenLevel1::Update(float deltaTime, SDL_Event e) 
{

}

void GameScreenLevel1::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
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

}