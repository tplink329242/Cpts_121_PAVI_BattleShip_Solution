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

	Battleship_ship array_ship[5] = {'0'};
	
	
	for (int i = 1; i <= GAME_BATTLESHIP_MAX_GAME_SHIP_NUM; ++i)
	{
		ship_direction = rand() % 2;
		array_ship[i - 1].direction = ship_direction;
		array_ship[i - 1].ship_type = i;
		array_ship[i - 1].array_ship_location = fnc_get_available_random_place(cell, i, ship_direction);
		fnc_update_cell_using_array_ship(cell, array_ship[i - 1], i);
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
		if (ship_direction == vertical)
		{
			do
			{
				is_AlreadyHaveAShip = false;
				
				rect.x = rand() % (11 - GAME_BATTLESHIP_HEALTH_CARRIER);
				rect.y = rand() % 9;

				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_CARRIER; ++i)
				{
					if (cell[rect.x + i][rect.y].is_ship_placed == true)
					{
						is_AlreadyHaveAShip = true;
						break;
					}
				}
				
			} while (is_AlreadyHaveAShip == true);
			
		}
		if (ship_direction == horizontal)
		{
			do
			{
				is_AlreadyHaveAShip = false;
				
				rect.x = rand() % 9;
				rect.y = rand() % (11 - GAME_BATTLESHIP_HEALTH_CARRIER);

				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_CARRIER; ++i)
				{
					if (cell[rect.x][rect.y + i].is_ship_placed == true)
					{
						is_AlreadyHaveAShip = true;
					}
				}

			} while (is_AlreadyHaveAShip == true);
		
		}

		break;
	case SHIP_TYPE_BATTLESHIP:

		if (ship_direction == vertical)
		{
			do
			{
				is_AlreadyHaveAShip = false;

				rect.x = rand() % (11 - GAME_BATTLESHIP_HEALTH_BATTLESHIP);
				rect.y = rand() % 9;

				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_BATTLESHIP; ++i)
				{
					if (cell[rect.x + i][rect.y].is_ship_placed == true)
					{
						is_AlreadyHaveAShip = true;
					}
				}

			} while (is_AlreadyHaveAShip == true);

		}
		if (ship_direction == horizontal)
		{
			do
			{
				is_AlreadyHaveAShip = false;

				rect.x = rand() % 9;
				rect.y = rand() % (11 - GAME_BATTLESHIP_HEALTH_BATTLESHIP);

				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_BATTLESHIP; ++i)
				{
					if (cell[rect.x][rect.y + i].is_ship_placed == true)
					{
						is_AlreadyHaveAShip = true;
						break;
					}
				}

			} while (is_AlreadyHaveAShip == true);

		}

		break;
	case SHIP_TYPE_CRUISER:

		if (ship_direction == vertical)
		{
			do
			{
				is_AlreadyHaveAShip = false;

				rect.x = rand() % (11 - GAME_BATTLESHIP_HEALTH_CRUISER);
				rect.y = rand() % 9;

				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_CRUISER; ++i)
				{
					if (cell[rect.x + i][rect.y].is_ship_placed == true)
					{
						is_AlreadyHaveAShip = true;
						break;
					}
				}

			} while (is_AlreadyHaveAShip == true);

		}
		if (ship_direction == horizontal)
		{
			do
			{
				is_AlreadyHaveAShip = false;

				rect.x = rand() % 9;
				rect.y = rand() % (11 - GAME_BATTLESHIP_HEALTH_CRUISER);

				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_CRUISER; ++i)
				{
					if (cell[rect.x][rect.y + i].is_ship_placed == true)
					{
						is_AlreadyHaveAShip = true;
					}
				}

			} while (is_AlreadyHaveAShip == true);

		}

		break;
	case SHIP_TYPE_SUBMARINE:

		if (ship_direction == vertical)
		{
			do
			{
				is_AlreadyHaveAShip = false;

				rect.x = rand() % (11 - GAME_BATTLESHIP_HEALTH_SUBMARINE);
				rect.y = rand() % 9;

				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_SUBMARINE; ++i)
				{
					if (cell[rect.x + i][rect.y].is_ship_placed == true)
					{
						is_AlreadyHaveAShip = true;
						break;
					}
				}

			} while (is_AlreadyHaveAShip == true);

		}
		if (ship_direction == horizontal)
		{
			do
			{
				is_AlreadyHaveAShip = false;

				rect.x = rand() % 9;
				rect.y = rand() % (11 - GAME_BATTLESHIP_HEALTH_SUBMARINE);

				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_SUBMARINE; ++i)
				{
					if (cell[rect.x][rect.y + i].is_ship_placed == true)
					{
						is_AlreadyHaveAShip = true;
					}
				}

			} while (is_AlreadyHaveAShip == true);

		}

		break;
	case SHIP_TYPE_DESTROYER:

		if (ship_direction == vertical)
		{
			do
			{
				is_AlreadyHaveAShip = false;

				rect.x = rand() % (11 - GAME_BATTLESHIP_HEALTH_DESTROYER);
				rect.y = rand() % 9;

				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_DESTROYER; ++i)
				{
					if (cell[rect.x + i][rect.y].is_ship_placed == true)
					{
						is_AlreadyHaveAShip = true;
						break;
					}
				}

			} while (is_AlreadyHaveAShip == true);

		}
		if (ship_direction == horizontal)
		{
			do
			{
				is_AlreadyHaveAShip = false;

				rect.x = rand() % 9;
				rect.y = rand() % (11 - GAME_BATTLESHIP_HEALTH_DESTROYER);

				for (int i = 0; i < GAME_BATTLESHIP_HEALTH_DESTROYER; ++i)
				{
					if (cell[rect.x][rect.y + i].is_ship_placed == true)
					{
						is_AlreadyHaveAShip = true;
						break;
					}
				}

			} while (is_AlreadyHaveAShip == true);

		}
		break;
	default:;
	}
	
	return rect;
}

