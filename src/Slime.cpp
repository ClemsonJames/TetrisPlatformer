#include "../include/Slime.h"

int Slime::getState() {
    return state;
}

Hit_Box Slime::get_Hitbox() {
    return Hit_Boxes[0];
}

void Slime::collision_response(char type, int edge, int Obj_index) {
    destRect.x -= velX;
    velX *= -1;
    left = (left+1) % 2;
    Hit_Boxes[0].LE = destRect.x;
    Hit_Boxes[0].RE = destRect.x + destRect.w;
}

void Slime::updatePos() {
    sprite->nextFrame();
    destRect.x += velX;
    Hit_Boxes[0].LE = destRect.x;
    Hit_Boxes[0].RE = destRect.x + destRect.w;
}

void Slime::render(SDL_Renderer* renderer) {
    sprite->render(renderer, destRect, !!left);
}