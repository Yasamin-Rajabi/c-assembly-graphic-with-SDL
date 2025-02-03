#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL_ttf.h>
using namespace std;

const double PI = 3.141592; 
const double PI_DEGREE = 180;

const int window_width = 1200;
const int window_height = 800;

int ballX0;
int ballY0;
int move_mod;
int speed;
int degree;
int angle;

SDL_Rect ball;
SDL_Texture* ball_tex;

SDL_Rect line;
SDL_Texture* line_tex;

SDL_Rect Speed_number;
SDL_Texture* Speed_number_tex;

SDL_Rect Speed_layer;
SDL_Texture* Speed_layer_tex;

SDL_Rect ISpeed;
SDL_Texture* ISpeed_tex;

SDL_Rect DSpeed;
SDL_Texture* DSpeed_tex;

SDL_Rect Degree_number;
SDL_Texture* Degree_number_tex;

SDL_Rect Degree_layer;
SDL_Texture* Degree_layer_tex;

SDL_Rect IDegree;
SDL_Texture* IDegree_tex;

SDL_Rect DDegree;
SDL_Texture* DDegree_tex;

SDL_Texture* move_type_tex[6];
SDL_Rect move_type[6];


bool is_click_on_rect(int mouseX, int mouseY, SDL_Rect rect){
	if(mouseX >= rect.x && mouseX <= (rect.x + rect.w) && mouseY >= rect.y && mouseY <= (rect.y + rect.h))
		return true;
	return false;
}

bool is_click_on_ISpeed(int mouseX, int mouseY){
	return is_click_on_rect(mouseX, mouseY, ISpeed);
}

bool is_click_on_DSpeed(int mouseX, int mouseY){
    return is_click_on_rect(mouseX, mouseY, DSpeed);
}

bool is_click_on_IDegree(int mouseX, int mouseY){
    return is_click_on_rect(mouseX, mouseY, IDegree);
}

bool is_click_on_DDegree(int mouseX, int mouseY){
    return is_click_on_rect(mouseX, mouseY, DDegree);
}

bool is_click_on_move_type(int mouseX, int mouseY, int layer_type){
    return is_click_on_rect(mouseX, mouseY, move_type[layer_type]);
}


void create_ball(SDL_Renderer* rend){

	SDL_Surface* ball_surface = IMG_Load("pictures/ball.png"); // creates a surface to load an image into the main memory
    ball_tex = SDL_CreateTextureFromSurface(rend, ball_surface); // loads image to our graphics hardware memory.
    SDL_FreeSurface(ball_surface); //clears main-memory (cause it is in RAM)
    SDL_QueryTexture(ball_tex, NULL, NULL, &ball.w, &ball.h); // connects our texture with dest to control position

	ball.w /= 6;
    ball.h /= 6;

	ballX0 = 0;
	ballY0 = (window_height - ball.h) / 2;

    ball.x = ballX0;
    ball.y = ballY0;
}

void create_line(SDL_Renderer* rend){

	SDL_Surface* line_surface = IMG_Load("pictures/line.png");
    line_tex = SDL_CreateTextureFromSurface(rend, line_surface);
    SDL_FreeSurface(line_surface);
    SDL_QueryTexture(line_tex, NULL, NULL, &line.w, &line.h);

	line.w = window_width;
    line.h /= 3;
    line.x = 0;
    line.y = 30;
}

void create_ISpeed(SDL_Renderer* rend){

	SDL_Surface* ISpeed_surface = IMG_Load("pictures/ISpeed.png");
    ISpeed_tex = SDL_CreateTextureFromSurface(rend, ISpeed_surface);
    SDL_FreeSurface(ISpeed_surface);
    SDL_QueryTexture(ISpeed_tex, NULL, NULL, &ISpeed.w, &ISpeed.h);
	
	ISpeed.w /= 4;
    ISpeed.h /= 4;
    ISpeed.x = 1.5 * move_type[0].w;
    ISpeed.y = 10 + ISpeed.h/2;
}

void create_DSpeed(SDL_Renderer* rend){

	SDL_Surface* DSpeed_surface = IMG_Load("pictures/DSpeed.png");
    DSpeed_tex = SDL_CreateTextureFromSurface(rend, DSpeed_surface);
    SDL_FreeSurface(DSpeed_surface);
    SDL_QueryTexture(DSpeed_tex, NULL, NULL, &DSpeed.w, &DSpeed.h);

	DSpeed.w /= 4;
    DSpeed.h /= 4;
    DSpeed.x = 1.5 * move_type[0].w;
    DSpeed.y = ISpeed.y + ISpeed.h;
}

