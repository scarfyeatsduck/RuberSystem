
# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

class Warship {

public:

	char * modelFile;
	float boundingRadius;
	const GLuint nVertices = 1752;
	bool controllable = false;

	float turnSpeed = 0.05f;
	float moveSpeed = 10.0f;

	glm::mat4 position;
	glm::mat4 rotation;
	glm::mat4 orientation;
	glm::mat4 bCam = glm::mat4();
	glm::mat4 nCam = glm::mat4();
	glm::mat4 tCam = glm::mat4();

	Warship(char * given) {

		modelFile = given;
		position = glm::mat4();
		rotation = glm::mat4();

		bCam[3][1] = 300.0f;
		bCam[3][2] = -1000.0f;

		nCam[3][2] = -600.0f;

		tCam[3][1] = 300.0f;

	}

	void update() {

		orientation = position * rotation;

	}

	glm::mat4 getModelMatrix() {

		return (position * rotation);

	}

	void setLocation(float x, float y, float z) {

		position[3][0] = x;
		position[3][1] = y;
		position[3][2] = z;

	}

	void setLocation(glm::vec3 location) {

		position[3][0] = location[0];
		position[3][1] = location[1];
		position[3][2] = location[2];

	}

	void setRotation(glm::vec3 right, glm::vec3 up, glm::vec3 at) {

		rotation[0][0] = right[0];
		rotation[0][1] = right[1];
		rotation[0][2] = right[2];

		rotation[1][0] = up[0];
		rotation[1][1] = up[1];
		rotation[1][2] = up[2];

		rotation[2][0] = at[0];
		rotation[2][1] = at[1];
		rotation[2][2] = at[2];

	}

	void resetRotation() {

		rotation = glm::mat4();

	}

	float getX() {

		return position[3][0];

	}

	float getY() {

		return position[3][1];

	}

	float getZ() {

		return position[3][2];

	}

	glm::vec3 getEye() {

		return getPosition(orientation * bCam);

	}

	glm::vec3 getEyeAlt() {

		return getPosition(orientation * nCam);

	}

	glm::vec3 getEyeTop() {

		return getPosition(orientation * tCam);

	}

	glm::vec3 getAt() {

		return glm::vec3(getX(), getY(), getZ());

	}

	glm::vec3 getShipUp() {

		return getUp(rotation);

	}

	glm::vec3 getForward() {

		return getOut(orientation);

	}

	void turnRight() {

		glm::mat4 turn = glm::mat4();
		turn[0][0] = (float)cos(turnSpeed);
		turn[0][2] = (float)sin(turnSpeed);
		turn[2][0] = -1.0f * (float)sin(turnSpeed);
		turn[2][2] = (float)cos(turnSpeed);

		rotation = rotation * turn;

	}

	void turnLeft() {

		glm::mat4 turn = glm::mat4();
		turn[0][0] = (float)cos(turnSpeed);
		turn[0][2] = -1.0f * (float)sin(turnSpeed);
		turn[2][0] = (float)sin(turnSpeed);
		turn[2][2] = (float)cos(turnSpeed);

		rotation = rotation * turn;

	}

	void moveForward() {

		glm::mat4 move = glm::mat4();
		move[3][2] = moveSpeed;
		move = rotation * move;

		position[3][0] += move[3][0];
		position[3][1] += move[3][1];
		position[3][2] += move[3][2];

	}

	void moveBackward() {

		glm::mat4 move = glm::mat4();
		move[3][2] = -moveSpeed;
		move = rotation * move;

		position[3][0] += move[3][0];
		position[3][1] += move[3][1];
		position[3][2] += move[3][2];

	}

	void tiltForward() {

		glm::mat4 turn = glm::mat4();
		turn[1][1] = (float)cos(turnSpeed);
		turn[1][2] = -1.0f * (float)sin(turnSpeed);
		turn[2][1] = (float)sin(turnSpeed);
		turn[2][2] = (float)cos(turnSpeed);

		rotation = rotation * turn;

	}

	void tiltBackward() {

		glm::mat4 turn = glm::mat4();
		turn[1][1] = (float)cos(turnSpeed);
		turn[1][2] = (float)sin(turnSpeed);
		turn[2][1] = -1.0f * (float)sin(turnSpeed);
		turn[2][2] = (float)cos(turnSpeed);

		rotation = rotation * turn;

	}

	void tiltRight() {

		glm::mat4 turn = glm::mat4();
		turn[0][0] = (float)cos(turnSpeed);
		turn[0][1] = (float)sin(turnSpeed);
		turn[1][0] = -1.0f * (float)sin(turnSpeed);
		turn[1][1] = (float)cos(turnSpeed);

		rotation = rotation * turn;

	}

	void tiltLeft() {

		glm::mat4 turn = glm::mat4();
		turn[0][0] = (float)cos(turnSpeed);
		turn[0][1] = -1.0f * (float)sin(turnSpeed);
		turn[1][0] = (float)sin(turnSpeed);
		turn[1][1] = (float)cos(turnSpeed);

		rotation = rotation * turn;

	}

	void changeSpeed() {

		if (moveSpeed <= 10.0f) moveSpeed = 50.0f;
		else if (moveSpeed <= 50.0f) moveSpeed = 200.0f;
		else moveSpeed = 10.0f;

	}

	void gravityToggle() {
		glm::mat4 gravity = glm::mat4();
		gravity[0][0] = (float)cos(turnSpeed);
		gravity[0][2] = -1.0f * (float)sin(turnSpeed);
		gravity[2][0] = (float)sin(turnSpeed);
		gravity[2][2] = (float)cos(turnSpeed);

		rotation = rotation * gravity;
	}

};