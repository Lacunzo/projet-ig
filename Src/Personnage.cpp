#include "Personnage.h"
#include <GL/gl.h>
#include <GL/glut.h>

Personnage::Personnage(void) {}
Personnage::Personnage(int posX, int posY, float taille) {
	this->POSX = posX;
	this->POSY = posY;
    this->taille = taille;
    this->angleCorps = 0;
    this->angleAvantBras1 = 10;
    this->angleAvantBras2 = 10;
    this->angleBras1 =-5;
    this->angleBras2 = -5;
    this->angleJambe1 = 0;
    this->angleJambe1T = 0;
    this->angleJambe2 = 0;
    this->angleJambe2T = 0;

    animationUp = true;
    nbFrameAnimation = 0;
}
Personnage::~Personnage(void) {}

void Personnage::idle() {
    this->angleCorps = 0;
    this->angleAvantBras1 = 0;
    this->angleAvantBras2 = 0;
    this->angleBras1 = 0;
    this->angleBras2 = 0;
    this->angleJambe1 = 0;
    this->angleJambe1T = 0;
    this->angleJambe2 = 0;
    this->angleJambe2T = 0;
    corps(this->taille);
}

void Personnage::avancer(){

    // variable montant à 10 puis descendant à -10
    if (nbFrameAnimation > 10) {
        animationUp = false;
    }
    if (nbFrameAnimation < -10) {
        animationUp = true;
    }
    if (animationUp) {
        nbFrameAnimation++;
    }
    else {
        nbFrameAnimation--;
    }

    this->angleCorps = 5;
    this->angleAvantBras1 = 110;
    this->angleAvantBras2 = 110;
    
    
    this->angleBras1 = 8 * nbFrameAnimation;
    this->angleBras2 = -this->angleBras1;

    this->angleJambe1 = 8 * nbFrameAnimation;
    this->angleJambe1T = -30;
    this->angleJambe2 = -angleJambe1;
    this->angleJambe2T = -45;
    corps(this->taille);
}

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

//créé un personnage selon une taille et l'angle du corps
void Personnage::corps(float size) {
    glPushMatrix();
    //repositionnement
    glRotatef(180,0,0,1);
    glTranslatef(0, -size * 1.5, 0);

    //corps
    glRotatef(this->angleCorps,1,0,0);
    glPushMatrix();
    
    glScalef(size/2, size, size/4);
    glutSolidCube(1);
    glPopMatrix();

    //cou
    glPushMatrix();
    glTranslatef(0, -size / 2 - size / 12, 0);
    glRotatef(-angleCorps, 1, 0, 0);
    glScalef(size / 6, size / 6, size / 6);
    glutSolidCube(1);
    glPopMatrix();
    //tete
    glPushMatrix();
    glTranslatef(0, -size / 2 - size / 6 - size / 12, 0);
    glRotatef(-angleCorps, 1, 0, 0);
    glScalef(size / 3, size / 3, size / 3);
    glutSolidCube(1);
    glPopMatrix();

    //bras 1
    glPushMatrix();
    glTranslatef(size/4 +size/14, -size/2, 0);
    bras(this->angleBras1,this->angleAvantBras1, size/2);
    glPopMatrix();
    //bras 2
    glPushMatrix();
    glTranslatef((-size / 4) - size / 14, -size / 2, 0);
    bras(this->angleBras2, this->angleAvantBras2, size / 2);
    glPopMatrix();

    //jambe 1 
    glPushMatrix();
    glTranslatef(size /2 - size / 3, size/2, 0);
    glRotatef(-angleCorps, 1, 0, 0);
    jambe(this->angleJambe1,this->angleJambe1T, size / 2);
    glPopMatrix();
    //jambe 2
    glPushMatrix();
    glTranslatef(-size / 2 + size / 3, size / 2, 0);
    glRotatef(-angleCorps, 1, 0, 0);
    jambe(this->angleJambe2, this->angleJambe2T, size / 2);
    glPopMatrix();
   
    glPopMatrix();
}
