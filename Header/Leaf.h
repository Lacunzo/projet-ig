#pragma once

#include <Room.h>

class Leaf {
	public:
		int x, y, width, height;
		Leaf* leftChild;
		Leaf* rightChild;
		Room room;
		
		Leaf(int x, int y, int width, int height);
		Leaf();
		virtual ~Leaf();
		
		bool split();
	private:
		const unsigned int MIN_LEAF_SIZE = 6;
};