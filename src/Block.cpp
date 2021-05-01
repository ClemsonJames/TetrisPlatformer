#include "../include/Block.h"


void Block::rotate(bool direct) {
	if (direct) {
		if (State == 3) {
			State = 0;
		}
		else {
			State += 1;
		}
	}
	else {
		if (State == 0) {
			State = 3;
		}
		else {
			State -= 1;
		}
	}

		dest_rect.w = w;
		dest_rect.h = h;
		
		if (State == 0) {
			Box.LE = Px - offset;
			Box.RE = Box.LE + w;
			Box.TE = Py;
			Box.BE = Py + h;
		}
		else if (State == 1) {
			dest_rect.w = h;
			dest_rect.h = w;
			Box.LE = Px;
			Box.RE = Px + h;
			Box.BE = Py + offset;
			Box.TE = Box.BE - w;
		}
		else if (State == 2) {
			dest_rect.w = w;
			dest_rect.h = h;
			Box.RE = Px + offset;
			Box.LE = Box.RE - w;
			Box.TE = Py - h;
			Box.BE = Py;
		}
		else if (State == 3) {
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

void Block::move(int x, int y){
	Px += x;
	Py += y;
	dest_rect.w = w;
	dest_rect.h = h;
	
	if (State == 0) {
		Box.LE = Px - offset;
		Box.RE = Box.LE + w;
		Box.TE = Py;
		Box.BE = Py + h;
	}
	else if (State == 1) {
		dest_rect.w = h;
		dest_rect.h = w;
		Box.LE = Px;
		Box.RE = Px + h;
		Box.BE = Py + offset;
		Box.TE = Box.BE - w;
	}
	else if (State == 2) {
		dest_rect.w = w;
		dest_rect.h = h;
		Box.RE = Px + offset;
		Box.LE = Box.RE - w;
		Box.TE = Py - h;
		Box.BE = Py;
	}
	else if (State == 3) {
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

bool Block::inside(int x, int y) {
	 //Check if mouse is in button
    bool inside = true;

    //Mouse is left of the button
    if( x < dest_rect.x )
    {
        inside = false;
    }
    //Mouse is right of the button
    else if( x > dest_rect.x + dest_rect.w )
    {
        inside = false;
    }
    //Mouse above the button
    else if( y < dest_rect.y )
    {
        inside = false;
    }
    //Mouse below the button
    else if( y > dest_rect.y + dest_rect.h )
    {
        inside = false;
    }

    return inside;
}


void Block::render(SDL_Renderer* gameRenderer, Sprite* sprite) {
	/*std::cout << "x:"<< Px - h << std::endl;
	std::cout << "y:"<< dest_rect.y << std::endl;
	std::cout << "w:"<< Px << std::endl;
	std::cout << "h:"<< h << "\n\n\n\n\n"<<std::endl;
	
	for (int i = 1; i < w / dest_rect.w; i++) {
		//std::cout << w / dest_rect.w << std::endl;
		sprite->render(gameRenderer, dest_rect, false);
		dest_rect.x += dest_rect.w;
	}
	dest_rect.y += dest_rect.h;
	for (int i = 1; i < h / dest_rect.h; i++) {
		sprite->render(gameRenderer, dest_rect, false);
		dest_rect.y += dest_rect.h;
	}

	dest_rect.x = Box.LE;
	dest_rect.y = Box.TE;*/
	sprite->render(gameRenderer, dest_rect, false);
}

int Block::get_Px(){
	return Px;
}

int Block::get_Py(){
	return Py;
}

SDL_Rect Block::getRect() {
	return dest_rect;
}
