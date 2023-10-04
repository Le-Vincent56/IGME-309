#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include "PolyObject.h"

PolyObject::PolyObject()
{
	color = new float[3];
}

PolyObject::~PolyObject()
{
	delete[] color;
	color = nullptr;
}

void PolyObject::addVertex(vec2 p_vert)
{
	// Add a vertex to the poly object
	vertices.push_back(p_vert);
}

void PolyObject::setColor(float* p_color)
{
	// Set the color of the poly object
	color = p_color;
}

unsigned int PolyObject::getVertNum()
{
	// Return the size of the vertex vector
	return vertices.size();
}

void PolyObject::draw()
{
}

void PolyObject::draw(vec2 p_mousePos)
{
	glColor3fv(color);

	if (vertices.size() == 1) {
		glBegin(GL_LINES);
		glVertex2f(vertices[0].x, vertices[0].y);
		glVertex2f(p_mousePos.x, p_mousePos.y);
		glEnd();
	}
	else if (vertices.size() >= 2) {
		glBegin(GL_POLYGON);
		for (int i = 0; i < vertices.size(); i++) {
			glVertex2f(vertices[i].x, vertices[i].y);
		}
		glVertex2f(p_mousePos.x, p_mousePos.y);
		glEnd();
	}
}
