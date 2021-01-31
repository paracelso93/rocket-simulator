//
// Created by edoardo biasio on 2021-01-31.
//


#include "label.h"

Label::Label(std::string text, int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    this->text = text;
    this->position.x = x;
    this->position.y = y;
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void Label::set_string(std::string text) {
    this->text = text;
}

void Label::set_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void Label::render(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Rect rec;
    rec.x = position.x;
    rec.y = position.y;
    rec.w = 24 * text.length() / 2;
    rec.h = 24;
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), {(uint8_t)r, (uint8_t)g, (uint8_t)b});
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, nullptr, &rec);
    SDL_DestroyTexture(texture);
}