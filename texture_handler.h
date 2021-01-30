#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <string>

#include "vectors.h"
#include "helper.h"

#define texture_t unsigned int

class TextureHandler {
	public:
		static TextureHandler* getInstance() {
			if (mInstance == nullptr) {
				mInstance = new TextureHandler();
				return mInstance;
			}
			return mInstance;
		}
		bool add_texture(const std::string& filePath, texture_t& id, SDL_Renderer* renderer);
		SDL_Texture* get_texture(texture_t id);
		void render(SDL_Renderer* renderer, texture_t id, const Vector2<float>& position, const Vector2<float>& scale = Vector2<float>(1.0f, 1.0f), float rotation = 0, const Vector2<float>& center = Vector2<float>(), SDL_RendererFlip flip = SDL_FLIP_NONE);
		bool point_in_texture(const Vector2<float>& point, const Vector2<float>& position, texture_t id);
		void set_src_rect(texture_t id, const Vector2<float>& src);
		void set_src_position(texture_t id, const Vector2<float>& src);
	private:
		static TextureHandler* mInstance;
		std::unordered_map<texture_t, Vector2<float> > mSizes;
		std::unordered_map<texture_t, Vector2<float> > mPositions;
		std::unordered_map<texture_t, SDL_Texture*> mTextures;
};
