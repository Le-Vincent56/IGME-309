#include "MyMesh.h"
#include <GL/freeglut.h>

#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
using namespace std;

MyMesh::MyMesh()
{
	vertNum = triNum = 0;
	vertices = NULL;
	indices = NULL;
	vertColors = NULL;
}

MyMesh::~MyMesh()
{
	if (vertices != NULL)
		delete[] vertices;
	if (indices != NULL)
		delete[] indices;

	if (vertColors != NULL)
		delete[] vertColors;
}

void MyMesh::load(char* fileName)
{
	vertNum = 0;
	triNum = 0;

	vertices = new float[100 * 2];
	indices = new unsigned int[100 * 3];
	vertColors = new float[100 * 3];

	ifstream file(fileName);

	if (!file.is_open()) {
		// Handle error
	}

	/****************************************/
	// Write your code below

	// Loop through each line in the file
	string line;
	string data1, data2, data3;
	while (getline(file, line)) {
		// Check if the line starts with 'v' (vertex)
		if (line[0] == 'v') {
			float x, y;

			// Find X and Y coordinates
			sscanf_s(line.c_str(), "v %f %f", &x, &y);

			// Store the vertex in the temporary array
			vertices[vertNum * 2] = x;
			vertices[vertNum * 2 + 1] = y;
			vertNum++;
		}
		// Check if the line starts with 'f' (face)
		else if (line[0] == 'f') {
			unsigned int v1, v2, v3;

			// Find the indices of the triangle
			sscanf_s(line.c_str(), "f %u %u %u", &v1, &v2, &v3);

			// Store the vertex indices in the temporary array
			indices[triNum * 3] = v1 - 1; // Subtract 1 to convert to 0-based index
			indices[triNum * 3 + 1] = v2 - 1;
			indices[triNum * 3 + 2] = v3 - 1;
			triNum++;
		}
	}

	// Close the file
	file.close();
	// Write your code above
	/****************************************/

	// generate random vertex colors
	for (unsigned int i = 0; i < vertNum; i++) {
		vertColors[i * 3 + 0] = float(rand()) / (RAND_MAX + 1);
		vertColors[i * 3 + 1] = float(rand()) / (RAND_MAX + 1);
		vertColors[i * 3 + 2] = float(rand()) / (RAND_MAX + 1);
	}
}

void MyMesh::load(const unsigned int p_vertNum, const unsigned int p_triNum, const float* p_vertices, const unsigned int* p_indices)
{
	vertNum = p_vertNum;
	triNum = p_triNum;

	vertices = new float[vertNum * 2];
	indices = new unsigned int[triNum * 3];
	vertColors = new float[vertNum * 3];

	for (unsigned int i = 0; i < vertNum * 2; i++) {
		vertices[i] = p_vertices[i];
	}

	for (unsigned int i = 0; i < triNum * 3; i++) {
		indices[i] = p_indices[i];
	}

	// generate random vertex colors
	for (unsigned int i = 0; i < vertNum; i++) {
		vertColors[i * 3 + 0] = float(rand()) / (RAND_MAX + 1);
		vertColors[i * 3 + 1] = float(rand()) / (RAND_MAX + 1);
		vertColors[i * 3 + 2] = float(rand()) / (RAND_MAX + 1);
	}

}

void MyMesh::update()
{
	// we will use this for transformations later.... 
}

void MyMesh::draw()
{
	for (int i = 0; i < triNum; ++i) {
		glBegin(GL_TRIANGLES);
		glColor3fv(vertColors + indices[i * 3 + 0] * 3);
		glVertex2fv(vertices + indices[i * 3 + 0] * 2);

		glColor3fv(vertColors + indices[i * 3 + 1] * 3);
		glVertex2fv(vertices + indices[i * 3 + 1] * 2);

		glColor3fv(vertColors + indices[i * 3 + 2] * 3);
		glVertex2fv(vertices + indices[i * 3 + 2] * 2);
		glEnd();
	}
}