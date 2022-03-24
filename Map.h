#ifndef __Map__

#define __Map__
#include <iostream>

class Map{
public:
	const static int SIZE_X = 50;
	const static int SIZE_Y = 30;
	int map[SIZE_Y][SIZE_X];
public:
	Map(void);
	Map(int i);
	Map(Map* m);
	virtual ~Map(void);

	void generate(int x, int y);
	void printConsole();
//private:
	void createRoom(int posX, int posY, int sizeX, int sizeY);
};
#endif