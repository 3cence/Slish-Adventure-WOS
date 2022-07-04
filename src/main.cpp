#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Constants.h"
#include "Entity.h"
#include "Green_Slish.h"
#include "Player.h"
#include "Utils/Graphing.h"

int main(int argc, char* argv[])
{
    //Init Subsystems
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cout << "SDL_Init: " << SDL_GetError() << std::endl;
    if(IMG_Init(IMG_INIT_PNG) < 0)
        std::cout << "IMG_Init: " << IMG_GetError() << std::endl;
    if(TTF_Init() < 0)
        std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
    srand(time(NULL));

    //Set up the Window and Renderer
    SDL_Window* window = SDL_CreateWindow("World of Slish", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    		k::window_x, k::window_y, SDL_WINDOW_SHOWN);
    if(window == NULL)
        std::cout << "SDL_CreateWindow: " << SDL_GetError() << std::endl;

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
        std::cout << "SDL_CreateRenderer: " << SDL_GetError() << std::endl;

    //Init core game objects
    Green_Slish::init(window, renderer);
    new Player(renderer, window);
    //Green_Slish::spawn();

    //Main Loop & Events
    SDL_Event event;
    bool running = true;
    long current_tick, last_second = SDL_GetTicks(), last_tick = SDL_GetTicks();
    int tps = 0, last_tps = 0;
    while(running)
    {
        std::vector<SDL_Event> events;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = false;
            }
            else
            {
                events.push_back(event);
            }
        }

        //Render Background
        static uint8_t bg_color = 150;
        SDL_SetRenderDrawColor(renderer, bg_color, bg_color, bg_color, 255);
        SDL_RenderFillRect(renderer, NULL);

        //Tick Entitys
        for(int i = 0; i < (int)Entity::entitys.size(); i++)
        {
             Entity::entitys[i]->start_tick(events, SDL_GetTicks());
        }
        Entity::enforce_boundaries();

        //Render Entitys
        for(int i = 0; i < (int)Entity::entitys.size(); i++)
        {
            Entity::entitys[i]->render();
        }

        //Print ticks per second
        current_tick = SDL_GetTicks();
        if(current_tick > last_second + 500)
        {
            SDL_SetWindowTitle(window, (std::string("World of Slish: ") + std::to_string(tps + last_tps)).c_str());
            last_second = current_tick;
            last_tps = tps;
            tps = 0;
        }
        tps++;

        //Render and time the next cycle
        SDL_RenderPresent(renderer);
        int delay = 20 - (current_tick - last_tick);
        if(delay <= 0)
        {
            delay = 1;
        }
        SDL_Delay(delay);
        last_tick = current_tick;
    }

    //Clean up
    int total = Entity::entitys.size();
    for(int i = 0; i < total; i++)
    {
        delete Entity::entitys[0];
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    return 0;
}
