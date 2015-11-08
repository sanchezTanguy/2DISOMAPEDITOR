#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "GRAPHICS_HANDLER.h"
#include "DATA_HANDLER.h"

int main()
{
	float mapBlocksW = 7;
	float mapBlocksH = 7;

	float tileW = 98;
	float tileH = 97;

	float screenWidth = (tileW * mapBlocksW) + (tileW*3);
	float screenHeight = (tileH * mapBlocksH) + (tileH/2) - (mapBlocksH * 2);

	GRAPHICS_HANDLER *GAME = new GRAPHICS_HANDLER("MMO", screenWidth, screenHeight);
	GAME->loadTextures();

	DATA_HANDLER *DATA = new DATA_HANDLER();
	DATA->newMap(mapBlocksW, mapBlocksH, 98, 97);
	DATA->addLayer();

	while(GAME->isRunning())
	{
		GAME->clear();
		GAME->drawMenu(DATA->getCurrentMap());

		GAME->listenEvents(DATA, DATA->getCurrentMap(), DATA->getCurrentLayerID());

		GAME->draw(DATA->getCurrentMap(), DATA->getCurrentLayerID());

		GAME->display();
	}

    return 0;
}
