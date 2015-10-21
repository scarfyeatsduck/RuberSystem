
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

	Missile (char * given) {

		modelFile = given;
		//allocSize = sizeof(vertex) + sizeof(normal) + sizeof(diffuseColorMaterial);

	}
	
	glm::mat4 getModelMatrix() {
		
		return (position * rotation);
		
	}
	
	void setLocation(float x, float y, float z) {
		
		position[3][0] = x;
		position[3][1] = y;
		position[3][2] = z;
		
	}
	
};