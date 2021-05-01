#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <functional>
#include <memory>

#include "Game_Entity.h"
#include "Player.h"
#include "Tile.h"
#include "Slime.h"
#include "Collision.h"
#include "Menu.h"
#include "Block_Holder.h"

//Window Size in Pixels
static const int SCREEN_WIDTH = 960;
static const int SCREEN_HEIGHT = 768;

/*Collition types
static const char col_left = 'L';
static const char col_top = 'T';
static const char col_bot = 'B';
static const char col_right = 'R';
static const char col_non = 'N';
*/

class Game_Engine {
private:
	std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>> game_window;
    std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>> game_renderer;
	SDL_Event input;
	Image_Handler Images;
	std::fstream Level_file;

	//Game Objects
	Player* player;
	std::vector<Game_Entity*> Objects;
	std::vector<Block_Holder*> Block_Holders;

	//Menu 
	Menu menu;

	//values to save
	bool Run_game = true;
	bool program_running = true;
	int Camera_move = 0;
	int Camera_move_dist = 0;
	int level_height = 0, level_width, tile_size, tile_x, tile_y, tile_type;
	bool col_check;
	//std::vector<std::vector<int>> Grid(20, std::vector<int>(20, 0));

	//Game Engin Functions
	int Render();
	int Handle_Events();
	int Update_Mechanics();
	int Level_init(int level);
	int Quit();
	void scanMap();

public:
	Game_Engine();
	int Game_loop();
	void rowIsFull(int r);
	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
};