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

#define MAX_RIG_PARTS 16

int win_width = 600, win_height = 600;
float canvas_width = 20.0f; 
float canvas_height = 20.0f;

float colors[3 * MAX_RIG_PARTS];
float translations[2 * MAX_RIG_PARTS];
float rotations[MAX_RIG_PARTS];

int rigIndex;

void init(void)
{
    for (int i = 0; i < MAX_RIG_PARTS; i++) {
        if (i == 0) {
            colors[i * 3 + 0] = 1.0f;
            colors[i * 3 + 1] = 0.0f;
            colors[i * 3 + 2] = 0.0f;
        }
        else {
            colors[i * 3 + 0] = 0.0f;
            colors[i * 3 + 1] = 0.0f;
            colors[i * 3 + 2] = 0.0f;
        }

        translations[i * 2 + 0] = 0.0f;
        translations[i * 2 + 1] = 0.0f;

        rotations[i] = 0.0f;
    }

    // rigIndex 0 is the highest level
    rigIndex = 0;
}

void drawSquare(const GLfloat lowX, const GLfloat lowY, const GLfloat highX, const GLfloat highY, const float* c)
{
    // Set the color and linewidth
    glColor3fv(c);
    glLineWidth(3.0f);

    // Begin drawing - sing Line_Loop for an outline
    glBegin(GL_LINE_LOOP);

    // Draw a line loop connecting each vertex
    glVertex2f(lowX, lowY);
    glVertex2f(lowX, highY);
    glVertex2f(highX, highY);
    glVertex2f(highX, lowY);

    // End
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
    translations[(currentIndex) * 2 + 0] = 0;
    translations[(currentIndex) * 2 + 1] = -1.5;
    glTranslatef(translations[currentIndex * 2 + 0], translations[currentIndex * 2 + 1], 0.0f);
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(-2.15, 0, 2.15, 3, colors + currentIndex * 3);
    translations[(currentIndex + 1) * 2 + 0] = 0; // Upper Body translations
    translations[(currentIndex + 1) * 2 + 1] = 3;
    translations[(currentIndex + 10) * 2 + 0] = -1.45; // Right Thigh Translations
    translations[(currentIndex + 10) * 2 + 1] = 0;
    translations[(currentIndex + 13) * 2 + 0] = 1.45; // Left Thigh Translations
    translations[(currentIndex + 13) * 2 + 1] = 0;
    glPushMatrix();
    
    // Upper Body
    currentIndex = 1;
    glTranslatef(translations[currentIndex * 2 + 0], translations[currentIndex * 2 + 1], 0.0f);
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(-3.15, 0, 3.15, 2.5, colors + currentIndex * 3);
    translations[(currentIndex + 1) * 2 + 0] = 0; // Neck Translations
    translations[(currentIndex + 1) * 2 + 1] = 2.5;
    translations[(currentIndex + 3) * 2 + 0] = 3.15; // Right Arm Translations
    translations[(currentIndex + 3) * 2 + 1] = 1.825;
    translations[(currentIndex + 6) * 2 + 0] = -3.15; // Left Arm Translations
    translations[(currentIndex + 6) * 2 + 1] = 1.825;
    glPushMatrix();

    // Neck
    currentIndex = 2;
    glTranslatef(translations[currentIndex * 2 + 0], translations[currentIndex * 2 + 1], 0.0f);
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(-0.85, 0, 0.85, 1.5, colors + currentIndex * 3);
    translations[(currentIndex + 1) * 2 + 0] = 0; // Head Translation
    translations[(currentIndex + 1) * 2 + 1] = 1.5;

    glPushMatrix();

    // Head
    currentIndex = 3;
    glTranslatef(translations[currentIndex * 2 + 0], translations[currentIndex * 2 + 1], 0.0f);
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(-1.5, 0, 1.5, 2, colors + currentIndex * 3);

    glPopMatrix();
    glPopMatrix();
    glPushMatrix();

    // Right Arm
    currentIndex = 4;
    glTranslatef(translations[currentIndex * 2 + 0], translations[currentIndex * 2 + 1], 0.0f);
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(0, -0.675, 1.6, 0.675, colors + currentIndex * 3);
    translations[(currentIndex + 1) * 2 + 0] = 1.6; // Right Forearm Translations
    translations[(currentIndex + 1) * 2 + 1] = 0;
    
    // Right Forearm
    currentIndex = 5;
    glTranslatef(translations[currentIndex * 2 + 0], translations[currentIndex * 2 + 1], 0.0f);
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(0, -0.675, 1.6, 0.675, colors + currentIndex * 3);
    translations[(currentIndex + 1) * 2 + 0] = 1.6; // Right Hand Translations
    translations[(currentIndex + 1) * 2 + 1] = 0;

    // Right Hand
    currentIndex = 6;
    glTranslatef(translations[currentIndex * 2 + 0], translations[currentIndex * 2 + 1], 0.0f);
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(0, -0.95, 1.3, 0.95, colors + currentIndex * 3);

    glPopMatrix();
    glPushMatrix();

    // Left Arm
    currentIndex = 7;
    glTranslatef(translations[currentIndex * 2 + 0], translations[currentIndex * 2 + 1], 0.0f);
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(-1.6, -0.675, 0, 0.675, colors + currentIndex * 3);
    translations[(currentIndex + 1) * 2 + 0] = -1.6; // Left Forearm Translations
    translations[(currentIndex + 1) * 2 + 1] = 0;

    // Left Forearm
    currentIndex = 8;
    glTranslatef(translations[currentIndex * 2 + 0], translations[currentIndex * 2 + 1], 0.0f);
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(-1.6, -0.67, 0, 0.67, colors + currentIndex * 3);
    translations[(currentIndex + 1) * 2 + 0] = -1.6; // Left Hand Translations
    translations[(currentIndex + 1) * 2 + 1] = 0;

    // Left Hand
    currentIndex = 9;
    glTranslatef(translations[currentIndex * 2 + 0], translations[currentIndex * 2 + 1], 0.0f);
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(-1.3, -0.95, 0, 0.95, colors + currentIndex * 3);
    
    glPopMatrix();
    glPopMatrix();
    glPushMatrix();

    // Right Thigh
    currentIndex = 10;
    glTranslatef(translations[currentIndex * 2 + 0], translations[currentIndex * 2 + 1], 0.0f);
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(-0.7, -2.5, 0.7, 0.0, colors + currentIndex * 3);
    translations[(currentIndex + 1) * 2 + 0] = 0; // Right Leg Translations
    translations[(currentIndex + 1) * 2 + 1] = -2.5;

    // Right Leg
    currentIndex = 11;
    glTranslatef(translations[currentIndex * 2 + 0], translations[currentIndex * 2 + 1], 0.0f);
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(-0.7, -2.5, 0.7, 0.0, colors + currentIndex * 3);
    translations[(currentIndex + 1) * 2 + 0] = 0; // Right Foot Translations
    translations[(currentIndex + 1) * 2 + 1] = -2.5;

    // Right Foot
    currentIndex = 12;
    glTranslatef(translations[currentIndex * 2 + 0], translations[currentIndex * 2 + 1], 0.0f);
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(-2, -1.0, 0.7, 0.0, colors + currentIndex * 3);

    glPopMatrix();
    glPushMatrix();

    // Left Thigh
    currentIndex = 13;
    glTranslatef(translations[currentIndex * 2 + 0], translations[currentIndex * 2 + 1], 0.0f);
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(0.7, -2.5, -0.7, 0.0, colors + currentIndex * 3);
    translations[(currentIndex + 1) * 2 + 0] = 0; // Left Leg Translations
    translations[(currentIndex + 1) * 2 + 1] = -2.5;

    // Left Leg
    currentIndex = 14;
    glTranslatef(translations[currentIndex * 2 + 0], translations[currentIndex * 2 + 1], 0.0f);
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(0.7, -2.5, -0.7, 0.0, colors + currentIndex * 3);
    translations[(currentIndex + 1) * 2 + 0] = 0; // Left Foot Translations
    translations[(currentIndex + 1) * 2 + 1] = -2.5;

    // Left Foot
    currentIndex = 15;
    glTranslatef(translations[currentIndex * 2 + 0], translations[currentIndex * 2 + 1], 0.0f);
    glRotatef(rotations[currentIndex], 0.0f, 0.0f, 1.0f);
    drawSquare(2, -1.0, -0.7, 0.0, colors + currentIndex * 3);

    glPopMatrix();

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
        // If possible, increment the rigIndex
        if (rigIndex < MAX_RIG_PARTS - 1) {
            rigIndex++;
        }
    }

    // Key press = "A/a"
    if (key == 65 || key == 97) {
        // Increment the rotation at the rigIndex
        rotations[rigIndex] += 1.0f;
    }

    // Key press = "S/s"
    if (key == 83 || key == 115) {
        // If possible, decrement the rigIndex
        if (rigIndex > 0) {
            rigIndex--;
        }
    }

    // Key press = "D/d"
    if (key == 68 || key == 100) {
        // Decrement the rotation at the rigIndex
        rotations[rigIndex] -= 1.0f;
    }

    // Highlight the current Rig at the rigIndex
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
    glutKeyboardUpFunc(keyboardUp);
    glutMainLoop();
    return 0;
}