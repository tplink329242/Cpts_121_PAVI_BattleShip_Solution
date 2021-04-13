#include "PAVI_logic_function.h"

typedef struct
{
	bool canPlaced;
	Battleship_ShipType ship_type;
	
}Battleship_RenderPlaceCell;



//init sdl window
SDL_Window* fnc_sdl_create_window();

//create render
SDL_Renderer* fnc_sdl_create_render(SDL_Window* win, Uint32 sdl_current_render_flags);

//create texture from picture
SDL_Texture* fnc_sdl_create_pic_texture(SDL_Renderer* battleship_main_window_renderer, const char* location_pic);

//create text texture
SDL_Texture* fnc_sdl_create_text_texture(SDL_Renderer* battleship_main_window_renderer, TTF_Font* font, SDL_Color textColor, char msg_user[100]);

//create text texture,  return rect and tex
void fnc_sdl_create_text_texture_and_location(SDL_Renderer* battleship_main_window_renderer, TTF_Font* font, SDL_Color textColor, SDL_Rect* text_rect, SDL_Texture** text_tex,char msg_user[100]);

//init sdl environment
int fnc_sdl_init(void);

//main render thread
int fnc_sdl_render_main(void* battleship_shared_data);

//mouse click checker
bool fnc_check_mouse_click_event_checker(SDL_Rect rect_Play_button);

//init & update render cell, if type = 0 is init
void fnc_update_array_render_place_cell(Battleship_RenderPlaceCell array_render_place_cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH], Battleship_Cell array_player_map[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH], Battleship_ShipType ship_type, Battleship_Direction ship_direction);

//init player place cell rect
void fnc_init_rect_array_render_place_cell(SDL_Rect rect_array_render_place_cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH]);