void create_Speed_layer(SDL_Renderer* rend){

    SDL_Surface* Speed_layer_surface = IMG_Load("pictures/SpeedLayer.png");
    Speed_layer_tex = SDL_CreateTextureFromSurface(rend, Speed_layer_surface);
    SDL_FreeSurface(Speed_layer_surface);
    SDL_QueryTexture(Speed_layer_tex, NULL, NULL, &Speed_layer.w, &Speed_layer.h);

    Speed_layer.w /= 6;
    Speed_layer.h /= 6;
    Speed_layer.x = ISpeed.x + ISpeed.w;
    Speed_layer.y = 40;
}


void create_IDegree(SDL_Renderer* rend){

    SDL_Surface* IDegree_surface = IMG_Load("pictures/IDegree.png");
    IDegree_tex = SDL_CreateTextureFromSurface(rend, IDegree_surface);
    SDL_FreeSurface(IDegree_surface);
    SDL_QueryTexture(IDegree_tex, NULL, NULL, &IDegree.w, &IDegree.h);

    IDegree.w /= 4;
    IDegree.h /= 4;
    IDegree.x = 80 + Speed_layer.x + Speed_layer.w;
    IDegree.y = 10 + IDegree.h/2;
}

void create_DDegree(SDL_Renderer* rend){

    SDL_Surface* DDegree_surface = IMG_Load("pictures/DDegree.png");
    DDegree_tex = SDL_CreateTextureFromSurface(rend, DDegree_surface);
    SDL_FreeSurface(DDegree_surface);
    SDL_QueryTexture(DDegree_tex, NULL, NULL, &DDegree.w, &DDegree.h);

    DDegree.w /= 4;
    DDegree.h /= 4;
    DDegree.x = 80 + Speed_layer.x + Speed_layer.w;
    DDegree.y = IDegree.y + IDegree.h;
}

void create_Degree_layer(SDL_Renderer* rend){

    SDL_Surface* Degree_layer_surface = IMG_Load("pictures/DegreeLayer.png");
    Degree_layer_tex = SDL_CreateTextureFromSurface(rend, Degree_layer_surface);
    SDL_FreeSurface(Degree_layer_surface);
    SDL_QueryTexture(Degree_layer_tex, NULL, NULL, &Degree_layer.w, &Degree_layer.h);

    Degree_layer.w /= 6;
    Degree_layer.h /= 6;
    Degree_layer.x = IDegree.x + IDegree.w;
    Degree_layer.y = 40;
}

void create_move_type_layers(SDL_Renderer* rend){

	for(int i = 0;i < 6;i++){
        string path = "pictures/" + to_string(i/2) + (i%2 == 0 ? "Def" : "Sel") + ".png";
        const char* Cpath = path.c_str();
        SDL_Surface* move_type_surface = IMG_Load(Cpath);
        move_type_tex[i] = SDL_CreateTextureFromSurface(rend, move_type_surface);
        SDL_FreeSurface(move_type_surface);
        SDL_QueryTexture(move_type_tex[i], NULL, NULL, &move_type[i].w, &move_type[i].h);

        move_type[i].h /= 5;
        move_type[i].w /= 5;
        move_type[i].x = 30;
        if(2 <= i)
            move_type[i].y = move_type[i-2].y + move_type[i-2].h;
    }
}

void create_Speed_number(SDL_Renderer* rend) {
    string text = to_string(speed);

	if (TTF_Init() == -1) {
	    std::cerr << "SDL_ttf could not initialize! Error: " << TTF_GetError() << std::endl;
    	return;
	}

	TTF_Font* font = TTF_OpenFont("arial-font/arial.ttf", 48);

	if (!font) {
    	std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    	return;
	}

	SDL_Color color = {110, 0, 128, 255};

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    Speed_number_tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
	SDL_QueryTexture(Speed_number_tex, NULL, NULL, &Speed_number.w, &Speed_number.h);

	Speed_number.h = 40;
	Speed_number.w = 40;
	Speed_number.x = Speed_layer.x + Speed_layer.w;
	Speed_number.y = Speed_layer.y;

}

