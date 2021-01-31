//
// Created by edoardo biasio on 2021-01-28.
//

#ifndef ROCKET_ROCKET_H
#define ROCKET_ROCKET_H

#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "animation.h"
#include "label.h"

const float GRAVITATIONAL_ACCELERATION =  9.80665f;

struct RocketData {
    float mass;
    float fuel;
    std::string name;
    float diameter;
    float height;
    float thrust;
    float fuel_consumption;

    std::string rocket_sprite;
};

class Rocket {
private:
    float initial_mass;
    float mass;
    float acceleration;
    float force;
    float fuel;
    float velocity;
    float dry_mass;
    float diameter;
    float height;
    float delta_v;
    bool stopped;
    float thrust;
    float fuel_consumption;
    Label* mass_text;
    Label* acceleration_text;
    Label* force_text;
    Label* fuel_text;
    Label* velocity_text;
    texture_t fire_sprite;
    Animation obamium;
    Label* altitude_text;
    Label* name_text;
    std::string name;

public:
    Rocket(float mass, float fuel, SDL_Renderer* renderer);
    Rocket(const RocketData& data, SDL_Renderer* renderer);
    float position;
    void update(float dt);
    void render(SDL_Renderer* renderer, TTF_Font *font, int& camera_x, int& camera_y);
};


#endif //ROCKET_ROCKET_H
