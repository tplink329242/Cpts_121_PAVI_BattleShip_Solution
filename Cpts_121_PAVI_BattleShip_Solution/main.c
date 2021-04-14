#include "PAVI_render_function.h"


int main(int argc, char* argv[])
{
	
	
	//mock_start_test_session();


	//thread def
	Battleship_ThreadParameter* thread_parameter = malloc(sizeof(Battleship_ThreadParameter));
	Battleship_GamePhase game_phase = 0;
	bool battleship_num_close_requested = false;

	if (thread_parameter == NULL)
	{
		printf_s("init parameter failed!\n");
		return -1;
	}

	fnc_init_parameter_environment(thread_parameter);

	
	//create sdl thread
	SDL_Thread* thread_render = SDL_CreateThread(fnc_sdl_render_main, "Battleship Render Thread", thread_parameter);

	//start new game session
	thread_parameter->game_phase = BS_GAME_PHASE_MAIN_MENU;
	

	while (!battleship_num_close_requested)
	{
		//load data from shared memory
		SDL_LockMutex(thread_parameter->battleship_thd_bufferLock);
		battleship_num_close_requested = thread_parameter->battleship_num_close_requested;
		game_phase = thread_parameter->game_phase;
		SDL_UnlockMutex(thread_parameter->battleship_thd_bufferLock);

		switch (game_phase)
		{
		case BS_GAME_PHASE_DECIDE_WHO_GO_FIRST:
			break;
		default:;
		}
		
		SDL_Delay(1000 / 60);
	}
	

	
	
	
	return 0;
}
