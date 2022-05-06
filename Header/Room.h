#pragma once

class Room {
	private:
	public:
		static const int HEIGHT = 10;
		int width;
		int length;
		int nbPillar;
		
		Room(int width, int length, int nbPillar);
		Room();
		virtual ~Room();
		
		void draw(int x, int y, int z);
};
