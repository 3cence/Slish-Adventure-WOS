#include "Green_Slish.h"
#include "Entity.h"
#include "Player.h"
#include "Constants.h"
#include "Utils/Graphing.h"

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

std::vector<Green_Slish*> Green_Slish::green_slishs;
SDL_Window* Green_Slish::u_window = NULL;
SDL_Renderer* Green_Slish::u_renderer = NULL;
SDL_Texture* Green_Slish::texture_green_slish[1];
int Green_Slish::size = 32;

Green_Slish::Green_Slish(SDL_Point position):
		Entity(u_renderer, u_window)
{
	if(u_renderer != NULL && u_window != NULL)
	{
		green_slishs.push_back(this);
		setup_bounds(size, size);
		bounds.x = position.x;
		bounds.y = position.y;

		texture_green_slish[0] = IMG_LoadTexture(renderer, "res/textures/enemy/slish-calm.png");
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
	SDL_RenderCopy(renderer, texture_green_slish[0], NULL, &bounds);
}

void Green_Slish::spawn()
{
	SDL_Rect canadate = {};
	canadate.h = size;
	canadate.w = size;
	canadate.x = rand() % k::window_x;
	canadate.y = rand() % k::window_y;

	bool is_valid = true;
	for(Entity* entity: Entity::entitys)
	{
		SDL_Rect e_bounds = entity->get_Bounds();
		if(SDL_HasIntersection(&canadate, &e_bounds))
		{
			is_valid = false;
		}
	}
	if(is_valid)
	{
		new Green_Slish({canadate.x, canadate.y});
	}
}

void Green_Slish::tick(std::vector<SDL_Event> events, int time)
{
	static long passed = time;
	passed++;

	if(passed % 4 == 0)
	{
		const int speed = 2;
		Point current_point = {(double)bounds.x, (double)bounds.y};
		current_point = Graphing::advance(current_point, {(double)Player::players[0]->get_Bounds().x + 16, (double)Player::players[0]->get_Bounds().y + 16}, speed);
		if(current_point.x - (int)current_point.x > 0.5)
			bounds.x += ceil(current_point.x);
		else
			bounds.x += floor(current_point.x);

		if(current_point.y - (int)current_point.y > 0.5)
			bounds.y += ceil(current_point.y);
		else
			bounds.y += floor(current_point.y);

		bounds.x += current_point.x;
		bounds.y += current_point.y;

		std::cout << current_point.x << " " << current_point.y << std::endl;
	}
}

Green_Slish::~Green_Slish()
{
	for(SDL_Texture* tex: texture_green_slish)
	{
		SDL_DestroyTexture(tex);
	}

    for(int i = 0; i < (int)green_slishs.size(); i++)
    {
        if (green_slishs[i]->get_UUID() == get_UUID())
        {
        	green_slishs.erase(green_slishs.begin() + i);
            break;
        }
    }
}
