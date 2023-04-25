#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>

using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}
Texture2D::~Texture2D()
{
	Free();

	m_renderer = nullptr;
}
bool Texture2D::LoadFromFile(std::string path)
{
	//remove memory used for a previous texture
	Free();

	//Load the Image
	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr)
	{
		SDL_SetColorKey(p_surface, SDL_TRUE, SDL_MapRGB(p_surface->format, 0, 0XFF, 0XFF));
		//create the texture from the pixels on the surface
		m_texture = SDL_CreateTextureFromSurface(m_renderer, p_surface);
		if (m_texture == nullptr)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError();
		}
		else
		{
			m_width = p_surface->w;
			m_height = p_surface->h;
		}

		//remove the loaded surface now that we have a texture
		SDL_FreeSurface(p_surface);
	}
	else
	{
		cout << "Unable to create texture from surface. Error: " << IMG_GetError();
	}

	return m_texture != nullptr; //return the texture
}
void Texture2D::Free()
{
	m_width = 0;
	m_height = 0;

	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;
}
void Texture2D::Render(Vector2D new_position, SDL_RendererFlip flip, double angel)
{
	//set where to render texture
	SDL_Rect renderLocation = { new_position.x,new_position.y,m_width, m_height };

	//Render to screen
	SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &renderLocation, 0, nullptr, flip);
}
void Texture2D::Render(SDL_Rect src_rect, SDL_Rect src_dest, SDL_RendererFlip flip, double angel = 0.0)
{
	//Render to screen
	SDL_RenderCopyEx(m_renderer, m_texture, &src_rect, &src_dest, angel, nullptr, flip);
}

