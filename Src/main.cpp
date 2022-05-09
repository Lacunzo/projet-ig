#include "Personnage.h"
#include "Map.h"
#include "Room.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

constexpr int FPS = 60;

static int wTx = 800;
static int wTy = 600;
static int wPx = (glutGet(GLUT_SCREEN_WIDTH) - wTx) / 2;
static int wPy = (glutGet(GLUT_SCREEN_HEIGHT) - wTy) / 2;
static int initial_time = time(NULL);
static int final_time;
static int frame_count;

static bool animation = false;

//personnage
float TAILLE_PERSO = 2;
Personnage p = Personnage(0, 0, TAILLE_PERSO);
bool animationAvancerPerso = false;
int nbFrameOffset = 25;

//fenêtres
int fenetreTop;
int fenetrePov;

Room r = Room(20, 30, 0);

static void init(void) {
	glLightf(GL_LIGHT0, GL_AMBIENT, 0.5);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

static void scene(void) {
    glPushMatrix();
    glutSolidSphere(1, 10, 10);

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
    
    r.draw(0, 0, 0);
    glPopMatrix();
}

static void displayPOV(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glPushMatrix();
    gluLookAt(
        p.getPosX(), 2.2*TAILLE_PERSO, p.getPosY(),
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


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
        cout << "FPS : " << frame_count / (final_time - initial_time) << endl;
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
    //printf("K  %4c %4d %4d\n", key, x, y);
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
    //printf("S  %4d %4d %4d\n", specialKey, x, y);
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

static void mouse(int button, int state, int x, int y) {
    //printf("M  %4d %4d %4d %4d\n", button, state, x, y);
}

static void mouseMotion(int x, int y) {
    //printf("MM %4d %4d\n", x, y);
}

static void passiveMouseMotion(int x, int y) {
    //printf("PM %4d %4d\n", x, y);
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
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutTimerFunc((1000/FPS), idle, 0);
    glutReshapeFunc(reshape);
    glutDisplayFunc(displayPOV);

    //deuxième fenêtre
    
    fenetreTop = glutCreateWindow("Rogue-like : Top view");
    init();
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutTimerFunc((1000 / FPS), idle, 0);
    glutReshapeFunc(reshape);
    glutDisplayFunc(displayTop);
    


    glutMainLoop();
    return(EXIT_SUCCESS);
}

/* TEST CLI
int main(int argc, char** argv) {
	Map map = Map();
    map.generate();
    map.print();
    return(EXIT_SUCCESS);
}
*/