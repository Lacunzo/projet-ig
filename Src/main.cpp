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

Personnage p = Personnage(2, 2);
Room r = Room(20, 30, 0);

static void init(void) {
	glLightf(GL_LIGHT0, GL_AMBIENT, 0.5);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

static void scene(void) {
    glPushMatrix();
	/*
    glRotatef(180, 0, 0, 1);
    glRotatef(-240, 0, 1, 0);
    p.corp(0.4F);
	*/
    r.draw(0, 0, 0);
    glPopMatrix();
}

static void display(void) {
    if (animation) {
        glRotatef(1, 1, 0, 0);
    }
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
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
    glOrtho(-15.0, 15.0, -15.0, 15.0, -15.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 10, 5, 0, 0, 0, 0, 1, 0);
}

static void idle(int) {
    glutPostRedisplay();
    glutTimerFunc((1000 / FPS), idle, 0);
}

static void keyboard(unsigned char key, int x, int y) {
    printf("K  %4c %4d %4d\n", key, x, y);
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
    printf("S  %4d %4d %4d\n", specialKey, x, y);
    switch (specialKey) {
    case GLUT_KEY_UP:
        p.avancer();
        break;
    case GLUT_KEY_DOWN:
        p.avancer();
        break;
    }
    glutPostRedisplay();
}

static void mouse(int button, int state, int x, int y) {
    printf("M  %4d %4d %4d %4d\n", button, state, x, y);
}

static void mouseMotion(int x, int y) {
    printf("MM %4d %4d\n", x, y);
}

static void passiveMouseMotion(int x, int y) {
    printf("PM %4d %4d\n", x, y);
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
    glutCreateWindow("Gestion événementielle de GLUt");
    init();
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutTimerFunc((1000/FPS), idle, 0);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    
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