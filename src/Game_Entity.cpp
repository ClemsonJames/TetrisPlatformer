#include "../include/Game_Entity.h"

double Game_Entity::get_velX(){
	return velX;
}
double Game_Entity::get_velY(){
	return velY;
}
bool Game_Entity::get_check_col(){
	return check_col;
}

std::vector<Hit_Box> Game_Entity::get_Hit_Boxs(){
	return Hit_Boxes;
}
void Game_Entity::render(SDL_Renderer* gameRenderer){
	sprite->render(gameRenderer, destRect, false);
}

int Game_Entity::getID() {
	return id;
}