/*
 * DATA_HANDLER.h
 *
 *  Created on: 5 nov. 2015
 *      Author: user
 */

#ifndef DATA_HANDLER_H_
#define DATA_HANDLER_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include "structures.h"

class DATA_HANDLER {
private:
	std::vector<map> maps;
	int currentMapID;
	int currentLayerID;

	int defaultTile;

public:
	DATA_HANDLER();

	//functions
	void newMap(int mapWidth, int mapHeight, float tileWidth, float tileHeight);

	void addLayer();//Use current map
	void addLayer(int mapID);

	//debug functions
	void setTileTexture(int tileNum, int texture);//Use current map and current layer
	void setTileTexture(int mapID, int layerID, int tileNum, int texture);

	//getters
	map getMapByID(int ID);
	map getCurrentMap();

	int getCurrentMapID();
	int getCurrentLayerID();

	//setters
	void setMap(int mapID, map map2);
};

#endif /* DATA_HANDLER_H_ */
