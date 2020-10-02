#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "Entity.h"
#include "Utils/Motion.h"

class Player : public Entity
{
private:
    static SDL_Texture* texture_base;
    static int base_width, base_height;
    static SDL_Texture* texture_cannon;
    static int cannon_width, cannon_height;
    Motion motion;
    int cannon_rotation = 0;
    SDL_Point mouse_pos;

    int rot_timer = 0;

    void handle_events(std::vector<SDL_Event>);

protected:
    virtual void tick(std::vector<SDL_Event>, int);

public:
    static std::vector<Player*> players;

    Player(SDL_Renderer*, SDL_Window*);
    virtual ~Player();
    virtual void render();
};