void create_Degree_number(SDL_Renderer* rend) {
    string text = to_string(degree);
    
	if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! Error: " << TTF_GetError() << std::endl;
        return;
    }

    TTF_Font* font = TTF_OpenFont("arial-font/arial.ttf", 48);

    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }


    SDL_Color color = {110, 0, 128, 255};

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    Degree_number_tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(Degree_number_tex, NULL, NULL, &Degree_number.w, &Degree_number.h);
	
	Degree_number.h = 40;
	Degree_number.w = 40;
    Degree_number.x = Degree_layer.x + Degree_layer.w;
    Degree_number.y = Degree_layer.y;

}


void create_objects(SDL_Renderer* rend){

	create_ball(rend);
	create_move_type_layers(rend);
	create_line(rend);

	create_ISpeed(rend);
	create_DSpeed(rend);
	create_Speed_layer(rend);
	create_Speed_number(rend);

	create_IDegree(rend);
    create_DDegree(rend);
	create_Degree_layer(rend);
	create_Degree_number(rend);

}

void render_present(SDL_Renderer* rend){
	// clears the screen
    SDL_RenderClear(rend);
	
	SDL_Point center = {ball.w / 2, ball.h / 2}; 
	SDL_RenderCopyEx(rend, ball_tex, nullptr, &ball, angle, &center, SDL_FLIP_NONE);

    //SDL_RenderCopy(rend, ball_tex, NULL, &ball);
    SDL_RenderCopy(rend, line_tex, NULL, &line);

    SDL_RenderCopy(rend, ISpeed_tex, NULL, &ISpeed);
    SDL_RenderCopy(rend, DSpeed_tex, NULL, &DSpeed);
	SDL_RenderCopy(rend, Speed_layer_tex, NULL, &Speed_layer);

	create_Speed_number(rend);
	SDL_RenderCopy(rend, Speed_number_tex, NULL, &Speed_number);

	SDL_RenderCopy(rend, IDegree_tex, NULL, &IDegree);
    SDL_RenderCopy(rend, DDegree_tex, NULL, &DDegree);
	SDL_RenderCopy(rend, Degree_layer_tex, NULL, &Degree_layer);

	create_Degree_number(rend);
	SDL_RenderCopy(rend, Degree_number_tex, NULL, &Degree_number);

    for(int i = 0;i < 6;i += 2)
    	SDL_RenderCopy(rend, move_type_tex[i + (move_mod == i/2 ? 1 : 0)], NULL, &move_type[i + (move_mod == i/2 ? 1 : 0)]);
        
    // triggers the double buffers for multiple rendering
   	SDL_RenderPresent(rend);

}


void quit_game(SDL_Window* win, SDL_Renderer* rend){

	SDL_DestroyTexture(ball_tex);
	SDL_DestroyTexture(line_tex);

	SDL_DestroyTexture(Speed_number_tex);
	SDL_DestroyTexture(Speed_layer_tex);
	SDL_DestroyTexture(ISpeed_tex);
	SDL_DestroyTexture(DSpeed_tex);
	
	SDL_DestroyTexture(Degree_number_tex);
	SDL_DestroyTexture(Degree_layer_tex);
    SDL_DestroyTexture(IDegree_tex);
    SDL_DestroyTexture(DDegree_tex);
	
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);

	SDL_Quit();
	TTF_Quit();
}


void set_move_variables(int m, int s, int d){
	move_mod = m;
	speed = s;
	degree = d;
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

bool shoot_ball(){

	// check hit
    if (ball.x + ball.w > window_width or ball.x < 0 or ball.y + ball.h > window_height or ball.y < line.y + line.h/2){
		ball.x = ballX0;
		ball.y = ballY0;
		degree = 45;
		angle = 0;

    	return true;
    }

	angle += 10;
	// Straight move
    if(move_mod == 0){
        ball.x = getX(degree * -1, speed, ball.x);
        ball.y = getY(degree * -1, speed, ball.y);
	}

	// Convex move
    if(move_mod == 1){
		if(degree <= -70)
        	degree --;    
		else
			degree -= 5;

        degree = max(degree, -80);
        ball.x = getX(degree * -1, speed, ball.x);
		ball.y = getY(degree * -1, speed, ball.y);
	}

	// Sinusoidal move
    if(move_mod == 2){
    	degree += 20;
		degree = degree % 360;
        ball.x += speed;
        ball.y = getY(degree * -1, 100, ballY0);
    }
	
	return false;
}


