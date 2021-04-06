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

bool fnc_ai_place_ship(Battleship_Cell cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH])
{
	//'c' for Carrier, 'b' for Battleship, 'r' for Cruiser, 's' for Submarine, or 'd' for Destroyer.

	bool is_AlreadyHaveAShip = false;
	Battleship_Direction ship_direction = horizontal;
	
	int rect_x = 0;
	int rect_y = 0;

	Battleship_ship array_ship[5];
	
	
	for (int i = 1; i <= GAME_BATTLESHIP_MAX_GAME_SHIP_NUM; ++i)
	{
		ship_direction = rand() % 2;
		array_ship[i - 1].direction = ship_direction;
		array_ship[i - 1].array_ship_location[0] = fnc_get_available_random_place(cell, i, ship_direction);
		fnc_update_cell_using_array_ship(cell, array_ship, i + 1);
	}	
	
	return true;
}

Battleship_Rect fnc_get_available_random_place(Battleship_Cell cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH], int ship_type, Battleship_Direction ship_direction)
{
	Battleship_Rect rect;
	bool is_AlreadyHaveAShip = false;

	//init rect
	rect.x = 0;
	rect.y = 0;

	
	switch (ship_type)
	{
	case SHIP_TYPE_CARRIER:
		if (ship_direction == horizontal)
		{
			do
			{
				is_AlreadyHaveAShip = false;
				
				rect.x = rand() % (9 - GAME_BATTLESHIP_HEALTH_CARRIER);
				rect.y = rand() % 9;

				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_CARRIER; ++i)
				{
					if (cell[rect.x + i][rect.y].is_ship_placed == true)
					{
						is_AlreadyHaveAShip = true;
						break;
					}
				}
				
			} while (is_AlreadyHaveAShip);
			
		}
		if (ship_direction == vertical)
		{
			do
			{
				is_AlreadyHaveAShip = false;
				
				rect.x = rand() % 9;
				rect.y = rand() % (9 - GAME_BATTLESHIP_HEALTH_CARRIER);

				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_CARRIER; ++i)
				{
					if (cell[rect.x][rect.y + i].is_ship_placed == true)
					{
						is_AlreadyHaveAShip = true;
					}
				}

			} while (is_AlreadyHaveAShip);
		
		}

		break;
	case SHIP_TYPE_BATTLESHIP:

		if (ship_direction == horizontal)
		{
			do
			{
				is_AlreadyHaveAShip = false;

				rect.x = rand() % (9 - GAME_BATTLESHIP_HEALTH_BATTLESHIP);
				rect.y = rand() % 9;

				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_BATTLESHIP; ++i)
				{
					if (cell[rect.x + i][rect.y].is_ship_placed == true)
					{
						is_AlreadyHaveAShip = true;
						break;
					}
				}

			} while (is_AlreadyHaveAShip);

		}
		if (ship_direction == vertical)
		{
			do
			{
				is_AlreadyHaveAShip = false;

				rect.x = rand() % 9;
				rect.y = rand() % (9 - GAME_BATTLESHIP_HEALTH_BATTLESHIP);

				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_BATTLESHIP; ++i)
				{
					if (cell[rect.x][rect.y + i].is_ship_placed == true)
					{
						is_AlreadyHaveAShip = true;
					}
				}

			} while (is_AlreadyHaveAShip);

		}

		break;
	case SHIP_TYPE_CRUISER:

		if (ship_direction == horizontal)
		{
			do
			{
				is_AlreadyHaveAShip = false;

				rect.x = rand() % (9 - GAME_BATTLESHIP_HEALTH_CRUISER);
				rect.y = rand() % 9;

				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_CRUISER; ++i)
				{
					if (cell[rect.x + i][rect.y].is_ship_placed == true)
					{
						is_AlreadyHaveAShip = true;
						break;
					}
				}

			} while (is_AlreadyHaveAShip);

		}
		if (ship_direction == vertical)
		{
			do
			{
				is_AlreadyHaveAShip = false;

				rect.x = rand() % 9;
				rect.y = rand() % (9 - GAME_BATTLESHIP_HEALTH_CRUISER);

				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_CRUISER; ++i)
				{
					if (cell[rect.x][rect.y + i].is_ship_placed == true)
					{
						is_AlreadyHaveAShip = true;
					}
				}

			} while (is_AlreadyHaveAShip);

		}

		break;
	case SHIP_TYPE_SUBMARINE:

		if (ship_direction == horizontal)
		{
			do
			{
				is_AlreadyHaveAShip = false;

				rect.x = rand() % (9 - GAME_BATTLESHIP_HEALTH_SUBMARINE);
				rect.y = rand() % 9;

				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_SUBMARINE; ++i)
				{
					if (cell[rect.x + i][rect.y].is_ship_placed == true)
					{
						is_AlreadyHaveAShip = true;
						break;
					}
				}

			} while (is_AlreadyHaveAShip);

		}
		if (ship_direction == vertical)
		{
			do
			{
				is_AlreadyHaveAShip = false;

				rect.x = rand() % 9;
				rect.y = rand() % (9 - GAME_BATTLESHIP_HEALTH_SUBMARINE);

				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_SUBMARINE; ++i)
				{
					if (cell[rect.x][rect.y + i].is_ship_placed == true)
					{
						is_AlreadyHaveAShip = true;
					}
				}

			} while (is_AlreadyHaveAShip);

		}

		break;
	case SHIP_TYPE_DESTROYER:

		if (ship_direction == horizontal)
		{
			do
			{
				is_AlreadyHaveAShip = false;

				rect.x = rand() % (9 - GAME_BATTLESHIP_HEALTH_DESTROYER);
				rect.y = rand() % 9;

				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_DESTROYER; ++i)
				{
					if (cell[rect.x + i][rect.y].is_ship_placed == true)
					{
						is_AlreadyHaveAShip = true;
						break;
					}
				}

			} while (is_AlreadyHaveAShip);

		}
		if (ship_direction == vertical)
		{
			do
			{
				is_AlreadyHaveAShip = false;

				rect.x = rand() % 9;
				rect.y = rand() % (9 - GAME_BATTLESHIP_HEALTH_DESTROYER);

				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_DESTROYER; ++i)
				{
					if (cell[rect.x][rect.y + i].is_ship_placed == true)
					{
						is_AlreadyHaveAShip = true;
					}
				}

			} while (is_AlreadyHaveAShip);

		}
		break;
	default:;
	}
	
	return rect;
}

