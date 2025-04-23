#include "Texture.h"

Texture::Texture() {
    texture = nullptr;
    width = 0;
    height = 0;
}

Texture::~Texture() {
    free();
}

bool Texture::loadFromFile(SDL_Renderer* renderer, const std::string& path) {
    free(); // Xóa texture cũ nếu có

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface) {
        SDL_Log("Unable to load image %s! SDL_image Error: %s", path.c_str(), IMG_GetError());
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (!texture) {
        SDL_Log("Unable to create texture from %s! SDL Error: %s", path.c_str(), SDL_GetError());
        SDL_FreeSurface(loadedSurface);
        return false;
    }

    width = loadedSurface->w;
    height = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);
    return true;
}

void Texture::render(SDL_Renderer* renderer, int x, int y, int w, int h) {
    SDL_Rect renderQuad = { x, y, w > 0 ? w : width, h > 0 ? h : height };
    SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);
}

void Texture::free() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        width = 0;
        height = 0;
    }
}

int Texture::getWidth() const {
    return width;
}

int Texture::getHeight() const {
    return height;
}
