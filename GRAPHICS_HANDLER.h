/*
 * GRAPHICS_HANDLER.h
 *
 *  Created on: 5 nov. 2015
 *      Author: user
 */

#ifndef GRAPHICS_HANDLER_H_
#define GRAPHICS_HANDLER_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include "structures.h"
#include "DATA_HANDLER.h"

class GRAPHICS_HANDLER {
private:
	sf::RenderWindow *window;
	float screenWidth;
	float screenHeight;

	sf::Event event;

	sf::Texture textureTMP;
	sf::Sprite spriteTMP;

	std::vector<sf::Texture> textures;
	std::vector<coordinates> texturesMenuCoordinates;

	int nbrTypesTile;

	int mouseX;
	int mouseY;

	int mouseMoveX;
	int mouseMoveY;

	//offsets
	float ratioOffsetLayer;
	float ratioOffsetLeft;
	float ratioOffsetTop;
	float offsetLayer;
	float offsetLeft;
	float offsetTop;
	float currentZLayer;

	int currentTexture;
	int currentGhostTexture;

	//menu button values
	coordinates addLayerButton;
	coordinates deleteLayerButton;
	coordinates previousLayerButton;
	coordinates nextLayerButton;
	coordinates viewButton;

	bool view;
	bool brushMode;

public:
	GRAPHICS_HANDLER(sf::String title, float width, float height);
	bool isRunning();

	std::string intToString(int i);

	sf::Sprite loadImg(sf::String path, float x, float y);
	map setTile(map mapTMP, int layerID, int tileID, int texture);

	void clear();
	void listenEvents(DATA_HANDLER * DATAREF,map currentMap, int currentLayerID);

	void draw(map currentMap, int currentLayerID);
	void drawMenu(map currentMap);

	void display();

	//getters
	void loadTextures();

	//setters
	//...
};

#endif /* GRAPHICS_HANDLER_H_ */
