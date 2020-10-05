#include "Entity.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SDL2/SDL.h>

#include "Constants.h"

std::vector<Entity*> Entity::entitys;

Entity::Entity(SDL_Renderer* renderer, SDL_Window* window)
{
    entitys.push_back(this);
    this->renderer = renderer;
    this->window = window;
    UUID = rand();
    UUID *= rand();
    UUID *= rand();
    std::cout << "UUID: " << UUID << " Count: " << entitys.size() << std::endl;
}

void Entity::enforce_boundaries()
{
	for(Entity* e: entitys)
	{
		if(e->enable_enforce_boundaries)
		{
			int& ex = e->bounds.x;
			int& ey = e->bounds.y;
			if(ex < 0)
			{
				ex += abs(ex);
			}
			if(ey < 0)
			{
				ey += abs(ey);
			}
			if(ex > k::window_x - e->bounds.w)
			{
				ex = k::window_x - e->bounds.w;
			}
			if(ey > k::window_y - e->bounds.h)
			{
				ey = k::window_y - e->bounds.h;
			}
		}
	}
}

void Entity::start_tick(std::vector<SDL_Event> events, int this_tick)
{
    tick(events, this_tick - last_tick);
    last_tick = this_tick;
}

void Entity::setup_bounds(int width, int height)
{
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = width;
    bounds.h = height;

    center.x = bounds.x + (bounds.w / 2);
    center.y = bounds.y + (bounds.h / 2) ;
}

long Entity::get_UUID()
{
    return UUID;
}

SDL_Point Entity::get_Pos()
{
    return {bounds.x, bounds.y};
}

SDL_Rect Entity::get_Bounds()
{
    return bounds;
}

Entity::~Entity()
{
    for (int i = 0; i < (int)entitys.size(); i++)
    {
        if (entitys[i]->UUID == UUID)
        {
            entitys.erase(entitys.begin() + i);
            std::cout << "UUID " << UUID << " Destroyed. " << entitys.size() << "\n";
            break;
        }
    }
}
