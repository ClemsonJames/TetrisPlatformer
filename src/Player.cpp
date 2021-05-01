#include "../include/Player.h"

void Player::controller(SDL_Event& input){
    //const uint8_t* kbState = SDL_GetKeyboardState(NULL);
    if (input.type == SDL_KEYDOWN) {
		switch (input.key.keysym.sym) {
		case SDLK_a:
			if (runLstop) {
				runLstop = false;
				Run_L();
			}
			break;

		case SDLK_d:
			if (runRstop) {
				runRstop = false;
				Run_R();
			}
			break;

		case SDLK_SPACE:
			if (end_jump) {
				end_jump = false;
				jump();
			}
			break;
		case SDLK_LSHIFT:
			Magic = true;
			break;

		case SDLK_s:
			if (state == JUMP) {
				groundPound();
			}
			break;
		case SDLK_w:
			kick = true;
			break;
		}
	}
	if (input.type == SDL_KEYUP) {
		switch (input.key.keysym.sym) {
		case SDLK_a:
			runLstop = true;
			if (velX < 0){
				stop_run();
			}
			break;

		case SDLK_d:
			runRstop = true;
			if (velX > 0) {
				stop_run();
			}
			break;
		case SDLK_SPACE:
			end_jump = true;
			break;
		case SDLK_LSHIFT:
			Magic = false;
		}
	}
}

void Player::updatePos() {
	//std::cout << state << std::endl;
    switch (state) {
		case IDLE:
			sprite->setFrame(0);
			break;
		case JUMP:
			jump();
			break;
		case SMASH:
			groundPound();
			break;

		case RUN:
			run();
            sprite->nextFrame();
			break;
	}
}

void Player::jump() {
	//std::cout << velY << std::endl;
	// Sets Vertical velocity, and Player state to Jump
	if (Jump_Frame == 0 && state != JUMP) {
		Jump_Start = SDL_GetTicks()/ Jump_FR;
		velY = -5;
		state = JUMP;
	}

	/*Increases the Y velocity when Jump_Frame modulus 7 = 0,
	  and the Y velocity is less then or equal to 4*/
	else if (Jump_Frame < (SDL_GetTicks() / Jump_FR - Jump_Start) && velY <= 4) {
		Jump_Frame = (SDL_GetTicks() / Jump_FR - Jump_Start);
		if (Jump_Frame < 1)
			sprite->setFrame(4);
		else if (Jump_Frame < 2)
			sprite->setFrame(5);
		else 
			sprite->setFrame(6);
		velY += Gravity;
		/*if (velY == 0) {
			Gravity = 2;
		}*/
	}


	//Adjust Player position and boundaries based on the X and Y velocity
	destRect.y += velY;
	destRect.x += velX;
	Hit_Boxes[0].TE = destRect.y;
	Hit_Boxes[0].BE = destRect.y + destRect.h;
	Hit_Boxes[0].LE = destRect.x + 6;
	Hit_Boxes[0].RE = destRect.x + destRect.w - 6;
}

void Player::stop_jump() {
	//Gravity = 1;

	//else if the player Velocity X = 0 Set state = Idle
	if (velX == 0) {
		state = IDLE;
	}

	//else set state = Run
	else {
		state = RUN;
	}

	Jump_Frame = 0;
	Jump_Start = 0;
}

void Player::groundPound() {
	//std::cout << velY << std::endl;
// Sets Vertical velocity, and Player state to Smash
	if (state != SMASH) {
		//Jump_Start = SDL_GetTicks() / Jump_FR;
		velY = 0;
		state = SMASH;
	}

	/*Increases the Y velocity when Jump_Frame modulus 7 = 0,
	  and the Y velocity is less then or equal to 4*/
	/*else if (Jump_Frame < (SDL_GetTicks() / Jump_FR - Jump_Start) && velY <= 4) {
		Jump_Frame = (SDL_GetTicks() / Jump_FR - Jump_Start);
		if (Jump_Frame < 1)
			sprite->setFrame(4);
		else if (Jump_Frame < 2)
			sprite->setFrame(5);
		else
			sprite->setFrame(6);
		velY += (Gravity*2);
		//if (velY == 0) {
			//Gravity = 2;
		//}
	}*/
	else if (velY <= 6) {
		velY += (Gravity * 1.5);
	}


	//Adjust Player position and boundaries based on the X and Y velocity
	destRect.y += velY;
	destRect.x += velX;
	Hit_Boxes[0].TE = destRect.y;
	Hit_Boxes[0].BE = destRect.y + destRect.h;
	Hit_Boxes[0].LE = destRect.x + 6;
	Hit_Boxes[0].RE = destRect.x + destRect.w - 6;
	
}

