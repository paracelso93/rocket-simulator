//
// Created by edoardo biasio on 2021-01-30.
//

#ifndef ROCKET_ANIMATION_H
#define ROCKET_ANIMATION_H

#include "texture_handler.h"

class Animation {
public:
    Animation(const std::string& file_path, Vector2<float> position, int rows, int cols, int total_frames, float time, SDL_Renderer* renderer);
    void update(float dt);
    void render(SDL_Renderer* renderer);

    Vector2<float> position;
private:
    int rows;
    int cols;
    float timer;
    float timer_max;
    int num_total;
    int current_col;
    int current_frame;
    int current_row;
    int height;
    int width;

    texture_t texture;
};


#endif //ROCKET_ANIMATION_H
