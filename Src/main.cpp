#include "Personnage.h"
#include "Map.h"
#include "Room.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

static const GLfloat jaune[] = { 1.0F,1.0F,0.0F,1.0F };
static const GLfloat rouge[] = { 1.0F,0.0F,0.0F,1.0F };
static const GLfloat vert[] = { 0.0F,1.0F,0.0F,1.0F };
static const GLfloat blanc[] = { 1.0F,1.0F,1.0F,1.0F };
static const GLfloat brun[] = { 0.59F,0.34F,0.09F,1.0F };
static const GLfloat magenta[] = { 1.0F,0.0F,1.0F,1.0F };
static const GLfloat bleu[] = { 0.0F,0.0F,1.0F,1.0F };
static const GLfloat noir[] = { 0.0F,0.0F,0.0F,1.0F };
static const GLfloat gris[] = { 0.65F,0.65F,0.65F,1.0F };
static const GLfloat blanc1[] = { 1.2F,1.2F,1.2F,1.0F };
constexpr int FPS = 60;

static int wTx = 800;
static int wTy = 600;
static int wPx = (glutGet(GLUT_SCREEN_WIDTH) - wTx) / 2;
static int wPy = (glutGet(GLUT_SCREEN_HEIGHT) - wTy) / 2;
static int initial_time = time(NULL);
static int final_time;
static int frame_count;

static bool animation = false;

float TAILLE_PERSO = 2;
Personnage p = Personnage(0, 0, TAILLE_PERSO);
bool animationAvancerPerso = false;
int nbFrameOffset = 25;

int fenetreTop;
int fenetrePov;

Map map = Map(100, 100);

static void init(void) {
    glLightf(GL_LIGHT0, GL_AMBIENT, 0.5);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

static void configurationLumieres(void) {
    const GLfloat pos0[] = { 50.0F,27.0F,2.0F,1.0F };
    glLightfv(GL_LIGHT0, GL_POSITION, pos0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, rouge);
    glLightfv(GL_LIGHT0, GL_SPECULAR, noir);
    glLightfv(GL_LIGHT0, GL_AMBIENT, noir);
    const GLfloat pos1[] = { -2.0F,0.0F,4.0F,0.0F };
    glLightfv(GL_LIGHT1, GL_POSITION, pos1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, vert);
    glLightfv(GL_LIGHT1, GL_SPECULAR, blanc);
    glLightfv(GL_LIGHT1, GL_AMBIENT, noir);
    const GLfloat pos2[] = { -3.0F,-3.0F, 15.0F,1.0F };
    const GLfloat dir2[] = { 3.0F, 3.0F,-10.0F };
    glLightfv(GL_LIGHT2, GL_POSITION, pos2);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir2);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 20.0F);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, bleu);
    glLightfv(GL_LIGHT2, GL_SPECULAR, jaune);
    glLightfv(GL_LIGHT2, GL_AMBIENT, noir);
    const GLfloat pos3[] = { 0.0F,0.0F,0.0F,1.0F };
    glLightfv(GL_LIGHT3, GL_POSITION, pos3);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, noir);
    glLightfv(GL_LIGHT3, GL_SPECULAR, noir);
    glLightfv(GL_LIGHT3, GL_AMBIENT, magenta);
}


static void scene(void) {
    glPushMatrix();
    //animation idle ou avancer
    if (animationAvancerPerso) {
        p.avancer();
        nbFrameOffset = 0;
    }
    else {
        if (nbFrameOffset < 25) {
            p.avancer();
            nbFrameOffset++;
        }
        else {
            p.idle();
        }
    }

    animationAvancerPerso = false;
    map.drawRooms();
    glPopMatrix();
}

static void displayPOV(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    const GLfloat light0_position[] = { 20.0,10.0,0.0,1.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, rouge);

    const GLfloat light1_position[] = { 0.0,-50.0,350.0,1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, jaune);

    const GLfloat light2_position[] = { 32.0,-18.0,110.0,1.0 };
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, blanc);

    const GLfloat light3_position[] = { 30.0f, 40.0f, 90.0f,0.0 };
    glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, noir);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    gluLookAt(
        p.getPosX(), 2.2 * TAILLE_PERSO, p.getPosY(),
        p.getPosX() - sin(p.getDir() * PI / 180), 2.1 * TAILLE_PERSO, p.getPosY() - cos(p.getDir() * PI / 180),
        0, 1, 0);
  
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    scene();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Attention erreur %d\n", error);
    glutPostWindowRedisplay(fenetreTop);

}

static void displayTop(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    const GLfloat light0_position[] = { 20.0,10.0,0.0,1.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, rouge);

    const GLfloat light1_position[] = { 0.0,-50.0,350.0,1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, jaune);

    const GLfloat light2_position[] = { 32.0,-18.0,110.0,1.0 };
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, blanc);

    const GLfloat light3_position[] = { 30.0f, 40.0f, 90.0f,0.0 };
    glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, noir);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
	
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    gluLookAt(
        p.getPosX(), 15 * TAILLE_PERSO, p.getPosY(),
        p.getPosX() - sin(p.getDir() * PI / 180), 0, p.getPosY() - cos(p.getDir() * PI / 180),
        0, 1, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    scene();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Attention erreur %d\n", error);

    frame_count++;
    final_time = time(NULL);
    if (final_time - initial_time > 0) {
        frame_count = 0;
        initial_time = final_time;
    }
}


static void reshape(int wx, int wy) {
    printf("R\n");
    wTx = wx;
    wTy = wy;
    glViewport(0, 0, wx, wy);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double ratio = (double)wx / (double)wy;
    if (ratio > 1) {
        gluPerspective(70, ratio, 1, 50);
    }
    else {
        gluPerspective(70 / ratio, ratio, 1, 50);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

static void idle(int) {
    glutPostRedisplay();
    glutTimerFunc((1000 / FPS), idle, 0);
}

static void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
        animation = !animation;
        break;
    case 0x1B:
        exit(0);
        break;
    }

}

static void special(int specialKey, int x, int y) {
    switch (specialKey) {
    case GLUT_KEY_UP:
        animationAvancerPerso = true;
        p.deplacement(-0.4);
        break;
    case GLUT_KEY_DOWN:
        animationAvancerPerso = true;
        p.deplacement(0.4);
        break;
    case GLUT_KEY_LEFT:
        p.changerDirection(5);
        break;
    case GLUT_KEY_RIGHT:
        p.changerDirection(-5);
        break;
    }
    glutPostRedisplay();
}

static void clean(void) {
    printf("Bye\n");
}

int main(int argc, char** argv) {
    atexit(clean);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(wTx, wTy);
    glutInitWindowPosition(wPx, wPy);

    fenetrePov = glutCreateWindow("Rogue-like : Point of view");
    init();
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutTimerFunc((1000 / FPS), idle, 0);
    glutReshapeFunc(reshape);
    glutDisplayFunc(displayPOV);
    
    fenetreTop = glutCreateWindow("Rogue-like : Top view");

    init();
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutTimerFunc((1000 / FPS), idle, 0);
    glutReshapeFunc(reshape);
    glutDisplayFunc(displayTop);

    glutMainLoop();
    return(EXIT_SUCCESS);
}
