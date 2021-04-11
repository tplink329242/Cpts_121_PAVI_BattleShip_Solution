#ifndef PAVI_LOGIC_FUNCTIONS_H
#define PAVI_LOGIC_FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

	//def base marco
#define _CRT_SECURE_NO_WARNINGS
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768


#define GAME_BATTLESHIP_HEALTH_CARRIER 5
#define GAME_BATTLESHIP_HEALTH_BATTLESHIP 4
#define GAME_BATTLESHIP_HEALTH_CRUISER 3
#define GAME_BATTLESHIP_HEALTH_SUBMARINE 3
#define GAME_BATTLESHIP_HEALTH_DESTROYER 2

#define GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH 10
#define GAME_BATTLESHIP_MAX_GAME_SHIP_NUM 5


//std library	
#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include <time.h> 
#include <Windows.h>
#include <stdbool.h>
#include <string.h>

//sdl include	
#include "include\SDL_mutex.h"
#include "include/SDL.h"
#include "include/SDL_timer.h"
#include "include/SDL_image.h"
#include "include/SDL_ttf.h"
#include "include/SDL_thread.h"
	
	
	typedef enum
	{
		round_none,
		round_player,
		round_ai

	}Battleship_WhoRound;

	typedef enum
	{
		player,
		ai

	}Battleship_PlayerType;
	
	typedef enum
	{
		vertical,
		horizontal
		
	}Battleship_Direction;

	typedef enum
	{
		SHIP_TYPE_INIT,
		SHIP_TYPE_CARRIER,
		SHIP_TYPE_BATTLESHIP,
		SHIP_TYPE_CRUISER,
		SHIP_TYPE_SUBMARINE,
		SHIP_TYPE_DESTROYER		
		
	}Battleship_ShipType;

	typedef enum
	{
		BS_GAME_PHASE_INIT,
		BS_GAME_PHASE_MAIN_MENU,
		BS_GAME_PHASE_PLAYER_PLACE_SHIP,
		BS_GAME_PHASE_DECIDE_WHO_GO_FIRST,		
		BS_GAME_PHASE_AI_PLACE_SHIP,
		BS_GAME_PHASE_PLAYER_SHOT,
		BS_GAME_PHASE_AI_SHOT,
		BS_GAME_PHASE_STATIC

	}Battleship_GamePhase;
	
	typedef struct
	{
		int x;
		int y;
		
	}Battleship_Rect;

	typedef struct
	{
		bool is_ship_placed;
		bool is_Hit;

		//init for twice
		char char_ship_type;
		Battleship_ShipType ship_type;

		Battleship_Rect rect;
		int cell_id;
		
		
	}Battleship_Cell;

	typedef struct
	{
		Battleship_ShipType ship_type;
		Battleship_Rect array_ship_location;
		int health;
		bool is_sunk;
		Battleship_Direction direction;
		
	}Battleship_ship;

	typedef struct
	{
		bool is_active;
		Battleship_Cell array_player_map[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH];
		Battleship_Cell array_AI_map[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH];

	}Battleship_GameRound;

	typedef struct
	{
		int num_total_shots;
		int num_hit;
		int num_miss;
		double ratio_miss;
				
	}Battleship_Static;
	
	typedef struct
	{
		int thread_id;
		
		//close flag
		bool battleship_num_close_requested;

		//thread lock
		bool battleship_is_consumer_go;
		bool battleship_is_producer_go;

		//thread signal
		SDL_cond* battleship_thd_canProduce;
		SDL_cond* battleship_thd_canConsume;
		SDL_mutex* battleship_thd_bufferLock;

		//game map data
		Battleship_Cell cell_player[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH];
		Battleship_Cell cell_ai[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH];

		//game round record
		//Battleship_GameRound game_round_map[100];

		Battleship_GamePhase game_phase;
		
		//define next round belongs to whom
		Battleship_WhoRound who_round;

		//make who is the first one
		Battleship_PlayerType who_go_first;
		

		//battleship health for both players
		int array_health_player_battleship[6];
		int array_health_ai_battleship[6];

		//battleship_statics
		Battleship_Static static_player;
		Battleship_Static static_ai;
		
			
	}Battleship_ThreadParameter;

	//start the game
	void fnc_start_game(Battleship_ThreadParameter* thread_parameter);

	//player place the ship
	bool fnc_player_place_ship(Battleship_ThreadParameter* thread_parameter);

	//player place the ship
	bool fnc_ai_place_ship(Battleship_Cell cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH]);

	//get an available rect for pick up
	Battleship_Rect fnc_get_available_random_place(Battleship_Cell cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH], int ship_type, Battleship_Direction ship_direction);
	
	//check who pick up the first round
	void fnc_update_cell_using_array_ship(Battleship_Cell cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH], Battleship_ship array_ship, Battleship_ShipType ship_type);

	//check who pick up the first round
	Battleship_PlayerType fnc_select_who_starts_first();

	//apply shot into board
	bool fnc_check_shot(Battleship_Cell cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH], Battleship_Rect hit_rect);

	//check if we have a winner
	int fnc_check_is_winner(Battleship_ThreadParameter* thread_parameter);

	//check every ship's health
	bool fnc_check_if_sunk_ship(Battleship_ThreadParameter* thread_parameter);

	//print player's log
	bool fnc_print_game_log(Battleship_ThreadParameter* thread_parameter);

	//print winner
	bool fnc_print_game_winner(Battleship_ThreadParameter* thread_parameter);

	//print winner
	bool fnc_print_2_game_maps(Battleship_ThreadParameter* thread_parameter);

	//play one round
	bool fnc_play_one_round(Battleship_ThreadParameter* thread_parameter);

	//init game surroundings
	bool fnc_init_parameter_environment(Battleship_ThreadParameter* thread_parameter);

	//init game cells
	void fnc_init_battleship_cell(Battleship_Cell cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH]);

	//ai drop a bomb to hit cells
	Battleship_Rect fnc_ai_attack_cell(Battleship_Cell cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH]);

	//sync battleship health
	void fnc_update_battleship_health(Battleship_Cell cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH], int* array_health_player_battleship);

	//sync parameter data
	void fnc_sync_data(Battleship_ThreadParameter* thread_parameter);

	//start a new session
	void fnc_start_session();

	//start a new mock session
	void mock_start_test_session();

	//test session condition
	void mock_test_session_map(Battleship_ThreadParameter* thread_parameter);

	//file components
	//
	//open a file
	FILE* fnc_open_file(char* file_name, char* file_access);

	//output session map to a file
	void fnc_output_session_map(Battleship_ThreadParameter* thread_parameter, FILE* outfile);

	//output ai and player statics
	void fnc_output_players_static(Battleship_ThreadParameter* thread_parameter, FILE* outfile);
	
#ifdef __cplusplus
}
#endif
#endif
