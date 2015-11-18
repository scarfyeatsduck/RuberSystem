
# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

class Missile {

public:
	
	char * modelFile;
	float boundingRadius;
	const GLuint nVertices = 192;
	
	//glm::vec4 vertex[nVertices];
	//glm::vec3 normal[nVertices];
	//glm::vec4 diffuseColorMaterial[nVertices];
	//GLsizeiptr allocSize;

	glm::mat4 position;
	glm::mat4 rotation;
	glm::vec3 direction;
	
	bool hasTarget;
	MissileSite * target;
	
	float speed = 20.0f;
	float maxTargetDistance = 1000.0f;

	Missile (char * given, glm::mat4 orientation) {

		modelFile = given;
		//allocSize = sizeof(vertex) + sizeof(normal) + sizeof(diffuseColorMaterial);
		
		position = glm::mat4();
		position[3][0] = orientation[3][0];
		position[3][1] = orientation[3][1];
		position[3][2] = orientation[3][2];
		
		rotation = glm::mat4();
		rotation[0][0] = orientation[0][0];
		rotation[0][1] = orientation[0][1];
		rotation[0][2] = orientation[0][2];
		rotation[1][0] = orientation[1][0];
		rotation[1][1] = orientation[1][1];
		rotation[1][2] = orientation[1][2];
		rotation[2][0] = orientation[2][0];
		rotation[2][1] = orientation[2][1];
		rotation[2][2] = orientation[2][2];
		
		direction = getOut(orientation);

	}
	
	glm::mat4 getModelMatrix() {
		
		return (position * rotation);
		
	}
	
	void update () {
		
		if (hasTarget) {
			
			direction = target->getLocation() - getPosition(position);
			
		}
		
		position[3][0] += direction[0] * speed;
		position[3][1] += direction[1] * speed;
		position[3][2] += direction[2] * speed;
		
	}
	
	bool targetNear (MissileSite * given) {
		
		float targetDistance = distance(getPosition(position),getPosition(given->getLocation()));
		
		return (target <= maxTargetDistance);
		
	}
	
	void setTarget(Missileite * given) {
		
		target = given;
		hasTarget = true;
		
	}
	
};