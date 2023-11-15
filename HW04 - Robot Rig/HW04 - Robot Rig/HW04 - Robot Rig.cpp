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

#define MAX_RIG_PARTS 8

int win_width = 600, win_height = 600;
float canvas_width = 20.0f; float canvas_height = 20.0f;


bool keyStates[256];
int buttonState;
float colors[3 * MAX_RIG_PARTS];
float rotations[MAX_RIG_PARTS];

int rigIndex;

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

void init(void)
{
    for (int i = 0; i < 256; i++) {
        keyStates[i] = false;
    }
    for (int i = 0; i < MAX_RIG_PARTS; i++) {
        if (i == 0) {
            colors[i * 3 + 0] = 1.0f;
            colors[i * 3 + 1] = 0.0f;
            colors[i * 3 + 2] = 0.0f;
        }
        else {
            colors[i * 3 + 0] = 0.0f; // red
            colors[i * 3 + 1] = 0.0f; // green
            colors[i * 3 + 2] = 0.0f; // blue
        }

        rotations[i] = 0.0f;
    }

    buttonState = -1;

    // rigIndex 0 is the highest level
    rigIndex = 0;
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

    int currentIndex = -1;

    // Lower Body
    currentIndex = 0;
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(-2.15, -1.5, 2.15, 1.5, colors + currentIndex * 3);

    glPushMatrix();
    // Upper Body
    currentIndex = 1;
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(-3.15, 1.5, 3.15, 3.5, colors + currentIndex * 3);
    
    // Neck
    currentIndex = 2;
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(-0.85, 3.5, 0.85, 5, colors + currentIndex * 3);

    // Head
    currentIndex = 3;
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(-1.5, 5, 1.5, 7, colors + currentIndex * 3);
    
    // Right Arm
    currentIndex = 4;
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(3.15, 2.15, 4.75, 3.5, colors + currentIndex * 3);

    // Left Arm
    currentIndex = 5;
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(-4.75, 2.15, -3.15, 3.5, colors + currentIndex * 3);

    glPopMatrix();
    
    // Right Thigh
    currentIndex = 6;
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(-2.15, -3, -0.75, -1.5, colors + currentIndex * 3);

    // Left Thight
    currentIndex = 7;
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(0.75, -3, 2.15, -1.5, colors + currentIndex * 3);

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
        std::cout << "W!\n";
        if (rigIndex < MAX_RIG_PARTS - 1) {
            rigIndex++;
        }
    }

    // Key press = "W/w"
    if (key == 65 || key == 97) {
        std::cout << "A!\n";
    }

    // Key press = "S/s"
    if (key == 83 || key == 115) {
        std::cout << "S!\n";
        if (rigIndex > 0) {
            rigIndex--;
        }
    }

    // Key press = "D/d"
    if (key == 68 || key == 100) {
        std::cout << "D!\n";
    }

    for (int i = 0; i < MAX_RIG_PARTS; i++) {
        if (i == rigIndex) {
            colors[i * 3 + 0] = 1.0f;
            colors[i * 3 + 1] = 0.0f;
            colors[i * 3 + 2] = 0.0f;
        }
        else {
            colors[i * 3 + 0] = 0.0f;
            colors[i * 3 + 1] = 0.0f;
            colors[i * 3 + 2] = 0.0f;
        }
    }

    glutPostRedisplay();
}

void
keyboardArrows(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT) {
        std::cout << "Left Arrow!\n";
        rotations[rigIndex] += 1.0f;
    } else if (key == GLUT_KEY_RIGHT) {
        std::cout << "Right Arrow\n";
        rotations[rigIndex] -= 1.0f;
    }

    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y)
{
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
    glutSpecialFunc(keyboardArrows);
    glutKeyboardUpFunc(keyboardUp);
    glutMainLoop();
    return 0;
}