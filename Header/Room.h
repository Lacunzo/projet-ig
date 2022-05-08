#pragma once

class Room {
	public:
		static const int HEIGHT = 10;
		int x, y, width, length;
		
		Room(int x, int y, int width, int length);
		
		void draw();
	private:
};
