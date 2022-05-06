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

void Map::generate(int nbRoom) {
	while(nbRoom != 0) {
		int randomX = rand() % (this->width - 1) + 1;
		int randomY = rand() % (this->height - 1) + 1;
		int randomWidth = rand() % (this->width - 1) + randomX;
		int randomHeight = rand() % (this->height - 1) + randomY;
		
		createRoom(randomX, randomY, randomWidth, randomHeight);
	}
}

void Map::createRoom(int x, int y, int width, int height) {
	if (x <= 0 || y <= 0 || x + width >= this->width || y + height >= this->height) {
		cout << "Room is out of map" << endl;
		return;
	} else if (width - x <= 1 || height - y <= 1) {
		cout << "Room is too small" << endl;
		return;
	}
	
	for (int i = x; i < x + width; i++) {
		for (int j = y; j < y + height; j++) {
			if (i == x || i == x + width - 1 || j == y || j == y + height - 1) {
				map[i][j] = Cell::Wall;
			} else {
				map[i][j] = Cell::Floor;
			}
		}
	}
}

void Map::print() {
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < width; j++) {
			cout << " " << map[i][j] << " ";
		}
		cout << endl;
	}
}