void fnc_update_cell_using_array_ship(Battleship_Cell cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH], Battleship_ship array_ship, Battleship_ShipType ship_type)
{
	int rect_x = 0;
	int rect_y = 0;

	switch (ship_type)
	{
	case SHIP_TYPE_INIT:break;
	case SHIP_TYPE_CARRIER:
		for (int j = 0; j < GAME_BATTLESHIP_HEALTH_CARRIER; ++j)
		{
			if (array_ship.direction == horizontal)
			{
				rect_x = array_ship.array_ship_location.x;				
				rect_y = array_ship.array_ship_location.y + j;
				cell[rect_x][rect_y].char_ship_type = 'c';
				cell[rect_x][rect_y].is_ship_placed = true;
				cell[rect_x][rect_y].ship_type = SHIP_TYPE_CARRIER;
			}
			if (array_ship.direction == vertical)
			{
				rect_x = array_ship.array_ship_location.x + j;
				rect_y = array_ship.array_ship_location.y;
				cell[rect_x][rect_y].char_ship_type = 'c';
				cell[rect_x][rect_y].is_ship_placed = true;
				cell[rect_x][rect_y].ship_type = SHIP_TYPE_CARRIER;
			}
		}
		break;
	case SHIP_TYPE_BATTLESHIP:
		for (int j = 0; j < GAME_BATTLESHIP_HEALTH_BATTLESHIP; ++j)
		{
			if (array_ship.direction == horizontal)
			{
				rect_x = array_ship.array_ship_location.x;
				rect_y = array_ship.array_ship_location.y + j;
				cell[rect_x][rect_y].char_ship_type = 'b';
				cell[rect_x][rect_y].is_ship_placed = true;
				cell[rect_x][rect_y].ship_type = SHIP_TYPE_BATTLESHIP;
			}
			if (array_ship.direction == vertical)
			{
				rect_x = array_ship.array_ship_location.x + j;
				rect_y = array_ship.array_ship_location.y;
				cell[rect_x][rect_y].char_ship_type = 'b';
				cell[rect_x][rect_y].is_ship_placed = true;
				cell[rect_x][rect_y].ship_type = SHIP_TYPE_BATTLESHIP;
			}
		}
		break;
	case SHIP_TYPE_CRUISER:
		for (int j = 0; j < GAME_BATTLESHIP_HEALTH_CRUISER; ++j)
		{
			if (array_ship.direction == horizontal)
			{
				rect_x = array_ship.array_ship_location.x;
				rect_y = array_ship.array_ship_location.y + j;
				cell[rect_x][rect_y].char_ship_type = 'r';
				cell[rect_x][rect_y].is_ship_placed = true;
				cell[rect_x][rect_y].ship_type = SHIP_TYPE_CRUISER;
			}
			if (array_ship.direction == vertical)
			{
				rect_x = array_ship.array_ship_location.x + j;
				rect_y = array_ship.array_ship_location.y;
				cell[rect_x][rect_y].char_ship_type = 'r';
				cell[rect_x][rect_y].is_ship_placed = true;
				cell[rect_x][rect_y].ship_type = SHIP_TYPE_CRUISER;
			}
		}
		break;
	case SHIP_TYPE_SUBMARINE:
		for (int j = 0; j < GAME_BATTLESHIP_HEALTH_SUBMARINE; ++j)
		{
			if (array_ship.direction == horizontal)
			{
				rect_x = array_ship.array_ship_location.x;
				rect_y = array_ship.array_ship_location.y + j;
				cell[rect_x][rect_y].char_ship_type = 's';
				cell[rect_x][rect_y].is_ship_placed = true;
				cell[rect_x][rect_y].ship_type = SHIP_TYPE_SUBMARINE;
			}
			if (array_ship.direction == vertical)
			{
				rect_x = array_ship.array_ship_location.x + j;
				rect_y = array_ship.array_ship_location.y;
				cell[rect_x][rect_y].char_ship_type = 's';
				cell[rect_x][rect_y].is_ship_placed = true;
				cell[rect_x][rect_y].ship_type = SHIP_TYPE_SUBMARINE;
			}
		}
		break;
	case SHIP_TYPE_DESTROYER:
		for (int j = 0; j < GAME_BATTLESHIP_HEALTH_DESTROYER; ++j)
		{
			if (array_ship.direction == horizontal)
			{
				rect_x = array_ship.array_ship_location.x;
				rect_y = array_ship.array_ship_location.y + j;
				cell[rect_x][rect_y].char_ship_type = 'd';
				cell[rect_x][rect_y].is_ship_placed = true;
				cell[rect_x][rect_y].ship_type = SHIP_TYPE_DESTROYER;
			}
			if (array_ship.direction == vertical)
			{
				rect_x = array_ship.array_ship_location.x + j;
				rect_y = array_ship.array_ship_location.y;
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

Battleship_PlayerType fnc_select_who_starts_first()
{
	const Battleship_PlayerType type = rand() % 2;
	return type;
}

bool fnc_check_shot(Battleship_Cell cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH], Battleship_Rect hit_rect)
{
	//return if it is a hit
	if (cell[hit_rect.x][hit_rect.y].is_ship_placed == true)
	{
		return true;
	}
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

	//init close request
	thread_parameter->battleship_num_close_requested = false;

	//init ship health
	thread_parameter->array_health_ai_battleship[0] = 0;
	thread_parameter->array_health_ai_battleship[1] = 5;
	thread_parameter->array_health_ai_battleship[2] = 4;
	thread_parameter->array_health_ai_battleship[3] = 3;
	thread_parameter->array_health_ai_battleship[4] = 3;
	thread_parameter->array_health_ai_battleship[5] = 2;
	
	thread_parameter->array_health_player_battleship[0] = 0;
	thread_parameter->array_health_player_battleship[1] = 5;
	thread_parameter->array_health_player_battleship[2] = 4;
	thread_parameter->array_health_player_battleship[3] = 3;
	thread_parameter->array_health_player_battleship[4] = 3;
	thread_parameter->array_health_player_battleship[5] = 2;

	thread_parameter->static_player.num_hit = 0;
	thread_parameter->static_player.num_miss = 0;
	thread_parameter->static_player.num_total_shots = 0;
	thread_parameter->static_player.ratio_miss = 0.0;

	thread_parameter->static_ai.num_hit = 0;
	thread_parameter->static_ai.num_miss = 0;
	thread_parameter->static_ai.num_total_shots = 0;
	thread_parameter->static_ai.ratio_miss = 0.0;

	//init game phase
	thread_parameter->game_phase = BS_GAME_PHASE_INIT;
	
	
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
			cell[i][j].char_ship_type = '-';
			cell[i][j].ship_type = SHIP_TYPE_INIT;
			cell[i][j].rect.x = i;
			cell[i][j].rect.y = j;
		}
	}
	
}

Battleship_Rect fnc_ai_attack_cell(Battleship_Cell cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH])
{
	Battleship_Rect rect_hit = {0, 0};
	bool is_already_hit = false;
	do
	{
		is_already_hit = false;
		
		rect_hit.x = rand() % 10;
		rect_hit.y = rand() % 10;
		if (cell[rect_hit.x][rect_hit.y].is_Hit == true)
		{
			is_already_hit = true;
		}		
	}
	while (is_already_hit == true);

	cell[rect_hit.x][rect_hit.y].is_Hit = true;

	//modify char as a * mark
	cell[rect_hit.x][rect_hit.y].char_ship_type = '*';

	return rect_hit;	
}

