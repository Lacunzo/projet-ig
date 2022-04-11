#include "Cell.h"
#include <iostream>
using namespace std;

ostream& operator<<(ostream& os, const Cell& cell) {
	switch (cell) {
		case Cell::Empty:
			os << " ";
			break;
		case Cell::Floor:
			os << ".";
			break;
		case Cell::Wall:
			os << "#";
			break;
		case Cell::Key:
			os << "k";
			break;
		case Cell::Pillar:
			os << "*";
			break;		
		default:
			break;
	}
	return os;
}