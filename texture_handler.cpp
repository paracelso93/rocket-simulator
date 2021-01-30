#include "texture_handler.h"

TextureHandler* TextureHandler::mInstance = nullptr;

bool TextureHandler::add_texture(const std::string& filePath, texture_t& id, SDL_Renderer* renderer) {
	id = std::hash<std::string>()(filePath);
	if (mTextures.find(id) != mTextures.end()) {
		return true;
	}
	
	SDL_Surface* sur = IMG_Load(filePath.c_str());
	LOG(sur, "load surface " + filePath);
	
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, sur);
	LOG(tex, "create texture " + filePath);
	
	mTextures[id] = tex;
    int w, h;
    SDL_QueryTexture(mTextures[id], nullptr, nullptr, &w, &h);
    //mSizes[id] = Vector2<float>(w, h);
    mSizes.insert(std::pair<texture_t, Vector2<float> >(id, Vector2<float>(w, h)));
    mSizes.insert(std::pair<texture_t, Vector2<float> >(id, Vector2<float>(0, 0)));

	return true;
}

SDL_Texture* TextureHandler::get_texture(texture_t id) {
	if (mTextures.find(id) != mTextures.end()) {
		return mTextures[id];
	} 
	std::cerr << "Unable to load " << std::to_string(id) << std::endl;
	return nullptr;
}

void TextureHandler::render(SDL_Renderer* renderer, texture_t id, const Vector2<float>& position, const Vector2<float>& scale, float rotation, const Vector2<float>& center, SDL_RendererFlip flip) {
	if (mTextures.find(id) == mTextures.end()) {
		std::cerr << "texture " << std::to_string(id) << " doesn't exists!" << std::endl;
		return;
	}
	
	SDL_Rect src;
	src.x = mPositions[id].x;
	src.y = mPositions[id].y;

	src.w = mSizes[id].x;
	src.h = mSizes[id].y;
	
	SDL_Rect dst;
	dst.x = position.x;
	dst.y = position.y;
	dst.w = mSizes[id].x * scale.x;
	dst.h = mSizes[id].y * scale.y;
	
	SDL_Point cen;
	cen.x = center.x;
	cen.y = center.y;
	
	SDL_RenderCopyEx(renderer, mTextures[id], &src, &dst, rotation, &cen, flip);
}

void TextureHandler::set_src_rect(texture_t id, const Vector2<float>& src) {
    if (mTextures.find(id) == mTextures.end()) {
        std::cerr << "texture " << std::to_string(id) << " doesn't exists!" << std::endl;
        return;
    }

    mSizes[id] = src;
}

void TextureHandler::set_src_position(texture_t id, const Vector2<float>& src) {
    if (mTextures.find(id) == mTextures.end()) {
        std::cerr << "texture " << std::to_string(id) << " doesn't exists!" << std::endl;
        return;
    }

    mPositions[id] = src;
}

bool TextureHandler::point_in_texture(const Vector2<float>& point, const Vector2<float>& position, texture_t id) {
	if (mTextures.find(id) == mTextures.end()) {
		std::cerr << "texture " << std::to_string(id) << " doesn't exists!" << std::endl;
		return false;
	}
	int w, h;
	SDL_QueryTexture(mTextures[id], nullptr, nullptr, &w, &h);
	return point_in_rectangle(point, position, Vector2<float>(static_cast<float>(w), static_cast<float>(h)));
}
	