void fnc_player_attack_cell(Battleship_Cell cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH], Battleship_Rect rect_hit)
{
	cell[rect_hit.x][rect_hit.y].is_Hit = true;

	//modify char as a * mark
	cell[rect_hit.x][rect_hit.y].char_ship_type = '*';
}

void fnc_update_battleship_health(Battleship_Cell cell[GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH][GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH], int* array_health_player_battleship)
{


	int* health_init = array_health_player_battleship;
	*health_init = 0;
	array_health_player_battleship++;

	

	int* health_carrier = array_health_player_battleship;
	*array_health_player_battleship = GAME_BATTLESHIP_HEALTH_CARRIER;
	array_health_player_battleship++;

	int* ship_ptr = health_carrier;
	

	int* health_battleship = array_health_player_battleship;
	*array_health_player_battleship = GAME_BATTLESHIP_HEALTH_BATTLESHIP;
	array_health_player_battleship++;

	int* health_cruiser = array_health_player_battleship;
	*array_health_player_battleship = GAME_BATTLESHIP_HEALTH_CRUISER;
	array_health_player_battleship++;

	int* health_submarine = array_health_player_battleship;
	*array_health_player_battleship = GAME_BATTLESHIP_HEALTH_SUBMARINE;
	array_health_player_battleship++;

	int* health_destroyer = array_health_player_battleship;
	*array_health_player_battleship = GAME_BATTLESHIP_HEALTH_DESTROYER;

	array_health_player_battleship = health_init;
	
	
	//init health
	//*array_health_player_battleship = 0;
	/*array_health_player_battleship++;
	*array_health_player_battleship = GAME_BATTLESHIP_HEALTH_CARRIER;
	array_health_player_battleship++;
	*array_health_player_battleship = GAME_BATTLESHIP_HEALTH_BATTLESHIP;
	array_health_player_battleship++;
	*array_health_player_battleship = GAME_BATTLESHIP_HEALTH_CRUISER;
	array_health_player_battleship++;
	*array_health_player_battleship = GAME_BATTLESHIP_HEALTH_SUBMARINE;
	array_health_player_battleship++;
	*array_health_player_battleship = GAME_BATTLESHIP_HEALTH_DESTROYER;

	array_health_player_battleship -= 5;*/

	
	/*array_health_player_battleship[SHIP_TYPE_CARRIER] = GAME_BATTLESHIP_HEALTH_CARRIER;
	array_health_player_battleship[SHIP_TYPE_BATTLESHIP] = GAME_BATTLESHIP_HEALTH_BATTLESHIP;
	array_health_player_battleship[SHIP_TYPE_CRUISER] = GAME_BATTLESHIP_HEALTH_CRUISER;
	array_health_player_battleship[SHIP_TYPE_SUBMARINE] = GAME_BATTLESHIP_HEALTH_SUBMARINE;
	array_health_player_battleship[SHIP_TYPE_DESTROYER] = GAME_BATTLESHIP_HEALTH_DESTROYER;*/

	

	int num_count = 0;

	for (int i = 0; i < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++i)
	{
		for (int j = 0; j < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++j)
		{
			if (cell[i][j].is_ship_placed == true)
			{
				if (cell[i][j].is_Hit == true)
				{
					switch (cell[i][j].ship_type)
					{
					case SHIP_TYPE_CARRIER:
						(*health_carrier)--;
						break;
					case SHIP_TYPE_BATTLESHIP:
						(*health_battleship)--;
						break;
					case SHIP_TYPE_CRUISER:
						(*health_cruiser)--;
						break;
					case SHIP_TYPE_SUBMARINE:
						(*health_submarine)--;
						break;
					case SHIP_TYPE_DESTROYER:
						(*health_destroyer)--;
						break;
					default:;
						//printf_s("unknown ship type!\n");		
					}					
				}				
			}
		}
	}

	//check winner condition
	for (int i = 1; i < 6; ++i)
	{
		if (*ship_ptr == 0)
		{
			num_count++;
		}
		ship_ptr++;
	}

	if (num_count == 5)
	{
		*health_init = 1;
	}	
}

