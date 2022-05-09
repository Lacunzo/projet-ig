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
		
		void createRooms();
		void print() const;
	private:
		const int MAX_LEAF_SIZE = 20;
		void split_rec(Leaf *leaf, vector<Leaf> *leafs);
};