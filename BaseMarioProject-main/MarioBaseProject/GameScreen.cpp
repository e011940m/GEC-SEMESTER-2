#include "GameScreen.h"
#include "Commons.h"
#include "SDL.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

using namespace std;

SDL_Renderer* m_renderer = m_renderer;

GameScreen::GameScreen(SDL_Renderer* renderer) 
{
	m_renderer = renderer;
}
GameScreen::~GameScreen() 
{
	m_renderer = nullptr;
}

void GameScreen::Render() 
{

}

void GameScreen::Update(float deltaTime, SDL_Event e)
{

}