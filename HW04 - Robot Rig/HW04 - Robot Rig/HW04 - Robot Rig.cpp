//Usage:
//Hold down the number keys , 1-7, to select one or multiple circles.
//While circle(s) are selected, use the left mouse button to translate and use the right mouse button to rotate.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <math.h>
using namespace std;

#define MAX_RIG_PARTS 7

int win_width = 600, win_height = 600;
float canvas_width = 20.0f; float canvas_height = 20.0f;


bool keyStates[256];
int buttonState;
float colors[3 * MAX_RIG_PARTS];
float rotations[MAX_RIG_PARTS];

int rigIndex;

// Lowerbody
float lb1[2];
float lb2[2];
float lb3[2];
float lb4[2];

// Upperbody
float ub1[2];
float ub2[2];
float ub3[2];
float ub4[2];

// Neck
float n1[2];
float n2[2];
float n3[2];
float n4[2];

// Head
float h1[2];
float h2[2];
float h3[2];
float h4[2];

void initializeVertices() {
    // Rig
    // Lowerbody
    lb1[0] = -2.15;
    lb1[1] = -1.5;
    lb2[0] = -2.15;
    lb2[1] = 1.5;
    lb3[0] = 2.15;
    lb3[1] = 1.5;
    lb4[0] = 2.15;
    lb4[1] = -1.5;

    // Upperbody
    ub1[0] = -3.15;
    ub1[1] = 1.5;
    ub2[0] = -3.15;
    ub2[1] = 3.5;
    ub3[0] = 3.15;
    ub3[1] = 3.5;
    ub4[0] = 3.15;
    ub4[1] = 1.5;

    // Neck
    n1[0] = -0.85;
    n1[1] = 3.5;
    n2[0] = -0.85;
    n2[1] = 5;
    n3[0] = 0.85;
    n3[1] = 5;
    n4[0] = 0.85;
    n4[1] = 3.5;

    // Head
    h1[0] = -1.5;
    h1[1] = 5;
    h2[0] = -1.5;
    h2[1] = 7;
    h3[0] = 1.5;
    h3[1] = 7;
    h4[0] = 1.5;
    h4[1] = 5;
}

void init(void)
{
    for (int i = 0; i < 256; i++) {
        keyStates[i] = false;
    }
    for (int i = 0; i < MAX_RIG_PARTS; i++) {
        colors[i * 3 + 0] = 0.0f; // red
        colors[i * 3 + 1] = 0.0f; // green
        colors[i * 3 + 2] = 0.0f; // blue

        rotations[i] = 0.0f;
    }

    buttonState = -1;

    // rigIndex 0 is the highest level
    rigIndex = 0;

    initializeVertices();
}

void drawSquare(const GLfloat* v1, const GLfloat* v2, const GLfloat* v3, const GLfloat* v4, const float* c)
{
    glColor3fv(c);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2fv(v1);
    glVertex2fv(v2);
    glVertex2fv(v3);
    glVertex2fv(v4);

    lb1[0] = -2.15;
    lb1[1] = -1.5;
    lb2[0] = -2.15;
    lb2[1] = 1.5;
    lb3[0] = 2.15;
    lb3[1] = 1.5;
    lb4[0] = 2.15;
    lb4[1] = -1.5;
    glEnd();
}

void drawSquare(const GLfloat lowX, const GLfloat lowY, const GLfloat highX, const GLfloat highY, const float* c)
{
    glColor3fv(c);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(lowX, lowY);
    glVertex2f(lowX, highY);
    glVertex2f(highX, highY);
    glVertex2f(highX, lowY);
    glEnd();
}

void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawSquare(lb1, lb2, lb3, lb4, colors + rigIndex * 3);
    drawSquare(ub1, ub2, ub3, ub4, colors + rigIndex * 3);
    drawSquare(n1, n2, n3, n4, colors + rigIndex * 3);
    drawSquare(h1, h2, h3, h4, colors + rigIndex * 3);

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    win_width = w;
    win_height = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-canvas_width / 2.0f, canvas_width / 2.0f, -canvas_height / 2.0f, canvas_height / 2.0f);
    glViewport(0, 0, (GLsizei)win_width, (GLsizei)win_height);

    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) // 'esc' key
        exit(0);

    // Key press = "W/w"
    if (key == 87 || key == 119) {
        std::cout << "W!";
    }

    // Key press = "W/w"
    if (key == 65 || key == 97) {
        std::cout << "A!";
    }

    // Key press = "S/s"
    if (key == 83 || key == 115) {
        std::cout << "S!";
    }

    // Key press = "D/d"
    if (key == 68 || key == 100) {
        std::cout << "D!";
    }

    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y)
{
    unsigned char asciiOffset = 49; // see an ascii table
    for (unsigned char i = '1'; i < '7'; i++) {
        if (key == i) {
            keyStates[i] = false;
            colors[(i - asciiOffset) * 3 + 0] = 0.0f;
            colors[(i - asciiOffset) * 3 + 1] = 0.0f;
            colors[(i - asciiOffset) * 3 + 2] = 0.0f;
        }
    }
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(win_width, win_height);
    glutCreateWindow("2D Transformation Tree");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMainLoop();
    return 0;
}