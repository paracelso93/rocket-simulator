#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "rocket.h"

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("Rocket", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "ERROR::MAIN.CPP::MAIN:SDL_CREATE_WINDOW_FAILED" << std::endl;
        return -1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "ERROR::MAIN.CPP::MAIN::SDL_CREATE_RENDERER_FAILED" << std::endl;
        return -1;
    }
    TTF_Font* arial = nullptr;
    arial = TTF_OpenFont("res/arial.ttf", 48);
    if (arial == nullptr) {
        std::cerr << "ERROR::MAIN.CPP::MAIN::TTF_OPEN_FONT_FAILED" << std::endl;
        return -1;
    }
    bool done = false;

    SDL_Texture* ground = IMG_LoadTexture(renderer, "res/ground2.png");

    Rocket rocket(4640.f + 2000.f, 3600.f, renderer);
    //Rocket rocket(4640.f + 2000.f, 1000.f, renderer);
    Uint32 startTime = 0;
    Uint32 endTime = 0;
    Uint32 delta = 160;
    short fps = 60;
    short timePerFrame = 16;

    int camera_x = 0, camera_y = 0;

    while (!done) {
        if (!startTime) {
            // get the time in ms passed from the moment the program started
            startTime = SDL_GetTicks();
        } else {
            delta = endTime - startTime; // how many ms for a frame
        }
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = true;
            }
        }

        const Uint8* state = SDL_GetKeyboardState(nullptr);
        if (state[SDL_SCANCODE_ESCAPE]) {
            done = true;
        }

        rocket.update(1.f / fps);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        rocket.render(renderer, arial, camera_x, camera_y);
        SDL_Rect gr;
        gr.x = 0 - camera_x;
        //gr.y = 100 + camera_y;
        gr.y = 720 - 100 + camera_y;
        gr.w = 1080;
        gr.h = 100;
        SDL_RenderCopy(renderer, ground, nullptr, &gr);

        SDL_RenderPresent(renderer);



        // if less than 16ms, delay
        if (delta < timePerFrame) {
            SDL_Delay(timePerFrame - delta);
        }

        // if delta is bigger than 16ms between frames, get the actual fps
        if (delta > timePerFrame) {
            fps = 1000 / delta;
        }

        startTime = endTime;
        endTime = SDL_GetTicks();
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}