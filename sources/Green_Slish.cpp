#include "Green_Slish.h"
#include "Entity.h"
#include <iostream>

std::vector<Green_Slish*> Green_Slish::green_slishs;
SDL_Window* Green_Slish::u_window = NULL;
SDL_Renderer* Green_Slish::u_renderer = NULL;

Green_Slish::Green_Slish(SDL_Point position):
		Entity(u_renderer, u_window)
{
	if(u_renderer != NULL && u_window != NULL)
	{
		green_slishs.push_back(this);
		setup_bounds(64, 64);
		bounds.x = position.x;
		bounds.y = position.y;
	}
	else
	{
		std::cout << "Could not generate a green slish. Missing u_window and u_renderer" << std::endl;
		delete this;
	}
}

void Green_Slish::init(SDL_Window* window, SDL_Renderer* renderer)
{
	Green_Slish::u_window = window;
	Green_Slish::u_renderer = renderer;
}

void Green_Slish::render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &bounds);
}

void Green_Slish::spawn()
{
	new Green_Slish({100, 100});
}

void Green_Slish::tick(std::vector<SDL_Event> events, int time)
{

}

Green_Slish::~Green_Slish()
{
    for (int i = 0; i < (int)green_slishs.size(); i++)
    {
        if (green_slishs[i]->get_UUID() == get_UUID())
        {
        	green_slishs.erase(green_slishs.begin() + i);
            break;
        }
    }
}
