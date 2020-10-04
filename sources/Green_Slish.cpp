#include "Green_Slish.h"
#include "Entity.h"
#include <iostream>

std::vector<Green_Slish*> Green_Slish::green_slishs;

Green_Slish::Green_Slish(SDL_Renderer* renderer, SDL_Window* window):
		Entity(renderer, window)
{

}

void Green_Slish::render()
{

}

void Green_Slish::spawned()
{

}

void Green_Slish::tick(std::vector<SDL_Event> events, int time)
{

}

Green_Slish::~Green_Slish()
{

}
