//Be grateful for humble beginnings, because the next level will always require so much more of you

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include <iostream>

#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"
#include "Character.h"


using namespace std;

//Global Variables
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
//SDL_Texture* g_texture = nullptr;
//Texture2D* g_texture = nullptr;
GameScreenManager* game_screen_manager;
Uint32 g_old_time;
Mix_Music* g_music = nullptr;

//Function prototypes
bool Update();
bool InitSDL();
//void CloseSDL();
void Render();
//SDL_Texture* LoadTextureFromFile(string path);
void FreeTexture();
void LoadMusic();


int main(int argc, char* args[])
{
	if (InitSDL())
	{
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
		//set the time
		g_old_time = SDL_GetTicks();

		bool quit = false; //flag to check if we wish to quit

			while (!quit) //game loop
			{
				Render();
				quit = Update();
			}
	}

	return 0;
}

bool Update()
{
	Uint32 new_time = SDL_GetTicks();

	//CloseSDL();

	SDL_Event e;		//event handler
	SDL_PollEvent(&e);	//get events

	switch (e.type)		//handle the events
	{
	case SDL_QUIT:		//click X to quit
		return true;
		break;
	}

	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;

	return false;
}

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//setup passed so create window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		//did the window get created?
		if (g_window == nullptr)
		{
			//window failed
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
	}

	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

	if (g_renderer != nullptr)
	{
		int imageFlags = IMG_INIT_PNG; //init PNG loading
		if (!(IMG_Init(imageFlags) & imageFlags))
		{
			cout << "SDL_Image could not initalise. Error: " << IMG_GetError();
			return false;
		}
	}
	else
	{
		cout << "Renderer could not inititalise. Error: " << SDL_GetError();
		return false;
	}

	//initialise the mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "Mixer could not init. Error: " << Mix_GetError();
		return false;
	}


	return true;
}


void CloseSDL()
{
	//destroy the game screen manager
	delete game_screen_manager;
	game_screen_manager = nullptr;

	//release the renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	//clear up music
	Mix_FreeMusic(g_music);
	g_music = nullptr;
}



void Render()
{
	//clear screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	//g_texture->Render(Vector2D(), SDL_FLIP_NONE);

	game_screen_manager->Render();

	//update the screen
	SDL_RenderPresent(g_renderer);


}

/*void LoadMusic()
{
	g_music = Mix_LoadMUS(path.c_str());
	if (g_music == nullptr)
	{
		cout << "Failed to load music. Error: " << Mix_GetError() << endl;
	}

	if (InitSDL())
	{
		LoadMusic("Music/Mario.mp3");
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(g_music, -1);
		}
	}
}*/
