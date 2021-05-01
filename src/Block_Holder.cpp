#include "../include/Block_Holder.h"


void Block_Holder::Rotate(bool direct){
	if(active){
		L_moveX = Blocks[0].get_Px();
		L_moveY = Blocks[0].get_Py();
		last_rotate = state;
		state += 1;
		action_take = 2;
		Blocks[0].rotate(direct);
		Blocks[1].rotate(direct);
		Hit_Boxes[0] = Blocks[0].Box;
		Hit_Boxes[1] = Blocks[1].Box;
	}
}

void Block_Holder::Move(int x, int y){
	if(active){
		action_take = 1;
		last_rotate = state;
		L_moveX = Blocks[0].get_Px();
		L_moveY = Blocks[0].get_Py();
		Blocks[0].move(x, y);
		Blocks[1].move(x, y);
		Hit_Boxes[0] = Blocks[0].Box;
		Hit_Boxes[1] = Blocks[1].Box;
	}
}

bool Block_Holder::inside(int x, int y) {
    //Check if mouse is in button
    return (Blocks[0].inside(x, y) || Blocks[1].inside(x, y));
} 

void Block_Holder::render(SDL_Renderer* gameRenderer){
	Blocks[0].render(gameRenderer, sprite);
	Blocks[1].render(gameRenderer, sprite);
}

void Block_Holder::collision_response(char type, int edge, int Obj_index) {
	if(active){
		// move
		if (action_take == 1){
			int x = L_moveX - Blocks[0].get_Px();
			int y = L_moveY - Blocks[0].get_Py();
			Blocks[0].move(x, y);
			Blocks[1].move(x, y);
			Hit_Boxes[0] = Blocks[0].Box;
			Hit_Boxes[1] = Blocks[1].Box;
		}
		// rotate
		else if (action_take == 2) {
			Blocks[0].rotate(false);
			Blocks[1].rotate(false);
			Hit_Boxes[0] = Blocks[0].Box;
			Hit_Boxes[1] = Blocks[1].Box;
		}

	}
	/*if(active && action_take == 1){
		Blocks[0].move(-1*L_moveX, -1*L_moveY);
		Blocks[1].move(-1*L_moveX, -1*L_moveY);
		Hit_Boxes[0] = Blocks[0].Box;
		Hit_Boxes[1] = Blocks[1].Box;
	}
	if(action_take == 2){
		if(active){
			action_take = 2;
			Blocks[0].rotate(!last_rotate);
			Blocks[1].rotate(!last_rotate);
			Hit_Boxes[0] = Blocks[0].Box;
			Hit_Boxes[1] = Blocks[1].Box;
		}*/
		/*switch (type) {
					case 'B':
						if(active){
							Blocks[0].move(Blocks[0].get_Px(), (edge - Hit_Boxes[0].BE));
							Blocks[1].move(Blocks[1].get_Px(), (edge - Hit_Boxes[1].BE));
							Hit_Boxes[0] = Blocks[0].Box;
							Hit_Boxes[1] = Blocks[1].Box;
						}
						break;
					case 'R':
						if(active){
							Blocks[0].move(edge - Hit_Boxes[0].RE, Blocks[0].get_Py());
							Blocks[1].move(edge - Hit_Boxes[1].RE, Blocks[1].get_Py());
							Hit_Boxes[0] = Blocks[0].Box;
							Hit_Boxes[1] = Blocks[1].Box;
						}
						break;
					case 'L':
						if(active){
							Blocks[0].move(edge - Hit_Boxes[0].LE, Blocks[0].get_Py());
							Blocks[1].move(edge - Hit_Boxes[1].LE, Blocks[1].get_Py());
							Hit_Boxes[0] = Blocks[0].Box;
							Hit_Boxes[1] = Blocks[1].Box;
						}
						break;
					case 'T':
						if(active){
							Blocks[0].move(Blocks[0].get_Px(), edge - Hit_Boxes[0].TE);
							Blocks[1].move(Blocks[1].get_Px(), edge - Hit_Boxes[1].TE);
							Hit_Boxes[0] = Blocks[0].Box;
							Hit_Boxes[1] = Blocks[1].Box;
						}
						break;
			}*/
		//}
}

void Block_Holder::no_action(){
	action_take = 0; //need to add this call when move or rotate are not called
}

int Block_Holder::get_action(){
	return action_take; //need to add this call when move or rotate are not called
}

bool Block_Holder::getActive(){
	return active;
}

std::vector<SDL_Rect> Block_Holder::getRect() {
	std::vector<SDL_Rect> rects;
	rects.push_back(Blocks[0].getRect());
	rects.push_back(Blocks[1].getRect());
	return rects;
}