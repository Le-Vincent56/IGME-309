#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <ctime>
#include <cmath>

using namespace std;

float canvasSize[] = { 20.0f, 20.0f };
int rasterSize[] = { 600, 600 };

// tracking the game time - millisecond 
unsigned int curTime = 0;
unsigned int preTime = 0;
float deltaTime = 0;

float rotationAngle = 0.0f;
float rotateSpeed = 90.0f;
int vertNum = 30;
float radius = 2.0f;

// Draws a filled circle with a specified color at specific center with a given radius
void drawFilledCircle(float red, float green, float blue, float center_x, float center_y, float radius) {
	// Set color
	glColor3f(red, green, blue);

	// Begin drawing a polygon
	glBegin(GL_POLYGON);

	// Set for how many vertices
	for (int i = 0; i < vertNum; i++) {
		// Calculate the angle in radians
		float angleRads = (2.0f * 3.1415f * i) / vertNum;

		// Calculate points
		float pointX = radius * cosf(angleRads);
		float pointY = radius * sinf(angleRads);

		glVertex2f(center_x + pointX, center_y + pointY);
	}

	// End drawing
	glEnd();
}

void display(void)
{
	glClearColor(0.9f, 0.9f, 0.7f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	/*****************************/
	// write your code below

	// Draw anchor
	drawFilledCircle(0.0f, 0.0f, 0.0f, 10.0f, 14.0f, 0.1f);

	// Apply transformations
	glTranslatef(10.0f, 14.0f, 0.0f); // Translate by anchorX and anchorY
	glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f); // Rotate by the rotationAngle around the z-axis
	glTranslatef(-10.0f, -14.0f, 0.0f); // Translate by -anchorX and -anchorY

	// Draw line segment
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(10.0f, 14.0f);
	glVertex2f(10.0f, 6.0f);
	glEnd();

	// Draw circle
	drawFilledCircle(1.0f, 1.0f, 1.0f, 10.0f, 6.0f, radius);

	// write your code above
	/*****************************/

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	rasterSize[0] = w;
	rasterSize[1] = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, canvasSize[0], 0, canvasSize[1]);
	glViewport(0, 0, rasterSize[0], rasterSize[1]);

	glutPostRedisplay();
}


void update() {
	curTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (float)(curTime - preTime) / 1000.0f; 


	if (rotationAngle > 45.0f) {
		rotateSpeed = -abs(rotateSpeed);
	}
	else if (rotationAngle < -45.0f) {
		rotateSpeed = abs(rotateSpeed);
	}
	rotationAngle += deltaTime * rotateSpeed;

	preTime = curTime;
	glutPostRedisplay();
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(rasterSize[0], rasterSize[1]);
	glutCreateWindow("Simple Pendulum");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(update);
	
	preTime = glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();
	return 0;
}