#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Texture {
public:
    Texture();
    ~Texture();

    bool loadFromFile(SDL_Renderer* renderer, const std::string& path);
    void render(SDL_Renderer* renderer, int x, int y, int w = 0, int h = 0);
    void free();

    int getWidth() const;
    int getHeight() const;

private:
    SDL_Texture* texture;
    int width;
    int height;
};

#endif // TEXTURE_H
