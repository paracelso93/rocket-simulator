//
// Created by edoardo biasio on 2021-01-28.
//

#include "rocket.h"

#include <iostream>

Rocket::Rocket(float mass, float fuel, SDL_Renderer* renderer) : position(100.f), initial_mass(mass), mass(mass), velocity(0.f), acceleration(0.f), fuel(fuel), force(0.f) {
    stopped = false;
    dry_mass = mass - fuel;

    fire_sprite = IMG_LoadTexture(renderer, "res/fire.png");
    mass_text = nullptr;
    acceleration_text = nullptr;
    force_text = nullptr;
    fuel_text = nullptr;
    velocity_text = nullptr;
    altitude_text = nullptr;
    name = "TsKB-7 solid (15D94)";

    diameter = 1.f;
    height = 5.45f;
}

void Rocket::update(float dt) {
    float mass_used = 0.f;
    if (!stopped) {
        mass_used = dt * 73.47f;
        mass = initial_mass - mass_used;
    }

    float down_force = -9.81f * mass;
    float thrust_force = 0.f;

    if (!stopped) {
        //float velocity_variation = 300.f * log(initial_mass / mass);
        //float up_acceleration = velocity_variation / dt;
        thrust_force = 180400.f;
    }

    float drag_force = 1.05f * 1.225f * velocity * velocity * (diameter / 2.f) * (diameter / 2.f) * 3.141 / 2.f;
    drag_force *= (velocity >= 0) ? -1 : 1;

    force = down_force + thrust_force + drag_force;
    acceleration = force / mass;
    velocity += acceleration * dt;
    position += velocity * dt;
    fuel -= mass_used;
    if (fuel <= 0) {
        stopped = true;
        fuel = 0.f;
        mass = dry_mass;
    }
    initial_mass = mass;

    if (position < 100.f) {
        position = 100.f;
        velocity = 0.f;
    }
}

void Rocket::render(SDL_Renderer* renderer, TTF_Font *font, int& camera_x, int& camera_y) {
    std::string mass_string = "mass: " + std::to_string(mass);
    SDL_Surface* mass_surface = TTF_RenderText_Solid(font, mass_string.c_str(), {255, 0, 0, 255});
    mass_text = SDL_CreateTextureFromSurface(renderer, mass_surface);
    SDL_FreeSurface(mass_surface);
    SDL_Rect dst;
    dst.x = 0;
    dst.y = 0;
    dst.w = 24 * mass_string.length() / 2;
    dst.h = 24;
    SDL_RenderCopy(renderer, mass_text, nullptr, &dst);
    SDL_DestroyTexture(mass_text);


    std::string velocity_string = "velocity: " + std::to_string(velocity);
    SDL_Surface* velocity_surface = TTF_RenderText_Solid(font, velocity_string.c_str(), {255, 0, 0, 255});
    velocity_text = SDL_CreateTextureFromSurface(renderer, velocity_surface);
    SDL_FreeSurface(velocity_surface);
    dst.w = 24 * mass_string.length() / 2;
    dst.y = 25;
    SDL_RenderCopy(renderer, velocity_text, nullptr, &dst);
    SDL_DestroyTexture(velocity_text);


    std::string force_string = "force: " + std::to_string(force);
    SDL_Surface* force_surface = TTF_RenderText_Solid(font, force_string.c_str(), {255, 0, 0, 255});
    force_text = SDL_CreateTextureFromSurface(renderer, force_surface);
    SDL_FreeSurface(force_surface);
    dst.w = 24 * mass_string.length() / 2;
    dst.y = 50;
    SDL_RenderCopy(renderer, force_text, nullptr, &dst);
    SDL_DestroyTexture(force_text);


    std::string acceleration_string = "acceleration: " + std::to_string(acceleration);
    SDL_Surface* acceleration_surface = TTF_RenderText_Solid(font, acceleration_string.c_str(), {255, 0, 0, 255});
    acceleration_text = SDL_CreateTextureFromSurface(renderer, acceleration_surface);
    SDL_FreeSurface(acceleration_surface);
    dst.w = 24 * acceleration_string.length() / 2;
    dst.y = 75;
    SDL_RenderCopy(renderer, acceleration_text, nullptr, &dst);
    SDL_DestroyTexture(acceleration_text);


    std::string fuel_string = "fuel: " + std::to_string(fuel);
    SDL_Surface* fuel_surface = TTF_RenderText_Solid(font, fuel_string.c_str(), {255, 0, 0, 255});
    fuel_text = SDL_CreateTextureFromSurface(renderer, fuel_surface);
    SDL_FreeSurface(fuel_surface);
    dst.w = 24 * fuel_string.length() / 2;
    dst.y = 100;
    SDL_RenderCopy(renderer, fuel_text, nullptr, &dst);
    SDL_DestroyTexture(fuel_text);


    std::string altitude_string = "altitude: " + std::to_string(position);
    SDL_Surface* altitude_surface = TTF_RenderText_Solid(font, altitude_string.c_str(), {255, 0, 0, 255});
    altitude_text = SDL_CreateTextureFromSurface(renderer, altitude_surface);
    SDL_FreeSurface(altitude_surface);
    dst.w = 24 * altitude_string.length() / 2;
    dst.y = 125;
    SDL_RenderCopy(renderer, altitude_text, nullptr, &dst);
    SDL_DestroyTexture(altitude_text);


    std::string name_string = "name: " + name;
    SDL_Surface* name_surface = TTF_RenderText_Solid(font, name_string.c_str(), {255, 0, 0, 255});
    name_text = SDL_CreateTextureFromSurface(renderer, name_surface);
    SDL_FreeSurface(name_surface);
    dst.w = 24 * name_string.length() / 2;
    dst.y = 150;
    SDL_RenderCopy(renderer, name_text, nullptr, &dst);
    SDL_DestroyTexture(name_text);

    camera_y = position - 300;
    if (!stopped) {

        dst.x = 500 - camera_x;
        dst.y = 720 - (int)position + camera_y;
        dst.w = 50;
        dst.h = 50;
        SDL_RenderCopy(renderer, fire_sprite, nullptr, &dst);
    }

    SDL_Rect rock;
    rock.x = 500 - camera_x;
    rock.y = 600 - (int)position + camera_y;
    rock.w = 50;
    rock.h = 120;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rock);
}