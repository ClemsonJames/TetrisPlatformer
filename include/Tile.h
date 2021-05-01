#pragma once

#include <iostream>
#include "../include/Game_Entity.h"

class Tile: public Game_Entity{
	protected:
		int tileType;
		int numCols;

	public:
		Tile(int typeTile, int x, int y, int s, int nCols, bool collision, Image_Handler* image):
			Game_Entity(x, y, s, s) {
			if (collision) {
				Hit_Box Temp; 
                Temp.LE = destRect.x;
	            Temp.RE = destRect.x + destRect.w;
	            Temp.TE = destRect.y;
	            Temp.BE = destRect.y + destRect.h;
                Hit_Boxes.push_back(Temp);
			}
			check_col = collision;
            tileType = typeTile;
			numCols = nCols;
			sprite = new Sprite(1, 16, 16, "./asset/tiles.png", image);

			id = 0;

			int srcx = (tileType % numCols);
			int srcy = (tileType / numCols);

			sprite->setFrame(srcx, srcy);
		}

		~Tile() {}
		virtual void render(SDL_Renderer* gameRenderer);

};