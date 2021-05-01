#pragma once

#include <SDL.h> 
#include <SDL_image.h> 
#include <SDL_timer.h>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "Sprite.h"
#include "Collision.h"

class Game_Entity {
    
	protected:
		std::vector<Hit_Box> Hit_Boxes;
		SDL_Rect destRect;
        Sprite* sprite;
        double velX = 0.0;
        double velY = 0.0;
		bool check_col = true;
		int id = -1;


	public:
		bool active;
		Game_Entity(int x, int y, int w, int h)
		{
			destRect.x = x;
            destRect.y = y;
            destRect.w = w;
            destRect.h = h;
		}
		~Game_Entity() {}

		double get_velX();
		double get_velY();
		bool get_check_col();
		int getID();
		std::vector<Hit_Box> get_Hit_Boxs();
		virtual void updatePos() {}
		virtual void render(SDL_Renderer *gameRenderer);
		virtual void collision_response(char type, int edge, int Obj_index) {}
		virtual void controller(SDL_Event& event) {}
		virtual void Rotate(bool direct) {}
		virtual void Move(int x, int y) {}
		virtual bool inside(int x, int y) {}
		virtual void no_action(){}
		virtual std::vector<SDL_Rect> getRect() {}
		virtual int get_action(){}
};