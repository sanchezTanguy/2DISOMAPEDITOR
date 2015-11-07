/*
 * DATA_HANDLER.cpp
 *
 *  Created on: 5 nov. 2015
 *      Author: user
 */

#include "DATA_HANDLER.h"


DATA_HANDLER::DATA_HANDLER() {
	defaultTile = 0;
}

void DATA_HANDLER::newMap(int mapWidth, int mapHeight, float tileWidth, float tileHeight)
{
	int mapID = maps.size();
	map mapTMP;

	mapTMP.ID = mapID;
	currentMapID = mapID;

	mapTMP.dim.width = mapWidth * tileWidth;
	mapTMP.dim.height = mapHeight * tileHeight;

	mapTMP.nbrTiles = mapWidth * mapHeight;

	mapTMP.width = mapWidth;
	mapTMP.height = mapHeight;

	mapTMP.tileSize.width = tileWidth;
	mapTMP.tileSize.height = tileHeight;

	maps.push_back(mapTMP);
}

void DATA_HANDLER::addLayer()
{
	//Add layer in the current map
	currentLayerID = maps[currentMapID].layers.size();

	layer layerTMP;
	std::vector<tile> tilesTMP;
	tile tileTMP;

	int height = maps[currentMapID].height;
	int width = maps[currentMapID].width;

	int tileWidth = maps[currentMapID].tileSize.width;
	int tileHeight = maps[currentMapID].tileSize.height;


	//allow tiles coordinates calculation
	float xIndex = 0;
	float yIndex = 0;
	int tileIndex = 0;

	layerTMP.mapID = currentMapID;

	for(int tile = 0; tile < maps[currentMapID].nbrTiles; tile++)
	{
		tileTMP.texture = defaultTile;
		tilesTMP.push_back(tileTMP);
	}

	//tiles coordinates calculation
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			tilesTMP[tileIndex].rawcoords.x = x + xIndex;
			tilesTMP[tileIndex].rawcoords.y = y + yIndex;

			tilesTMP[tileIndex].isocoords.x = (x - y) * (tileWidth / 2);
			tilesTMP[tileIndex].isocoords.y = (x + y) * (tileHeight / 4);

			tileIndex++;
			xIndex += tileWidth;
		}

		xIndex = 0;
		yIndex += tileHeight;
	}

	layerTMP.tiles = tilesTMP;

	maps[currentMapID].layers.push_back(layerTMP);
}

void DATA_HANDLER::addLayer(int mapID)
{
	currentMapID = mapID;
	currentLayerID = maps[mapID].layers.size();

	layer layerTMP;
	std::vector<tile> tilesTMP;
	tile tileTMP;

	int height = maps[mapID].height;
	int width = maps[mapID].width;

	int tileWidth = maps[mapID].tileSize.width;
	int tileHeight = maps[mapID].tileSize.height;


	//allow tiles coordinates calculation
	int xIndex = 0;
	int yIndex = 0;
	int tileIndex = 0;

	layerTMP.mapID = mapID;

	for(int tile = 0; tile < maps[mapID].nbrTiles; tile++)
	{
		tileTMP.texture = 0;//default tile
		tilesTMP.push_back(tileTMP);
	}

	//tiles coordinates calculation
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			tilesTMP[tileIndex].rawcoords.x = x + xIndex;
			tilesTMP[tileIndex].rawcoords.y = y + yIndex;

			tilesTMP[tileIndex].isocoords.x = (y - x) * (tileWidth / 2);
			tilesTMP[tileIndex].isocoords.y = (y + x) * (tileHeight / 2);

			tileIndex++;
			xIndex += tileWidth;
		}

		xIndex = 0;
		yIndex += tileHeight;
	}

	layerTMP.tiles = tilesTMP;

	maps[mapID].layers.push_back(layerTMP);
}

//debug functions
void DATA_HANDLER::setTileTexture(int tileNum, int texture)
{
	maps[currentMapID].layers[currentLayerID].tiles[tileNum].texture = texture;
}


void DATA_HANDLER::setTileTexture(int mapID, int layerID, int tileNum, int texture)
{
	maps[mapID].layers[layerID].tiles[tileNum].texture = texture;
}

map DATA_HANDLER::getMapByID(int ID)
{
	return maps[ID];
}


map DATA_HANDLER::getCurrentMap()
{
	return maps[currentMapID];
}

int DATA_HANDLER::getCurrentMapID()
{
	return currentMapID;
}

int DATA_HANDLER::getCurrentLayerID()
{
	return currentLayerID;
}

void DATA_HANDLER::setMap(int mapID, map map2)
{
	maps[mapID] = map2;
}

void DATA_HANDLER::setCurrentLayer(int layerID)
{
	currentLayerID = layerID;
}
