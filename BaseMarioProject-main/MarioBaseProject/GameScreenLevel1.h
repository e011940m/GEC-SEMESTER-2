#pragma once
#include "GameScreen.h"
#include "Commons.h"
#include "LevelMap.h"
#include "SDL.h"
class Texture2D;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* m_background_texture;

	LevelMap* m_level_map;
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();
	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
private:
	bool SetUpLevel();

	void SetLevelMap();

};

