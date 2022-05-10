#include "Cell.h"
#include "Map.h"
#include <iostream>
using namespace std;

Map::Map(int width, int height): width(width), height(height) {
	srand(time(NULL));
	Leaf* root = new Leaf(0, 0, this->width, this->height);

	if (root->width > MAX_LEAF_SIZE || root->height > MAX_LEAF_SIZE || rand() > 0.25) {
		if (root->split()) {
			split_rec(root->leftChild, &this->leafs);
			split_rec(root->rightChild, &this->leafs);
		}
	}
	createRooms();
	
}

void Map::split_rec(Leaf *leaf, vector<Leaf> *leafs) {
	if (leaf->leftChild == nullptr && leaf->rightChild == nullptr) {
		if (leaf->width > MAX_LEAF_SIZE || leaf->height > MAX_LEAF_SIZE || rand() > 0.25) {
			if (leaf->split()) {
				split_rec(leaf->leftChild, leafs);
				split_rec(leaf->rightChild, leafs);
			} else {
				leafs->push_back(*leaf);
			}
		}
	}
}

void Map::createRooms() {
	for (Leaf &leaf : this->leafs) {
		leaf.room = new Room(leaf.x, leaf.y, leaf.width, leaf.height);
	}
}

void Map::drawRooms() {
	for (Leaf& leaf : this->leafs) {
		leaf.room->draw();
	}
}
