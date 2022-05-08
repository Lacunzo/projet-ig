#include "Cell.h"
#include "Map.h"
#include <iostream>
using namespace std;

Map::Map(int width, int height): width(width), height(height) {
	Leaf* root = new Leaf(0, 0, this->width, this->height);
	this->leafs.push_back(*root);

	if (root->width > MAX_LEAF_SIZE || root->height > MAX_LEAF_SIZE || rand() > 0.25) {
		if (root->split()) {
			split_rec(root->leftChild, &this->leafs);
			split_rec(root->rightChild, &this->leafs);
		}
	}
}

void Map::split_rec(Leaf *leaf, vector<Leaf> *leafs) {
	leafs->push_back(*leaf);
	
	if (leaf->leftChild == nullptr && leaf->rightChild == nullptr) {
		if (leaf->width > MAX_LEAF_SIZE || leaf->height > MAX_LEAF_SIZE || rand() > 0.25) {
			if (leaf->split()) {
				split_rec(leaf->leftChild, leafs);
				split_rec(leaf->rightChild, leafs);
			}
		}
	}
}

void Map::createRooms() {	
	for (const Leaf &leaf : this->leafs) {
		Room room(leaf.x, leaf.y, leaf.width, leaf.height);
		room.draw();
	}
}

void Map::print() const {
	for (const Leaf& leaf : this->leafs) {
		leaf.print();
	}
}