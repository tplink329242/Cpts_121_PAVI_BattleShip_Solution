#include "PAVI_render_function.h"

SDL_Window* fnc_sdl_create_window()
{
	SDL_Window* win = SDL_CreateWindow("Cpts 121 PAVI 'Battleship'",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT, 0);
	if (!win)
	{
		printf_s("Error creating SDL window: %s ", SDL_GetError());
		return NULL;
	}
	return win;
}

SDL_Renderer* fnc_sdl_create_render(SDL_Window* win, Uint32 sdl_current_render_flags)
{
	SDL_Renderer* render = SDL_CreateRenderer(win, -1, sdl_current_render_flags);
	if (!render)
	{
		printf_s("Error creating SDL render: %s ", SDL_GetError());
		return NULL;
	}
	return render;
}

SDL_Texture* fnc_sdl_create_pic_texture(SDL_Renderer* battleship_main_window_renderer, const char* location_pic)
{
	SDL_Surface* surface = IMG_Load(location_pic);
	if (surface == NULL)
	{
		printf_s("Error creating SDL surface: %s ", SDL_GetError());
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(battleship_main_window_renderer, surface);

	//free surface
	SDL_FreeSurface(surface);

	if (!tex)
	{
		printf_s("Error creating SDL texture: %s ", SDL_GetError());
	}
	return tex;
}

SDL_Texture* fnc_sdl_create_text_texture(SDL_Renderer* battleship_main_window_renderer, TTF_Font* font, SDL_Color textColor, char msg_user[100])
{
	SDL_Surface* msg_input = TTF_RenderUTF8_Solid(font, msg_user, textColor);
	SDL_Texture* battleship_fonts = SDL_CreateTextureFromSurface(battleship_main_window_renderer, msg_input);
	SDL_FreeSurface(msg_input);
	return battleship_fonts;
}

void fnc_sdl_create_text_texture_and_location(SDL_Renderer* battleship_main_window_renderer, TTF_Font* font, SDL_Color textColor, SDL_Rect* text_rect, SDL_Texture** text_tex, char msg_user[100])
{
	*text_tex = fnc_sdl_create_text_texture(battleship_main_window_renderer, font, textColor, msg_user);
	SDL_QueryTexture(*text_tex, NULL, NULL, &text_rect->w, &text_rect->h);
}

int fnc_sdl_render_main(void* battleship_shared_data)
{

	//init render environment
	fnc_sdl_init();
	bool battleship_num_close_requested = FALSE;

	//shared mem
	Battleship_ThreadParameter* parameter_thread_data = battleship_shared_data;

	//sdl event
	SDL_Event battleship_event;

	//mouse rect
	Battleship_Rect mouse_rect;

	//game phase
	Battleship_GamePhase game_phase = 0;
	
	//sdl const var
	const Uint32 battleship_sdl_render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	const char* pic_background = "res/pic/main_menu.jpg";
	const char* pic_dice_six = "res/pic/dice_6.PNG";
	
	//init main window
	SDL_Window* battleship_main_window = fnc_sdl_create_window();
	SDL_Renderer* battleship_renderer = fnc_sdl_create_render(battleship_main_window, battleship_sdl_render_flags);
	SDL_Texture* tex_menu_background = fnc_sdl_create_pic_texture(battleship_renderer, pic_background);

	//init who go first session
	SDL_Texture* tex_who_first_dice = fnc_sdl_create_pic_texture(battleship_renderer, pic_dice_six);
	int who_go_first = 2;

	//init font and size
	TTF_Font* font = TTF_OpenFont("res/data/calibri.ttf", 25);
	TTF_Font* font_medium = TTF_OpenFont("res/data/calibri.ttf", 50);
	TTF_Font* font_big = TTF_OpenFont("res/data/calibri.ttf", 80);
	const SDL_Color textColor_blue = { 0, 0, 255 };
	const SDL_Color textColor_Fuchsia = { 255, 0, 255 };

	
	//main menu text var
	//welcome text generator
	SDL_Rect rect_menu_main_text = { 100,100, 0, 0 };
	SDL_Texture* tex_menu_main_text = NULL;
	fnc_sdl_create_text_texture_and_location(battleship_renderer, font_big, textColor_blue, &rect_menu_main_text, &tex_menu_main_text, "Welcome To Battleship!");

	//play button generator
	SDL_Rect rect_menu_play_button = { 700,500, 0, 0 };
	SDL_Texture* tex_menu_play_button = NULL;
	fnc_sdl_create_text_texture_and_location(battleship_renderer, font_big, textColor_Fuchsia, &rect_menu_play_button, &tex_menu_play_button, "Play!");


	//player place ship phase
	//place ship message
	SDL_Rect rect_player_place_ship_text = { 60,40, 0, 0 };
	SDL_Texture* tex_player_place_ship_text = NULL;
	fnc_sdl_create_text_texture_and_location(battleship_renderer, font_medium, textColor_blue, &rect_player_place_ship_text, &tex_player_place_ship_text, "Please start to place your ship!");


	//ship type message and rect
	//ship rect
	SDL_Rect rect_player_place_ship_type_carrier_text = { 60,60, 0, 0 };
	SDL_Rect rect_player_place_ship_type_battleship_text = { 60,60, 0, 0 };
	SDL_Rect rect_player_place_ship_type_cruiser_text = { 60,60, 0, 0 };
	SDL_Rect rect_player_place_ship_type_submarine_text = { 60,60, 0, 0 };
	SDL_Rect rect_player_place_ship_type_destroyer_text = { 60,60, 0, 0 };

	//ship type tex
	SDL_Texture* tex_player_place_ship_type_carrier_text = NULL;
	SDL_Texture* tex_player_place_ship_type_battleship_text = NULL;
	SDL_Texture* tex_player_place_ship_type_cruiser_text = NULL;
	SDL_Texture* tex_player_place_ship_type_submarine_text = NULL;
	SDL_Texture* tex_player_place_ship_type_destroyer_text = NULL;
	
	//who go first var
	SDL_Rect rect_who_go_fist_text = { 90,100, 0, 0 };
	SDL_Rect rect_who_go_fist_dice = { 462,300, 100, 100 };
	SDL_Texture* tex_who_go_fist_text = NULL;
	fnc_sdl_create_text_texture_and_location(battleship_renderer, font_medium, textColor_blue, &rect_who_go_fist_text, &tex_who_go_fist_text, "Please click dice for picking up who go first!");

	//ai and player message
	SDL_Rect rect_who_go_fist_ai = { -150,500, 0, 0 };
	SDL_Rect rect_who_go_fist_player = { -150,500, 0, 0 };
	SDL_Texture* tex_who_go_fist_ai = NULL;
	SDL_Texture* tex_who_go_fist_player = NULL;
	fnc_sdl_create_text_texture_and_location(battleship_renderer, font_medium, textColor_blue, &rect_who_go_fist_ai, &tex_who_go_fist_ai, "Oops, looks like AI have better lucky!");
	fnc_sdl_create_text_texture_and_location(battleship_renderer, font_medium, textColor_blue, &rect_who_go_fist_player, &tex_who_go_fist_player, "You got lucky and you go first!");

	

	while (!battleship_num_close_requested)
	{
		// clear the window
		SDL_RenderClear(battleship_renderer);

		//copy the main background
		SDL_RenderCopy(battleship_renderer, tex_menu_background, NULL, NULL);


		//load data from shared memory
		SDL_LockMutex(parameter_thread_data->battleship_thd_bufferLock);
		battleship_num_close_requested = parameter_thread_data->battleship_num_close_requested;
		game_phase = parameter_thread_data->game_phase;
		SDL_UnlockMutex(parameter_thread_data->battleship_thd_bufferLock);

		//reset sdl event states;
		battleship_event.type = SDL_FIRSTEVENT;
		
		//quit identify
		while (SDL_PollEvent(&battleship_event))
		{
			if (battleship_event.type == SDL_QUIT)
			{
				//close flag
				SDL_LockMutex(parameter_thread_data->battleship_thd_bufferLock);
				parameter_thread_data->battleship_num_close_requested = true;
				SDL_UnlockMutex(parameter_thread_data->battleship_thd_bufferLock);
			}
		}	


		
		//text & rect generator & mouse click detection & phase switcher
		switch (game_phase)
		{
		case BS_GAME_PHASE_MAIN_MENU:
			if (battleship_event.type == SDL_MOUSEBUTTONUP)
			{
				if (fnc_check_mouse_click_event_checker(rect_menu_play_button))
				{
					SDL_LockMutex(parameter_thread_data->battleship_thd_bufferLock);
					parameter_thread_data->game_phase = BS_GAME_PHASE_PLAYER_PLACE_SHIP;
					SDL_UnlockMutex(parameter_thread_data->battleship_thd_bufferLock);
				}
			}	
			break;
			
		case BS_GAME_PHASE_PLAYER_PLACE_SHIP:
			if (battleship_event.type == SDL_MOUSEBUTTONUP)
			{
				if (fnc_check_mouse_click_event_checker(rect_who_go_fist_dice))
				{
				}
			}

			//switch game phase to the next round

			break;
			
		case BS_GAME_PHASE_DECIDE_WHO_GO_FIRST:
			if (battleship_event.type == SDL_MOUSEBUTTONUP)
			{
				if (fnc_check_mouse_click_event_checker(rect_who_go_fist_dice))
				{
					who_go_first = fnc_select_who_starts_first();					
					SDL_LockMutex(parameter_thread_data->battleship_thd_bufferLock);
					parameter_thread_data->who_go_first = who_go_first;					
					SDL_UnlockMutex(parameter_thread_data->battleship_thd_bufferLock);
				}
			}

			//move text to new location
			if (rect_who_go_fist_player.x < 900 || rect_who_go_fist_ai.x < 900)
			{
				if (who_go_first == 0)
				{
					rect_who_go_fist_player.x += 3;
				}
				if (who_go_first == 1)
				{
					rect_who_go_fist_ai.x += 3;
				}
			}			
			//switch game phase to the next round
			if (rect_who_go_fist_player.x >=900 || rect_who_go_fist_ai.x >= 900)
			{
				SDL_LockMutex(parameter_thread_data->battleship_thd_bufferLock);
				parameter_thread_data->game_phase = BS_GAME_PHASE_PLAYER_PLACE_SHIP;
				SDL_UnlockMutex(parameter_thread_data->battleship_thd_bufferLock);
			}
					
			break;
			
		

		default:;
		}

		

		//game phase render copy
		switch (game_phase)
		{
		case BS_GAME_PHASE_MAIN_MENU:
			SDL_RenderCopy(battleship_renderer, tex_menu_main_text, NULL, &rect_menu_main_text);
			SDL_RenderCopy(battleship_renderer, tex_menu_play_button, NULL, &rect_menu_play_button);
			break;
			
		case BS_GAME_PHASE_PLAYER_PLACE_SHIP:
			SDL_RenderCopy(battleship_renderer, tex_player_place_ship_text, NULL, &rect_player_place_ship_text);
			break;
			
		case BS_GAME_PHASE_DECIDE_WHO_GO_FIRST:
			SDL_RenderCopy(battleship_renderer, tex_who_go_fist_text, NULL, &rect_who_go_fist_text);
			SDL_RenderCopy(battleship_renderer, tex_who_first_dice, NULL, &rect_who_go_fist_dice);
			if (who_go_first == 0)
			{
				SDL_RenderCopy(battleship_renderer, tex_who_go_fist_player, NULL, &rect_who_go_fist_player);
			}
			if (who_go_first == 1)
			{
				SDL_RenderCopy(battleship_renderer, tex_who_go_fist_ai, NULL, &rect_who_go_fist_ai);
			}		
			break;
			
		default:;
		}
		
		//show the render
		SDL_RenderPresent(battleship_renderer);

		//destroy phase
		switch (game_phase)
		{
		case BS_GAME_PHASE_MAIN_MENU:
			break;
		case BS_GAME_PHASE_DECIDE_WHO_GO_FIRST:
			break;
		default:;
		}

		
		

		// wait 1/60th of a second
		SDL_Delay(1000 / 60);
		
	}	
	return 0;
}

int fnc_sdl_init(void)
{
	int res = 0;
	res = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS);
	if (res != 0)
	{
		printf_s("Error for init SDL: %s ", SDL_GetError());
		return 1;
	}
	if (TTF_Init() == -1)
	{
		return 1;
	}
	printf_s("init success!\n");
	return 0;
}

bool fnc_check_mouse_click_event_checker(SDL_Rect rect_Play_button)
{
	int mouse_state_x;
	int mouse_state_y;
	SDL_GetMouseState(&mouse_state_x, &mouse_state_y);

	if ((mouse_state_x > rect_Play_button.x) && (mouse_state_x < (rect_Play_button.x + rect_Play_button.w)))
	{
		if ((mouse_state_y > rect_Play_button.y) && (mouse_state_y < (rect_Play_button.y + rect_Play_button.h)))
		{
			return true;
		}
	}
	return false;
}

