#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL_ttf.h>
using namespace std;

extern "C" double get_asm_x(double ,double, double);
extern "C" double get_asm_y(double, double, double);

const double PI = 3.141592; 
const double PI_DEGREE = 180;

const int window_width = 1200;
const int window_height = 800;

bool door_move = true; // true -> up false -> down
int delta_door_move = 10;
int goal_display;

Uint32 format = SDL_PIXELFORMAT_ARGB8888;

double ballX0;
double ballY0;
int move_mod;
int speed;
int degree;
int degree0;
int angle;

SDL_Rect ball;
SDL_Texture* ball_tex;
SDL_Surface* ball_surface;

SDL_Rect line;
SDL_Texture* line_tex;
SDL_Surface* line_surface;
Uint8* line_color_array;

SDL_Rect door;
SDL_Texture* door_tex;

SDL_Rect goal;
SDL_Texture* goal_tex;

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

	ball_surface = IMG_Load("pictures/ball.png"); // creates a surface to load an image into the main memory
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

	SDL_Surface* surface = IMG_Load("pictures/line.png");
    line_tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(line_tex, NULL, NULL, &line.w, &line.h);

	line.w = window_width;
    line.h /= 3;
    line.x = 0;
    line.y = 100;

	line_color_array = (Uint8*) malloc(4 * line.w * line.h * sizeof(Uint8));

	SDL_Surface* surface1 = SDL_CreateRGBSurfaceWithFormat(0, line.w, line.h, 32, format);

    if (SDL_RenderReadPixels(rend, &line, format, surface1->pixels, surface1->pitch) != 0){
        SDL_Log("SDL_RenderReadPixels failed: %s", SDL_GetError());
    }else{
        SDL_SaveBMP(surface, "screenshot1.bmp");
    }

}

void create_door(SDL_Renderer* rend){

    SDL_Surface* door_surface = IMG_Load("pictures/door.png");
	
    door_tex = SDL_CreateTextureFromSurface(rend, door_surface);
    SDL_FreeSurface(door_surface);
    SDL_QueryTexture(door_tex, NULL, NULL, &door.w, &door.h);

	door.w /= 3;
    door.h = (window_height - line.y) / 4;

    door.x = window_width - door.w / 2 - 20;
    door.y = (window_height - door.h) / 2;
}

void create_goal(SDL_Renderer* rend){

    SDL_Surface* goal_surface = IMG_Load("pictures/goal.png");

    goal_tex = SDL_CreateTextureFromSurface(rend, goal_surface);
    SDL_FreeSurface(goal_surface);
    SDL_QueryTexture(goal_tex, NULL, NULL, &goal.w, &goal.h);

    goal.w /= 6;
    goal.h /= 6;

    goal.x = window_width - goal.w - 50;
    goal.y = 40;
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

TTF_Font* font;
SDL_Color color = {110, 0, 128, 255};

void create_Speed_number(SDL_Renderer* rend) {

	if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }
    string text = to_string(speed);

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
	create_door(rend);
	create_goal(rend);

	if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! Error: " << TTF_GetError() << std::endl;
        return;
    }
	font = TTF_OpenFont("arial-font/arial.ttf", 48);

	create_ISpeed(rend);
	create_DSpeed(rend);
	create_Speed_layer(rend);
	create_Speed_number(rend);

	create_IDegree(rend);
    create_DDegree(rend);
	create_Degree_layer(rend);
	create_Degree_number(rend);

}

const int BytesPerPixel = 4;


void get_color_array(SDL_Renderer* rend, SDL_Rect* rect, Uint8* color_array){

	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, line.w, line.h, 32, format);

    if (SDL_RenderReadPixels(rend, &line, format, surface->pixels, surface->pitch) != 0){
    	SDL_Log("SDL_RenderReadPixels failed: %s", SDL_GetError());
    }else{
        SDL_SaveBMP(surface, "screenshot2.bmp");
	}

	for(int x = 0; x < line.w; x++)
		for(int y = 0; y < line.h; y++){

			Uint8* pixel_base = static_cast<Uint8*>(surface->pixels);
            Uint8* pixel_address = pixel_base + (y * surface->pitch) + (x * BytesPerPixel);
            Uint32* pixel_ptr = reinterpret_cast<Uint32*>(pixel_address);

            Uint32 pixel_value;
            memcpy(&pixel_value, pixel_ptr, surface -> format -> BytesPerPixel);
			
			SDL_GetRGBA(pixel_value, surface->format,   &color_array[BytesPerPixel * (y * line.w + x)],      //R
														&color_array[BytesPerPixel * (y * line.w + x) + 1],  //G
														&color_array[BytesPerPixel * (y * line.w + x) + 2],  //B
														&color_array[BytesPerPixel * (y * line.w + x) + 3]); //A
		}
	
}


