#pragma once
#include <SDL2/SDL.h>

namespace Graphing
{
	double distance(SDL_Point, SDL_Point);
	void advance(SDL_Point&, SDL_Point, int);
}
