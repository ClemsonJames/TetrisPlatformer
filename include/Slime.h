#pragma once
#include <cmath>
#include <SDL.h> 
#include <SDL_image.h> 
#include <SDL_timer.h>
#include <string>
#include <iostream>

#include "Enemy.h"
#include "../include/Image_Handler.h"

class Slime: public Enemy {
    protected:
        const double SPEED = 2.0;
        int counter = 0;

	public:

		Slime(int x, int y, int w, int h, std::string name, Image_Handler* image):
            Enemy(x, y, w, h, 3, name, image) {
                velX = SPEED;

                Hit_Box Temp; 
                Temp.LE = destRect.x;
                Temp.RE = destRect.x + destRect.w;
                Temp.TE = destRect.y;
                Temp.BE = destRect.y + destRect.h;
                Hit_Boxes.push_back(Temp);
            }

		~Slime() {}

        int getState();
		Hit_Box get_Hitbox();
        virtual void collision_response(char type, int edge, int Obj_index);
        void updatePos();
        void render(SDL_Renderer* renderer);

		
};