//
// Created by edoardo biasio on 2021-01-31.
//

#ifndef ROCKET_LABEL_H
#define ROCKET_LABEL_H

#include "texture_handler.h"
#include <SDL2/SDL_ttf.h>

class Label {
private:
    std::string text;
    Vector2<float> position;
    int r, g, b, a;
public:
    Label(std::string text, int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void set_string(std::string text);
    void set_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void render(SDL_Renderer* renderer, TTF_Font* font);
};


#endif //ROCKET_LABEL_H
