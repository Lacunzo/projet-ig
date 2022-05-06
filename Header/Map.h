#pragma once

#include "Cell.h"
#include <iostream>
#include <vector>
#include <Room.h>
#include <Leaf.h>

class Map {
	public:
		const unsigned int MAX_LEAF_SIZE = 20;
		int width;
		int height;
		vector<Leaf> leafs;
		
		Map();
		Map(int width, int height);
		virtual ~Map();

		void generate(int nbRoom);
		void print();
	private:
		void createRoom(int posX, int posY, int sizeX, int sizeY);
};