void local_RenderCopy(SDL_Renderer* rend, SDL_Rect rect, Uint8* color_array){
    // Draw a point at coordinate (100, 100)
	for(int i = rect.x, x = 0; i < rect.x + rect.w; i++, x++)
		for(int j = rect.y, y = 0; j < rect.y + rect.h; j++, y++){

			Uint8 r = color_array[BytesPerPixel * (y * rect.w + x)];
			Uint8 g = color_array[BytesPerPixel * (y * rect.w + x) + 1];
			Uint8 b = color_array[BytesPerPixel * (y * rect.w + x) + 2];
			Uint8 a = color_array[BytesPerPixel * (y * rect.w + x) + 3];

    		// Extract RGBA components
			SDL_SetRenderDrawColor(rend, r, g, b, a); // r g b a

			if((r && r != 0) or (g && g != 0) or (b && b != 0))
    			SDL_RenderDrawPoint(rend, i, j);
			
		}

	SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);

}

void display_object(SDL_Renderer* rend, SDL_Texture* texture, SDL_Rect rect, Uint8* color_array){
	//if(!asm_mod)
	//	SDL_RenderCopy(rend, texture, Null, &rect);
	//else
	//	local_RenderCopy(rend, rect, color_array);
}

bool test_t = false;

SDL_Point ball_center = {ball.w / 2, ball.h / 2};

void render_present(SDL_Renderer* rend){
	if(test_t)
		get_color_array(rend, &line, line_color_array);

	// clears the screen
    SDL_RenderClear(rend);

	SDL_RenderCopyEx(rend, ball_tex, NULL, &ball, angle, &ball_center, SDL_FLIP_NONE);

	if(!test_t){
		SDL_RenderCopy(rend, line_tex, NULL, &line);
	}else{
    	local_RenderCopy(rend, line, line_color_array);
	}

	if(door_move)
		door.y -= delta_door_move;
	else
		door.y += delta_door_move;
	
	if(door.y + door.h > window_height)
		door_move = true;
	if(door.y < line.y + line.h + delta_door_move)
		door_move = false;

	SDL_RenderCopy(rend, door_tex, NULL, &door);

	if(goal_display > 0){
		SDL_RenderCopy(rend, goal_tex, NULL, &goal);
		goal_display--;
	}

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
        
   	SDL_RenderPresent(rend);


	test_t = true;


}


void quit_game(SDL_Window* win, SDL_Renderer* rend){

	SDL_DestroyTexture(ball_tex);
	SDL_DestroyTexture(line_tex);
	SDL_DestroyTexture(door_tex);
	SDL_DestroyTexture(goal_tex);

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

void set_degree0(int x){
	degree0 = x;
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

bool shoot_ball(bool asm_mode){

	// check hit
    if (ball.x + ball.w > window_width or ball.x < 0 or ball.y + ball.h > window_height or ball.y < line.y + line.h/2){

		if(ball.x + ball.w > window_width and door.y <= ball.y and ball.y + ball.h <= door.y + door.h)
			goal_display = 30;

		ball.x = ballX0;
		ball.y = ballY0;
		degree = degree0;
		angle = 0;

    	return true;
    }

	
	angle += 10;

	// Convex move
    if(move_mod == 1){
		if(degree <= -70 && degree >= -75)
        	degree --;    
		else
			degree -= 5;
	}    

	// Sinusoidal move
    if(move_mod == 2){
    	degree += 20;
	
		if(degree >= 360)
			degree -= 360;
	}

	double ddegree = degree * -1;
    double dspeed = speed;
    double ballX = ball.x;
    double ballY = ball.y;
	double sad = 100;

	if(move_mod != 2){
    	if(!asm_mode){
    		ball.x = getX(degree * -1, speed, ball.x);
        	ball.y = getY(degree * -1, speed, ball.y);

    	}else{
        	ball.x = get_asm_x(ddegree, dspeed, ballX);
        	ball.y = get_asm_y(ddegree, dspeed, ballY);
    	}

	}else{
		if(!asm_mode){
			ball.x += 20;
            ball.y = getY(degree * -1, 100, ballY0);

        }else{
			ball.x += 20;
            ball.y = get_asm_y(ddegree, sad, ballY0);

		}
	}
    

	
	return false;
}


