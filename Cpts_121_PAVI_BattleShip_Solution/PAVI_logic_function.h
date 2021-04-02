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
		
	}Battleship_ship;

	typedef struct
	{
		int num_game_round;
		Battleship_Cell array_player_map[10][10];
		Battleship_Cell array_AI_map[10][10];

	}Battleship_GameRound;
	
	

#ifdef __cplusplus
}
#endif
#endif
