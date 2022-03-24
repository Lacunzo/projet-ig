#include "Map.h"
#include <iostream>
using namespace std;

Map::Map(void){}
Map::Map(int i){}
Map::Map(Map *m){}
Map::~Map(void){}

void Map::generate(int x, int y){
	for (int l = 0; l < SIZE_Y; l++) {
		for (int c = 0; c < SIZE_X; c++) {
			if (l == x && c == y) {
				map[l][c] = 1;
			}
			else{
				map[l][c] = 0;
			}
		}
	}
}

void Map::printConsole() {
	for (int l = 0; l < SIZE_Y; l++) {
		for (int c = 0; c < SIZE_X; c++) {
			cout << map[l][c];
		}
		cout << "\n";
	}
}

void Map::createRoom(int posX, int posY, int sizeX, int sizeY) {
	if (posX<0 || posY<0 || posX + sizeX > SIZE_X || posY + sizeY > SIZE_Y) {
		cout << "erreur out of bound room";
		return;
	}
	for (int l = sizeY; l <= sizeY + posY; l++) {
		for (int c = sizeX; c <= sizeX + posX; c++) {
			if (l == sizeY && c != sizeX && c != sizeX+posX) {
				map[l][c] = 3;
			}
			else {
				if (l == sizeY + posY && c != sizeX && c != sizeX + posX) {
					map[l][c] = 5;
				}
				else {
					if (c == sizeX && l != sizeY && l != sizeY + posY) {
						map[l][c] = 2;
					}
					else {
						if (c == sizeX + posX && l != sizeY && l != sizeY + posY) {
							map[l][c] = 4;
						}
						else {
							map[l][c] = 1;
						}
					}
				}
			}
		}
	}

}