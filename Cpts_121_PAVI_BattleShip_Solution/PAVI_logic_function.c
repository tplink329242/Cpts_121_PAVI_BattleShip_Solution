#include "PAVI_logic_function.h"

void fnc_start_game(Battleship_ThreadParameter* thread_parameter)
{
	//init game environment
	
	//player place ship

	//decide who pick up first

	//print both maps

	//switch player or ai

	while (true)
	{
		//start one round

		//print this round
		
	}
	
	//print the winner

	//wait for back to menu
	
}

bool fnc_player_place_ship(Battleship_ThreadParameter* thread_parameter)
{
	//'c' for Carrier, 'b' for Battleship, 'r' for Cruiser, 's' for Submarine, or 'd' for Destroyer.

	//while loop

	//if place is empty

	// place carrier

	//place battleship

	//place cruiser

	//place submarine

	//place destroyer

	return false;
}

bool fnc_ai_place_ship(Battleship_ThreadParameter* thread_parameter)
{
	//'c' for Carrier, 'b' for Battleship, 'r' for Cruiser, 's' for Submarine, or 'd' for Destroyer.

	//while loop

	//if place is empty

	// place carrier

	//place battleship

	//place cruiser

	//place submarine

	//place destroyer
	
	return false;
}

Battleship_PlayerType fnc_select_who_starts_first(Battleship_ThreadParameter* thread_parameter)
{
	const Battleship_PlayerType type = rand() % 2;
	return type;
}

bool fnc_check_shot(Battleship_ThreadParameter* thread_parameter)
{
	//return if it is a hit
	return false;
}

int fnc_check_is_winner(Battleship_ThreadParameter* thread_parameter)
{
	//return 0 for player, return 1 for ai, return -1 for no winner

	//for loop 5 with player ship

	//for loop 5 with ai ship

	//if statement x2

	return -1;
}

bool fnc_check_if_sunk_ship(Battleship_ThreadParameter* thread_parameter)
{
	//for loop and check hit point with each ship, update the health.
	//if health equals to zero mark it has been sunk
	
	return false;
}

bool fnc_print_game_log(Battleship_ThreadParameter* thread_parameter)
{
	//compare the old and new maps
	//check hit or miss
	
	return false;
}

bool fnc_print_game_winner(Battleship_ThreadParameter* thread_parameter)
{
	//get winner and print it
	return false;
}

bool fnc_print_2_game_maps(Battleship_ThreadParameter* thread_parameter)
{
	//get 2 cell maps and print it
	return false;
}

bool fnc_play_one_round(Battleship_ThreadParameter* thread_parameter)
{
	//first player place shot and check if it is available

	//check shot and select if it is a hit, then lock the cell

	//update ship's health

	//check win condition if we have a winner then switch the game phase, return

	//second player go and do the same things

	//check win condition if we have a winner then switch the game phase, return
	
	return false;
}

bool fnc_init_parameter_environment(Battleship_ThreadParameter* thread_parameter)
{
	//init parameter
	return false;
}

void fnc_start_session()
{
	//init sdl environment

	//create new parameter

	//user switch game phase

	//game menu

	//in game

	//result page	
}

void mock_start_test_session()
{
	//create a new parameter
	Battleship_ThreadParameter mock_tp_parameter;

	//init game environment
	fnc_init_parameter_environment(&mock_tp_parameter);
	
	
}
