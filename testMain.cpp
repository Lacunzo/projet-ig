#include "Map.h"

int main(int argc, char** argv) {
	Map map = Map();
	map.generate(5, 5);
	map.createRoom(10, 10, 10, 10);
	map.printConsole();

}