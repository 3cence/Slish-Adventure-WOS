#pragma once

#include "Entity.h"
#include <SDL2/SDL.h>
#include <vector>

class Green_Slish: Entity
{
private:
protected:
    virtual void tick(std::vector<SDL_Event>, int);
public:
    static std::vector<Green_Slish*> green_slishs;

    Green_Slish(SDL_Renderer*, SDL_Window*);
    virtual ~Green_Slish();
    virtual void render();
    virtual void spawned();
};
