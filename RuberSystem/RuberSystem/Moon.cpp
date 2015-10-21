
# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

class Moon {

private:

	const double SPEED = 1.0;
	
	Planet * orbitPlanet;
	float distance;
	float orbitRadians;
	
	glm::mat4 position;
	glm::mat4 rotation;

public:
	
	char * modelFile;
	float boundingRadius;
	const GLuint nVertices = 1440;
	
	
	//glm::vec4 vertex[nVertices];
	//glm::vec3 normal[nVertices];
	//glm::vec4 diffuseColorMaterial[nVertices];
	//GLsizeiptr allocSize;
	
	
	
	Moon (char * given, Planet * planet, float distanceFromPlanet, float radians) {

		modelFile = given;
		orbitPlanet = planet;
		distance = distanceFromPlanet;
		orbitRadians = radians;
		//allocSize = sizeof(vertex) + sizeof(normal) + sizeof(diffuseColorMaterial);
		
		position[3][0] = distance;

	}
	
	glm::mat4 getModelMatrix() {
		
		return (position * rotation);
		
	}
	
	void update() {
		
		position[3][0] = distance * (float) cos(((double)glutGet(GLUT_ELAPSED_TIME) * 0.025f * orbitRadians * SPEED)) + orbitPlanet->getPlanetX();
		position[3][2] = distance * (float) sin(((double)glutGet(GLUT_ELAPSED_TIME) * 0.025f * orbitRadians * SPEED)) + orbitPlanet->getPlanetZ();
		
	}
	
};