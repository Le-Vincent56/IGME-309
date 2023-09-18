// Course: 		    IGME 309
// Student Name: 	Vincent Le
// Friday Exercise: 03

#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#endif

// The window's width and height
int width, height;

// Christmas tree triangles
// Bottom triangle verticies
float bv1[2];
float bv2[2];
float bv3[2];

// Middle triangle vertices
float mv1[2];
float mv2[2];
float mv3[2];

// Top triangle vertices
float tv1[2];
float tv2[2];
float tv3[2];

// Christmas tree trunk
// Trunk vertices
float trv1[2];
float trv2[2];
float trv3[2];
float trv4[2];

// Christmas tree ornaments
float ov1[2];
float ov2[2];
float ov3[2];
float ov4[2];
float ov5[2];

void InitializeVertices() {
    // Initialize the bottom's vertices
    bv1[0] = -1.5f;
    bv1[1] = 0.0f;
    bv2[0] = 1.5f;
    bv2[1] = 0.0f;
    bv3[0] = 0.0f;
    bv3[1] = 2.5f;

    // Initialize the middle's vertices
    mv1[0] = -1.5f;
    mv1[1] = 2.5f;
    mv2[0] = 1.5f;
    mv2[1] = 2.5f;
    mv3[0] = 0.0f;
    mv3[1] = 5.0f;

    // Initialize the middle's vertices
    tv1[0] = -1.5f;
    tv1[1] = 5.0f;
    tv2[0] = 1.5f;
    tv2[1] = 5.0f;
    tv3[0] = 0.0f;
    tv3[1] = 7.5f;

    // Initialize the trunk
    trv1[0] = -0.5f;
    trv1[1] = 0.0f;
    trv2[0] = 0.5f;
    trv2[1] = 0.0f;
    trv3[0] = 0.5f;
    trv3[1] = -1.0f;
    trv4[0] = -0.5f;
    trv4[1] = -1.0f;

    // Initialize ornaments
    ov1[0] = -0.25f;
    ov1[1] = 3.5f;
    ov2[0] = 0.65f;
    ov2[1] = 2.75f;
    ov3[0] = -0.15f;
    ov3[1] = 0.85f;
    ov4[0] = 0.75f;
    ov4[1] = 6.25;
    ov5[0] = -0.35f;
    ov5[1] = 5.5f;
}

// Initialize
void init(void)
{
    // initialize the size of the window
    width = 600;
    height = 600;
    InitializeVertices();
}

// Draw a triangle
void DrawTriangle(float v1[], float v2[], float v3[]) {
    glBegin(GL_TRIANGLES);
    glVertex2fv(v1);
    glVertex2fv(v2);
    glVertex2fv(v3);
    glEnd();
}

// Draw a point
void DrawPoint(float v1[], float pointSize) {
    glPointSize(pointSize);
    glBegin(GL_POINTS);
    glVertex2fv(v1);
    glEnd();
    glPointSize(1.0f);
}

// Draw the tree
void DrawTree() {
    // Draw triangles for the tree
    DrawTriangle(bv1, bv2, bv3);
    DrawTriangle(mv1, mv2, mv3);
    DrawTriangle(tv1, tv2, tv3);
}

// Draw the trunk
void DrawTrunk() {
    // Draw the trunk
    glBegin(GL_POLYGON);
    glVertex2fv(trv1);
    glVertex2fv(trv2);
    glVertex2fv(trv3);
    glVertex2fv(trv4);
    glEnd();
}

void DrawOrnaments() {
    DrawPoint(ov1, 17.5f);
    DrawPoint(ov2, 30.0f);
    DrawPoint(ov3, 22.5f);
    DrawPoint(ov4, 25.0f);
    DrawPoint(ov5, 22.5f);
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

    // Change color to brown
    glColor3f(0.6f, 0.3f, 0.0f);

    // Draw the trunk
    DrawTrunk();

    // Change color to green
    glColor3f(0.0, 1.0, 0.0);

    // Draw the tree
    DrawTree();

    // Change color to red
    glColor3f(1.0, 0.0, 0.0);

    // Draw the ornaments
    DrawOrnaments();

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
    gluOrtho2D(-5, 5.0, -2.5, 10);
    //gluOrtho2D(-5.0, 5.0, -5.0, 5.0);

    /* tell OpenGL to use the whole window for drawing */
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

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

    //register function to handle window resizes
    glutReshapeFunc(reshape);

    //register function that draws in the window
    glutDisplayFunc(display);

    //start the glut main loop
    glutMainLoop();

    return 0;
}