void fnc_update_cell_using_array_ship(Battleship_Cell cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH], Battleship_ship array_ship[5], Battleship_ShipType ship_type)
{
	int rect_x = 0;
	int rect_y = 0;

	switch (ship_type)
	{
	case SHIP_TYPE_INIT:break;
	case SHIP_TYPE_CARRIER:
		for (int j = 0; j < GAME_BATTLESHIP_HEALTH_CARRIER; ++j)
		{
			if (array_ship[0].direction == vertical)
			{
				rect_x = array_ship[0].array_ship_location->x;
				rect_y = array_ship[0].array_ship_location->y + j;
				cell[rect_x][rect_y].char_ship_type = 'c';
				cell[rect_x][rect_y].is_ship_placed = true;
				cell[rect_x][rect_y].ship_type = SHIP_TYPE_CARRIER;
			}
			if (array_ship[0].direction == horizontal)
			{
				rect_x = array_ship[0].array_ship_location->x + j;
				rect_y = array_ship[0].array_ship_location->y;
				cell[rect_x][rect_y].char_ship_type = 'c';
				cell[rect_x][rect_y].is_ship_placed = true;
				cell[rect_x][rect_y].ship_type = SHIP_TYPE_CARRIER;
			}
		}
		break;
	case SHIP_TYPE_BATTLESHIP:
		for (int j = 0; j < GAME_BATTLESHIP_HEALTH_BATTLESHIP; ++j)
		{
			if (array_ship[1].direction == vertical)
			{
				rect_x = array_ship[1].array_ship_location->x;
				rect_y = array_ship[1].array_ship_location->y + j;
				cell[rect_x][rect_y].char_ship_type = 'b';
				cell[rect_x][rect_y].is_ship_placed = true;
				cell[rect_x][rect_y].ship_type = SHIP_TYPE_BATTLESHIP;
			}
			if (array_ship[1].direction == horizontal)
			{
				rect_x = array_ship[1].array_ship_location->x + j;
				rect_y = array_ship[1].array_ship_location->y;
				cell[rect_x][rect_y].char_ship_type = 'b';
				cell[rect_x][rect_y].is_ship_placed = true;
				cell[rect_x][rect_y].ship_type = SHIP_TYPE_BATTLESHIP;
			}
		}
		break;
	case SHIP_TYPE_CRUISER:
		for (int j = 0; j < GAME_BATTLESHIP_HEALTH_CRUISER; ++j)
		{
			if (array_ship[2].direction == vertical)
			{
				rect_x = array_ship[2].array_ship_location->x;
				rect_y = array_ship[2].array_ship_location->y + j;
				cell[rect_x][rect_y].char_ship_type = 'r';
				cell[rect_x][rect_y].is_ship_placed = true;
				cell[rect_x][rect_y].ship_type = SHIP_TYPE_CRUISER;
			}
			if (array_ship[1].direction == horizontal)
			{
				rect_x = array_ship[1].array_ship_location->x + j;
				rect_y = array_ship[1].array_ship_location->y;
				cell[rect_x][rect_y].char_ship_type = 'r';
				cell[rect_x][rect_y].is_ship_placed = true;
				cell[rect_x][rect_y].ship_type = SHIP_TYPE_CRUISER;
			}
		}
		break;
	case SHIP_TYPE_SUBMARINE:
		for (int j = 0; j < GAME_BATTLESHIP_HEALTH_SUBMARINE; ++j)
		{
			if (array_ship[2].direction == vertical)
			{
				rect_x = array_ship[2].array_ship_location->x;
				rect_y = array_ship[2].array_ship_location->y + j;
				cell[rect_x][rect_y].char_ship_type = 's';
				cell[rect_x][rect_y].is_ship_placed = true;
				cell[rect_x][rect_y].ship_type = SHIP_TYPE_SUBMARINE;
			}
			if (array_ship[1].direction == horizontal)
			{
				rect_x = array_ship[1].array_ship_location->x + j;
				rect_y = array_ship[1].array_ship_location->y;
				cell[rect_x][rect_y].char_ship_type = 's';
				cell[rect_x][rect_y].is_ship_placed = true;
				cell[rect_x][rect_y].ship_type = SHIP_TYPE_SUBMARINE;
			}
		}
		break;
	case SHIP_TYPE_DESTROYER:
		for (int j = 0; j < GAME_BATTLESHIP_HEALTH_DESTROYER; ++j)
		{
			if (array_ship[2].direction == vertical)
			{
				rect_x = array_ship[2].array_ship_location->x;
				rect_y = array_ship[2].array_ship_location->y + j;
				cell[rect_x][rect_y].char_ship_type = 'd';
				cell[rect_x][rect_y].is_ship_placed = true;
				cell[rect_x][rect_y].ship_type = SHIP_TYPE_DESTROYER;
			}
			if (array_ship[1].direction == horizontal)
			{
				rect_x = array_ship[1].array_ship_location->x + j;
				rect_y = array_ship[1].array_ship_location->y;
				cell[rect_x][rect_y].char_ship_type = 'd';
				cell[rect_x][rect_y].is_ship_placed = true;
				cell[rect_x][rect_y].ship_type = SHIP_TYPE_DESTROYER;
			}
		}
		break;
	default:
		/// <summary>
		/// place a ship
		/// </summary>
		/// <param name="cell"></param>
		/// <param name="array_ship"></param>
		/// <param name="ship_type"></param>
		break;
	}
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
	//get game round array for loop for printing
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
	//game round ++
	
	//first player place shot and check if it is available

	//check shot and select if it is a hit, then lock the cell

	//update ship's health

	//check win condition if we have a winner then switch the game phase, return

	//second player go and do the same things

	//apply it to parameter

	//check win condition if we have a winner then switch the game phase, return
	
	return false;
}

