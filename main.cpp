#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "GRAPHICS_HANDLER.h"
#include "DATA_HANDLER.h"

int main()
{
	GRAPHICS_HANDLER *GAME = new GRAPHICS_HANDLER("MMO", 800, 800);
	GAME->loadTextures();

	DATA_HANDLER *DATA = new DATA_HANDLER();
	DATA->newMap(7, 7, 98, 97);
	DATA->addLayer();

	while(GAME->isRunning())
	{
		GAME->clear();
		GAME->drawMenu(DATA->getCurrentMap());

		GAME->listenEvents(DATA, DATA->getCurrentMap(), DATA->getCurrentLayerID());

		GAME->draw(DATA->getCurrentMap());

		GAME->display();
	}

    return 0;
}
