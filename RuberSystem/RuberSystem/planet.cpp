
# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

class Planet {

private:
	
	const double SPEED = 1.0;
	
	float distance;
	float cModifier;
	float orbitRadians;
	
	glm::mat4 position;
	glm::mat4 rotation;
	glm::mat4 orientation;
	glm::mat4 camera;
	
public:

	char * modelFile;
	float boundingRadius;
	const GLuint nVertices = 1440;


	//glm::vec4 vertex[nVertices];
	//glm::vec3 normal[nVertices];
	//glm::vec4 diffuseColorMaterial[nVertices];
	//GLsizeiptr allocSize;



	Planet(char * given, float distanceFromRuber, float radians) {

		modelFile = given;
		distance = distanceFromRuber;
		cModifier = 3.0f * distance / abs(distance);
		orbitRadians = radians;
		position = glm::mat4();
		//allocSize = sizeof(vertex) + sizeof(normal) + sizeof(diffuseColorMaterial);

		position[3][0] = distance;
		camera[3][2] = 5000.0f;
		if (distance < 0) camera[3][2] = -5000.0f;

	}

	glm::mat4 getModelMatrix() {

		return orientation;

	}

	void printLocation() {

		showMat4("Orientation", orientation);

	}

	float getPlanetX(void) {

		return position[3][0];

	}

	float getPlanetY(void) {

		return position[3][1];

	}

	float getPlanetZ(void) {

		return position[3][2];

	}

	glm::vec3 getAt() {

		return getPosition(position);

	}

	glm::vec3 getEye() {

		return getPosition(orientation * camera);

	}

	glm::vec3 getUp() {

		return glm::vec3(0.0f, 1.0f, 0.0f);

	}

	float getCos() {

		return (float)cos(((double)glutGet(GLUT_ELAPSED_TIME) * 0.025f * orbitRadians * SPEED));

	}

	float getSin() {

		return (float)sin(((double)glutGet(GLUT_ELAPSED_TIME) * 0.025f * orbitRadians * SPEED));

	}

	void update() {

		position[3][0] = distance * getCos();
		position[3][2] = distance * getSin();

		rotation = rotate(glm::mat4(), (float)(-glutGet(GLUT_ELAPSED_TIME) * 0.025f * orbitRadians * SPEED), glm::vec3(0.0f, 1.0f, 0.0f));

		orientation = position * rotation;

	}

};