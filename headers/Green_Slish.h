#pragma once

#include "Entity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class Green_Slish: Entity
{
private:
	static SDL_Renderer* u_renderer;
	static SDL_Window* u_window;

	static SDL_Texture* texture_green_slish[];
protected:
    virtual void tick(std::vector<SDL_Event>, int);
public:
    static std::vector<Green_Slish*> green_slishs;

    Green_Slish(SDL_Point = {-1, -1});
    static void init(SDL_Window*, SDL_Renderer*);
    virtual ~Green_Slish();
    virtual void render();
    static void spawn();
};
