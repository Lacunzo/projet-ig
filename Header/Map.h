#pragma once

#include "Cell.h"
#include <iostream>
#include <vector>
#include <Room.h>
#include <Leaf.h>

class Map {
	public:
		int width;
		int height;
		vector<Leaf> leafs;
		
		Map(int width, int height);
		void drawRooms();
	private:
		const int MAX_LEAF_SIZE = 40;
		void split_rec(Leaf *leaf, vector<Leaf> *leafs);
		void createRooms();
};