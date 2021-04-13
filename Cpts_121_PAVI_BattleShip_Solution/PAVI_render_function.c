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

	//open a output file
	FILE* outfile = fnc_open_file("output.dat", "w");

	//shared mem
	Battleship_ThreadParameter* parameter_thread_data = battleship_shared_data;

	//sdl event
	SDL_Event battleship_event;

	//mouse rect
	Battleship_Rect mouse_rect;

	//game phase
	Battleship_GamePhase game_phase = 0;

	Battleship_PlayerType winner = player;

	//game round
	int game_round = 0;

	//place ship array & direction
	Battleship_ship array_player_place_ship[6];
	Battleship_ShipType now_placing = SHIP_TYPE_CARRIER;
	Battleship_Direction ship_direction = horizontal;
	Battleship_RenderPlaceCell array_render_place_cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH];
	
	
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
	//
	//init ship environment
	//place ship message
	SDL_Rect rect_player_place_ship_text = { 40,20, 0, 0 };
	SDL_Texture* tex_player_place_ship_text = NULL;
	fnc_sdl_create_text_texture_and_location(battleship_renderer, font_medium, textColor_blue, &rect_player_place_ship_text, &tex_player_place_ship_text, "Please start to place your ship!");
	fnc_update_array_render_place_cell(array_render_place_cell, NULL, SHIP_TYPE_INIT, ship_direction);

	
	//vertical horizontal message
	SDL_Rect rect_player_place_ship_direction_vertical_text = { 40,60, 0, 0 };
	SDL_Rect rect_player_place_ship_direction_horizontal_text = { 40,60, 0, 0 };
	SDL_Texture* tex_player_place_ship_direction_vertical_text = NULL;
	SDL_Texture* tex_player_place_ship_direction_horizontal_text = NULL;
	fnc_sdl_create_text_texture_and_location(battleship_renderer, font_medium, textColor_Fuchsia, &rect_player_place_ship_direction_vertical_text, &tex_player_place_ship_direction_vertical_text, "Ship location: vertical");
	fnc_sdl_create_text_texture_and_location(battleship_renderer, font_medium, textColor_Fuchsia, &rect_player_place_ship_direction_horizontal_text, &tex_player_place_ship_direction_horizontal_text, "Ship location: horizontal");

	//vertical horizontal variable
	
	
	//ship type message and rect
	//ship text rect
	SDL_Rect rect_player_place_ship_type_carrier_text = { 40,100, 0, 0 };
	SDL_Rect rect_player_place_ship_type_battleship_text = { 40,100, 0, 0 };
	SDL_Rect rect_player_place_ship_type_cruiser_text = { 40,100, 0, 0 };
	SDL_Rect rect_player_place_ship_type_submarine_text = { 40,100, 0, 0 };
	SDL_Rect rect_player_place_ship_type_destroyer_text = { 40,100, 0, 0 };

	//ship type tex
	SDL_Texture* tex_player_place_ship_type_carrier_text = NULL;
	SDL_Texture* tex_player_place_ship_type_battleship_text = NULL;
	SDL_Texture* tex_player_place_ship_type_cruiser_text = NULL;
	SDL_Texture* tex_player_place_ship_type_submarine_text = NULL;
	SDL_Texture* tex_player_place_ship_type_destroyer_text = NULL;
	fnc_sdl_create_text_texture_and_location(battleship_renderer, font_medium, textColor_blue, &rect_player_place_ship_type_carrier_text, &tex_player_place_ship_type_carrier_text, "Now placing: Carrier");
	fnc_sdl_create_text_texture_and_location(battleship_renderer, font_medium, textColor_blue, &rect_player_place_ship_type_battleship_text, &tex_player_place_ship_type_battleship_text, "Now placing: Battleship");
	fnc_sdl_create_text_texture_and_location(battleship_renderer, font_medium, textColor_blue, &rect_player_place_ship_type_cruiser_text, &tex_player_place_ship_type_cruiser_text, "Now placing: Cruiser");
	fnc_sdl_create_text_texture_and_location(battleship_renderer, font_medium, textColor_blue, &rect_player_place_ship_type_submarine_text, &tex_player_place_ship_type_submarine_text, "Now placing: Submarine");
	fnc_sdl_create_text_texture_and_location(battleship_renderer, font_medium, textColor_blue, &rect_player_place_ship_type_destroyer_text, &tex_player_place_ship_type_destroyer_text, "Now placing: Destroyer");

	//cell rect and tex
	SDL_Rect rect_array_render_place_cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH];
	fnc_init_rect_array_render_place_cell(rect_array_render_place_cell);

	//ship tex
	SDL_Texture* tex_player_place_ship_pic_carrier = fnc_sdl_create_pic_texture(battleship_renderer, "res/pic/carrier.jpg");
	SDL_Texture* tex_player_place_ship_pic_battleship = fnc_sdl_create_pic_texture(battleship_renderer, "res/pic/battleship.jpeg");
	SDL_Texture* tex_player_place_ship_pic_cruiser = fnc_sdl_create_pic_texture(battleship_renderer, "res/pic/cruiser.jpg");
	SDL_Texture* tex_player_place_ship_pic_submarine = fnc_sdl_create_pic_texture(battleship_renderer, "res/pic/submarine.jpg");
	SDL_Texture* tex_player_place_ship_pic_destroyer = fnc_sdl_create_pic_texture(battleship_renderer, "res/pic/destroyer.jpg");

	//stop & sea placing tex
	SDL_Texture* tex_player_place_ship_pic_stop = fnc_sdl_create_pic_texture(battleship_renderer, "res/pic/stop.PNG");
	SDL_Texture* tex_player_place_ship_pic_sea = fnc_sdl_create_pic_texture(battleship_renderer, "res/pic/sea.jpg");
	
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


	//ai & player shot elements

	//new cell tex
	SDL_Texture* tex_shot_boom_pic = fnc_sdl_create_pic_texture(battleship_renderer, "res/pic/boom.png");

	//text tex and rect
	SDL_Rect rect_shot_text_is_miss = { -150,500, 0, 0 };
	SDL_Rect rect_shot_text_is_hit = { -150,500, 0, 0 };
	
	SDL_Texture* tex_shot_text_is_miss = NULL;
	SDL_Texture* tex_shot_text_is_hit = NULL;
	fnc_sdl_create_text_texture_and_location(battleship_renderer, font_medium, textColor_blue, &rect_shot_text_is_miss, &tex_shot_text_is_miss, "Oops, this is a miss!");
	fnc_sdl_create_text_texture_and_location(battleship_renderer, font_medium, textColor_blue, &rect_shot_text_is_hit, &tex_shot_text_is_hit, "Yes, hit!");

	//is hit or miss flag
	bool is_hit = false;
	bool is_hide_map = false;

	//hit rect
	Battleship_Rect rect_hit;

	//call once in 1 round
	bool is_already_shot = false;
	
	//player & ai round title
	SDL_Rect rect_shot_player_round_title  = { 90,80, 0, 0 };
	SDL_Rect rect_shot_ai_round_title = { 90,80, 0, 0 };
	SDL_Texture* tex_shot_player_round_title = NULL;
	SDL_Texture* tex_shot_ai_round_title = NULL;
	
	fnc_sdl_create_text_texture_and_location(battleship_renderer, font_medium, textColor_blue, &rect_shot_player_round_title, &tex_shot_player_round_title, "Now it is a player round!");
	fnc_sdl_create_text_texture_and_location(battleship_renderer, font_medium, textColor_blue, &rect_shot_ai_round_title, &tex_shot_ai_round_title, "Now it is an AI round!");


	//winner text and location
	SDL_Rect rect_winner_player_round_title = { 90,80, 0, 0 };
	SDL_Rect rect_winner_ai_round_title = { 90,80, 0, 0 };
	SDL_Texture* tex_winner_player_round_title = NULL;
	SDL_Texture* tex_winner_ai_round_title = NULL;

	fnc_sdl_create_text_texture_and_location(battleship_renderer, font_medium, textColor_blue, &rect_winner_player_round_title, &tex_winner_player_round_title, "The winner is player! Static already written to file!");
	fnc_sdl_create_text_texture_and_location(battleship_renderer, font_medium, textColor_blue, &rect_winner_ai_round_title, &tex_winner_ai_round_title, "The winner is AI! Static already written to file!");



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
			SDL_LockMutex(parameter_thread_data->battleship_thd_bufferLock);
			fnc_update_array_render_place_cell(array_render_place_cell, parameter_thread_data->cell_player, now_placing, ship_direction);
			SDL_UnlockMutex(parameter_thread_data->battleship_thd_bufferLock);
			
			if (battleship_event.type == SDL_MOUSEBUTTONUP)
			{
				//switch vertical or horizontal
				if (ship_direction == vertical)
				{
					if (fnc_check_mouse_click_event_checker(rect_player_place_ship_direction_vertical_text))
					{
						ship_direction = horizontal;
					}
				}
				else
				{
					if (fnc_check_mouse_click_event_checker(rect_player_place_ship_direction_horizontal_text))
					{
						ship_direction = vertical;
					}
				}

				//apply player selected
				for (int i = 0; i < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++i)
				{
					for (int j = 0; j < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++j)
					{
						if (array_render_place_cell[i][j].canPlaced == true)
						{
							if (fnc_check_mouse_click_event_checker(rect_array_render_place_cell[i][j]))
							{
								array_player_place_ship[now_placing].ship_type = now_placing;
								array_player_place_ship[now_placing].direction = ship_direction;
								array_player_place_ship[now_placing].array_ship_location.x = i;
								array_player_place_ship[now_placing].array_ship_location.y = j;
								SDL_LockMutex(parameter_thread_data->battleship_thd_bufferLock);
								fnc_update_cell_using_array_ship(parameter_thread_data->cell_player, array_player_place_ship[now_placing], now_placing);
								SDL_UnlockMutex(parameter_thread_data->battleship_thd_bufferLock);

								//update render array
								fnc_update_array_render_place_cell(array_render_place_cell, parameter_thread_data->cell_player, now_placing, ship_direction);
								now_placing++;
								if (now_placing == 6)
								{
									SDL_LockMutex(parameter_thread_data->battleship_thd_bufferLock);

									//switch game phase to the next round
									parameter_thread_data->game_phase = BS_GAME_PHASE_DECIDE_WHO_GO_FIRST;
							
									fnc_ai_place_ship(parameter_thread_data->cell_ai);
									mock_test_session_map(parameter_thread_data);
									SDL_UnlockMutex(parameter_thread_data->battleship_thd_bufferLock);
								}
								break;
							}
						}
					}
				}
				
			}
			
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

				//print original map
				fnc_output_session_map(parameter_thread_data, outfile);

				if (who_go_first == player)
				{
					fprintf(outfile, "The first is player! \n");
				}
				else
				{
					fprintf(outfile, "The first is AI! \n");
				}
				
				if (parameter_thread_data->who_go_first == player)
				{
					parameter_thread_data->game_phase = BS_GAME_PHASE_PLAYER_SHOT;
				}
				else
				parameter_thread_data->game_phase = BS_GAME_PHASE_AI_SHOT;
				
				SDL_UnlockMutex(parameter_thread_data->battleship_thd_bufferLock);
			}
					
			break;

		case BS_GAME_PHASE_PLAYER_SHOT:

			if (is_already_shot == false)
			{
				SDL_LockMutex(parameter_thread_data->battleship_thd_bufferLock);
				fnc_update_array_render_place_cell(array_render_place_cell, parameter_thread_data->cell_ai, now_placing, ship_direction);

				

				//apply a shot to ai map



				
				for (int i = 0; i < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++i)
				{
					for (int j = 0; j < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++j)
					{
						if (parameter_thread_data->cell_ai[i][j].is_Hit == false)
						{
							if (battleship_event.type == SDL_MOUSEBUTTONUP)
							{
								if (fnc_check_mouse_click_event_checker(rect_array_render_place_cell[i][j]))
								{
									//hit the ai target
									rect_hit.x = i;
									rect_hit.y = j;

									//apply hit to ai map
									fnc_player_attack_cell(parameter_thread_data->cell_ai, rect_hit);
									is_hit = fnc_check_shot(parameter_thread_data->cell_ai, rect_hit);
									fnc_update_battleship_health(parameter_thread_data->cell_ai, parameter_thread_data->array_health_ai_battleship);


									//fprint game rect result
									if (is_hit == true)
									{
										fprintf(outfile, "(%d, %d) is a player hit!\n", rect_hit.x, rect_hit.y);
										parameter_thread_data->static_player.num_hit++;
									}
									else
									{
										fprintf(outfile, "(%d, %d) is a player miss!\n", rect_hit.x, rect_hit.y);
										parameter_thread_data->static_player.num_miss++;
									}

									
									if (parameter_thread_data->array_health_ai_battleship[0] == 1)
									{
										winner = player;
										parameter_thread_data->game_phase = BS_GAME_PHASE_STATIC;
									}

									//plus game round
									game_round++;
									is_already_shot = true;
								}
							}
						}
					}
				}
				SDL_UnlockMutex(parameter_thread_data->battleship_thd_bufferLock);
	
			}

			if (is_already_shot == true)
			{
				rect_shot_text_is_miss.x += 5;
				rect_shot_text_is_hit.x += 5;
			}

			
			if (rect_shot_text_is_miss.x >= 1000 || rect_shot_text_is_hit.x >= 1000)
			{
				is_already_shot = false;

				rect_shot_text_is_miss.x = -350;
				rect_shot_text_is_hit.x = -350;

				SDL_LockMutex(parameter_thread_data->battleship_thd_bufferLock);
				parameter_thread_data->game_phase = BS_GAME_PHASE_AI_SHOT;
				SDL_UnlockMutex(parameter_thread_data->battleship_thd_bufferLock);
			}

			break;
		case BS_GAME_PHASE_AI_SHOT:

			if (is_already_shot == false)
			{
				SDL_LockMutex(parameter_thread_data->battleship_thd_bufferLock);
				fnc_update_array_render_place_cell(array_render_place_cell, parameter_thread_data->cell_player, now_placing, ship_direction);

				//hit the player target
				rect_hit = fnc_ai_attack_cell(parameter_thread_data->cell_player);
				is_hit = fnc_check_shot(parameter_thread_data->cell_player, rect_hit);
				fnc_update_battleship_health(parameter_thread_data->cell_player, parameter_thread_data->array_health_player_battleship);


				//fprint game rect result
				if (is_hit == true)
				{
					fprintf(outfile, "(%d, %d) is a ai hit!\n", rect_hit.x, rect_hit.y);
					parameter_thread_data->static_ai.num_hit++;
				}
				else
				{
					fprintf(outfile, "(%d, %d) is a ai miss!\n", rect_hit.x, rect_hit.y);
					parameter_thread_data->static_ai.num_miss++;
				}
				

				if (parameter_thread_data->array_health_player_battleship[0] == 1)
				{
					winner = ai;
					parameter_thread_data->game_phase = BS_GAME_PHASE_STATIC;
				}
				
				SDL_UnlockMutex(parameter_thread_data->battleship_thd_bufferLock);

				
		
				//plus game round
				game_round++;
				is_already_shot = true;
			}

			rect_shot_text_is_miss.x += 5;
			rect_shot_text_is_hit.x += 5;

			if (rect_shot_text_is_miss.x >= 1000 || rect_shot_text_is_hit.x >= 1000)
			{
				is_already_shot = false;

				rect_shot_text_is_miss.x = -150;
				rect_shot_text_is_hit.x = -150;
				
				SDL_LockMutex(parameter_thread_data->battleship_thd_bufferLock);
				parameter_thread_data->game_phase = BS_GAME_PHASE_PLAYER_SHOT;
				SDL_UnlockMutex(parameter_thread_data->battleship_thd_bufferLock);
			}

						
			break;


		case BS_GAME_PHASE_STATIC:
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

			//copy ship direction
			if (ship_direction == vertical)
			{
				SDL_RenderCopy(battleship_renderer, tex_player_place_ship_direction_vertical_text, NULL, &rect_player_place_ship_direction_vertical_text);
			}
			if (ship_direction == horizontal)
			{
				SDL_RenderCopy(battleship_renderer, tex_player_place_ship_direction_horizontal_text, NULL, &rect_player_place_ship_direction_horizontal_text);
			}

			//copy now placing text
			switch (now_placing)
			{
			case SHIP_TYPE_CARRIER:
				SDL_RenderCopy(battleship_renderer, tex_player_place_ship_type_carrier_text, NULL, &rect_player_place_ship_type_carrier_text);
				break;
			case SHIP_TYPE_BATTLESHIP:
				SDL_RenderCopy(battleship_renderer, tex_player_place_ship_type_battleship_text, NULL, &rect_player_place_ship_type_battleship_text);
				break;
			case SHIP_TYPE_CRUISER:
				SDL_RenderCopy(battleship_renderer, tex_player_place_ship_type_cruiser_text, NULL, &rect_player_place_ship_type_cruiser_text);
				break;
			case SHIP_TYPE_SUBMARINE:
				SDL_RenderCopy(battleship_renderer, tex_player_place_ship_type_submarine_text, NULL, &rect_player_place_ship_type_submarine_text);
				break;
			case SHIP_TYPE_DESTROYER:
				SDL_RenderCopy(battleship_renderer, tex_player_place_ship_type_destroyer_text, NULL, &rect_player_place_ship_type_destroyer_text);
				break;
			default:;
			}
			
			
			//copy cell
			for (int i = 0; i < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++i)
			{
				for (int j = 0; j < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++j)
				{
					if (array_render_place_cell[i][j].ship_type == SHIP_TYPE_INIT)
					{
						if (array_render_place_cell[i][j].canPlaced == false)
						{
							SDL_RenderCopy(battleship_renderer, tex_player_place_ship_pic_stop, NULL, &rect_array_render_place_cell[i][j]);
						}
						else
						{
							SDL_RenderCopy(battleship_renderer, tex_player_place_ship_pic_sea, NULL, &rect_array_render_place_cell[i][j]);
						}
					}
					else
					{
						switch (array_render_place_cell[i][j].ship_type)
						{
						case SHIP_TYPE_CARRIER:
							SDL_RenderCopy(battleship_renderer, tex_player_place_ship_pic_carrier, NULL, &rect_array_render_place_cell[i][j]);
							break;
						case SHIP_TYPE_BATTLESHIP:
							SDL_RenderCopy(battleship_renderer, tex_player_place_ship_pic_battleship, NULL, &rect_array_render_place_cell[i][j]);
							break;
						case SHIP_TYPE_CRUISER:
							SDL_RenderCopy(battleship_renderer, tex_player_place_ship_pic_cruiser, NULL, &rect_array_render_place_cell[i][j]);
							break;
						case SHIP_TYPE_SUBMARINE:
							SDL_RenderCopy(battleship_renderer, tex_player_place_ship_pic_submarine, NULL, &rect_array_render_place_cell[i][j]);
							break;
						case SHIP_TYPE_DESTROYER:
							SDL_RenderCopy(battleship_renderer, tex_player_place_ship_pic_destroyer, NULL, &rect_array_render_place_cell[i][j]);
							break;
						default:;
						}
					}
				
				}
			}			
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

		case BS_GAME_PHASE_PLAYER_SHOT:

			//enalbe the hide map
			is_hide_map = true;

			//display the title
			SDL_RenderCopy(battleship_renderer, tex_shot_player_round_title, NULL, &rect_shot_player_round_title);

			SDL_LockMutex(parameter_thread_data->battleship_thd_bufferLock);

			//copy cell with hit update
			for (int i = 0; i < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++i)
			{
				for (int j = 0; j < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++j)
				{
					if (parameter_thread_data->cell_ai[i][j].is_Hit == true)
					{
						SDL_RenderCopy(battleship_renderer, tex_shot_boom_pic, NULL, &rect_array_render_place_cell[i][j]);
					}

					else if (is_hide_map == true)
					{
						SDL_RenderCopy(battleship_renderer, tex_player_place_ship_pic_sea, NULL, &rect_array_render_place_cell[i][j]);
					}
					else
					{
						if (parameter_thread_data->cell_ai[i][j].ship_type == SHIP_TYPE_INIT)
						{
							SDL_RenderCopy(battleship_renderer, tex_player_place_ship_pic_sea, NULL, &rect_array_render_place_cell[i][j]);
						}
						else
						{
							switch (parameter_thread_data->cell_ai[i][j].ship_type)
							{
							case SHIP_TYPE_CARRIER:
								SDL_RenderCopy(battleship_renderer, tex_player_place_ship_pic_carrier, NULL, &rect_array_render_place_cell[i][j]);
								break;
							case SHIP_TYPE_BATTLESHIP:
								SDL_RenderCopy(battleship_renderer, tex_player_place_ship_pic_battleship, NULL, &rect_array_render_place_cell[i][j]);
								break;
							case SHIP_TYPE_CRUISER:
								SDL_RenderCopy(battleship_renderer, tex_player_place_ship_pic_cruiser, NULL, &rect_array_render_place_cell[i][j]);
								break;
							case SHIP_TYPE_SUBMARINE:
								SDL_RenderCopy(battleship_renderer, tex_player_place_ship_pic_submarine, NULL, &rect_array_render_place_cell[i][j]);
								break;
							case SHIP_TYPE_DESTROYER:
								SDL_RenderCopy(battleship_renderer, tex_player_place_ship_pic_destroyer, NULL, &rect_array_render_place_cell[i][j]);
								break;
							default:;
							}
						}
					}
				}
			}
			SDL_UnlockMutex(parameter_thread_data->battleship_thd_bufferLock);
			
			//copy hit or miss text

			if (is_already_shot == true)
			{
				if (is_hit == false)
				{
					SDL_RenderCopy(battleship_renderer, tex_shot_text_is_miss, NULL, &rect_shot_text_is_miss);
				}
				else
				{
					SDL_RenderCopy(battleship_renderer, tex_shot_text_is_hit, NULL, &rect_shot_text_is_hit);
				}
			}

			break;

		case BS_GAME_PHASE_AI_SHOT:

			//disable the hide map
			is_hide_map = false;

			//display the title
			SDL_RenderCopy(battleship_renderer, tex_shot_ai_round_title, NULL, &rect_shot_ai_round_title);

			SDL_LockMutex(parameter_thread_data->battleship_thd_bufferLock);
				
			//copy cell with hit update
			for (int i = 0; i < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++i)
			{
				for (int j = 0; j < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++j)
				{
					if (parameter_thread_data->cell_player[i][j].is_Hit == true)
					{
						SDL_RenderCopy(battleship_renderer, tex_shot_boom_pic, NULL, &rect_array_render_place_cell[i][j]);
					}

					else if (is_hide_map == true)
					{
						SDL_RenderCopy(battleship_renderer, tex_player_place_ship_pic_sea, NULL, &rect_array_render_place_cell[i][j]);
					}
					else
					{
						if (parameter_thread_data->cell_player[i][j].ship_type == SHIP_TYPE_INIT)
						{
							SDL_RenderCopy(battleship_renderer, tex_player_place_ship_pic_sea, NULL, &rect_array_render_place_cell[i][j]);
						}
						else
						{
							switch (parameter_thread_data->cell_player[i][j].ship_type)
							{
							case SHIP_TYPE_CARRIER:
								SDL_RenderCopy(battleship_renderer, tex_player_place_ship_pic_carrier, NULL, &rect_array_render_place_cell[i][j]);
								break;
							case SHIP_TYPE_BATTLESHIP:
								SDL_RenderCopy(battleship_renderer, tex_player_place_ship_pic_battleship, NULL, &rect_array_render_place_cell[i][j]);
								break;
							case SHIP_TYPE_CRUISER:
								SDL_RenderCopy(battleship_renderer, tex_player_place_ship_pic_cruiser, NULL, &rect_array_render_place_cell[i][j]);
								break;
							case SHIP_TYPE_SUBMARINE:
								SDL_RenderCopy(battleship_renderer, tex_player_place_ship_pic_submarine, NULL, &rect_array_render_place_cell[i][j]);
								break;
							case SHIP_TYPE_DESTROYER:
								SDL_RenderCopy(battleship_renderer, tex_player_place_ship_pic_destroyer, NULL, &rect_array_render_place_cell[i][j]);
								break;
							default:;
							}
						}
					}
				}
			}
			SDL_UnlockMutex(parameter_thread_data->battleship_thd_bufferLock);
			//copy hit or miss text
			if (is_hit == false)
			{
				SDL_RenderCopy(battleship_renderer, tex_shot_text_is_miss, NULL, &rect_shot_text_is_miss);
			}
			else
			{
				SDL_RenderCopy(battleship_renderer, tex_shot_text_is_hit, NULL, &rect_shot_text_is_hit);
			}

			break;

		case BS_GAME_PHASE_STATIC:

			if (winner == player)
			{
				SDL_RenderCopy(battleship_renderer, tex_winner_player_round_title, NULL, &rect_winner_player_round_title);

				fprintf(outfile, "The winner is player\n");
				
			}
			else
			{
				SDL_RenderCopy(battleship_renderer, tex_winner_ai_round_title, NULL, &rect_winner_ai_round_title);

				fprintf(outfile, "The winner is AI\n");
				
			}

			//total static update
			SDL_LockMutex(parameter_thread_data->battleship_thd_bufferLock);
			parameter_thread_data->game_phase = BS_GAME_PHASE_PLAYER_SHOT;
			SDL_UnlockMutex(parameter_thread_data->battleship_thd_bufferLock);
			
			parameter_thread_data->static_player.num_total_shots = parameter_thread_data->static_player.num_miss + parameter_thread_data->static_player.num_hit;
			parameter_thread_data->static_player.ratio_miss = parameter_thread_data->static_player.num_miss / (double)parameter_thread_data->static_player.num_total_shots;

			parameter_thread_data->static_ai.num_total_shots = parameter_thread_data->static_ai.num_miss + parameter_thread_data->static_ai.num_hit;
			parameter_thread_data->static_ai.ratio_miss = parameter_thread_data->static_ai.num_miss / (double)parameter_thread_data->static_ai.num_total_shots;

			mock_test_session_map(parameter_thread_data);
			
			//print final map
			fnc_output_session_map(parameter_thread_data, outfile);
			fnc_output_players_static(parameter_thread_data, outfile);

			
			fclose(outfile);
			SDL_Delay(5000);
			

			SDL_LockMutex(parameter_thread_data->battleship_thd_bufferLock);
			parameter_thread_data->battleship_num_close_requested = true;
			SDL_UnlockMutex(parameter_thread_data->battleship_thd_bufferLock);

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
		case BS_GAME_PHASE_PLAYER_PLACE_SHIP:

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

