#include "MyHunter.h"

MyHunter::MyHunter(vec2 _position, int _ID)
{
	this->ID = _ID;

	/****************************/
	// write your code below
	// customize your player

	// customize the name of your player
	playerName = "Quickdraw Hunter" + to_string(ID);

	// upgrade your player by calling the upgrade(armor, speed, shotgun, bullet) function
	// You have a total of 20 points for upgrading, 
	// and each attribute (armor, speed, shotgun, and bullet) can’t exceed 10 points. 
	unsigned int armorPoint = 2;
	unsigned int speedPoint = 10;
	unsigned int shotgunPoint = 2;
	unsigned int bulletPoint = 6;
	upgrade(armorPoint, speedPoint, shotgunPoint, bulletPoint);

	// customize the color of your player
	bodyColor = vec3(1.0f, 0.0f, 0.0f);
	headColor = vec3(0.7f, 0.1f, 0.1f);
	shotgunColor = vec3(0.0f, 0.0f, 0.0f);
	bulletColor = vec3(0.0f, 0.0f, 0.0f);
	// write your code above
	/******************************/

	this->position = _position;
	reloadTimer = reloadDuration * (1.0f + rand() % 10 / 20.0f);
	life = maxLife;

	nearestMonster = nullptr;
}

void MyHunter::update(float _deltaTime, const vector<Monster*> _monsters, const vector<Hunter*> _players)
{
	if (isActived == true) {
		// shoot bullet
		reloadTimer -= _deltaTime;
		if (reloadTimer < 0.0f) {
			fire();
			reloadTimer = reloadDuration * (1.0f + rand() % 10 / 20.0f);
		}

		/*********************************************/
		// Write your implementation below:
		// 1. Update the hunter's position: Utilize the 'speed' variable and 'deltaTime' to calculate the new position.
		// 2. Update the hunter's rotation: Adjust the rotation based on the current game logic or input.

		// Provided Example:
		// The following example code demonstrates how to locate the nearest monster:
		float minDis = 1000.0f;

		for (int i = 0; i < _monsters.size(); i++) {
			if (_monsters[i]->isActived == false)
				continue;
			float dist = distance(this->position, _monsters[i]->position);
			if (dist < minDis - 10.0f) {
				minDis = dist;
				nearestMonster = _monsters[i];
			}
		}

		// Check if nearest monster is set
		if (nearestMonster != nullptr) {
			// Update position to flee from the nearest monster
			position += flee(nearestMonster->position, 3.0f) * _deltaTime;

			// Update position to separate from other hunters
			position += separate(_players) * _deltaTime;

			// Set rotation to look towards the nearest monster
			this->rotation = atan(normalize(this->position - nearestMonster->position).x, normalize(this->position - nearestMonster->position).y);
		}

		// Write your implementation above
		/************************************************************/

		// ensure the hunter stay in the battleground
		if (this->position.x < -300.0f + radius)
			this->position.x = -300.0f + radius;
		if (this->position.y < -300.0f + radius)
			this->position.y = -300.0f + radius;
		if (this->position.x > 300.0f - radius)
			this->position.x = 300.0f - radius;
		if (this->position.y > 300.0f - radius)
			this->position.y = 300.0f - radius;
	}
}

vec2 MyHunter::flee(vec2 _positionToFlee, float weight) {
	vec2 fleeForce = normalize(this->position - _positionToFlee) * speed * weight;
	return fleeForce;
}

vec2 MyHunter::separate(vector<Hunter*> _players) {
	vec2 separateForce = vec2(0.0f, 0.0f);
	float sqrPersonalSpace = pow(this->personalSpace, 2);

	// Loop through all other players
	for (int i = 0; i < _players.size(); i++) {
		if (_players[i] != this) {
			// Find the square distance between the two agents
			float sqrtDist = glm::sqrt(distance(this->position, _players[i]->position));

			// Modify weight depending on how close the other player is
			if (sqrtDist < sqrPersonalSpace) {
				float weight = sqrPersonalSpace / (sqrtDist + 0.1f);
				separateForce += flee(_players[i]->position, weight);
			}	
		}
	}
	
	return separateForce;
}

bool MyHunter::circleCollision(vec2 c1, vec2 c2, float r1, float r2)
{
	/***************************************/
	// return whether or not two circles are intersected
	return false;
	/***************************************/
}

void MyHunter::collisionDetection(vector<Monster*> _monsters)
{
	if (isActived == true) {
		for (int i = 0; i < _monsters.size(); i++) {
			if (_monsters[i]->isActived) {
				if (circleCollision(this->position, _monsters[i]->position, this->radius, _monsters[i]->radius)) {
					this->life--;
					if (this->life <= 0) {
						bodyColor = 0.5f * bodyColor;
						headColor = 0.5f * headColor;
						shotgunColor = 0.5f * shotgunColor;
						isActived = false;
						return;
					}
					_monsters[i]->attackPlayer(this->ID);
				}
			}
		}
	}
}

void MyHunter::draw()
{
	glPushMatrix();

	glTranslatef(position.x, position.y, 0);
	drawLifeBar();

	glRotatef(rotation, 0, 0, 1);

	glColor3f(bodyColor.x, bodyColor.y, bodyColor.z);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 30; i++) {
		float angle = 2 * pi<float>() * i / 30;
		glVertex2f(radius * cos(angle), radius * sin(angle));
	}
	glEnd();

	glColor3f(shotgunColor.x, shotgunColor.y, shotgunColor.z);
	glBegin(GL_POLYGON);
	glVertex2f(0.0f, -1.0f);
	glVertex2f(radius * 1.5f, -1.0f);
	glVertex2f(radius * 1.5f, 1.0f);
	glVertex2f(0.0f, 1.0f);
	glEnd();

	glColor3f(headColor.x, headColor.y, headColor.z);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 30; i++) {
		float angle = 2 * pi<float>() * i / 30;
		glVertex2f(0.5f * radius * cos(angle), 0.5f * radius * sin(angle));
	}
	glEnd();

	if (nearestMonster != nullptr) {
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex2f(this->position.x, this->position.y);
		glVertex2f(nearestMonster->position.x, nearestMonster->position.y);
		glEnd();
	}

	glPopMatrix();
}

void MyHunter::drawLifeBar()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex2f(-1.0f * radius, 1.2f * radius);
	glVertex2f((-1.0f + 2.0f * life / maxLife) * radius, 1.2f * radius);
	glVertex2f((-1.0f + 2.0f * life / maxLife) * radius, 1.5f * radius);
	glVertex2f(-1.0f * radius, 1.5f * radius);
	glEnd();
}


void MyHunter::fire()
{
	Bullet::bullets.push_back(new Bullet(this->position, this->rotation, this, this->bulletSpeed, this->bulletColor));
}

void MyHunter::getDamagePoint(int _damage)
{
	damage += _damage;
}

void MyHunter::getScore(int _score)
{
	score += _score;
}

void MyHunter::upgrade(unsigned int _armor, unsigned int _speed, unsigned int _shotgun, unsigned int _bullet)
{
	if (_armor + _speed + _shotgun + _bullet > 20)
		return;
	if (_armor > 10 || _speed > 10 || _shotgun > 10 || _bullet > 10)
		return;
	maxLife += _armor;
	speed *= 1.0f + _speed / 10.0f;
	reloadDuration *= 1.0f - _shotgun / 15.0f;
	bulletSpeed *= 1.0f + _bullet / 10.0f;
}