// Course: 		        IGME 309
// Student Name: 	    Vincent Le
// Assignment Number:   01

#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#endif
#include <math.h>

// The window's width and height
int width, height;

// Set amount of vertices for all shapes - range of 3-100
int vertices = 100;

// Initialize
void init(void)
{
    // initialize the size of the window
    width = 600;
    height = 600;
}

// Draws a filled circle with a specified color at specific center with a given radius
void drawFilledCircle(float red, float green, float blue, float center_x, float center_y, float radius) {
    // Set color
    glColor3f(red, green, blue);

    // Begin drawing a polygon
    glBegin(GL_POLYGON);

    // Set for how many vertices
    for (int i = 0; i < vertices; i++) {
        // Calculate the angle in radians
        float angleRads = (2.0f * 3.1415f * i) / vertices;

        // Calculate points
        float pointX = radius * cosf(angleRads);
        float pointY = radius * sinf(angleRads);

        glVertex2f(center_x + pointX, center_y + pointY);
    }

    // End drawing
    glEnd();
}

// Draws a wireframe circle with a specified color at a specified center with a given radius and line width
void drawWireframeCircle(float red, float green, float blue, float center_x, float center_y, float radius, float lineWidth) {
    // Set color
    glColor3f(red, green, blue);

    // Set line width
    glLineWidth(lineWidth);

    // Begin drawing a line loop
    glBegin(GL_LINE_LOOP);

    // Set for how many vertices
    for (int i = 0; i < vertices; i++) {
        // Calculate the angle in radians
        float angleRads = (2.0f * 3.1415f * i) / vertices;

        // Calculate points
        float pointX = radius * cosf(angleRads);
        float pointY = radius * sinf(angleRads);

        glVertex2f(center_x + pointX, center_y + pointY);
    }

    // End drawing
    glEnd();
}

// called when the GL context need to be rendered
void display(void)
{
    // clear the screen to white, which is the background color
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // clear the buffer stored for drawing
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // ----- Draw the body -----
    drawFilledCircle(0.0f, 0.0f, 0.0f, 5.0, 4.0, 1.75);

    // ----- Draw the feet -----
    // Upper-left
    drawFilledCircle(1.0f, 1.0f, 1.0f, 3.3, 4.5, 0.65);
    drawWireframeCircle(0.0f, 0.0f, 0.0f, 3.3, 4.5, 0.65, 4);
    drawFilledCircle(0.89f, 0.63f, 0.81f, 3.3, 4.25, 0.35);

    // Upper-right
    drawFilledCircle(1.0f, 1.0f, 1.0f, 6.7, 4.5, 0.65);
    drawWireframeCircle(0.0f, 0.0f, 0.0f, 6.7, 4.5, 0.65, 4);
    drawFilledCircle(0.89f, 0.63f, 0.81f, 6.7, 4.25, 0.35);

    // Bottom-left
    drawFilledCircle(1.0f, 1.0f, 1.0f, 5.75, 2.3, 0.65);
    drawWireframeCircle(0.0f, 0.0f, 0.0f, 5.75, 2.3, 0.65, 4);
    drawFilledCircle(0.89f, 0.63f, 0.81f, 5.75, 2.05, 0.35);

    // Bottom-right
    drawFilledCircle(1.0f, 1.0f, 1.0f, 4.25, 2.3, 0.65);
    drawWireframeCircle(0.0f, 0.0f, 0.0f, 4.25, 2.3, 0.65, 4);
    drawFilledCircle(0.89f, 0.63f, 0.81f, 4.25, 2.05, 0.35);

    // ----- Draw the head -----
    drawFilledCircle(1.0f, 1.0f, 1.0f, 5.0, 6.75, 1.75);
    drawWireframeCircle(0.0f, 0.0f, 0.0f, 5.0, 6.75, 1.75, 4);

    // ----- Draw the ears -----
    // Left ear
    drawFilledCircle(0.0f, 0.0f, 0.0f, 3.75, 8.15, 0.85);
    drawFilledCircle(0.22f, 0.22f, 0.22f, 3.925, 7.8, 0.4);

    // Right ear
    drawFilledCircle(0.0f, 0.0f, 0.0f, 6.25, 8.15, 0.85);
    drawFilledCircle(0.22f, 0.22f, 0.22f, 6.075, 7.8, 0.4);

    // ----- Draw the eyes -----
    // Left eye
    drawFilledCircle(0.0f, 0.0f, 0.0f, 4.25, 6.75, 0.5);
    drawFilledCircle(1.0f, 1.0f, 1.0f, 4.4, 6.75, 0.25);

    // Right eye
    drawFilledCircle(0.0f, 0.0f, 0.0f, 5.75, 6.75, 0.5);
    drawFilledCircle(1.0f, 1.0f, 1.0f, 5.6, 6.75, 0.25);

    // ----- Draw the glasses -----
    // Lenses
    drawWireframeCircle(0.0f, 0.0f, 0.0f, 5.75, 6.75, 0.6, 4);
    drawWireframeCircle(0.0f, 0.0f, 0.0f, 4.25, 6.75, 0.6, 4);

    // Bridge
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(4.85f, 6.75f);
    glVertex2f(5.15f, 6.75f);
    glEnd();

    // ----- Draw the nose -----
    drawFilledCircle(0.0f, 0.0f, 0.0f, 5.0, 5.9, 0.4);
    drawFilledCircle(0.4f, 0.4f, 0.4f, 4.8, 5.7, 0.10);
    drawFilledCircle(0.4f, 0.4f, 0.4f, 5.2, 5.7, 0.10);

    glutSwapBuffers();
}

// called when window is first created or when window is resized
void reshape(int w, int h)
{
    // update thescreen dimensions
    width = w;
    height = h;

    //do an orthographic parallel projection, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 10, 0, 10);
    //gluOrtho2D(-5.0, 5.0, -5.0, 5.0);

    /* tell OpenGL to use the whole window for drawing */
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    // Press '-' to subtract the number of vertices, to a minimum of 3
    if (key == '-') {
        if (vertices > 3) {
            vertices--;
        }
    }

    // Press '+' to add to the number of vertices, to a maximum of 3
    if (key == '+') {
        if (vertices < 100) {
            vertices++;
        }
    }

    // Update display
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    // before create a glut window,
    // initialize stuff not opengl/glut dependent
    init();

    //initialize GLUT, let it extract command-line GLUT options that you may provide
    //NOTE that the '&' before argc
    glutInit(&argc, argv);

    // specify as double bufferred can make the display faster
    // Color is speicfied to RGBA, four color channels with Red, Green, Blue and Alpha(depth)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    //set the initial window size */
    glutInitWindowSize((int)width, (int)height);

    // create the window with a title
    glutCreateWindow("First OpenGL Program");

    /* --- register callbacks with GLUT --- */

    // Register function to handle window resizes
    glutReshapeFunc(reshape);

    // Register function that draws in the window
    glutDisplayFunc(display);

    // Register function that takes keyboard input
    glutKeyboardFunc(keyboard);

    //start the glut main loop
    glutMainLoop();

    return 0;
}