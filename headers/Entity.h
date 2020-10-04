#pragma once
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>

class Entity
{
private:
    long UUID;
    int last_tick = 0;

protected:
    SDL_Rect bounds = {-1, -1, 0, 0};
    SDL_Point center = {-1, -1};
    SDL_Renderer* renderer = NULL;
    SDL_Window* window = NULL;

    void setup_bounds(int, int);
    virtual void tick(std::vector<SDL_Event>, int) {std::cout << "WARNING: Ticking base entity!" << std::endl;}

public:
    static std::vector<Entity*> entitys;

    Entity(SDL_Renderer* = NULL, SDL_Window* = NULL);
    virtual ~Entity();

    void start_tick(std::vector<SDL_Event>, int);
    virtual void render() {std::cout << "WARNING: Rendering base entity!" << std::endl;}

    long get_UUID();
    SDL_Point get_Pos();
    SDL_Rect get_Bounds();
};
