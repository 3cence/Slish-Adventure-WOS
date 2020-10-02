#include "Player.h"

#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture* Player::texture_base = NULL;
int Player::base_width, Player::base_height;
SDL_Texture* Player::texture_cannon = NULL;
int Player::cannon_width, Player::cannon_height;
std::vector<Player*> Player::players;

Player::Player(SDL_Renderer* renderer, SDL_Window* window):
    Entity(renderer, window)
{
    //Add to the player list and set it up for rendering
    players.push_back(this);
    setup_render(128, 128);
    bounds.x = 720/2-64;
    bounds.y = 480/2-64;

    //Load the textures if has not been yet
    if(texture_base == NULL)
    {
        texture_base = IMG_LoadTexture(renderer, "res/textures/player/player_base.png");
        SDL_QueryTexture(texture_base, NULL, NULL, &base_width, &base_height);
        if(texture_base == NULL)
        {
            std::cout << "WARNING: Failed to load texture player_base\n";
        }
    }
    if(texture_cannon == NULL)
    {
        texture_cannon = IMG_LoadTexture(renderer, "res/textures/player/player_cannon.png");
        SDL_QueryTexture(texture_cannon, NULL, NULL, &cannon_width, &cannon_height);
        if(texture_cannon == NULL)
        {
            std::cout << "WARNING: Failed to load texture texture_cannon\n";
        }
    }
}

void Player::tick(std::vector<SDL_Event> events, int since_last_tick)
{
    handle_events(events);
    center.x = bounds.x + (bounds.w / 2);
    center.y = bounds.y + (bounds.h / 2) ;

    //Postion the cannnon
    int x = mouse_pos.x - center.x;
    int y = mouse_pos.y - center.y;
    int tri_len_x = abs(x);
    int tri_len_y = abs(y);

    cannon_rotation = atan2(tri_len_y, tri_len_x) * (180 / M_PI);
    cannon_rotation = -(cannon_rotation - 90);

    //I
    if(x >= 0 && y >= 0)
    {
        cannon_rotation = 180 - cannon_rotation;
    }
    //II
    else if(x <= 0 && y >= 0)
    {
        cannon_rotation += 180;
    }
    //III
    else if(x <= 0 && y <= 0)
    {
        cannon_rotation *= -1;
    }

    //Move the player
    static int speed = 2;
    if(motion.up)
    {
        bounds.y -= speed;
    }
    if(motion.down)
    {
        bounds.y += speed;
    }
    if(motion.left)
    {
        bounds.x -= speed;
    }
    if(motion.right)
    {
        bounds.x += speed;
    }
}

void Player::handle_events(std::vector<SDL_Event> events)
{
    for(SDL_Event event: events)
    {
        //On Press
        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
                motion.up = true;
                break;
            case SDL_SCANCODE_A:
                motion.left = true;
                break;
            case SDL_SCANCODE_S:
                motion.down = true;
                break;
            case SDL_SCANCODE_D:
                motion.right = true;
                break;
            default:
                break;
            }
        }
        // On Release
        if(event.type == SDL_KEYUP)
        {
            switch(event.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
                motion.up = false;
                break;
            case SDL_SCANCODE_A:
                motion.left = false;
                break;
            case SDL_SCANCODE_S:
                motion.down = false;
                break;
            case SDL_SCANCODE_D:
                motion.right = false;
                break;
            default:
                break;
            }
        }
        //mouse handling
        if(event.type == SDL_MOUSEMOTION)
        {
            mouse_pos = {event.motion.x, event.motion.y};
        }
    }
}

void Player::render()
{
    if(texture_base == NULL)
        return;
    SDL_RenderCopy(renderer, texture_base, NULL, &bounds);
    SDL_Point can_center = {bounds.w / 2, bounds.h / 2};
    SDL_RenderCopyEx(renderer, texture_cannon, NULL, &bounds, cannon_rotation, &can_center, SDL_FLIP_NONE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

Player::~Player()
{
    //Destory the texture if it is the player
    if(players.size() <= 1)
    {
        SDL_DestroyTexture(texture_base);
        SDL_DestroyTexture(texture_cannon);
        texture_base = NULL;
        texture_cannon = NULL;
        //std::cout << "Destorying last Texture\n";
    }
    //Remove player from static player list
    for (int i = 0; i < (int)players.size(); i++)
    {
        if (players[i]->get_UUID() == get_UUID())
        {
            players.erase(players.begin() + i);
            //std::cout << "Player " << get_UUID() << " Destroyed. " << players.size() << "\n";
            break;
        }
    }
}
