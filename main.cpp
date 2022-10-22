#define SDL_MAIN_HANDLED

#include "game.hpp"

int main()
{
	Game* game = Game::instance();
	if (game!=nullptr)
		game->run();

	Game::release();
	return 0;
}