void fnc_sync_data(Battleship_ThreadParameter* thread_parameter)
{
	//update map about ship health and winner
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
	//open a output file
	FILE* outfile = fnc_open_file("output.dat", "w");

	
	//create a new parameter
	Battleship_ThreadParameter mock_tp_parameter;

	//init game environment
	fnc_init_parameter_environment(&mock_tp_parameter);

	//place ship for both side
	fnc_ai_place_ship(mock_tp_parameter.cell_ai);
	fnc_ai_place_ship(mock_tp_parameter.cell_player);

	mock_test_session_map(&mock_tp_parameter);

	//decide who go first
	mock_tp_parameter.who_go_first = fnc_select_who_starts_first();

	//define 1 round var, 0 player win, 1 ai win
	int winner = -1;
	Battleship_Rect rect_hit;
	bool is_ai_hit = false;
	bool is_Player_hit = false;

	//health ptr test
	int* health_player_ptr = mock_tp_parameter.array_health_player_battleship;
	int* health_ai_ptr = mock_tp_parameter.array_health_ai_battleship;


	//define round count
	int num_round = 0;
	//int num_hit = 0;
	//int num_miss = 0;
	

	//print original map
	fnc_output_session_map(&mock_tp_parameter, outfile);
	

	while (winner == -1)
	{
		//reset flag
		is_ai_hit = false;
		is_Player_hit = false;

		num_round++;

		//fprint game round number
		fprintf(outfile, "Game Round %d !\n", num_round);

		
		//player go first
		if (mock_tp_parameter.who_go_first == player)
		{
			//hit will need return rect to judge if hit
			rect_hit = fnc_ai_attack_cell(mock_tp_parameter.cell_ai);
			is_Player_hit = fnc_check_shot(mock_tp_parameter.cell_ai, rect_hit);
			if (is_Player_hit)
			{
				printf_s("\nIt is a player hit!");

				//fprint game rect result
				fprintf(outfile, "(%d, %d) is a player hit!\n", rect_hit.x, rect_hit.y);


				//static data update
				mock_tp_parameter.static_player.num_hit++;
				
				
				fnc_update_battleship_health(mock_tp_parameter.cell_ai, health_ai_ptr);

				
				//check if we have a winner
				if (mock_tp_parameter.array_health_ai_battleship[0] == 1)
				{
					winner = 0;
					break;
				}
				
			}
			else
			{
				printf_s("\nIt is a player miss!");

				//fprint game rect result
				fprintf(outfile, "(%d, %d) is a player miss!\n", rect_hit.x, rect_hit.y);

				//static data update
				mock_tp_parameter.static_player.num_miss++;

				
			}

				
			//ai go then
			rect_hit = fnc_ai_attack_cell(mock_tp_parameter.cell_player);
			is_ai_hit = fnc_check_shot(mock_tp_parameter.cell_player, rect_hit);
			if (is_ai_hit)
			{
				printf_s("\nIt is a ai hit!");
				fnc_update_battleship_health(mock_tp_parameter.cell_player, health_player_ptr);


				//fprint game rect result
				fprintf(outfile, "(%d, %d) is a ai hit!\n", rect_hit.x, rect_hit.y);


				//static data update
				mock_tp_parameter.static_ai.num_hit++;

						

				if (mock_tp_parameter.array_health_player_battleship[0] == 1)
				{
					winner = 1;
					break;
				}

			}
			else
			{
				printf_s("\nIt is a ai miss!");


				//fprint game rect result
				fprintf(outfile, "(%d, %d) is a ai miss!\n", rect_hit.x, rect_hit.y);

				//static data update
				mock_tp_parameter.static_ai.num_miss++;
				
			}
			
		}
	
		else
		{
			//ai go first
			rect_hit = fnc_ai_attack_cell(mock_tp_parameter.cell_player);
			is_ai_hit = fnc_check_shot(mock_tp_parameter.cell_player, rect_hit);
			if (is_ai_hit)
			{
				printf_s("\nIt is a ai hit!");
				fnc_update_battleship_health(mock_tp_parameter.cell_player, health_player_ptr);


				//fprint game rect result
				fprintf(outfile, "(%d, %d) is a ai hit!\n", rect_hit.x, rect_hit.y);


				//static data update
				mock_tp_parameter.static_ai.num_hit++;

				

				if (mock_tp_parameter.array_health_player_battleship[0] == 1)
				{
					winner = 1;
					break;
				}
			}
			else
			{
				printf_s("\nIt is a ai miss!");


				//fprint game rect result
				fprintf(outfile, "(%d, %d) is a ai miss!\n", rect_hit.x, rect_hit.y);

				//static data update
				mock_tp_parameter.static_ai.num_miss++;

				
			}

			//player go then
			rect_hit = fnc_ai_attack_cell(mock_tp_parameter.cell_ai);
			is_Player_hit = fnc_check_shot(mock_tp_parameter.cell_ai, rect_hit);
			if (is_Player_hit)
			{
				printf_s("\nIt is a player hit!");
				fnc_update_battleship_health(mock_tp_parameter.cell_ai, health_ai_ptr);


				//fprint game rect result
				fprintf(outfile, "(%d, %d) is a player hit!\n", rect_hit.x, rect_hit.y);


				//static data update
				mock_tp_parameter.static_player.num_hit++;


				

				if (mock_tp_parameter.array_health_ai_battleship[0] == 1)
				{
					winner = 0;
					break;
				}

			}
			else
			{
				printf_s("\nIt is a player miss!");

				
				//fprint game rect result
				fprintf(outfile, "(%d, %d) is a player miss!\n", rect_hit.x, rect_hit.y);

				//static data update
				mock_tp_parameter.static_player.num_miss++;

				
			}

		}
		
	}

	if (winner == 0)
	{
		printf_s("\nPlayer win!\n");

		//fprint game winner
		fprintf(outfile, "The winner is player\n");
		
	}
	else if(winner == 1)
	{
		printf_s("\nAI win!\n");

		//fprint game winner
		fprintf(outfile, "The winner is AI\n");
		
	}

	//total static update
	mock_tp_parameter.static_player.num_total_shots = num_round;
	mock_tp_parameter.static_player.ratio_miss = mock_tp_parameter.static_player.num_miss / (double)num_round;
	
	mock_tp_parameter.static_ai.num_total_shots = num_round;
	mock_tp_parameter.static_ai.ratio_miss = mock_tp_parameter.static_ai.num_miss / (double)num_round;


	//fprint map and static
	mock_test_session_map(&mock_tp_parameter);
	
	//print final map
	fnc_output_session_map(&mock_tp_parameter, outfile);	
	fnc_output_players_static(&mock_tp_parameter, outfile);

	fclose(outfile);
}

