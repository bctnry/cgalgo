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

static const int SUB_WINDOW_WIDTH = 120;
static const int SUB_WINDOW_HEIGHT = 120;
static const int SUB_WINDOW_1_OFFSET_X = 100;
static const int SUB_WINDOW_2_OFFSET_X = 420;
static const int SUB_WINDOW_1_OFFSET_Y = 180;
static const int SUB_WINDOW_2_OFFSET_Y = 180;
// XL = 100, XR = 100 + 120, YB = 180, YT = 180 + 120
// XL = 420, XR = 420 + 120, YB = 180, YT = 180 + 120
static const int XL[2] = {100, 420}, XR[2] = {220, 540}, YB[2] = {180, 180}, YT[2] = {300, 300};

int abs(int a) { return a >= 0? a : -a; }

void drawSubWindows();

// draw the "two window" frame.
void mainFrame() {
    drawSubWindows();
    glBegin(GL_LINES); {
        glVertex2f(WINDOW_WIDTH / 2.0, 0);
        glVertex2f(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT);
    } glEnd();
}

void init() {
    // your initialization stuff goes here
    glClearColor(1.0, 1.0, 1.0, 1.0);
    // default black
    glColor3f(0.0, 0.0, 0.0);
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

void calculateAndDrawClippedLine(int x, int y);
// mouse motion handling.
static int prevX = 0, prevY = 0;
void onDrag(int x, int y) {
    // on drag callback.
    y = WINDOW_HEIGHT - y;
    if(lastX <= WINDOW_WIDTH / 2 && x > WINDOW_WIDTH / 2) x = WINDOW_WIDTH / 2;
    if(lastX >= WINDOW_WIDTH / 2 && x < WINDOW_WIDTH / 2) x = WINDOW_WIDTH / 2;


    clear();
    mainFrame();
    
    glBegin(GL_LINES); {
        glVertex2f(lastX, lastY);
        glVertex2f(x, y);
    } glEnd();

    calculateAndDrawClippedLine(x, y);

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
    
    if((!right)&&(!mid)&&(!release)) {
        lastX = x, lastY = y;
    }
    if(right&&holddown) {
    }
    if(release) {
    }
}


// keyboard handling.
void onKey(unsigned char key, int x, int y) {
    int modifiers = glutGetModifiers();
    // check using GLUT_ACTIVE_SHIFT/CTRL/ALT.
}



// the main display callback.
void onDisplay() {
    // the whole display is controlled by the drawline func
    // so nothing to do here.
    clear();
    mainFrame();
}
void drawLine(float x1, float y1, float x2, float y2);
bool clip(float p, float q, float& u1, float& u2);
void calculateAndDrawClippedLine(int x, int y) {
    // the line is (lastX, lastY) (x, y).
    // we now check if it's at the right side or the left side:
    int x1 = lastX, y1 = lastY, x2 = x, y2 = y;
    
    bool isRight = false;
    if(x1 > WINDOW_WIDTH / 2) {
        x1 -= WINDOW_WIDTH / 2, x2 -= WINDOW_WIDTH / 2;
    } else if(x1 < WINDOW_WIDTH / 2) {
        x1 += WINDOW_WIDTH / 2, x2 += WINDOW_WIDTH / 2;
        isRight = true;
    }
    // we now swap the 2 points if x2 < x1.
    if(x2 < x1) {
        int temp = x1; x1 = x2; x2 = temp;
        temp = y1; y1 = y2; y2 = temp;
    }
    // we now crop (x1, y1) (x2, y2).

    float dx, dy, u1 = 0, u2 = 1;
    dx = x2 - x1, dy = y2 - y1;
    if(clip(-dx, x1 - XL[isRight], u1, u2)) {
        if(clip(dx, XR[isRight] - x1, u1, u2)) {
            if(clip(-dy, y1 - YB[isRight], u1, u2)) {
                if(clip(dy, YT[isRight] - y1, u1, u2)) {
                    drawLine(x1 + u1 * dx, y1 + u1 * dy, x1 + u2 * dx, y1 + u2 * dy);
                }
            }
        }
    }
}
void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES); {
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    } glEnd();
}
bool clip(float p, float q, float& u1, float& u2) {
    float r;
    if(p < 0) {
        r = q / p;
        if(r > u2) return false;
        if(r > u1) u1 = r;
    } else if(p > 0) {
        r = q / p;
        if(r < u1) return false;
        if(r < u2) u2 = r;
    }
    else return (q >= 0);
    return true;
}

// draw the two subwindows.
void drawSubWindows() {
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP); {
        glVertex2f(SUB_WINDOW_1_OFFSET_X, SUB_WINDOW_1_OFFSET_Y);
        glVertex2f(SUB_WINDOW_1_OFFSET_X + SUB_WINDOW_WIDTH,
                   SUB_WINDOW_1_OFFSET_Y);
        glVertex2f(SUB_WINDOW_1_OFFSET_X + SUB_WINDOW_WIDTH,
                   SUB_WINDOW_1_OFFSET_Y + SUB_WINDOW_WIDTH);
        glVertex2f(SUB_WINDOW_1_OFFSET_X,
                   SUB_WINDOW_1_OFFSET_Y + SUB_WINDOW_WIDTH);
    } glEnd();
    glBegin(GL_LINE_LOOP); {
        glVertex2f(SUB_WINDOW_2_OFFSET_X,
                   SUB_WINDOW_2_OFFSET_Y);
        glVertex2f(SUB_WINDOW_2_OFFSET_X + SUB_WINDOW_WIDTH,
                   SUB_WINDOW_2_OFFSET_Y);
        glVertex2f(SUB_WINDOW_2_OFFSET_X + SUB_WINDOW_WIDTH,
                   SUB_WINDOW_2_OFFSET_Y + SUB_WINDOW_WIDTH);
        glVertex2f(SUB_WINDOW_2_OFFSET_X,
                   SUB_WINDOW_2_OFFSET_Y + SUB_WINDOW_WIDTH);
    } glEnd();

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
