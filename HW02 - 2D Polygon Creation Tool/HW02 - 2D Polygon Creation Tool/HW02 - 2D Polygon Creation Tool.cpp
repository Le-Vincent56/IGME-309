// Course: IGME 309
// Student Name: Vincent Le
// Assignment Number: 02

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <vector>
#include "PolyObject.h"
using namespace std;

float canvasSize[] = { 10.0f, 10.0f };
int rasterSize[] = { 800, 600 };
vec3 color = vec3(1.0, 0.0, 0.0);

float mousePos[2];

vector<PolyObject> polygonList;
PolyObject polygon;

void init(void)
{
    mousePos[0] = mousePos[1] = 0.0f;
    color[0] = 1.0f;
    color[1] = color[2] = 0.0f;

    // Create a polygon then push it to the back
    polygon = PolyObject();
    polygon.setColor(color);
}

void drawCursor()
{
    glColor3f(1.0f, 0.0f, 1.0f);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex2fv(mousePos);
    glEnd();
    glPointSize(1.0f);
}

void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw all finished polygons
    for (int i = 0; i < polygonList.size(); i++) {
        polygonList[i].draw();
    }

    // Draw the current polygon
    polygon.draw(vec2(mousePos[0], mousePos[1]));

    drawCursor();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    rasterSize[0] = w;
    rasterSize[1] = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, canvasSize[0], 0.0, canvasSize[1]);
    glViewport(0, 0, rasterSize[0], rasterSize[1]);

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Calculate the vertex using the mouse position
        mousePos[0] = (float)x / rasterSize[0] * canvasSize[0];
        mousePos[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];

        // Add the vertex to the polygon object
        polygon.addVertex(vec2(mousePos[0], mousePos[1]));

        // call glutPostRedisplay()
        glutPostRedisplay();
    }
}

void motion(int x, int y)
{
    // mouse events are handled by OS, eventually. When using mouse in the raster window, it assumes top-left is the origin.
    // Note: the raster window created by GLUT assumes bottom-left is the origin.
    mousePos[0] = (float)x / rasterSize[0] * canvasSize[0];
    mousePos[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);
            break;

        // Press D to stop creating and draw final
        case 100:
            // Add the polygon into the list
            polygonList.push_back(polygon);

            // Reset the polygon
            polygon = PolyObject();
            polygon.setColor(color);

            // Update the display
            glutPostRedisplay();
            break;
    }
}

void menu(int value)
{
    switch (value) {
    case 0: // clear
        // Clear the polygon list
        polygonList.clear();
        glutPostRedisplay();
        break;
    case 1:
        // Exit
        exit(0);
    case 2:
        // Set color to red
        color = vec3(1.0, 0.0, 0.0);
        polygon.setColor(color);
        glutPostRedisplay();
        break;
    case 3:
        // Set color to green
        color = vec3(0.0, 1.0, 0.0);
        polygon.setColor(color);
        glutPostRedisplay();
        break;
    case 4:
        // Set color to blue
        color = vec3(0.0, 0.0, 1.0);
        polygon.setColor(color);
        glutPostRedisplay();
        break;
    default:
        break;
    }
}
void createMenu()
{
    int colorMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Red", 2);
    glutAddMenuEntry("Green", 3);
    glutAddMenuEntry("Blue", 4);

    glutCreateMenu(menu);
    glutAddMenuEntry("Clear", 0);
    glutAddSubMenu("Colors", colorMenu);
    glutAddMenuEntry("Exit", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char* argv[])
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(rasterSize[0], rasterSize[1]);
    glutCreateWindow("Draw a 2D Polygon");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion);
    createMenu();
    glutMainLoop();
    return 0;


}