#include <iostream>
#include"manager.h"
#include"game_manager.h"

int main() {
	GameManager* instance = GameManager::instance();

	std::cout << "helloworld" << std::endl;
	return 0;
}