bool fnc_init_parameter_environment(Battleship_ThreadParameter* thread_parameter)
{
	//init parameter

	//init player and ai cell
	fnc_init_battleship_cell(thread_parameter->cell_player);
	fnc_init_battleship_cell(thread_parameter->cell_ai);

	//init thread lock
	thread_parameter->battleship_thd_bufferLock = SDL_CreateMutex();
	thread_parameter->battleship_thd_canConsume = SDL_CreateCond();
	thread_parameter->battleship_thd_canProduce = SDL_CreateCond();

	//thread lock bool
	//thread lock
	thread_parameter->battleship_is_consumer_go = false;
	thread_parameter->battleship_is_producer_go = false;
	
	return true;
}

void fnc_init_battleship_cell(Battleship_Cell cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH])
{
	int cell_id = 0;
	for (int i = 0; i < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++i)
	{
		for (int j = 0; j < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++j)
		{
			//arrange the id
			cell_id++;
			cell[i][j].cell_id = cell_id;
			cell[i][j].is_Hit = false;
			cell[i][j].is_ship_placed = false;
			cell[i][j].char_ship_type = '\0';
			cell[i][j].ship_type = SHIP_TYPE_INIT;
			cell[i][j].rect.x = i;
			cell[i][j].rect.y = j;
		}
	}
	
}

void fnc_sync_data(Battleship_ThreadParameter* thread_parameter)
{
	
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

	//place ship for both side

	
	
	
}