void fnc_update_array_render_place_cell(Battleship_RenderPlaceCell array_render_place_cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH], Battleship_Cell array_player_map[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH], Battleship_ShipType ship_type, Battleship_Direction ship_direction)
{
	int max_x = 0;
	int max_y = 0;

	
	if (ship_type == SHIP_TYPE_INIT)
	{
		for (int i = 0; i < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++i)
		{
			for (int j = 0; j < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++j)
			{
				array_render_place_cell[i][j].ship_type = SHIP_TYPE_INIT;
				array_render_place_cell[i][j].canPlaced = true;
			}
		}
	}
	else
	{
		//get max length
		if (ship_direction == horizontal)
		{
			max_x = 10;
			switch (ship_type)
			{
			case SHIP_TYPE_CARRIER:
				max_y = 11 - GAME_BATTLESHIP_HEALTH_CARRIER;
				break;
			case SHIP_TYPE_BATTLESHIP:
				max_y = 11 - GAME_BATTLESHIP_HEALTH_BATTLESHIP;
				break;
			case SHIP_TYPE_CRUISER:
				max_y = 11 - GAME_BATTLESHIP_HEALTH_CRUISER;
				break;
			case SHIP_TYPE_SUBMARINE:
				max_y = 11 - GAME_BATTLESHIP_HEALTH_SUBMARINE;
				break;
			case SHIP_TYPE_DESTROYER:
				max_y = 11 - GAME_BATTLESHIP_HEALTH_DESTROYER;
				break;
			default:;
			}
		}
		else
		{
			max_y = 10;
			switch (ship_type)
			{
			case SHIP_TYPE_CARRIER:
				max_x = 11 - GAME_BATTLESHIP_HEALTH_CARRIER;
				break;
			case SHIP_TYPE_BATTLESHIP:
				max_x = 11 - GAME_BATTLESHIP_HEALTH_BATTLESHIP;
				break;
			case SHIP_TYPE_CRUISER:
				max_x = 11 - GAME_BATTLESHIP_HEALTH_CRUISER;
				break;
			case SHIP_TYPE_SUBMARINE:
				max_x = 11 - GAME_BATTLESHIP_HEALTH_SUBMARINE;
				break;
			case SHIP_TYPE_DESTROYER:
				max_x = 11 - GAME_BATTLESHIP_HEALTH_DESTROYER;
				break;
			default:;
			}
		}

		//get available slot
		switch (ship_type)
		{
		case SHIP_TYPE_CARRIER:
			for (int i = 0; i < max_x; ++i)
			{
				for (int j = 0; j < max_y; ++j)
				{
					array_render_place_cell[i][j].ship_type = array_player_map[i][j].ship_type;
					if (array_render_place_cell[i][j].ship_type != SHIP_TYPE_INIT)
					{
						array_render_place_cell[i][j].canPlaced = false;
					}
					else
					{
						array_render_place_cell[i][j].canPlaced = true;
						if (ship_direction == horizontal)
						{
							for (int k = 0; k < GAME_BATTLESHIP_HEALTH_CARRIER; ++k)
							{
								if (array_player_map[i][j + k].is_ship_placed == true)
								{
									array_render_place_cell[i][j].canPlaced = false;
									break;
								}
							}
						}
						else
						{
							for (int k = 0; k < GAME_BATTLESHIP_HEALTH_CARRIER; ++k)
							{
								if (array_player_map[i + k][j].is_ship_placed == true)
								{
									array_render_place_cell[i][j].canPlaced = false;
									break;
								}
							}
						}
					}				
				}
			}

			//full fill the rest of slot
			if (ship_direction == horizontal)
			{
				for (int i = 0; i < 10; ++i)
				{
					for (int j = 0; j < GAME_BATTLESHIP_HEALTH_CARRIER - 1; ++j)
					{
						array_render_place_cell[i][6 + j].canPlaced = false;
					}
				}
			}
			else
			{
				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_CARRIER; ++i)
				{
					for (int j = 0; j < 10; ++j)
					{
						array_render_place_cell[6 + i][j].canPlaced = false;
					}
				}				
			}		
			break;
			
		case SHIP_TYPE_BATTLESHIP:
			for (int i = 0; i < max_x; ++i)
			{
				for (int j = 0; j < max_y; ++j)
				{
					array_render_place_cell[i][j].ship_type = array_player_map[i][j].ship_type;
					if (array_render_place_cell[i][j].ship_type != SHIP_TYPE_INIT)
					{
						array_render_place_cell[i][j].canPlaced = false;
					}
					else
					{
						array_render_place_cell[i][j].canPlaced = true;
						if (ship_direction == horizontal)
						{
							for (int k = 0; k < GAME_BATTLESHIP_HEALTH_BATTLESHIP; ++k)
							{
								if (array_player_map[i][j + k].is_ship_placed == true)
								{
									array_render_place_cell[i][j].canPlaced = false;
									break;
								}
							}
						}
						else
						{
							for (int k = 0; k < GAME_BATTLESHIP_HEALTH_BATTLESHIP; ++k)
							{
								if (array_player_map[i + k][j].is_ship_placed == true)
								{
									array_render_place_cell[i][j].canPlaced = false;
									break;
								}
							}
						}
					}
				}
			}

			//full fill the rest of slot
			if (ship_direction == horizontal)
			{
				for (int i = 0; i < 10; ++i)
				{
					for (int j = 0; j < GAME_BATTLESHIP_HEALTH_BATTLESHIP - 1; ++j)
					{
						array_render_place_cell[i][7 + j].canPlaced = false;
					}
				}
			}
			else
			{
				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_BATTLESHIP; ++i)
				{
					for (int j = 0; j < 10; ++j)
					{
						array_render_place_cell[7 + i][j].canPlaced = false;
					}
				}
			}
			break;
			
		case SHIP_TYPE_CRUISER:
			for (int i = 0; i < max_x; ++i)
			{
				for (int j = 0; j < max_y; ++j)
				{
					array_render_place_cell[i][j].ship_type = array_player_map[i][j].ship_type;
					if (array_render_place_cell[i][j].ship_type != SHIP_TYPE_INIT)
					{
						array_render_place_cell[i][j].canPlaced = false;
					}
					else
					{
						array_render_place_cell[i][j].canPlaced = true;
						if (ship_direction == horizontal)
						{
							for (int k = 0; k < GAME_BATTLESHIP_HEALTH_CRUISER; ++k)
							{
								if (array_player_map[i][j + k].is_ship_placed == true)
								{
									array_render_place_cell[i][j].canPlaced = false;
									break;
								}
							}
						}
						else
						{
							for (int k = 0; k < GAME_BATTLESHIP_HEALTH_CRUISER; ++k)
							{
								if (array_player_map[i + k][j].is_ship_placed == true)
								{
									array_render_place_cell[i][j].canPlaced = false;
									break;
								}
							}
						}
					}
				}
			}

			//full fill the rest of slot
			if (ship_direction == horizontal)
			{
				for (int i = 0; i < 10; ++i)
				{
					for (int j = 0; j < GAME_BATTLESHIP_HEALTH_CRUISER - 1; ++j)
					{
						array_render_place_cell[i][8 + j].canPlaced = false;
					}
				}
			}
			else
			{
				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_CRUISER; ++i)
				{
					for (int j = 0; j < 10; ++j)
					{
						array_render_place_cell[8 + i][j].canPlaced = false;
					}
				}
			}
			break;
			
		case SHIP_TYPE_SUBMARINE:
			for (int i = 0; i < max_x; ++i)
			{
				for (int j = 0; j < max_y; ++j)
				{
					array_render_place_cell[i][j].ship_type = array_player_map[i][j].ship_type;
					if (array_render_place_cell[i][j].ship_type != SHIP_TYPE_INIT)
					{
						array_render_place_cell[i][j].canPlaced = false;
					}
					else
					{
						array_render_place_cell[i][j].canPlaced = true;
						if (ship_direction == horizontal)
						{
							for (int k = 0; k < GAME_BATTLESHIP_HEALTH_SUBMARINE; ++k)
							{
								if (array_player_map[i][j + k].is_ship_placed == true)
								{
									array_render_place_cell[i][j].canPlaced = false;
									break;
								}
							}
						}
						else
						{
							for (int k = 0; k < GAME_BATTLESHIP_HEALTH_SUBMARINE; ++k)
							{
								if (array_player_map[i + k][j].is_ship_placed == true)
								{
									array_render_place_cell[i][j].canPlaced = false;
									break;
								}
							}
						}
					}
				}
			}

			//full fill the rest of slot
			if (ship_direction == horizontal)
			{
				for (int i = 0; i < 10; ++i)
				{
					for (int j = 0; j < GAME_BATTLESHIP_HEALTH_SUBMARINE - 1; ++j)
					{
						array_render_place_cell[i][8 + j].canPlaced = false;
					}
				}
			}
			else
			{
				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_SUBMARINE; ++i)
				{
					for (int j = 0; j < 10; ++j)
					{
						array_render_place_cell[8 + i][j].canPlaced = false;
					}
				}
			}
			break;

		case SHIP_TYPE_DESTROYER:
			for (int i = 0; i < max_x; ++i)
			{
				for (int j = 0; j < max_y; ++j)
				{
					array_render_place_cell[i][j].ship_type = array_player_map[i][j].ship_type;
					if (array_render_place_cell[i][j].ship_type != SHIP_TYPE_INIT)
					{
						array_render_place_cell[i][j].canPlaced = false;
					}
					else
					{
						array_render_place_cell[i][j].canPlaced = true;
						if (ship_direction == horizontal)
						{
							for (int k = 0; k < GAME_BATTLESHIP_HEALTH_DESTROYER; ++k)
							{
								if (array_player_map[i][j + k].is_ship_placed == true)
								{
									array_render_place_cell[i][j].canPlaced = false;
									break;
								}
							}
						}
						else
						{
							for (int k = 0; k < GAME_BATTLESHIP_HEALTH_DESTROYER; ++k)
							{
								if (array_player_map[i + k][j].is_ship_placed == true)
								{
									array_render_place_cell[i][j].canPlaced = false;
									break;
								}
							}
						}
					}
				}
			}

			//full fill the rest of slot
			if (ship_direction == horizontal)
			{
				for (int i = 0; i < 10; ++i)
				{
					for (int j = 0; j < GAME_BATTLESHIP_HEALTH_DESTROYER - 1; ++j)
					{
						array_render_place_cell[i][9 + j].canPlaced = false;
					}
				}
			}
			else
			{
				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_DESTROYER; ++i)
				{
					for (int j = 0; j < 10; ++j)
					{
						array_render_place_cell[9 + i][j].canPlaced = false;
					}
				}
			}
			break;
			
		default:;
		}
	}
}

void fnc_init_rect_array_render_place_cell(SDL_Rect rect_array_render_place_cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH])
{
	int init_x = 140;
	int init_y = 150;
	const int init_w = 50;
	const int init_h = 50;
	for (int i = 0; i < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++i)
	{
		for (int j = 0; j < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++j)
		{
			init_x += 60;
			rect_array_render_place_cell[i][j].x = init_x;
			rect_array_render_place_cell[i][j].y = init_y;
			rect_array_render_place_cell[i][j].w = init_w;
			rect_array_render_place_cell[i][j].h = init_h;
		}
		init_x = 140;
		init_y += 60;
	}
}

