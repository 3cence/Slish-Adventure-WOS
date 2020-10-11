#include "Utils/Shapes.h"
#include <cmath>
#include <SDL2/SDL.h>

SDL_Rect Rect_SDL(Rect current_point)
{
	SDL_Rect bounds;
	if(current_point.x - (int)current_point.x > 0.5)
		bounds.x += ceil(current_point.x);
	else
		bounds.x += floor(current_point.x);

	if(current_point.y - (int)current_point.y > 0.5)
		bounds.y += ceil(current_point.y);
	else
		bounds.y += floor(current_point.y);
	return bounds;
}
