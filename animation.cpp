//
// Created by edoardo biasio on 2021-01-30.
//

#include "animation.h"

Animation::Animation(const std::string& file_path, Vector2<float> position, int rows, int cols, int total_frames, float time, SDL_Renderer* renderer) {
    TextureHandler::getInstance()->add_texture(file_path, this->texture, renderer);
    this->rows = rows;
    this->cols = cols;
    this->current_frame = 0;
    this->current_col = 0;
    this->current_row = 0;
    this->num_total = total_frames;
    this->timer = 0.f;
    this->timer_max = time;
    int w, h;
    SDL_Texture* obama_piramide = TextureHandler::getInstance()->get_texture(this->texture);

    SDL_QueryTexture(obama_piramide, nullptr, nullptr, &w, &h);
    this->width = w / cols;
    this->height = h / rows;
    this->position = position;
    TextureHandler::getInstance()->set_src_rect(texture, Vector2<float>(width, height));
}

void Animation::update(float dt) {
    this->timer += dt;
    if (timer >= timer_max) {
        this->current_frame ++;
        this->timer = 0.f;
        if (this->current_frame >= num_total) {
            this->current_frame = 0;
            this->current_row = 0;
            this->current_col = 0;

            TextureHandler::getInstance()->set_src_position(texture, Vector2<float>(0, 0));
        } else {

            this->current_col++;
            if (current_col >= cols) {
                current_col = 0;
                current_row++;

                TextureHandler::getInstance()->set_src_position(texture, Vector2<float>(0, current_row * height));
            } else {
                TextureHandler::getInstance()->set_src_position(texture, Vector2<float>(current_col * width,
                                                                                        current_row * height));
            }
        }
    }
}

void Animation::render(SDL_Renderer* renderer) {
    TextureHandler::getInstance()->render(renderer, texture, position, Vector2<float>(0.1f, 0.24f));
}