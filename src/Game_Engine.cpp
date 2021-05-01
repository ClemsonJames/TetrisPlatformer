#include "../include/Game_Engine.h"

static const int numberSpriteColumns = 8;

/*Constructs the Game Engine*/
Game_Engine::Game_Engine() {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
	}

	IMG_Init(IMG_INIT_PNG);

	game_window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>> (SDL_CreateWindow("Tetris Platformer", 
				SDL_WINDOWPOS_CENTERED, 
				SDL_WINDOWPOS_CENTERED, 
				SCREEN_WIDTH,
				SCREEN_HEIGHT, 0), 
				SDL_DestroyWindow);

    game_renderer = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>> 
        (SDL_CreateRenderer(game_window.get(), -1, SDL_RENDERER_PRESENTVSYNC), SDL_DestroyRenderer);

	//Init Image Handler
	std::vector <std::string> Image_names = {"./asset/player.png", "./asset/tiles.png", "./asset/slime.png", "./asset/Level_0.png", 
	"./asset/Level_1.png", "./asset/Quit.png", "./asset/Resume.png", "./asset/Start.png", "./asset/Main.png"};

	Images = Image_Handler(Image_names, game_renderer.get());
	menu = Menu(game_window.get(), &Images);
}


/* Calls Level init
   Then loops through the Game Engine Functions while Run_game = ture
 */
int Game_Engine::Game_loop() {
	program_running = true;
	while (program_running) {
		int level = menu.menuLoop(0, game_renderer.get());

		Level_init(level);
		Run_game = true;
		while (Run_game) {
			//LST = SDL_GetTicks();
			Handle_Events();
			Update_Mechanics();
			Render();

			/*/Hold until current frame finishes
			hold_duration = SDL_GetTicks() - LST;
			if (hold_duration < frame_duration) {
				SDL_Delay(frame_duration - hold_duration);
			}*/
		}
	}

	Quit();
	return 0;
}


