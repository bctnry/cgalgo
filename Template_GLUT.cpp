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

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // this defines the axes.
    // x : [0.0, 100.0], y : [0.0, 100.0]
    // start from the bottom-left corner and goes to the top-right.
    gluOrtho2D(0.0, 100.0, 0.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    GLfloat vertices[3][2] = {{0.0, 0.0}, {25.0, 50.0}, {50.0, 0.0}};
    int i, j, k;
    int rand();
    GLfloat p[2] = {7.5, 5.0};
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    for(k = 0; k < 5000; k++) {
        j = rand() % 3;
        p[0] = (p[0] + vertices[j][0]) / 2.0;
        p[1] = (p[1] + vertices[j][1]) / 2.0;
        glVertex2fv(p);
    }
    glEnd();
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("test");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
