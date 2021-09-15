#include "Texture.h"


Texture::Texture()
{	
   _texture = NULL;	
   _textureWidth = 0;	
   _textureHeight = 0;
}

Texture::~Texture()
{
   free();
}

bool Texture::loadFromFile(std::string filePath, SDL_Renderer* renderer, float scale)
{
   free();	
 SDL_Texture* newTexture = NULL;	
 SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());
 if(loadedSurface == NULL)	
{
std::cout << "Could not load texture from file. IMG_Error\n" << IMG_GetError(); << std::endl;
}
else	
{
SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
	 newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
 if(newTexture == NULL)		
{
std::cout << "Could not create texture. SDL_Error\n", << SDL_GetError();	<< std::endl;	
}
 else		
{			
   _textureWidth = 35;			
   _textureHeight = 35;		
}
SDL_FreeSurface(loadedSurface);		_texture = newTexture;	
}
  return !_texture == NULL;
}

void Texture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip)
{
 SDL_Rect renderQuad = { x, y, _textureWidth, _textureHeight };
 if(clip != NULL)	
{		
 renderQuad.w = clip->w;		
 renderQuad.h = clip->h;	
}
SDL_RenderCopy(renderer, _texture, NULL, &renderQuad);
}

void Texture::setColor(Uint8 blue, Uint8 green, Uint8 red) 
{
 SDL_SetTextureColorMod( _texture, blue, green, red ); 
}
 SDL_Texture* Texture::getTexture()
{
  return _texture;
}

void Texture::setTexture(SDL_Texture* texture)
{
   _texture = texture;
}
 int Texture::getWidth()
{
  return _textureWidth;
}
 int Texture::getHeight()
{
  return _textureHeight;
}

void Texture::setWidth(int width)
{	
   _textureWidth = width;
}

void Texture::setHeight(int height)
{	
   _textureHeight = height;
}

void Texture::free()
{
 if(!_texture)	
 {
 SDL_DestroyTexture(_texture);		
   _texture = NULL;		
   _textureWidth = 0;	
   _textureHeight = 0;	
 }

}