/* Constructs Objects in the Level
   Objects Include:
		- Level Boundary Rect
		- Background Rect
		- Wall Rects
		- Player
*/
int Game_Engine::Level_init(int level) {
	
	char symbol; 
	int x=0, y=0, nCols=numberSpriteColumns;

	//Read tile and level dementions
	switch (level) {
		case 0:
			Level_file.open("./asset/level_0.txt");
			break;
		case 1:
			Level_file.open("./asset/level_1.txt");
			break;	
	}


	if (Level_file.is_open()){
		Level_file >> tile_size;
	}

	//Level bound
	/*
	DestRect.x = 0;
	DestRect.y = 0;
	DestRect.h = 0;
	DestRect.w = tile_size * level_length;
	Level = new Game_obj(DestRect, &Images, 0, true, "");
	*/

	//Read level editor sheet layout
	int i = 0;
	int j = 0;
	Objects.clear();
	if (Level_file.is_open()) {
		while (!Level_file.eof()) {
			/*
			Grid[i].push_back(new Game_Entity(x, y, tile_size, tile_size));
			j++;
			if(j == 20){
				i++;
				j = 0;
			}*/
			Level_file >> symbol;
			switch (symbol) {
				case '0':
					Objects.push_back(new Tile(0, x, y, tile_size, nCols, true, &Images));
					break;
				case '1':
					Objects.push_back(new Tile(1, x, y, tile_size, nCols, false, &Images));
					break;
				case '2':
					Objects.push_back(new Tile(2, x, y, tile_size, nCols, false, &Images));
					break;
				case '3':
					Objects.push_back(new Tile(0, x, y, tile_size, nCols, false, &Images));
					break;
				case '8':
					player = new Player(x, y, tile_size, tile_size, &Images);
					break;
				case '9':
					Objects.push_back(new Slime(x, y, tile_size, tile_size, "./asset/slime.png", &Images));
					break;
				case 'I':
					Objects.push_back(new Block_Holder(0, 3, x, y, tile_size, nCols, true, &Images, true, 0));
					break;
				case 'i':
					Objects.push_back(new Block_Holder(0, 10, x, y, tile_size, nCols, true, &Images, false, 0));
					break;
				case 'N':
					Objects.push_back(new Block_Holder(0, 3, x, y, tile_size, nCols, true, &Images, true, 1));
					break;
				case 'n':
					Objects.push_back(new Block_Holder(0, 10, x, y, tile_size, nCols, true, &Images, false, 1));
					break;
				case 'M':
					Objects.push_back(new Block_Holder(0, 3, x, y, tile_size, nCols, true, &Images, true, 2));
					break;
				case 'm':
					Objects.push_back(new Block_Holder(0, 10, x, y, tile_size, nCols, true, &Images, false, 2));
					break;
				case '<':
					Objects.push_back(new Block_Holder(0, 3, x, y, tile_size, nCols, true, &Images, true, 3));
					break;
				case ',':
					Objects.push_back(new Block_Holder(0, 10, x, y, tile_size, nCols, true, &Images, false, 3));
					break;
				case 'F':
					Objects.push_back(new Block_Holder(2, 4, x, y, tile_size, nCols, true, &Images, true, 0));
					break;
				case 'f':
					Objects.push_back(new Block_Holder(2, 11, x, y, tile_size, nCols, true, &Images, false, 0));
					break;
				case 'G':
					Objects.push_back(new Block_Holder(2, 4, x, y, tile_size, nCols, true, &Images, true, 1));
					break;
				case 'g':
					Objects.push_back(new Block_Holder(2, 11, x, y, tile_size, nCols, true, &Images, false, 1));
					break;
				case 'H':
					Objects.push_back(new Block_Holder(2, 4, x, y, tile_size, nCols, true, &Images, true, 2));
					break;
				case 'h':
					Objects.push_back(new Block_Holder(2, 11, x, y, tile_size, nCols, true, &Images, false, 2));
					break;
				case 'J':
					Objects.push_back(new Block_Holder(2, 4, x, y, tile_size, nCols, true, &Images, true, 3));
					break;
				case 'j':
					Objects.push_back(new Block_Holder(2, 11, x, y, tile_size, nCols, true, &Images, false, 3));
					break;
				case 'K':
					Objects.push_back(new Block_Holder(1, 5, x, y, tile_size, nCols, true, &Images, true, 0));
					break;
				case 'k':
					Objects.push_back(new Block_Holder(1, 12, x, y, tile_size, nCols, true, &Images, false, 0));
					break;
				case 'L':
					Objects.push_back(new Block_Holder(1, 5, x, y, tile_size, nCols, true, &Images, true, 1));
					break;
				case 'l':
					Objects.push_back(new Block_Holder(1, 12, x, y, tile_size, nCols, true, &Images, false, 1));
					break;
				case ':':
					Objects.push_back(new Block_Holder(1, 5, x, y, tile_size, nCols, true, &Images, true, 2));
					break;
				case ';':
					Objects.push_back(new Block_Holder(1, 12, x, y, tile_size, nCols, true, &Images, false, 2));
					break;
				case '?':
					Objects.push_back(new Block_Holder(1, 5, x, y, tile_size, nCols, true, &Images, true, 3));
					break;
				case '/':
					Objects.push_back(new Block_Holder(1, 12, x, y, tile_size, nCols, true, &Images, false, 3));
					break;
				case 'O':
					Objects.push_back(new Block_Holder(3, 6, x, y, tile_size, nCols, true, &Images, true, 0));
					break;
				case 'o':
					Objects.push_back(new Block_Holder(3, 13, x, y, tile_size, nCols, true, &Images, false, 0));
					break;
				case 'P':
					Objects.push_back(new Block_Holder(3, 6, x, y, tile_size, nCols, true, &Images, true, 1));
					break;
				case 'p':
					Objects.push_back(new Block_Holder(3, 13, x, y, tile_size, nCols, true, &Images, false, 1));
					break;
				case '{':
					Objects.push_back(new Block_Holder(3, 6, x, y, tile_size, nCols, true, &Images, true, 2));
					break;
				case '[':
					Objects.push_back(new Block_Holder(3, 13, x, y, tile_size, nCols, true, &Images, false, 2));
					break;
				case '}':
					Objects.push_back(new Block_Holder(3, 6, x, y, tile_size, nCols, true, &Images, true, 3));
					break;
				case ']':
					Objects.push_back(new Block_Holder(3, 13, x, y, tile_size, nCols, true, &Images, false, 3));
					break;
				case 'S':
					Objects.push_back(new Block_Holder(5, 7, x, y, tile_size, nCols, true, &Images, true, 0));
					break;
				case 's':
					Objects.push_back(new Block_Holder(5, 14, x, y, tile_size, nCols, true, &Images, false, 0));
					break;
				case 'A':
					Objects.push_back(new Block_Holder(5, 7, x, y, tile_size, nCols, true, &Images, true, 1));
					break;
				case 'a':
					Objects.push_back(new Block_Holder(5, 14, x, y, tile_size, nCols, true, &Images, false, 1));
					break;
				case 'D':
					Objects.push_back(new Block_Holder(5, 7, x, y, tile_size, nCols, true, &Images, true, 2));
					break;
				case 'd':
					Objects.push_back(new Block_Holder(5, 14, x, y, tile_size, nCols, true, &Images, false, 2));
					break;
				case 'Q':
					Objects.push_back(new Block_Holder(5, 7, x, y, tile_size, nCols, true, &Images, true, 3));
					break;
				case 'q':
					Objects.push_back(new Block_Holder(5, 14, x, y, tile_size, nCols, true, &Images, false, 3));
					break;
				case 'T':
					Objects.push_back(new Block_Holder(6, 8, x, y, tile_size, nCols, true, &Images, true, 0));
					break;
				case 't':
					Objects.push_back(new Block_Holder(6, 15, x, y, tile_size, nCols, true, &Images, false, 0));
					break;
				case 'R':
					Objects.push_back(new Block_Holder(6, 8, x, y, tile_size, nCols, true, &Images, true, 1));
					break;
				case 'r':
					Objects.push_back(new Block_Holder(6, 15, x, y, tile_size, nCols, true, &Images, false, 1));
					break;
				case 'E':
					Objects.push_back(new Block_Holder(6, 8, x, y, tile_size, nCols, true, &Images, true, 2));
					break;
				case 'e':
					Objects.push_back(new Block_Holder(6, 15, x, y, tile_size, nCols, true, &Images, false, 2));
					break;
				case 'W':
					Objects.push_back(new Block_Holder(6, 8, x, y, tile_size, nCols, true, &Images, true, 3));
					break;
				case 'w':
					Objects.push_back(new Block_Holder(6, 15, x, y, tile_size, nCols, true, &Images, false, 3));
					break;
				case 'X':
					Objects.push_back(new Block_Holder(4, 9, x, y, tile_size, nCols, true, &Images, true, 0));
					break;
				case 'x':
					Objects.push_back(new Block_Holder(4, 16, x, y, tile_size, nCols, true, &Images, false, 0));
					break;
				case 'C':
					Objects.push_back(new Block_Holder(4, 9, x, y, tile_size, nCols, true, &Images, true, 1));
					break;
				case 'c':
					Objects.push_back(new Block_Holder(4, 16, x, y, tile_size, nCols, true, &Images, false, 1));
					break;
				case 'V':
					Objects.push_back(new Block_Holder(4, 9, x, y, tile_size, nCols, true, &Images, true, 2));
					break;
				case 'v':
					Objects.push_back(new Block_Holder(4, 16, x, y, tile_size, nCols, true, &Images, false, 2));
					break;
				case 'B':
					Objects.push_back(new Block_Holder(4, 9, x, y, tile_size, nCols, true, &Images, true, 3));
					break;
				case 'b':
					Objects.push_back(new Block_Holder(4, 16, x, y, tile_size, nCols, true, &Images, false, 3));
					break;

				default:
					break;
			}
			
			x += tile_size;
			if(x >= SCREEN_WIDTH) {
				x = 0;
				y += tile_size;
			}
		}
	}
	Level_file.close();

	//Background

	/*
	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.h = SCREEN_HEIGHT;
	src_rect.w = SCREEN_WIDTH;

	DestRect.x = SCREEN_WIDTH;
	DestRect.y = 0;
	DestRect.h = SCREEN_HEIGHT;
	DestRect.w = SCREEN_WIDTH;

	std::vector <SDL_Rect> Src_rect = { src_rect, DestRect };
	std::vector <std::string> TRX_names = { "Layer2.png", "Layer3.png", "Layer4.png", "Layer5.png", "Layer6.png", "Layer7.png", "Layer8.png", "Layer9.png" };
	background = Background(Src_rect, TRX_names, &Images);
	*/

	//Player Character


	return 0;

}


