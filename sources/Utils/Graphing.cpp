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

	Point advance(Point current, Point destination, int step)
	{
		Point result;
	    int angle = atan2(abs(current.x - destination.x), abs(current.y - destination.y)) * (180 / M_PI);
	    angle = -(angle - 90);
	    std::cout << angle << std::endl;
	    result.x = abs(cos(angle) * step);
	    result.y = abs(sin(angle) * step);

	    if(current.x > destination.x)
	    	result.x *= -1;
	    if(current.y > destination.y)
	    	result.y *= -1;

	    return result;
	}
}
