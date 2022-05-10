#include "Room.h"
#include <GL/gl.h>
#include <GL/glut.h>
using namespace std;

Room::Room(int x, int y, int width, int length) : x(x), y(y), width(width), length(length) {}

void Room::draw() {
	glPushMatrix();
	glNormal3f(0, 1, 0);
	// Draw base
	glBegin(GL_QUADS);
		glVertex3d(x, 0, y);
		glVertex3d(x + width, 0, y);
		glVertex3d(x + width, 0, y + length);
		glVertex3d(x, 0, y + length);
	glEnd();
	glNormal3f(-1, 0, 0);
	// Draw right wall
	glBegin(GL_QUADS);
		glVertex3d(x + width, 0, y);
		glVertex3d(x + width, 0, y + length);
		glVertex3d(x + width, HEIGHT, y + length);
		glVertex3d(x + width, HEIGHT, y);
	glEnd();
	glNormal3f(0, 0, -1);
	// Draw back wall
	glBegin(GL_QUADS);
		glVertex3d(x + width, 0, y + length);
		glVertex3d(x, 0, y + length);
		glVertex3d(x, HEIGHT, y + length);
		glVertex3d(x + width, HEIGHT, y + length);
	glEnd();
	glNormal3f(1, 0, 0);
	// Draw left wall
	glBegin(GL_QUADS);
		glVertex3d(x, 0, y + length);
		glVertex3d(x, 0, y);
		glVertex3d(x, HEIGHT, y);
		glVertex3d(x, HEIGHT, y + length);
	glEnd();
	// Draw door
	glBegin(GL_QUADS);
		glVertex3d(x, 0, y);
		glVertex3d(x + width, 0, y);
		glVertex3d(x + width, HEIGHT, y);
		glVertex3d(x, HEIGHT, y);
	glEnd();
	glPopMatrix();
}