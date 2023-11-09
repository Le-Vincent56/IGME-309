#include <GL/glew.h>
#include <GL/freeglut.h>
#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem(int _numParticles)
{
	numParticles = _numParticles;	// Set the number of particles

	// Allocate memory for positions, velocities, colors, and lifetimes.
	positions = new float[numParticles * 3];
	velocities = new float[numParticles * 3];
	colors = new float[numParticles * 4];
	lifeTimes = new float[numParticles];

	for (int i = 0; i < numParticles; i++) {
		// Initialize the life times
		lifeTimes[i] = maxLifeTime - maxLifeTime * i / numParticles;

		/***************************/
		// Write your code below
		// Please add initializations for other arrays as you see appropriate.
		
		// Positions initialization
		positions[i * 3 + 0] = 0;
		positions[i * 3 + 1] = 0;
		positions[i * 3 + 2] = 0;

		// Velocity initialization
		velocities[i * 3 + 0] = getRandomValue(minSpeedX, maxSpeedX);
		velocities[i * 3 + 1] = getRandomValue(minSpeedY, maxSpeedY);
		velocities[i * 3 + 2] = getRandomValue(minSpeedZ, maxSpeedZ);

		// Colors initialization
		colors[i * 4 + 0] = 0;
		colors[i * 4 + 1] = 0;
		colors[i * 4 + 2] = 255;
		colors[i * 4 + 3] = 255;

		/***************************/
	}
}

void ParticleSystem::update(float deltaTime)
{
	for (int i = 0; i < numParticles; i++) {
		/***************************/
		// Write your code below
		// Update lifetime, velocity, position, and color.
		// Reset particle states (positions, velocities, colors, and lifetimes) when the lifetime reaches the maxLifeTime
		// 
		// Add deltaTime to the lifeTimes of this particle
		lifeTimes[i] += deltaTime;

		// Check if the lifetime has reached the max, if so, reinitialize the particle
		if (lifeTimes[i] >= 5) {
			// Reset lifetime
			lifeTimes[i] = maxLifeTime - maxLifeTime * i / numParticles;

			// Positions initialization
			positions[i * 3 + 0] = 0;
			positions[i * 3 + 1] = 0;
			positions[i * 3 + 2] = 0;

			// Velocity initialization
			velocities[i * 3 + 0] = getRandomValue(minSpeedX, maxSpeedX);
			velocities[i * 3 + 1] = getRandomValue(minSpeedY, maxSpeedY);
			velocities[i * 3 + 2] = getRandomValue(minSpeedZ, maxSpeedZ);

			// Colors initialization
			colors[i * 4 + 0] = 0;
			colors[i * 4 + 1] = 0;
			colors[i * 4 + 2] = 255;
			colors[i * 4 + 3] = 255;
		}

		// Change velocity based on acceleration and deltaTime
		velocities[i * 3 + 0] += acceleration[0] * deltaTime;
		velocities[i * 3 + 1] += acceleration[1] * deltaTime;
		velocities[i * 3 + 2] += acceleration[2] * deltaTime;

		// Update positions based on velocities
		positions[i * 3 + 0] += velocities[i * 3 + 0] * deltaTime;
		positions[i * 3 + 1] += velocities[i * 3 + 1] * deltaTime;
		positions[i * 3 + 2] += velocities[i * 3 + 2] * deltaTime;

		// Update alpha channel based on the ratio of the lifeTime to maxLifeTime
		colors[i * 4] *= (lifeTimes[i] / maxLifeTime);

		// Write your code above
		/***************************/
	}
}

void ParticleSystem::draw()
{
	/***************************/
	// Write your code below
	// Use GL_POINTS for rendering

	glPointSize(3);
	glBegin(GL_POINTS);
	for (int i = 0; i < numParticles; i++) {
		// Change colors
		glColor4f(colors[i * 4 + 0], colors[i * 4 * 1], colors[i * 4 + 2], colors[i * 4 + 3]);

		// Draw positions
		glVertex3f(positions[i * 3 + 0], positions[i * 3 + 1], positions[i * 3 + 2]);
	}
	glEnd();

	// Write your code above
	/***************************/
}

float ParticleSystem::getRandomValue(float min_value, float max_value)
{
	return min_value + (std::rand()) / (RAND_MAX / (max_value - min_value));;
}
