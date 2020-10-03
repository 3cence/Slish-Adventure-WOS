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
    virtual void render();
    virtual void spawn();
};
