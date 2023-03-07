//Be grateful for humble beginnings, because the next level will always require so much more of you

//YOU ARE ON WEEK 3 10B

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include <iostream>

#include "Texture2d.h"
#include "Commons.h"

using namespace std;

//Global Variables
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
//SDL_Texture* g_texture = nullptr;
Texture2D* g_texture = nullptr;

//Function prototypes
bool Update();
bool InitSDL();
//void CloseSDL();
void Render();
//SDL_Texture* LoadTextureFromFile(string path);
void FreeTexture();


int main(int argc, char* args[])
{
	if (InitSDL())
	{
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
	//CloseSDL();

	SDL_Event e;		//event handler
	SDL_PollEvent(&e);	//get events

	switch (e.type)		//handle the events
	{
	case SDL_QUIT:		//click X to quit
		return true;
		break;
	}
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

	//Load the background texture
	g_texture = LoadTextureFromFile("Images/test.bmp");
	if (g_texture == nullptr)
	{
		return false;
	}
	return true;
}

/*
void CloseSDL()
{
	//clear texture
	FreeTexture();
	//release the renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
*/

void Render()
{
	//clear screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	//set where to render texture
	SDL_Rect renderLocation = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

	//Render to screen
	SDL_RenderCopyEx(g_renderer, g_texture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);

	//update the screen
	SDL_RenderPresent(g_renderer);

}
/*
SDL_Texture* LoadTextureFromFile(string path)
{
	//remove memory used for a previous texture
	FreeTexture();

	SDL_Texture* p_texture = nullptr;

	//Load the Image
	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr)
	{
		//create the texture from the pixels on the surface
		p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
		if (p_texture == nullptr)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError();
		}
		//remove the loaded surface now that we have a texture
		SDL_FreeSurface(p_surface);
	}
	else
	{
		cout << "Unable to create texture from surface. Error: " << IMG_GetError();
	}

	return p_texture; //return the texture
}
*/

/*
void FreeTexture()
{
	//check if texture exist before removing it
	if (g_texture != nullptr)
	{
		SDL_DestroyTexture(g_texture);
		g_texture = nullptr;
	}
}
*/