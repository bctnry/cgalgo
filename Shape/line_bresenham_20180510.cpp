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

int abs(int a) { return a >= 0? a : -a; }

void drawline(int, int, int, int);

void init() {
    // your initialization stuff goes here
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // this defines the axes.
    // x : [0.0, window_width], y : [0.0, window_height]
    // start from the bottom-left corner and goes to the top-right.
    gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
}

void clear() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

// window reshape handling
void onReshape(int width, int height) {
    // on reshape callback.
    static int prevWidth = 0, prevHeight = 0;
    prevWidth = width, prevHeight = height;
}

// for keep tracking mouse positions.
static int lastX = 0, lastY = 0;

// mouse motion handling.
static int prevX = 0, prevY = 0;
void onDrag(int x, int y) {
    // on drag callback.
    y = WINDOW_HEIGHT - y;
    
    // clear window
    clear();

    // drawline
    drawline(lastX, lastY, x, y);

    // flush.
    glFlush();
    
    prevX = x, prevY = y;
}

void onMouseMove(int x, int y) {
    // on mousemove callback.
    prevX = x, prevY = y;
}

// mouse handling.
void onMouse(int button, int state, int x, int y) {
    char
        right = button&GLUT_RIGHT_BUTTON,
        mid = button&GLUT_MIDDLE_BUTTON,
        left = (!right)&&(!mid),
        release = state&GLUT_UP,
        holddown = (!release);
    y = WINDOW_HEIGHT - y;
    if((!right)&&(!mid)&&(!release)) { // left click
        lastX = x, lastY = y;
    }
    if(right&&holddown) {
        clear();
        drawline(lastX, lastY, x, y);
        glFlush();
    }
}


// keyboard handling.
void onKey(unsigned char key, int x, int y) {
    int modifiers = glutGetModifiers();
    // check using GLUT_ACTIVE_SHIFT/CTRL/ALT.
}

void drawpoint(int x, int y) {
    glBegin(GL_POINTS); {
        glVertex2f(x, y);
    } glEnd();
}

// drawline func.
void drawline(int x1, int y1, int x2, int y2) {
    int x, y, dx, dy, e;
    dx = x2 - x1, dy = y2 - y1;

    if(abs(dy) < abs(dx)) {
        // if x1 is at the right of x2
        // then swap points.
        if(x1 > x2) {
            int temp = x2; x2 = x1, x1 = temp;
            temp = y2; y2 = y1, y1 = temp;
            // and then modify dx & dy.
            dx = -dx, dy = -dy;
        }
        /* |k| <= 1:
           downwards: k < 0, e = 0.5, e += k,
           if e <= 0 then y--; e += 1 (reset to 0.5);
           else y same;
           upwards: k > 0, e = -0.5, e += k,
           if e >= 0 then y++; e -= 1 (reset to -0.5);
           else y same;
           here, e is actually 2edx --> dx,
           and 1 is actually 2dx.
        */
        char updown = dy > 0? 1 : 0;
        e = updown? -dx : dx;
        x = x1, y = y1;
        for(int i = 0; i <= dx; i++) {
            drawpoint(x, y);
            x++, e += 2 * dy;
            if(updown? e >= 0 : e <= 0) {
                y += updown? 1 : -1;
                e += (updown? -1 : 1) * 2 * dx;
            }
        }
    } else {
        // now, |k| > 1, the role of y and x has changed.
        // if y1 is at the top of y2
        // then swap points.
        if(y1 > y2) {
            int temp = y2; y2 = y1, y1 = temp;
            temp = x2; x2 = x1, x1 = temp;
            dx = -dx, dy = -dy;
        }
        char updown = dx > 0? 1 : 0;
        /*
          upwards: k > 0, e = -0.5, e += 1/k = dx/dy,
                   if e >= 0 then x++, e -= 1 (reset to -0.5)
          downwards: k < 0, e = 0.5, e += 1/k = dx/dy,
                     if e <= 0 then x--, e += 1 (reset to 0.5)
          
         */
        e = updown? -dy : dy;
        x = x1, y = y1;
        for(int i = 0; i <= dy; i++) {
            drawpoint(x, y);
            y++, e += 2 * dx;
            if(updown? e >= 0 : e <= 0) {
                x += (updown? 1 : -1);
                e += (updown? -1 : 1) * 2 * dy;
            }
        }
    }
}


// the main display callback.
void onDisplay() {
    // the whole display is controlled by the drawline func
    // so nothing to do here.
    clear();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("test");
    glutDisplayFunc(onDisplay);
    //    glutReshapeFunc(onReshape);
    glutMotionFunc(onDrag);
    glutPassiveMotionFunc(onMouseMove);
    //    glutKeyboardFunc(onKey);
    glutMouseFunc(onMouse);
    init();
    glutMainLoop();
    return 0;
}