/* Closes the Game Down*/
int Game_Engine::Quit() {
	IMG_Quit();
	SDL_Quit();
	return 0;
}


/* Clears Last Render
   Then Renders:
		- Objects
		- Background
		- Player

   Putes the Resulting image to the window
*/
int Game_Engine::Render() {

	//clear last Render
	SDL_SetRenderDrawColor(game_renderer.get(), 118, 147, 179, 255);
	SDL_RenderClear(game_renderer.get());

	//Render background and player
	//background.Draw(game_renderer.get(), Camera_move);

	//Loop Through Objects to Render
	for (int i = 0; i < Objects.size(); i++) {
		Objects[i]->render(game_renderer.get());
	}

	player->render(game_renderer.get());
	/*if (Hive.get_is_rendered() || !Hive.get_Done()) {
		Hive.Pe_render(game_renderer);
	}*/

	// Put the Image from the game_renderer to the screen
	SDL_RenderPresent(game_renderer.get());
	return 0;
}

// Handles all user Input
int Game_Engine::Handle_Events() {
	SDL_Event input;
	SDL_PollEvent(&input);

	if (input.type == SDL_QUIT) {
		Run_game =false;
		program_running = false;
	}

	if (input.type == SDL_KEYDOWN) {
		switch(input.key.keysym.sym ) {
			case SDLK_ESCAPE:
				if (menu.menuLoop(2, game_renderer.get()) == 9999) {
					Run_game = false;
				}
				break;
			default:
				break;
		}
	}

	if (input.type == SDL_MOUSEBUTTONDOWN) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		for (int i = 0; i < Objects.size(); i++) {
			if (Objects[i]->inside(x, y) && Objects[i]->active && Objects[i]->getID() == 2) {
				Objects[i]->Rotate(true);
			}
			/*
			else{
				Objects[i]->no_action();
			}*/
		}
	}

	/* Calls Player movemet Functions when a key is pressed
		Jump : Space
		Run Left : A
		Run Right : D
		
		Calls Player Functions to end end actions when there repective Key is relesed
	*/
	player->controller(input);

	return 0;
}