void mock_test_session_map(Battleship_ThreadParameter* thread_parameter)
{
	printf_s("*********************** AI Map **************************\n");
	printf_s("   0  1  2  3  4  5  6  7  8  9 \n");
	
	for (int i = 0; i < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++i)
	{
		printf_s("%d:", i);
		for (int j = 0; j < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++j)
		{
			
			printf_s("|%c|", thread_parameter->cell_ai[i][j].char_ship_type);
		}
		printf_s("\n");
	}
	printf_s("*********************************************************\n");
	printf_s("*********************** Player Map ********************\n");
	printf_s("   0  1  2  3  4  5  6  7  8  9 \n");

	for (int i = 0; i < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++i)
	{
		printf_s("%d:", i);
		for (int j = 0; j < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++j)
		{

			printf_s("|%c|", thread_parameter->cell_player[i][j].char_ship_type);
		}
		printf_s("\n");
	}
	printf_s("*********************************************************\n");
}

FILE* fnc_open_file(char* file_name, char* file_access)
{
	FILE* infile = NULL;
	infile = fopen(file_name, file_access);
	if (infile == NULL)
	{
		perror("Error: ");
		return NULL;
	}

	//printf("Opening success\n");
	return infile;
}

void fnc_output_session_map(Battleship_ThreadParameter* thread_parameter, FILE* outfile)
{
	//AI map
	fprintf(outfile, "*********************** AI Map ********************\n");
	fprintf(outfile, "   0  1  2  3  4  5  6  7  8  9 \n");

	for (int i = 0; i < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++i)
	{
		fprintf(outfile, "%d:", i);
		for (int j = 0; j < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++j)
		{

			fprintf(outfile, "|%c|", thread_parameter->cell_ai[i][j].char_ship_type);
		}
		fprintf(outfile, "\n");
	}

	fprintf(outfile, "\n");
	fprintf(outfile, "**************************************************\n");
	fprintf(outfile, "\n");
	
	//Player map
	fprintf(outfile, "************* Player Map *************************\n");
	fprintf(outfile, "   0  1  2  3  4  5  6  7  8  9 \n");

	for (int i = 0; i < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++i)
	{
		fprintf(outfile, "%d:", i);
		for (int j = 0; j < GAME_BATTLESHIP_MAX_GAME_MAP_LENGTH; ++j)
		{

			fprintf(outfile, "|%c|", thread_parameter->cell_player[i][j].char_ship_type);
		}
		fprintf(outfile, "\n");
	}
	fprintf(outfile, "**************************************************\n");	
}

