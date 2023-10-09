#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include "PolyObject.h"

PolyObject::PolyObject()
{
}

PolyObject::~PolyObject()
{
}

void PolyObject::addVertex(vec2 p_vert)
{
	// Add a vertex to the poly object
	vertices.push_back(p_vert);
}

void PolyObject::setColor(vec3 p_color)
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
	// Set color
	glColor3f(color.x, color.y, color.z);

	// Check vertices
	if (vertices.size() == 1) {
		// If 1, draw using points
		glBegin(GL_POINTS);
		glVertex2f(vertices[0].x, vertices[0].y);
		glEnd();
	}
	else if (vertices.size() == 2) {
		// If 2, draw using lines
		glBegin(GL_LINES);
		glVertex2f(vertices[0].x, vertices[0].y);
		glVertex2f(vertices[1].x, vertices[1].y);
		glEnd();
	}
	else if (vertices.size() > 2) {
		// If greater than 2, draw using polygons
		glBegin(GL_POLYGON);
		for (int i = 0; i < vertices.size(); i++) {
			glVertex2f(vertices[i].x, vertices[i].y);
		}
		glEnd();
	}
}

void PolyObject::draw(vec2 p_mousePos)
{
	// Set color
	glColor3f(color.x, color.y, color.z);

	// Check vertices
	if (vertices.size() == 1) {
		// If 1, draw a line from the point to the mouse
		glBegin(GL_LINES);
		glVertex2f(vertices[0].x, vertices[0].y);
		glVertex2f(p_mousePos.x, p_mousePos.y);
		glEnd();
	}
	else if (vertices.size() >= 2) {
		// If 2 or more, draw a polygon from the two points to the mouse
		glBegin(GL_POLYGON);
		for (int i = 0; i < vertices.size(); i++) {
			glVertex2f(vertices[i].x, vertices[i].y);
		}
		glVertex2f(p_mousePos.x, p_mousePos.y);
		glEnd();
	}
}