/* Updates the Player and Game Object Positions
   Checks For collitions between the Player Character and:
		-Gmae objects
		-Camera boundaries
*/
int Game_Engine::Update_Mechanics() {

	// Get Player State and call the coresponding Player Position update function
	Hit_Box playerHitbox;
	Hit_Box objectHitbox;
	Hit_Box kickBox;
	std::vector<Hit_Box> BlockHolderHitboxes;
	for (int i = 0; i < Objects.size(); i++) {
		Objects[i]->updatePos();
	}
	player->updatePos();

	// player collision

	playerHitbox = player->get_Hitbox();

	bool NoBcollision = true;

	bool doKick = player->getKick();

	for (int i = 0; i < Objects.size(); i++) {
			if (Objects[i]->get_check_col())
			{
				// not a block holder
				if (Objects[i]->getID() != 2)
				{
					objectHitbox = Objects[i]->get_Hit_Boxs()[0];
					if (Collision_check(playerHitbox, objectHitbox))
					{
						if (playerHitbox.BE - objectHitbox.TE <= 7) {
							NoBcollision = false;
							if (Objects[i]->getID() == 1) {
								Objects.erase(Objects.begin() + i);
							}
							player->collision_response('B', objectHitbox.TE, i);

						}
						else if (playerHitbox.RE - objectHitbox.LE <= 5) {
							NoBcollision = false;
							player->collision_response('R', objectHitbox.LE, i);
							if (Objects[i]->getID() == 1) {
								if (menu.menuLoop(3, game_renderer.get()) == 9999) {
									Run_game = false;
								}
							}
						}
						else if (objectHitbox.RE - playerHitbox.LE <= 5) {
							NoBcollision = false;
							player->collision_response('L', objectHitbox.RE, i);
							if (Objects[i]->getID() == 1) {
								if (menu.menuLoop(3, game_renderer.get()) == 9999) {
									Run_game = false;
								}
							}
						}
						else if (objectHitbox.BE - playerHitbox.TE <= 6) {
							NoBcollision = false;
							player->collision_response('T', objectHitbox.BE, i);
						}
						else {
							player->collision_response('N', 0, i );
						}
				}
			}
			else {
				// if object is a block holder
				BlockHolderHitboxes = Objects[i]->get_Hit_Boxs();
				for (int j = 0; j < BlockHolderHitboxes.size(); j++) {
					objectHitbox = BlockHolderHitboxes[j];
					if(doKick) {
						kickBox = player->Kick();
						if(Collision_check(kickBox, objectHitbox)) {
							if(player->getLeft() == 1){
								int dist = tile_size * -1;
								Objects[i]->Move(dist, 0);
							}
							else{
								Objects[i]->Move(tile_size, 0);
							}
						}
						/*else if (Objects[i]->get_action() != 2){
							Objects[i]->no_action();
						}*/
					}
					if (Collision_check(playerHitbox, objectHitbox)) {
							if (playerHitbox.BE - objectHitbox.TE <= 7) {
								NoBcollision = false;
								if (Objects[i]->getID() == 2 && player->getState() == 4) {
									Objects[i]->Move(0, tile_size);
								}
								player->collision_response('B', objectHitbox.TE, i);
							}
							else if (playerHitbox.RE - objectHitbox.LE <= 5) {
								NoBcollision = false;
								player->collision_response('R', objectHitbox.LE, i);
							}
							else if (objectHitbox.RE - playerHitbox.LE <= 5) {
								NoBcollision = false;
								player->collision_response('L', objectHitbox.RE, i);
							}
							else if (objectHitbox.BE - playerHitbox.TE <= 6) {
								NoBcollision = false;
								player->collision_response('T', objectHitbox.BE, i);
							}
							else {
								player->collision_response('N', 0, i );
							}
					}
				}
			}
		}
	}
	if(NoBcollision) {
		player->collision_response('N', 0, 0);
	}

	//other object collision
	std::vector<Hit_Box> BlockHolderHitboxes1;
	std::vector<Hit_Box> BlockHolderHitboxes2;
	Hit_Box objectHitbox1;
	Hit_Box objectHitbox2;
	for (int i = 0; i < Objects.size(); i++) {
		if (Objects[i]->get_check_col()) {
			for (int j = 0; j < Objects.size(); j++) {
				if (i != j && Objects[j]->get_check_col()) {
					// when first and second object are block holder
					if (Objects[i]->getID() == 2 && Objects[j]->getID() == 2) {
						BlockHolderHitboxes1 = Objects[i]->get_Hit_Boxs();
						BlockHolderHitboxes2 = Objects[j]->get_Hit_Boxs();
						for (int k = 0; k < BlockHolderHitboxes1.size(); k++) {
							objectHitbox1 = BlockHolderHitboxes1[k];
							for (int l = 0; l < BlockHolderHitboxes2.size(); l++) {
								objectHitbox2 = BlockHolderHitboxes2[l];
								if (Collision_check(objectHitbox1, objectHitbox2)) {
									Objects[i]->collision_response('c', objectHitbox2.RE, 0);
								}
							}
						}
					}

					// when first and second are not block holder
					else if (Objects[i]->getID() != 2 && Objects[j]->getID() != 2) {
						objectHitbox1 = Objects[i]->get_Hit_Boxs()[0];
						objectHitbox2 = Objects[j]->get_Hit_Boxs()[0];
						if (Collision_check(objectHitbox1, objectHitbox2)) {
							Objects[i]->collision_response('c', objectHitbox2.RE, 0);
						}
					}
					// when first is block holder, second not block holder
					else if (Objects[i]->getID() == 2 && Objects[j]->getID() != 2) {
						BlockHolderHitboxes1 = Objects[i]->get_Hit_Boxs();
						objectHitbox2 = Objects[j]->get_Hit_Boxs()[0];
						for (int k = 0; k < BlockHolderHitboxes.size(); k++) {
							objectHitbox1 = BlockHolderHitboxes1[k];
							if (Collision_check(objectHitbox1, objectHitbox2)) {
								Objects[i]->collision_response('c', objectHitbox2.RE, 0);
							}
						}
					}
					// when first is not block holder, second is block holder
					else if (Objects[i]->getID() != 2 && Objects[j]->getID() == 2) {
						objectHitbox1 = Objects[i]->get_Hit_Boxs()[0];
						BlockHolderHitboxes2 = Objects[j]->get_Hit_Boxs();
						for (int k = 0; k < BlockHolderHitboxes2.size(); k++) {
							objectHitbox2 = BlockHolderHitboxes2[k];
							if (Collision_check(objectHitbox1, objectHitbox2)) {
								Objects[i]->collision_response('c', objectHitbox2.RE, 0);
							}
						}
					}
				}
			}
		}
	}

	for(int i = 0; i < 20; i++){
		rowIsFull(i);
	}

	if (player->get_Hitbox().BE > 732) {
		if (menu.menuLoop(4, game_renderer.get()) == 9999) {
			Run_game = false;
		}
	}

	return 0;
}

