#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
using namespace std;

const double PI = 3.141592; 
const double PI_DEGREE = 180;
const int window_width = 1200;
const int window_height = 800;

SDL_Texture* move_type_tex[6];
SDL_Rect move_type[6];

double getRadians(double);
double getX(double, double, double);
double getY(double, double, double);

bool is_click_on_rect(int mouseX, int mouseY, SDL_Rect rect){
	if(mouseX >= rect.x && mouseX <= (rect.x + rect.w) && mouseY >= rect.y && mouseY <= (rect.y + rect.h))
		return true;
	return false;
}

int main(int argc, char *argv[])
{

	// returns zero on success else non-zero
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}

	// creates a window
	SDL_Window* win = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, window_width, window_height, 0);

	// triggers the program that controls

	Uint32 render_flags = SDL_RENDERER_ACCELERATED; // your graphics hardware and sets flags
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags); // creates a renderer to render our images

	SDL_Surface* ball_surface = IMG_Load("pictures/ball.png"); // creates a surface to load an image into the main memory
	SDL_Texture* ball_tex = SDL_CreateTextureFromSurface(rend, ball_surface); // loads image to our graphics hardware memory.
	SDL_FreeSurface(ball_surface); //clears main-memory (cause it is in RAM)
	SDL_Rect ball; // controll ball image for moving it
    SDL_QueryTexture(ball_tex, NULL, NULL, &ball.w, &ball.h); // connects our texture with dest to control position
	

	SDL_Surface* line_surface = IMG_Load("pictures/line.png");
    SDL_Texture* line_tex = SDL_CreateTextureFromSurface(rend, line_surface); 
	SDL_FreeSurface(line_surface);
	SDL_Rect line;
	SDL_QueryTexture(line_tex, NULL, NULL, &line.w, &line.h);

	SDL_Surface* ISpeed_surface = IMG_Load("pictures/ISpeed.png");
    SDL_Texture* ISpeed_tex = SDL_CreateTextureFromSurface(rend, ISpeed_surface);
    SDL_FreeSurface(ISpeed_surface);
    SDL_Rect ISpeed;
    SDL_QueryTexture(ISpeed_tex, NULL, NULL, &ISpeed.w, &ISpeed.h);

	SDL_Surface* DSpeed_surface = IMG_Load("pictures/DSpeed.png");
    SDL_Texture* DSpeed_tex = SDL_CreateTextureFromSurface(rend, DSpeed_surface);
    SDL_FreeSurface(DSpeed_surface);
    SDL_Rect DSpeed;
    SDL_QueryTexture(DSpeed_tex, NULL, NULL, &DSpeed.w, &DSpeed.h);

	ISpeed.w /= 4;
    ISpeed.h /= 4;
    ISpeed.x = ISpeed.w/2;
    ISpeed.y = ISpeed.h/3;

    DSpeed.w /= 4;
    DSpeed.h /= 4;
    DSpeed.x = DSpeed.w/2;
    DSpeed.y = ISpeed.y + ISpeed.h;

	for(int i = 0;i < 6;i++){
		string path = "pictures/" + to_string(i/2) + (i%2 == 0 ? "Def" : "Sel") + ".png";
		const char* Cpath = path.c_str();
		SDL_Surface* move_type_surface = IMG_Load(Cpath);
    	move_type_tex[i] = SDL_CreateTextureFromSurface(rend, move_type_surface);
    	SDL_FreeSurface(move_type_surface);
    	SDL_QueryTexture(move_type_tex[i], NULL, NULL, &move_type[i].w, &move_type[i].h);

		move_type[i].h /= 5;
		move_type[i].w /= 5;
		move_type[i].x = ISpeed.x + 2 * ISpeed.w;
		if(2 <= i)
			move_type[i].y = move_type[i-2].y + move_type[i-2].h;
	}

	line.w = window_width;
	line.h /= 3;
	line.x = 0;
	line.y = 30;

	ball.w /= 6;
	ball.h /= 6;

	double ballX0 = 0;
	ball.x = ballX0;

	double ballY0 = (window_height - ball.h) / 2;
	ball.y = ballY0;


	int move_mod = 2; //0 simple //1 mohadab //2 sinosi
	// controls animation loop
	bool close = 0;

	// speed of box
	int speed = 30;
	double degree = 45;
	double length = 0;

	bool shoot = false;


	SDL_Event event;
	while (!close) {
		SDL_Event event;

		// Events management
		while (SDL_PollEvent(&event)) {
			switch (event.type) {

				case SDL_QUIT:
					// handling of close button
					close = 1;
					break;

				case SDL_MOUSEBUTTONDOWN:
					int mouseX, mouseY;
            		SDL_GetMouseState(&mouseX, &mouseY);
					if(is_click_on_rect(mouseX, mouseY, ISpeed)){
						speed++;
						printf("%d\n", speed);
					} 

					if(is_click_on_rect(mouseX, mouseY, DSpeed)){
						speed--;
						printf("%d\n", speed);
					}

					for(int i = 0;i < 6;i += 2)
						if(is_click_on_rect(mouseX, mouseY, move_type[i]))
							move_mod = i/2;


					break;
					


				case SDL_KEYDOWN:
					// keyboard API for key pressed
					switch (event.key.keysym.scancode) {
						case SDL_SCANCODE_W:
						case SDL_SCANCODE_UP:
							//change_back();
							
						case SDL_SCANCODE_A:
						case SDL_SCANCODE_LEFT:
							//dest.x -= speed / 30;
							break;
						case SDL_SCANCODE_DOWN:
							//dest.y += speed / 30;
							break;
						case SDL_SCANCODE_D:
						case SDL_SCANCODE_RIGHT:
							//dest.x += speed / 30;
							break;

						case SDL_SCANCODE_S:
							shoot = true;
							break;
						default:
							break;
					}
			}

		}


		// clears the screen
		SDL_RenderClear(rend);
		SDL_RenderCopy(rend, ball_tex, NULL, &ball);
		SDL_RenderCopy(rend, line_tex, NULL, &line);
		SDL_RenderCopy(rend, ISpeed_tex, NULL, &ISpeed);
		SDL_RenderCopy(rend, DSpeed_tex, NULL, &DSpeed);
		for(int i = 0;i < 6;i += 2){
			SDL_RenderCopy(rend, move_type_tex[i + (move_mod == i/2 ? 1 : 0)], NULL, &move_type[i + (move_mod == i/2 ? 1 : 0)]);
		}

		// triggers the double buffers for multiple rendering
		SDL_RenderPresent(rend);

		// calculates to 60 fps
		SDL_Delay(100);
	}

	
	SDL_DestroyTexture(ball_tex);
	SDL_DestroyTexture(line_tex);
	SDL_DestroyTexture(ISpeed_tex);
	SDL_DestroyTexture(DSpeed_tex);
	
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}

double getRadians(double degree){
	return PI * (degree / PI_DEGREE);
}

double getX(double degree, double length, double x0){
	return x0 + (cos(getRadians(degree)) * length);
}

double getY(double degree, double length, double y0){
	return y0 + (sin(getRadians(degree)) * length);
}