int Player::getLeft(){
	return left;
}

/*set Player State = Run, and Player X velocity = 4*/
void Player::Run_R() {
	if (state != JUMP)
		state = RUN;
	velX = 4;
	left = 0;
}


/*set Player State = Run, and Player X velocity = -4*/
void Player::Run_L() {
	if (state != JUMP)
		state = RUN;
	velX = -4;
	left = 1;
}


/*Update Player position based on Player X velocity*/
void Player::run() {
	//destRect.y += velY;
	destRect.x += velX;
	//Hit_Boxes[0].TE = destRect.y;
	//Hit_Boxes[0].BE = destRect.y + destRect.h;
	Hit_Boxes[0].LE = destRect.x + 6;
	Hit_Boxes[0].RE = destRect.x + destRect.w -6;
	//Hit_Boxes[1].BE = Hit_Boxes[0].BE - KickH;
	//Hit_Boxes[1].TE = Hit_Boxes[1].BE - KickH;
	//Hit_Boxes[2].BE = Hit_Boxes[0].BE - KickH;
	//Hit_Boxes[2].TE = Hit_Boxes[2].BE - KickH;

}

void Player::stop_run() {
	velX = 0;
	//runstop = true;
	if (velY != 0) {
		state = JUMP;
	}
	else {
		state = IDLE;
	}
}

Hit_Box Player::get_Hitbox() {
	return Hit_Boxes[0];
}

Hit_Box Player::Kick(){
	kick = false;
	Hit_Boxes[2].BE = Hit_Boxes[0].BE - KickH;
	Hit_Boxes[2].TE = Hit_Boxes[2].BE - KickH;
	Hit_Boxes[2].RE = Hit_Boxes[0].LE;
	Hit_Boxes[2].LE = Hit_Boxes[2].RE - KickL;
	Hit_Boxes[1].LE = Hit_Boxes[0].RE;
	Hit_Boxes[1].RE = Hit_Boxes[1].LE + KickL;
	Hit_Boxes[1].BE = Hit_Boxes[0].BE - KickH;
	Hit_Boxes[1].TE = Hit_Boxes[1].BE - KickH;
	return Hit_Boxes[left + 1];
}

void Player::collision_response(char type, int edge, int Obj_index) {
	bool collision = true;
	//std::cout << type << std::endl;
	switch (type) {
            case 'B':
				velY = 0;
				if (edge > Hit_Boxes[0].BE) {
					collision = false;
				}
				destRect.y -= Hit_Boxes[0].BE - edge -1;
				Rotate_block = Obj_index;
				Hit_Boxes[0].TE = destRect.y;
				Hit_Boxes[0].BE = destRect.y + destRect.h;
				//if (collision) {
				stop_jump();
				//}
                break;
            case 'R':
				velX = 0;
				destRect.x += edge - Hit_Boxes[0].RE - 1;
				Hit_Boxes[0].LE = destRect.x + 6;
				Hit_Boxes[0].RE = destRect.x + destRect.w - 6;
				//stop_run();
                break;
            case 'L':
				velX = 0;
				destRect.x -= Hit_Boxes[0].LE - edge - 1;
				Hit_Boxes[0].LE = destRect.x + 6;
				Hit_Boxes[0].RE = destRect.x + destRect.w -6;
				//stop_run();
                break;
            case 'T':
				velY = 0;
				destRect.y += edge - Hit_Boxes[0].TE;
				Hit_Boxes[0].TE = destRect.y;
				Hit_Boxes[0].BE = destRect.y + destRect.h;
                break;
            default:
                if (Hit_Boxes[0].BE != edge && state != SMASH) {
                    state = JUMP;
                    break;
                }
    }
}

int Player::getState() {
	return state;
}

bool Player::getKick(){
	return kick;
}

void Player::render(SDL_Renderer* renderer) {
    sprite->render(renderer, destRect, !!left);
}
