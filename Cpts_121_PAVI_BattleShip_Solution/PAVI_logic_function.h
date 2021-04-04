#ifndef PAVI_LOGIC_FUNCTIONS_H
#define PAVI_LOGIC_FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

	//def base marco
#define _CRT_SECURE_NO_WARNINGS
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768


#define GAME_BATTLESHIP_VALUE_HEALTH_CARRIER 5
#define GAME_BATTLESHIP_VALUE_HEALTH_BATTLESHIP 4
#define GAME_BATTLESHIP_VALUE_HEALTH_CRUISER 3
#define GAME_BATTLESHIP_VALUE_HEALTH_SUBMARINE 2


	

//std library	
#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include <time.h> 
#include <Windows.h>
#include <stdbool.h>
#include <string.h>

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
	
	typedef struct
	{
		int x;
		int y;
		
	}Battleship_Rect;

	typedef struct
	{
		boolean is_LockedInGame;
		boolean is_Hit;

		//init for twice
		char char_ship_type;
		Battleship_ShipType ship_type;

		Battleship_Rect rect;
		int cell_id;
		
		
	}Battleship_Cell;

	typedef struct
	{
		Battleship_ShipType ship_type;
		Battleship_Rect array_ship_location[5];
		int health;
		bool is_sunk;
		Battleship_Direction direction;
		
	}Battleship_ship;

	typedef struct
	{
		int num_game_round;
		Battleship_Cell array_player_map[10][10];
		Battleship_Cell array_AI_map[10][10];

	}Battleship_GameRound;

	typedef struct
	{
		int thread_id;
		
	}Battleship_ThreadParameter;

	//start the game
	void fnc_start_game(Battleship_ThreadParameter* thread_parameter);

	//player place the ship
	bool fnc_player_place_ship(Battleship_ThreadParameter* thread_parameter);

	//player place the ship
	bool fnc_ai_place_ship(Battleship_ThreadParameter* thread_parameter);

	//check who pick up the first round
	Battleship_PlayerType fnc_select_who_starts_first(Battleship_ThreadParameter* thread_parameter);

	//apply shot into board
	bool fnc_check_shot(Battleship_ThreadParameter* thread_parameter);

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

	//start a new session
	void fnc_start_session();

	//start a new mock session
	void mock_start_test_session();
	
#ifdef __cplusplus
}
#endif
#endif
