#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "graphicManagment.h"
using namespace std;

const int window_width = 1200;
const int window_height = 800;

int main(int argc, char *argv[])
{

	// returns zero on success else non-zero
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
		printf("error initializing SDL: %s\n", SDL_GetError());

	// creates a window
	SDL_Window* win = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, window_width, window_height, 0);

	// triggers the program that controls
	Uint32 render_flags = SDL_RENDERER_ACCELERATED; // your graphics hardware and sets flags
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags); // creates a renderer to render our images

	create_objects(rend);


	bool close = 0;
	bool shoot = 0;

	int move_mod = 0; //0 simple //1 mohadab //2 sinosi
	int speed = 35;
	int degree0 = 6;
	int degree = degree0;

	set_degree0(degree0);
	set_move_variables(move_mod, speed, degree);


	SDL_Event event;
	while (!close) {
		
		if(!shoot){
			// Events management
			while (SDL_PollEvent(&event)) {
				switch (event.type) {

					// handling of close button
					case SDL_QUIT:
						close = 1;
						break;

					// handling change of speed and move_mod and degree
					case SDL_MOUSEBUTTONDOWN:
						int mouseX, mouseY;
            			SDL_GetMouseState(&mouseX, &mouseY);
						if(is_click_on_ISpeed(mouseX, mouseY))
							speed++;

						if(is_click_on_DSpeed(mouseX, mouseY))
							speed--;

						if(is_click_on_IDegree(mouseX, mouseY))
                            degree++;

                        if(is_click_on_DDegree(mouseX, mouseY))
                            degree--;
                        

						for(int i = 0;i < 6;i += 2)
							if(is_click_on_move_type(mouseX, mouseY, i))
								move_mod = i/2;

						speed = max(speed, 1);
						degree = max(degree, -80);
						//printf("speed = %d   degree = %d\n", speed, degree);
						
						set_move_variables(move_mod, speed, degree);

						break;
					

				 	// keyboard API for key pressed
					case SDL_KEYDOWN:
						switch (event.key.keysym.scancode) {
							case SDL_SCANCODE_S:
								shoot = true;
								break;
							default:
								break;
						}
				}
			}

		}

		if(shoot){
			if(shoot_ball(0))
				shoot = false, degree = degree0;
		}
		

		render_present(rend);
		SDL_Delay(100);
	}

	quit_game(win, rend);
	return 0;
}

