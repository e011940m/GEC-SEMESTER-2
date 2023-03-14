#pragma once
#include "GameScreen.h"
#include "Commons.h"
#include "SDL.h"
#include "GameScreen.h"
#include "GameScreenManager.h"

class Texture2D;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* m_background_texture;
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();
	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
private:
	bool SetUpLevel();
};

