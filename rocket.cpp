//
// Created by edoardo biasio on 2021-01-28.
//

#include "rocket.h"

#include <iostream>

Rocket::Rocket(float mass, float fuel, SDL_Renderer* renderer) : obamium("", Vector2<float>(0, 0), 0, 0, 0, 0, renderer), position(100.f), initial_mass(mass), mass(mass), velocity(0.f), acceleration(0.f), fuel(fuel), force(0.f) {
    stopped = false;
    dry_mass = mass - fuel;

    //fire_sprite = IMG_LoadTexture(renderer, "res/fire.png");

    TextureHandler::getInstance()->add_texture("res/flame.png", fire_sprite, renderer);
    //TextureHandler::getInstance()->add_texture("res/obamium.png", obamium, renderer);
    //TextureHandler::getInstance()->set_src_rect(obamium, Vector2<float>(498, 498));
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

Rocket::Rocket(const RocketData& data, SDL_Renderer* renderer) : obamium(data.rocket_sprite, Vector2<float>(500.f, 100.f), 6, 5, 29, 1.f / 24.f, renderer) {
    this->position = 100.f;
    this->initial_mass = data.mass;
    this->mass = data.mass;
    this->velocity = 0.f;
    this->acceleration = 0.f;
    this->fuel = data.fuel;
    this->force = 0.f;
    this->stopped = false;
    this->dry_mass = this->mass - this->fuel;

    TextureHandler::getInstance()->add_texture("res/flame.png", fire_sprite, renderer);

    //this->obamium = data.rocket_sprite;

    //TextureHandler::getInstance()->add_texture("res/obamium.png", obamium, renderer);
    //TextureHandler::getInstance()->set_src_rect(obamium, Vector2<float>(498, 498));

    mass_text = new Label("", 10, 10, 255, 0, 0, 255);
    acceleration_text = new Label("", 10, 35, 255, 0, 0, 255);
    force_text = new Label("", 10, 60, 255, 0, 0, 255);
    fuel_text = new Label("", 10, 85, 255, 0, 0, 255);
    velocity_text = new Label("", 10, 110, 255, 0, 0, 255);
    altitude_text = new Label("", 10, 135, 255, 0, 0, 255);
    name_text = new Label("", 10, 160, 255, 0, 0, 255);

    this->name = data.name;
    this->diameter = data.diameter;
    this->height = data.height;
    this->thrust = data.thrust;
    this->fuel_consumption = data.fuel_consumption;
}

void Rocket::update(float dt) {
    float mass_used = 0.f;
    if (!stopped) {
        mass_used = dt * fuel_consumption;
        mass = initial_mass - mass_used;
    }

    float down_force = -GRAVITATIONAL_ACCELERATION * mass;
    float thrust_force = 0.f;

    if (!stopped) {
        //float velocity_variation = 300.f * log(initial_mass / mass);
        //float up_acceleration = velocity_variation / dt;
        thrust_force = thrust;
    }

    float radius = diameter / 2.f;
    float drag_force = 1.05f * 1.225f * velocity * velocity * radius * radius * PI / 2.f;
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

    if (position <= 101.f && stopped) {
        obamium.set_running(false);
    }

    obamium.update(dt);
}

void Rocket::render(SDL_Renderer* renderer, TTF_Font *font, int& camera_x, int& camera_y) {
    SDL_Rect big_rect;
    big_rect.x = 0;
    big_rect.y = 0;
    big_rect.w = 350;
    big_rect.h = 200;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &big_rect);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &big_rect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    std::string mass_string = "mass: " + std::to_string(mass);
    mass_text->set_string(mass_string);
    mass_text->render(renderer, font);

    std::string velocity_string = "velocity: " + std::to_string(velocity);
    velocity_text->set_string(velocity_string);
    velocity_text->render(renderer, font);

    std::string force_string = "force: " + std::to_string(force);
    force_text->set_string(force_string);
    force_text->render(renderer, font);

    std::string acceleration_string = "acceleration: " + std::to_string(acceleration);
    acceleration_text->set_string(acceleration_string);
    acceleration_text->render(renderer, font);

    std::string fuel_string = "fuel: " + std::to_string(fuel);
    fuel_text->set_string(fuel_string);
    fuel_text->render(renderer, font);

    std::string altitude_string = "altitude: " + std::to_string(position);
    altitude_text->set_string(altitude_string);
    altitude_text->render(renderer, font);

    std::string name_string = "name: " + name;
    name_text->set_string(name_string);
    name_text->render(renderer, font);

    /*SDL_Surface* mass_surface = TTF_RenderText_Solid(font, mass_string.c_str(), {255, 0, 0, 255});
    mass_text = SDL_CreateTextureFromSurface(renderer, mass_surface);
    SDL_FreeSurface(mass_surface);
    SDL_Rect dst;
    dst.x = 10;
    dst.y = 10;
    dst.w = 24 * mass_string.length() / 2;
    dst.h = 24;
    SDL_RenderCopy(renderer, mass_text, nullptr, &dst);
    SDL_DestroyTexture(mass_text);


    std::string velocity_string = "velocity: " + std::to_string(velocity);
    SDL_Surface* velocity_surface = TTF_RenderText_Solid(font, velocity_string.c_str(), {255, 0, 0, 255});
    velocity_text = SDL_CreateTextureFromSurface(renderer, velocity_surface);
    SDL_FreeSurface(velocity_surface);
    dst.w = 24 * mass_string.length() / 2;
    dst.y = 35;
    SDL_RenderCopy(renderer, velocity_text, nullptr, &dst);
    SDL_DestroyTexture(velocity_text);


    std::string force_string = "force: " + std::to_string(force);
    SDL_Surface* force_surface = TTF_RenderText_Solid(font, force_string.c_str(), {255, 0, 0, 255});
    force_text = SDL_CreateTextureFromSurface(renderer, force_surface);
    SDL_FreeSurface(force_surface);
    dst.w = 24 * mass_string.length() / 2;
    dst.y = 60;
    SDL_RenderCopy(renderer, force_text, nullptr, &dst);
    SDL_DestroyTexture(force_text);


    std::string acceleration_string = "acceleration: " + std::to_string(acceleration);
    SDL_Surface* acceleration_surface = TTF_RenderText_Solid(font, acceleration_string.c_str(), {255, 0, 0, 255});
    acceleration_text = SDL_CreateTextureFromSurface(renderer, acceleration_surface);
    SDL_FreeSurface(acceleration_surface);
    dst.w = 24 * acceleration_string.length() / 2;
    dst.y = 85;
    SDL_RenderCopy(renderer, acceleration_text, nullptr, &dst);
    SDL_DestroyTexture(acceleration_text);


    std::string fuel_string = "fuel: " + std::to_string(fuel);
    SDL_Surface* fuel_surface = TTF_RenderText_Solid(font, fuel_string.c_str(), {255, 0, 0, 255});
    fuel_text = SDL_CreateTextureFromSurface(renderer, fuel_surface);
    SDL_FreeSurface(fuel_surface);
    dst.w = 24 * fuel_string.length() / 2;
    dst.y = 110;
    SDL_RenderCopy(renderer, fuel_text, nullptr, &dst);
    SDL_DestroyTexture(fuel_text);


    std::string altitude_string = "altitude: " + std::to_string(position);
    SDL_Surface* altitude_surface = TTF_RenderText_Solid(font, altitude_string.c_str(), {255, 0, 0, 255});
    altitude_text = SDL_CreateTextureFromSurface(renderer, altitude_surface);
    SDL_FreeSurface(altitude_surface);
    dst.w = 24 * altitude_string.length() / 2;
    dst.y = 135;
    SDL_RenderCopy(renderer, altitude_text, nullptr, &dst);
    SDL_DestroyTexture(altitude_text);


    std::string name_string = "name: " + name;
    SDL_Surface* name_surface = TTF_RenderText_Solid(font, name_string.c_str(), {255, 0, 0, 255});
    name_text = SDL_CreateTextureFromSurface(renderer, name_surface);
    SDL_FreeSurface(name_surface);
    dst.w = 24 * name_string.length() / 2;
    dst.y = 160;
    SDL_RenderCopy(renderer, name_text, nullptr, &dst);
    SDL_DestroyTexture(name_text);
*/
    camera_y = position - 300;
    if (!stopped) {

        //dst.x = 500 - camera_x;
        //dst.y = 720 - (int)position + camera_y;
        //dst.w = 50;
        //dst.h = 50;
        //SDL_RenderCopy(renderer, fire_sprite, nullptr, &dst);

        TextureHandler::getInstance()->render(renderer, fire_sprite, Vector2<float>(500 - camera_x, 720 - (int)position + camera_y), Vector2<float>(3.125, 3.125));
    }

    /*SDL_Rect rock;
    rock.x = 500 - camera_x;
    rock.y = 600 - (int)position + camera_y;
    rock.w = 50;
    rock.h = 120;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rock);*/
    obamium.position.y = 600 - (int)position + camera_y;
    //TextureHandler::getInstance()->render(renderer, obamium, Vector2<float>(500 - camera_x, 600 - (int)position + camera_y), Vector2<float>(0.1f, 0.24f));
    obamium.render(renderer);
}