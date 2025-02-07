#ifndef X0
#define X0

bool is_click_on_ISpeed(int, int);
bool is_click_on_DSpeed(int, int);
bool is_click_on_IDegree(int, int);
bool is_click_on_DDegree(int, int);
bool is_click_on_move_type(int, int, int);

void create_objects(SDL_Renderer*);
void render_present(SDL_Renderer*);
void quit_game(SDL_Window*, SDL_Renderer*);

void set_move_variables(int, int, int);
void set_degree0(int);
void set_asm_mode(bool);
bool shoot_ball();

#endif