SDL_Window* Game_Engine::getWindow() {
	return game_window.get();
}
SDL_Renderer* Game_Engine::getRenderer() {
	return game_renderer.get();
}

void Game_Engine::scanMap() {
	/*vector<SDL_Rect> rects;
	SDL_Rect rect;
	for (int i = 0; i < Objects.size(); i++) {
		if (Objects[i]->getID() == 2) {
			rects = Objects[i]->getRect();
			for (int j = 0; j < rects.size(); j++) {
				
			}
				x 160
			y 64
		}
	}*/
}

void Game_Engine::rowIsFull(int r){
	
	int yLoc = (32*r) + 80;
	int xLoc = 176;
	bool activity = false;

	for(int i = 0; i < Objects.size(); i++){
		if(Objects[i]->getID() == 2){
			if(Objects[i]->inside(xLoc, yLoc)){
				xLoc+=32;
				if (Objects[i]->active) {
					activity = true;
				}
				i = 0;
			}
		}
	}

	if(xLoc >= 800 && activity){

		for(int j = xLoc; j > 160; j -= 32){
			for(int i = 0; i < Objects.size(); i++){
				if(Objects[i]->getID() == 2){
					if(Objects[i]->inside(j, yLoc)){
						Objects.erase(Objects.begin()+i);
					}
				}
			}
		}
	}
}

