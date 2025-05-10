#define SDL_MAIN_HANDLED
#include "game_manager.h"

int main(int argc,char** argv) {

	GameManager* instance = static_cast<GameManager*>(GameManager::instance());
	instance->run(argc, argv);
	return 0;
	
}