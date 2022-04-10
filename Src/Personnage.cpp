#include "Personnage.h"
#include <GL/gl.h>
#include <GL/glut.h>

Personnage::Personnage(void) {}
Personnage::Personnage(int posX, int posY) {
	this->POSX = posX;
	this->POSY = posY;
}
Personnage::~Personnage(void) {}

/*créé un bras et un avant bras selon deux angles et une taille*/
void Personnage::bras(float angleBras, float angleAvantBras, float size) {
    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    //bras
    glRotatef(angleBras, 0, 1, 0);
    glTranslatef(size/2, 0, 0);
    glPushMatrix();
    glScalef(size, size/3, size/3);
    glutSolidCube(1);
    glPopMatrix();
    //avant bras
    glTranslatef(size/2, 0, 0);
    glRotatef(angleAvantBras, 0, 1, 0);
    glTranslatef(size/2, 0, 0);
    glPushMatrix();
    glScalef(size, size/4, size/4);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void Personnage::jambe(float angleCuisse, float angleTibia, float size) {
    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    //cuisse
    glRotatef(angleCuisse, 0, 1, 0);
    glTranslatef(size / 2, 0, 0);
    glPushMatrix();
    glScalef(size, size / 3, size / 3);
    glutSolidCube(1);
    glPopMatrix();
    //Tibia
    glTranslatef(size / 2, 0, 0);
    glRotatef(angleTibia, 0, 1, 0);
    glTranslatef(size / 2, 0, 0);
    glPushMatrix();
    glScalef(size, size / 4, size / 4);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void Personnage::corp(float size) {
    glPushMatrix();

    //corps
    //glTranslatef(0, size * 1.5, 0);
    //glTranslatef(0, 0, 0);
    glPushMatrix();
    
    glScalef(size/2, size, size/4);
    glutSolidCube(1);
    glPopMatrix();

    //tete
    glPushMatrix();
    glTranslatef(0, -size / 2 - size / 12, 0);
    glScalef(size / 6, size / 6, size / 6);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, -size / 2 - size / 6 - size / 12, 0);
    glScalef(size / 3, size / 3, size / 3);
    glutSolidCube(1);
    glPopMatrix();

    //bras 1
    glPushMatrix();
    glTranslatef(size/4 +size/14, -size/2, 0);
    bras(25, 25, size/2);
    glPopMatrix();
    //bras 2
    glPushMatrix();
    glTranslatef((-size / 4) - size / 14, -size / 2, 0);
    bras(40, 40, size / 2);
    glPopMatrix();

    //jambe 1 
    glPushMatrix();
    glTranslatef(size /2 - size / 3, size/2, 0);
    jambe(0, 0, size / 2);
    glPopMatrix();
    //jambe 2
    glPushMatrix();
    glTranslatef(-size / 2 + size / 3, size / 2, 0);
    jambe(0, 0, size / 2);
    glPopMatrix();
   
    glPopMatrix();
}
