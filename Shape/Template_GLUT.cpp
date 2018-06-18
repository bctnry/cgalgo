/* OpenGL template.
   require freeglut.
   compile using:
       g++ [your_source_filename_here] -O2 -lGL -lGLU -lglut
   this template code draws the spierniski triangle in a
   640x480 window using a technique called the "chaos game".
*/


#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/freeglut.h>

#include<stdio.h>

static const int WINDOW_WIDTH = 640;
static const int WINDOW_HEIGHT = 480;

void init() {
    // your initialization stuff goes here
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // this defines the axes.
    // x : [0.0, 100.0], y : [0.0, 100.0]
    // start from the bottom-left corner and goes to the top-right.
    gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
}

// window reshape handling
void onReshape(int width, int height) {
    // on reshape callback.
    static int prevWidth = 0, prevHeight = 0;
    prevWidth = width, prevHeight = height;
}


// mouse motion handling.
static int prevX = 0, prevY = 0;
void onDrag(int x, int y) {
    // on drag callback.
    prevX = x, prevY = y;
}

void onMouseMove(int x, int y) {
    // on mousemove callback.
    prevX = x, prevY = y;
}


// keyboard handling.
void onKey(unsigned char key, int x, int y) {
    int modifiers = glutGetModifiers();
    // check using GLUT_ACTIVE_SHIFT/CTRL/ALT.
    /*
    printf("Key %c pressed with modifier%s%s%s!\n",
           key,
           modifiers&GLUT_ACTIVE_SHIFT?" SHIFT":"",
           modifiers&GLUT_ACTIVE_CTRL?" CTRL":"",
           modifiers&GLUT_ACTIVE_ALT?" ALT":"");
    */
}


// the main display callback.
void onDisplay() {
    glClear();
    render();
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("test");
    glutDisplayFunc(onDisplay);
    glutReshapeFunc(onReshape);
    glutMotionFunc(onDrag);
    glutPassiveMotionFunc(onMouseMove);
    glutKeyboardFunc(onKey);
    init();
    glutMainLoop();
    return 0;
}
