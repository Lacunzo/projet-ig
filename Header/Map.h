#pragma once

#include "Cell.h"
#include <iostream>
#include <vector>
using namespace std;

class Map {
	public:
		int width;
		int height;
		vector<vector<Cell>> map;
		
		Map();
		Map(int width, int height);
		virtual ~Map();

		void generate();
		void print();
	private:
		void createRoom(int posX, int posY, int sizeX, int sizeY);
};