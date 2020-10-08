#include "Utils/Graphing.h"
#include <iostream>
#include <SDL2/SDL.h>

namespace Graphing
{
	double distance(SDL_Point p1, SDL_Point p2)
	{
		int x = (p1.x - p2.x) * (p1.x - p2.x);
		int y = (p1.y - p2.y) * (p1.y - p2.y);
		return sqrt(x + y);
	}

	void advance(SDL_Point& current, SDL_Point destination, int step)
	{

	}
}
