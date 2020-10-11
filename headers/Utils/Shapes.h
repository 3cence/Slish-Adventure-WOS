#pragma once
#include <SDL2/SDL.h>

struct Point
{
	double x;
	double y;
};

struct Rect
{
	double x;
	double y;
	double w;
	double h;
};

SDL_Rect Rect_SDL(Rect);

struct Circle
{
	double r;
};
