#include "../include/Menu.h"

int Menu::menuLoop(int type, SDL_Renderer* renderer) {
    menuRunning = true;
    menuType = type;
    while (menuRunning) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        // handles mouse clicking on menu
        eventHandler();
        menuSetup(renderer);

        SDL_RenderPresent(renderer);
    }
    return res;
}

void Menu::eventHandler() {
    SDL_Event input;
    while(SDL_PollEvent(&input) != 0) {
        if (input.type == SDL_QUIT) {
            TTF_Quit();
            SDL_Quit(); 
            exit(0);  
        }
        if (input.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            switch(menuType) {
                case 0:
                    for (int i = 0; i < startButtons.size(); i++) {
                        if (startButtons[i].inside(x, y)) {
                            if (startButtons[i].getID() == 0) {
                                menuType = 1;
                            }
                            else if (startButtons[i].getID() == 1) {
                                TTF_Quit();
                                SDL_Quit(); 
                                exit(0); 
                            }
                        }
                    }
                    break;
                case 1:
                    for (int i = 0; i < levelButtons.size(); i++) {
                        if (levelButtons[i].inside(x, y)) {
                            if (levelButtons[i].getID() == 2) {
                                res = 0;
                            }
                            else if (levelButtons[i].getID() == 3) {
                                res = 1;
                            }
                            menuRunning = false;
                        }
                    }
                    break;
                case 2:
                    for (int i = 0; i < pauseButtons.size(); i++) {
                        if (pauseButtons[i].inside(x, y)) {
                            if (pauseButtons[i].getID() == 4) {
                                // resume game play
                            }
                            else if (pauseButtons[i].getID() == 5) {
                                res = 9999; // stop the game loop and go back to main menu
                            }
                            menuRunning = false;
                        }
                    }
                    break;
                case 3:
                    for (int i = 0; i < deathButtons.size(); i++) {
                        if (deathButtons[i].inside(x, y)) {
                            if (deathButtons[i].getID() == 6) {
                                res = 9999; // stop the game loop and go back to main menu
                            }
                            else if (deathButtons[i].getID() == 7) {
                                TTF_Quit();
                                SDL_Quit(); 
                                exit(0); 
                            }
                            menuRunning = false;
                        }
                    }
                    break;
                case 4:
                    for (int i = 0; i < winButtons.size(); i++) {
                        if (winButtons[i].inside(x, y)) {
                            if (winButtons[i].getID() == 8) {
                                res = 9999; // stop the game loop and go back to main menu
                            }
                            else if (winButtons[i].getID() == 9) {
                                TTF_Quit();
                                SDL_Quit(); 
                                exit(0); 
                            }
                            menuRunning = false;
                        }
                    }
                    break;
            }
        }
    }
}

void Menu::menuSetup(SDL_Renderer* renderer) {
    // render based on menu type
    switch (menuType) {
        case 0:
            renderText(windowWidth/2, 50, "Tetris Platformer", renderer);
        	for (int i = 0; i < startButtons.size(); i++) {
		        startButtons[i].render(renderer);
	        }
            break;
        case 1:
            renderText(windowWidth/2, 50, "Select Level", renderer);
            for (int i = 0; i < levelButtons.size(); i++) {
		        levelButtons[i].render(renderer);
	        }
            break;
        case 2:
            renderText(windowWidth/2, 50, "Pause", renderer);
            for (int i = 0; i < pauseButtons.size(); i++) {
		        pauseButtons[i].render(renderer);
	        }
            break;
        case 3:
            renderText(windowWidth/2, 50, "Game Over", renderer);
            for (int i = 0; i < deathButtons.size(); i++) {
		        deathButtons[i].render(renderer);
	        }
            break;
        case 4:
            renderText(windowWidth/2, 50, "Victory", renderer);
            for (int i = 0; i < winButtons.size(); i++) {
		        winButtons[i].render(renderer);
	        }
            break;
    }
}

void Menu::renderText(int x, int y, const char* text, SDL_Renderer* renderer) {
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("asset/berkshireswash-regular.ttf", 80);
    SDL_Color textColor = {255, 255, 255, 255};
    //std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>> texture;
    auto surface = std::shared_ptr<SDL_Surface> (TTF_RenderText_Solid(font, text, textColor), SDL_FreeSurface);
    auto texture = std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>>
                (SDL_CreateTextureFromSurface(renderer, surface.get()), SDL_DestroyTexture);

    SDL_Rect rect;
    SDL_QueryTexture(texture.get(), NULL, NULL, &rect.w, &rect.h);
    rect.x = x - rect.w/2;
    rect.y = y;


    SDL_RenderCopy(renderer, texture.get(), NULL, &rect);
    TTF_CloseFont(font); 
    TTF_Quit();

}