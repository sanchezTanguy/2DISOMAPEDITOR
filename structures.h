/*
 * structures.h
 *
 *  Created on: 5 nov. 2015
 *      Author: user
 */

#ifndef structures_H_
#define structures_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>

typedef struct coordinates coordinates;
struct coordinates
{
	float x;
	float y;
	float z;
};

typedef struct size size;
struct size
{
	float width;
	float height;
};

typedef struct tile tile;
struct tile
{
	int texture;

	coordinates rawcoords;
	coordinates isocoords;
};

typedef struct layer layer;
struct layer
{
	int mapID;
	std::vector<tile> tiles;
};

typedef struct map map;
struct map
{
	int ID;
	int nbrTiles;
	int width;
	int height;
	size tileSize;
	size dim;
	std::vector<layer> layers;
};

#endif /* structures_H_ */
