
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
	float moveSpeed = 50.0f;
	
	float radians;
	glm::mat4 position;
	glm::mat4 rotation;
	glm::mat4 orientation;
	glm::mat4 bCam = glm::mat4();
	glm::mat4 nCam = glm::mat4();
	glm::mat4 tCam = glm::mat4();
	
	Warship (char * given) {
		
		modelFile = given;
		position = glm::mat4();
		rotation = glm::mat4();
		
		bCam[3][1] = 300.0f;
		bCam[3][2] = -1000.0f;
		
		nCam[3][2] = -600.0f;
		
		tCam[3][1] = 300.0f;
		
		radians = 0.0f;
		
	}
	
	void update() {
		
		rotation[0][0] = (float) cos(radians);
		rotation[0][2] = -1.0f * (float) sin(radians);
		rotation[2][0] = (float) sin(radians);
		rotation[2][2] = (float) cos(radians);
		
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
	
	float getX () {
		
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
	
	glm::vec3 getUp() {
		
		return glm::vec3(0.0f, 1.0f, 0.0f);
		
	}
	
	glm::vec3 getForward() {
		
		return getOut(orientation);
		
	}
	
	void turnRight() {
		
		radians -= turnSpeed;
		
		if (radians >= 2.0f * PI) radians = 0.0f;
		
	}
	
	void turnLeft() {
		
		radians += turnSpeed;
		
		if (radians <= -2.0f * PI) radians = 0.0f;
		
	}
	
	void moveForward() {
		
		position[3][0] += (float) sin(radians) * moveSpeed; // x movement
		position[3][2] += (float) cos(radians) * moveSpeed; // z movement
		
	}
	
	void moveBackward() {
		
		position[3][0] -= (float) sin(radians) * moveSpeed; // x movement
		position[3][2] -= (float) cos(radians) * moveSpeed; // z movement
		
	}
	
};