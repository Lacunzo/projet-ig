#include "Cell.h"
#include "Map.h"
#include <iostream>
using namespace std;

Map::Map(): width(20), height(20) {
	this->map = {};
	for (int i = 0; i < height; i++) {
		vector<Cell> row;
		for (int j = 0; j < width; j++) {
			if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
				row.push_back(Cell::Wall);
			} else {
				row.push_back(Cell::Empty);
			}
		}
		map.push_back(row);
	}
}
Map::Map(int width, int height): width(width), height(height) {}
Map::~Map(){}

void Map::generate() {
	
}

void Map::print() {
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < width; j++) {
			cout << " " << map[i][j] << " ";
		}
		cout << endl;
	}
}