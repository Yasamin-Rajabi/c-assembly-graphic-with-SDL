#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "HandelGame.h"
using namespace std;

const double PI = 3.141592; 
const double PI_DEGREE = 180;
const int window_width = 1200;
const int window_height = 800;

double getRadians(double);
double getX(double, double, double);
double getY(double, double, double);

int main(int argc, char *argv[])
{

	// returns zero on success else non-zero
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}

	// creates a window
	SDL_Window* win = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, window_width, window_height, 0);

	// triggers the program that controls
	// your graphics hardware and sets flags
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	// creates a renderer to render our images
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);

	// creates a surface to load an image into the main memory
	SDL_Surface* surface;

	// please provide a path for your image
	surface = IMG_Load("ball.png");

	// loads image to our graphics hardware memory.
	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);

	// clears main-memory
	SDL_FreeSurface(surface);

	// let us control our image position
	// so that we can move it with our keyboard.
	SDL_Rect ball;

	// connects our texture with dest to control position
	SDL_QueryTexture(tex, NULL, NULL, &ball.w, &ball.h);

	// adjust height and width of our image box.
	ball.w /= 6;
	ball.h /= 6;

	// sets initial x-position of object
	double ballX0 = 0;
	ball.x = ballX0;

	// sets initial y-position of object
	double ballY0 = (window_height - ball.h) / 2;
	ball.y = ballY0;


	int move_type = 0; //0 simple //1 mohadab //2 sinosi
	// controls animation loop
	bool close = 0;

	// speed of box
	int speed = 30;
	double degree = 45;
	double length = 0;

	bool shoot = false;


	SDL_Event event;
	h(event);
	/*while (!close) {
		SDL_Event event;

		// Events management
		while (SDL_PollEvent(&event)) {
			switch (event.type) {

				case SDL_QUIT:
					// handling of close button
					close = 1;
					break;

				case SDL_KEYDOWN:
					// keyboard API for key pressed
					switch (event.key.keysym.scancode) {
						case SDL_SCANCODE_W:
						case SDL_SCANCODE_UP:
							//dest.y -= speed / 30;
							break;
						case SDL_SCANCODE_A:
						case SDL_SCANCODE_LEFT:
							//dest.x -= speed / 30;
							break;
						case SDL_SCANCODE_S:
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

			if(shoot){
				bool hit = false;
		        while(!hit){
        	    	if(move_type == 0){
            	    	length += speed;
                		ball.x = getX(degree * -1, length, ballX0);
                		ball.y = getY(degree * -1, length, ballY0);
                		printf("%d\n", ball.y);
            		}

            		if(move_type == 1){
                		length += speed;
               			degree--;
                		double en = -89;
                		degree = max(degree, en);
                		printf("%lf %lf %d\n", degree, cos(getRadians(degree * -1)), ball.x);
                		ball.x = getX(degree * -1, length, ballX0);
                		ball.y = getY(degree * -1, length, ballY0);
            		}

            		if(move_type == 2){
                		degree += 20;
                		ball.x += speed;
                		ball.y = getY(degree * -1, 100, ballY0);
            		}


            		// check hit
            		if (ball.x + ball.w > window_width or ball.x < 0 or ball.y + ball.h > window_height or ball.y < 0){
                		ball.x = ballX0;
                		ball.y = ballY0;
                		hit = true;
            		}
        		}
			}
		}


		// clears the screen
		SDL_RenderClear(rend);
		SDL_RenderCopy(rend, tex, NULL, &ball);

		// triggers the double buffers
		// for multiple rendering
		SDL_RenderPresent(rend);

		// calculates to 60 fps
		SDL_Delay(100);
	}*/

	// destroy texture
	SDL_DestroyTexture(tex);

	// destroy renderer
	SDL_DestroyRenderer(rend);

	// destroy window
	SDL_DestroyWindow(win);
	
	// close SDL
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



