#include "Room.h"
#include <GL/gl.h>
#include <GL/glut.h>
using namespace std;

Room::Room(int width, int length, int nbPillar) : width(width), length(length), nbPillar(nbPillar) {}
Room::~Room() {}

void Room::draw(int x, int y, int z) {
	int realWidth = this->width / 2;
	int realLength = this->length / 2;
	glPushMatrix();
	glNormal3f(0, 1, 0);
	// Draw base
	glBegin(GL_QUADS);
		glVertex3d(x - realWidth, y, z - realLength);
		glVertex3d(x + realWidth, y, z - realLength);
		glVertex3d(x + realWidth, y, z + realLength);
		glVertex3d(x - realWidth, y, z + realLength);
	glEnd();
	glNormal3f(-1, 0, 0);
	// Draw right wall
	glBegin(GL_QUADS);
		glVertex3d(x + realWidth, y + this->HEIGHT, z - realLength);
		glVertex3d(x + realWidth, y, z - realLength);
		glVertex3d(x + realWidth, y, z + realLength);
		glVertex3d(x + realWidth, y + this->HEIGHT, z + realLength);
	glEnd();
	glNormal3f(0, 0, -1);
	// Draw back wall
	glBegin(GL_QUADS);
		glVertex3d(x - realWidth, y + this->HEIGHT, z + realLength);
		glVertex3d(x + realWidth, y + this->HEIGHT, z + realLength);
		glVertex3d(x + realWidth, y, z + realLength);
		glVertex3d(x - realWidth, y, z + realLength);
	glEnd();
	glNormal3f(1, 0, 0);
	// Draw left wall
	glBegin(GL_QUADS);
		glVertex3d(x - realWidth, y, z - realLength);
		glVertex3d(x - realWidth, y + this->HEIGHT, z - realLength);
		glVertex3d(x - realWidth, y + this->HEIGHT, z + realLength);
		glVertex3d(x - realWidth, y, z + realLength);
	glEnd();
	glNormal3f(0, 0, 1);
	// Draw door
	glBegin(GL_QUAD_STRIP);
		int doorSize = this->length / 4;
		int doorHeight = this->HEIGHT / 2;

		glVertex3d(x - doorSize, y, z - realLength);
		glVertex3d(x - realWidth, y, z - realLength);
		glVertex3d(x - realWidth, y + this->HEIGHT, z - realLength);
		glVertex3d(x - doorSize, y + doorHeight, z - realLength);
		glVertex3d(x + doorSize, y + doorHeight, z - realLength);
		glVertex3d(x + realWidth, y + this->HEIGHT, z - realLength);
		glVertex3d(x + realWidth, y, z - realLength);
		glVertex3d(x + doorSize, y, z - realLength);
		
		
		
		
		
	glEnd();
	glPopMatrix();
}