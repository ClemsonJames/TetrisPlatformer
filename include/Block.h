#pragma once
#include <SDL.h>
#include "Collision.h"
#include "Sprite.h"
#include <iostream>

class Block {
private:
	int Px, Py, w, h;
	int offset;
	double degree;

	//int Tile_Size;
	int State = 0;

	SDL_Rect dest_rect;

public:
	Hit_Box Box;
	Block(int Px, int Py, int w, int h, int Tile_Size, int state, int offset): Px(Px), Py(Py), w(w), h(h), State(state), offset(offset){
		dest_rect.w = w;
		dest_rect.h = h;
		
		if (state == 0) {
			Box.LE = Px - offset;
			Box.RE = Box.LE + w;
			Box.TE = Py;
			Box.BE = Py + h;
		}
		else if (state == 1) {
			dest_rect.w = h;
			dest_rect.h = w;
			Box.LE = Px;
			Box.RE = Px + h;
			Box.BE = Py + offset;
			Box.TE = Box.BE - w;
		}
		else if (state == 2) {
			dest_rect.w = w;
			dest_rect.h = h;
			Box.RE = Px + offset;
			Box.LE = Box.RE - w;
			Box.TE = Py - h;
			Box.BE = Py;
		}
		else if (state == 3) {
			dest_rect.w = h;
			dest_rect.h = w;
			Box.LE = Px - h;
			Box.RE = Px;
			Box.TE = Py - offset;
			Box.BE = Box.TE + w;
		}
		dest_rect.x = Box.LE;
		dest_rect.y = Box.TE;
	}

	void rotate(bool direct);
	void rotate2(bool direct);
	void move(int x, int y);
	bool inside(int x, int y);
	void render(SDL_Renderer* gameRenderer, Sprite* sprite);
	int get_Px();
	int get_Py();
	SDL_Rect getRect();
};
