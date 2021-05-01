#pragma once
#include <cmath>
#include <SDL.h> 
#include <SDL_image.h> 
#include <SDL_timer.h>
#include <string>
#include "Sprite.h"

class Button{
	private:
        SDL_Rect destRect;
        Sprite* sprite;
        int ID;

	public:

		Button(int x, int y, int w, int h, int id, std::string name, Image_Handler* image) {
            destRect.x = x;
            destRect.y = y;
            destRect.w = w;
            destRect.h = h;
            ID = id;
            sprite = new Sprite(0, w, h, name, image);
            sprite->setFrame(0);
        }

        ~Button() {}

        SDL_Rect getRect();
        int getID();
        void render(SDL_Renderer* renderer);
        bool inside(int x, int y); 
};