#pragma once
#include "Utils/Shapes.h"
#include <SDL2/SDL.h>

namespace Graphing
{
	double distance(SDL_Point, SDL_Point);
	Point advance(Point, Point, int);
}
