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
static int cFond = 0;              // Numero de la couleur de fond (0: gris, 1: blanc, 2:noir)


static bool animation = false;
static float spotDir[3] = { 0.0, -1.0,0.0 };
const GLfloat spotCutOff = 20.0;

float TAILLE_PERSO = 2;
Personnage p = Personnage(0, 0, TAILLE_PERSO);
bool animationAvancerPerso = false;
int nbFrameOffset = 25;

int fenetreTop;
int fenetrePov;
bool ligth1 = true, ligth2 = true, ligth3 = true, ligth4 = true, ligth5 = true;

Map map = Map(100, 100);

static void init(void) {
    const GLfloat shininess[] = { 50.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glLightf(GL_LIGHT0, GL_AMBIENT, 0.5);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, rouge);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, jaune);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, bleu);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);
    glEnable(GL_LIGHT5);
    glEnable(GL_LIGHT6);
    glEnable(GL_LIGHT7);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

void lighting1()
{

    GLfloat pos[4] = { p.getPosX(),p.getPosY(), -20.0, 1.0 };
    glLightfv(GL_LIGHT3, GL_DIFFUSE, blanc);
    glLightfv(GL_LIGHT3, GL_POSITION, pos);
    glEnable(GL_LIGHT3);
}

void lighting2()
{
    GLfloat pos[4] = { p.getPosX(),p.getPosY(), -1.0, 0.0 };
    glLightfv(GL_LIGHT4, GL_POSITION, pos);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, vert);
    glLightfv(GL_LIGHT4, GL_SPECULAR, blanc);
    glEnable(GL_LIGHT4);
}

void lighting3()
{
    GLfloat pos[4] = { -3.0,-3.0, 15.0, 1.0 };
    glLightfv(GL_LIGHT5, GL_DIFFUSE, vert);
    glLightfv(GL_LIGHT5, GL_POSITION, pos);
    glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spotDir);
    glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, spotCutOff);
    glEnable(GL_LIGHT5);
}


void lighting4()
{
    GLfloat pos[4] = { 0.0,0.0,0.0,1.0 };

    glLightfv(GL_LIGHT6, GL_DIFFUSE, vert);
    glLightfv(GL_LIGHT6, GL_POSITION, pos);
    glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, spotDir);
    glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, spotCutOff);
    glEnable(GL_LIGHT6);
}

void lighting5()
{
    GLfloat pos[4] = { -1.0,1.0,1.0,0.0 };
    glLightfv(GL_LIGHT7, GL_DIFFUSE, vert);
    glLightfv(GL_LIGHT7, GL_POSITION, pos);
    glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, spotDir);
    glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, spotCutOff);
    glEnable(GL_LIGHT7);
}

void lighting6()
{
    GLfloat pos[4] = { -1.0,1.0,1.0,0.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vert);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutOff);
    glEnable(GL_LIGHT0);
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
    const float* fond;
    switch (cFond) {
    case 0:
        fond = gris;
        break;
    case 1:
        fond = blanc;
        break;
    case 2:
        fond = noir;
        break;
    }
    glClearColor(fond[0], fond[1], fond[2], fond[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    const GLfloat light0_position[] = { 0.0,0.0,0.0,1.0 };
    const GLfloat light1_position[] = { -1.0,1.0,1.0,0.0 };
    const GLfloat light2_position[] = { 1.0,-1.0,1.0,0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

    if (ligth1 == true)
    {
        lighting1();
    }
    else
    {
        glDisable(GL_LIGHT3);
    }

    if (ligth2 == true)
    {
        lighting2();
    }
    else
    {
        glDisable(GL_LIGHT4);
    }

    if (ligth3 == true)
    {
        lighting3();
    }
    else
    {
        glDisable(GL_LIGHT5);
    }
    if (ligth4 == true)
    {
        lighting4();
    }
    else
    {
        glDisable(GL_LIGHT6);
    }
    if (ligth5 == true)
    {
        lighting3();
    }
    else
    {
        glDisable(GL_LIGHT7);
    }
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    gluLookAt(
        p.getPosX(), 2.2 * TAILLE_PERSO, p.getPosY(),
        p.getPosX() - sin(p.getDir() * PI / 180), 2.1 * TAILLE_PERSO, p.getPosY() - cos(p.getDir() * PI / 180),
        0, 1, 0);
  
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

    const float* fond;
    switch (cFond) {
    case 0:
        fond = gris;
        break;
    case 1:
        fond = blanc;
        break;
    case 2:
        fond = noir;
        break;
    }
    glClearColor(fond[0], fond[1], fond[2], fond[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    const GLfloat light0_position[] = { 0.0,0.0,0.0,1.0 };
    const GLfloat light1_position[] = { -1.0,1.0,1.0,0.0 };
    const GLfloat light2_position[] = { 1.0,-1.0,1.0,0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

    if (ligth1 == true)
    {
        lighting1();
    }
    else
    {
        glDisable(GL_LIGHT3);
    }

    if (ligth2 == true)
    {
        lighting2();
    }
    else
    {
        glDisable(GL_LIGHT4);
    }

    if (ligth3 == true)
    {
        lighting3();
    }
    else
    {
        glDisable(GL_LIGHT5);
    }
    if (ligth4 == true)
    {
        lighting4();
    }
    else
    {
        glDisable(GL_LIGHT6);
    }
    if (ligth5 == true)
    {
        lighting3();
    }
    else
    {
        glDisable(GL_LIGHT7);
    }
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    gluLookAt(
        p.getPosX(), 15 * TAILLE_PERSO, p.getPosY(),
        p.getPosX() - sin(p.getDir() * PI / 180), 0, p.getPosY() - cos(p.getDir() * PI / 180),
        0, 1, 0);
  
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
