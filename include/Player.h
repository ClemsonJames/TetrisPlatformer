#pragma once
#include <cmath>
#include <SDL.h> 
#include <SDL_image.h> 
#include <SDL_timer.h>
#include <string>
#include <iostream>

#include "Game_Entity.h"
#include "../include/Image_Handler.h"

class Player: public Game_Entity {
    protected:
    double Gravity = 1.3;
    int state = IDLE;
    int left = 0;
    int Jump_Frame = 0;
    int Jump_Start = 0; 
    int Jump_FR = 150;
    int Rotate_block;
	bool Magic = false;
	bool end_jump = false;
    bool runRstop = true;
    bool runLstop = true;
    bool kick = false;

public:
    const double SPEED = 3.0;
    const int KickL = 10;
    const int KickH = 10;
    static constexpr int IDLE = 0;
    static constexpr int RUN = 1;
    static constexpr int JUMP = 2;
    static constexpr int KICK = 3;
    static constexpr int SMASH = 4;

    Player(int x, int y, int w, int h, Image_Handler *image) : Game_Entity(x, y, w, h)
    {
        sprite = new Sprite(4, 32, 32, "./asset/player.png", image);
        sprite->setFrame(0);

        Hit_Box Temp;
        Temp.LE = destRect.x;
        Temp.RE = destRect.x + destRect.w;
        Temp.TE = destRect.y;
        Temp.BE = destRect.y + destRect.h;
        Hit_Boxes.push_back(Temp);
        Hit_Box Kick_1;
        Kick_1.LE = Temp.RE;
        Kick_1.RE = Temp.LE + KickL;
        Kick_1.BE = Temp.BE - KickH;
        Kick_1.TE = Kick_1.BE - KickH;
        Hit_Boxes.push_back(Kick_1);
        Kick_1.LE = Temp.LE - KickL;
        Kick_1.RE = Temp.LE;
        Kick_1.BE = Temp.BE - KickH;
        Kick_1.TE = Kick_1.BE - KickH;
        Hit_Boxes.push_back(Kick_1);

        id = 5;
            }

		~Player() {}

		void jump();
        void run();
        void stop_jump();
        void groundPound();
        int getLeft();
        void Run_L();
        void Run_R();
        void stop_run();
        int getState();
        bool getKick();
        Hit_Box get_Hitbox();
		Hit_Box Kick();
		virtual void controller(SDL_Event& event);
        virtual void collision_response(char type, int edge, int Obj_index);
        virtual void updatePos();
        void render(SDL_Renderer* renderer);

		
};