void fnc_output_players_static(Battleship_ThreadParameter* thread_parameter, FILE* outfile)
{
	//print total statics
	fprintf(outfile, "*******Output information***********************\n");
	fprintf(outfile, "*******Player Information***********************\n");
	fprintf(outfile, "******Total shots: %d\n", thread_parameter->static_player.num_total_shots);
	fprintf(outfile, "******Total hits: %d\n", thread_parameter->static_player.num_hit);
	fprintf(outfile, "******Total miss: %d\n", thread_parameter->static_player.num_miss);
	fprintf(outfile, "******Miss Ratio: %.2lf\n", thread_parameter->static_player.ratio_miss);
	fprintf(outfile, "**************************************************\n");
	
	fprintf(outfile, "\n");
	
	fprintf(outfile, "*******AI Information***********************\n");
	fprintf(outfile, "******Total shots: %d\n", thread_parameter->static_ai.num_total_shots);
	fprintf(outfile, "******Total hits: %d\n", thread_parameter->static_ai.num_hit);
	fprintf(outfile, "******Total miss: %d\n", thread_parameter->static_ai.num_miss);
	fprintf(outfile, "******Miss Ratio: %.2lf\n", thread_parameter->static_ai.ratio_miss);
	fprintf(outfile, "**************************************************\n");
}
