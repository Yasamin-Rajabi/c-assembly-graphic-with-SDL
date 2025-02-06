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

	set_asm_mode(0);
	auto t1 = std::chrono::high_resolution_clock::now();

	for(int i = 1;i <= 40;i++){
		while(!shoot_ball()){
			render_present(rend);
	        SDL_Delay(1);
		}

		render_present(rend);
        SDL_Delay(1);
	}

	set_asm_mode(1);
	auto t2 = std::chrono::high_resolution_clock::now();

	for(int i = 1;i <= 40;i++){
        while(!shoot_ball()){
            render_present(rend);
            SDL_Delay(1);
        }

        render_present(rend);
        SDL_Delay(1);
    }

	auto t3 = std::chrono::high_resolution_clock::now();

	double delta_time1 = std::chrono::duration<double, std::milli>(t2-t1).count();
	double delta_time2 = std::chrono::duration<double, std::milli>(t3-t2).count();

	printf("normal time = %lf\nassembly time = %lf\n", delta_time1, delta_time2);

	quit_game(win, rend);
	return 0;
}

