#include "Personnage.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>



Personnage::Personnage(void) {
    this->POSX = 0;
    this->POSY = 0;
    this->taille = 2;
    this->angleCorps = 0;
    this->angleAvantBras1 = 10;
    this->angleAvantBras2 = 10;
    this->angleBras1 = -5;
    this->angleBras2 = -5;
    this->angleJambe1 = 0;
    this->angleJambe1T = 0;
    this->angleJambe2 = 0;
    this->angleJambe2T = 0;
    animationUp = true;
    nbFrameAnimation = 0;
    this->direction = 0;
}
Personnage::Personnage(float posX, float posY, float taille) {
	this->POSX = posX;
	this->POSY = posY;
    this->taille = taille;
    this->direction = 0;
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
    glPushMatrix();
    glTranslatef(POSX, 0, POSY);
    glRotatef(direction, 0, 1, 0);

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
    glPopMatrix();
}

void Personnage::avancer(){
    glPushMatrix();
    glTranslatef(POSX, 0, POSY);
    glRotatef(direction, 0, 1, 0);

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

    this->angleJambe1 = -8 * nbFrameAnimation;
    this->angleJambe1T = -30;
    this->angleJambe2 = -angleJambe1;
    this->angleJambe2T = -45;
    corps(this->taille);
    glPopMatrix();
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
    //glColor3f((double)rand() /RAND_MAX, (double)rand() / RAND_MAX, (double) rand() / RAND_MAX);
    glColor3f(0.8, 0.8, 0.2);
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
    glColor3f(0.1, 0.1, 0.1);
}

void Personnage::deplacement(float dist) {

    this->POSX += sin(direction * PI / 180) * dist;
    this->POSY += cos(direction * PI / 180) * dist;
}

float Personnage::getPosX() { return POSX; };
float Personnage::getPosY() { return POSY; };
float Personnage::getDir() { return direction; };

void Personnage::changerDirection(float changementDir) {
    this->direction += changementDir;
}