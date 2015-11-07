/*
 * GRAPHICS_HANDLER.cpp
 *
 *  Created on: 5 nov. 2015
 *      Author: user
 */

#include "GRAPHICS_HANDLER.h"

GRAPHICS_HANDLER::GRAPHICS_HANDLER(sf::String title, float width, float height) {
	screenWidth = width;
	screenHeight = height;

	window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), title);

	nbrTypesTile = 5;

	mouseX = 0;
	mouseY = 0;

	currentTexture = 1; //default

	addLayerButton.x = screenWidth/2;
	addLayerButton.y = 0;
}

//Integer to String converstion function
std::string GRAPHICS_HANDLER::intToString(int i)
{
     std::ostringstream oss;
     oss << i;
     return oss.str();
}


sf::Sprite GRAPHICS_HANDLER::loadImg(sf::String path, float x, float y)
{
	if (!textureTMP.loadFromFile(path))
	{
		//...
	}

	spriteTMP.setTexture(textureTMP);
	spriteTMP.setPosition(x, y);

	return spriteTMP;
}


map GRAPHICS_HANDLER::setTile(map mapTMP, int layerID, int tileID, int texture)
{
	mapTMP.layers[layerID].tiles[tileID].texture = texture;
	return mapTMP;
}

bool GRAPHICS_HANDLER::isRunning()
{
	if(window->isOpen())
		return true;
	else
		return false;
}

void GRAPHICS_HANDLER::clear()
{
	window->clear();
}

void GRAPHICS_HANDLER::listenEvents(DATA_HANDLER * DATAREF, map currentMap, int currentLayerID)
{
	float tileX = 0;
	float tileY = 0;

	float tileISOx = 0;
	float tileISOy = 0;

	int currentMapNbrTiles = currentMap.nbrTiles;

	int tileWidth = currentMap.tileSize.width;
	int tileHeight = currentMap.tileSize.height;

    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();

        if(event.type == sf::Event::MouseButtonPressed)
        {
        	if(event.mouseButton.button == sf::Mouse::Left)
        	{
        		mouseX = event.mouseButton.x;
        		mouseY = event.mouseButton.y;
    			//DO NOT WORK -------------------------------->
        		offsetLayer = currentMap.tileSize.height / 2;
        		offsetLeft = currentMap.dim.width / 1.95;
        		offsetTop = currentMap.dim.height / 1.8;
        		currentZLayer = currentLayerID * offsetLayer;
    			//<-------------------------------- DO NOT WORK

        		mouseISOx = (mouseX - mouseY) + offsetLayer;
        		mouseISOy = (((mouseX + mouseY) / 2) - currentZLayer) + offsetTop;

				std::cout << "(" << mouseX << ", " << mouseY << ")" << std::endl;

        		for(int tile = 0; tile < currentMapNbrTiles; tile++)
        		{
        			//do not work !
        			tileX = currentMap.layers[currentLayerID].tiles[tile].rawcoords.x;
        			tileY = currentMap.layers[currentLayerID].tiles[tile].rawcoords.y;

        			tileISOx = currentMap.layers[currentLayerID].tiles[tile].isocoords.x;
        			tileISOy = currentMap.layers[currentLayerID].tiles[tile].isocoords.y;

        			if(mouseX >= tileISOx + offsetLeft && mouseX <= (tileISOx + tileWidth)+offsetLeft && mouseY >= (tileISOy - currentZLayer)+offsetTop && mouseY <= ((tileISOy + tileHeight)-currentZLayer)+offsetTop)
        			{
        				std::cout << "tile " << tile << std::endl;

        				DATAREF->setMap(currentMap.ID, setTile(currentMap, currentLayerID, tile, currentTexture));
        			}
        		}

        		for(int T = 0; T < textures.size(); T++)
        		{
        			if(mouseX >= texturesMenuCoordinates[T].x && mouseX <= texturesMenuCoordinates[T].x + currentMap.tileSize.width && mouseY >= texturesMenuCoordinates[T].y && mouseY <= texturesMenuCoordinates[T].y + currentMap.tileSize.height)
        			{
        				currentTexture = T;
        			}
        		}

    			if(mouseX >= addLayerButton.x && mouseX <= addLayerButton.x + tileWidth && mouseY >= addLayerButton.y && mouseY <= addLayerButton.y + tileHeight)
    			{
    				DATAREF->addLayer();
    			}
        	}
        }
    }

}

//...

void GRAPHICS_HANDLER::draw(map currentMap)
{
	//add layer button
	window->draw(loadImg("tiles/al.png", addLayerButton.x, addLayerButton.y));

	int nbrTiles = currentMap.nbrTiles;
	int nbrLayers = currentMap.layers.size();

	offsetLayer = currentMap.tileSize.height / 2;
	offsetLeft = currentMap.dim.width / 1.95;
	offsetTop = currentMap.dim.height / 1.8;

	int zLayer = 0;

	float isoX = 0;
	float isoY = 0;

	int texture = 0;

	sf::String path;

	for(int layer = 0; layer < nbrLayers; layer++)
	{
		zLayer = layer * offsetLayer;

		for(int tile = 0; tile < nbrTiles; tile++)
		{
			texture = currentMap.layers[layer].tiles[tile].texture;
			path = "tiles/" + intToString(texture) + ".png";

			isoX = currentMap.layers[layer].tiles[tile].isocoords.x + offsetLeft;
			isoY = (currentMap.layers[layer].tiles[tile].isocoords.y - zLayer) + offsetTop;

			window->draw(loadImg(path, isoX, isoY));
		}
	}
}

void GRAPHICS_HANDLER::drawMenu(map currentMap)
{
	float x = 0;
	float y = 0;

	coordinates coordsTMP;

	for(int T = 0; T < nbrTypesTile; T++)
	{
		spriteTMP.setTexture(textures[T]);
		spriteTMP.setPosition(x, y);

		window->draw(spriteTMP);

		coordsTMP.x = x;
		coordsTMP.y = y;
		texturesMenuCoordinates.push_back(coordsTMP);

		y += currentMap.tileSize.height;
	}
}

void GRAPHICS_HANDLER::display()
{
	window->display();
}

void GRAPHICS_HANDLER::loadTextures()
{
	std::string path;

	for(int typesTile = 0; typesTile < nbrTypesTile; typesTile++)
	{
		path = "tiles/" + intToString(typesTile) + ".png";
		if (!textureTMP.loadFromFile(path))
		{
			    // erreur...
		}

		textures.push_back(textureTMP);
	}
}
