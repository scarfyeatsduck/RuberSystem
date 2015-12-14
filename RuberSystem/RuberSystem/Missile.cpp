
# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

class Missile {

public:
	
	char * modelFile;
	float boundingRadius;
	const GLuint nVertices = 180;
	
	//glm::vec4 vertex[nVertices];
	//glm::vec3 normal[nVertices];
	//glm::vec4 diffuseColorMaterial[nVertices];
	//GLsizeiptr allocSize;
	
	glm::mat4 position;
	glm::mat4 rotation;
	glm::mat4 orientation;
	glm::vec3 direction;
	
	int liveCount;
	bool hasTarget, live;
	MissileSite * target1;
	MissileSite * target2;
	Planet * sun;
	Planet * planet1;
	Planet * planet2;
	
	float speed = 20.0f;
	float maxTargetDistance = 1000.0f;
	
	Missile (char * given, Planet * sgiven, Planet * pgiven1, Planet * pgiven2, MissileSite * tgiven1, MissileSite * tgiven2) {
		
		modelFile = given;
		
		sun = sgiven;
		planet1 = pgiven1;
		planet2 = pgiven2;
		target1 = tgiven1;
		target2 = tgiven2;
		
		hasTarget = false;

	}
	
	void init (glm::mat4 pGiven, glm::mat4 rGiven) {
		
		liveCount = 0;
		
		position = pGiven;
		
		rotation = rGiven;
		
		orientation = position * rotation;
		
		direction = getOut(orientation);
		
		return;
		
	}
	
	glm::mat4 getModelMatrix() {
		
		return (orientation);
		
	}
	
	void destroy () {
		
		printf("Missile Detonating.\n");
		
		position = glm::mat4();
		rotation = glm::mat4();
		
	}
	
	bool deathCheck() {
		
		if (liveCount >= 2000) {
			
			destroy();
			return false;
			
		}
		if (distance(getPosition(position),planet1->getAt()) <= planet1->boundingRadius) {
			
			destroy();
			return false;
			
		}
		if (distance(getPosition(position),planet2->getAt()) <= planet2->boundingRadius) {
			
			destroy();
			return false;
			
		}
		if (distance(getPosition(position),sun->getAt()) <= sun->boundingRadius) {
			
			destroy();
			return false;
			
		}
		if (distance(getPosition(position),target1->getAt()) <= target1->boundingRadius) {
			
			destroy();
			return false;
			
		}
		if (distance(getPosition(position),target2->getAt()) <= target2->boundingRadius) {
			
			destroy();
			return false;
			
		}
		
	}
	
	bool update () {
		
		liveCount++;
		
		if (liveCount == 200) {
			
			printf("Targeting Missile Site on ");
			
			glm::vec3 t1 = target1->getAt();
			glm::vec3 t2 = target2->getAt();
			glm::vec3 l = getPosition(position);
			
			if (distance(l,t1) < distance(l,t2))
				printf("Unum.\n");
			else
				printf("Duo.\n");
			
		}
		
		if (liveCount >= 200) {
			glm::vec3 t1 = target1->getAt();
			glm::vec3 t2 = target2->getAt();
			glm::vec3 l = getPosition(position);
			
			if (distance(l,t1) < distance(l,t2))
				direction = normalize(target1->getAt() - getPosition(position));
			else
				direction = normalize(target2->getAt() - getPosition(position));
			
		}
		
		position[3][0] += direction[0] * speed;
		position[3][1] += direction[1] * speed;
		position[3][2] += direction[2] * speed;
		
		orientation = position * rotation;
		
		return deathCheck();
		
	}
	
	/*
	bool targetNear (MissileSite * given) {
		
		float targetDistance = distance(getPosition(position),getPosition(given->getLocation()));
		
		return (target <= maxTargetDistance);
		
	}
	
	void setTarget(MissileSite * given) {
		
		target = given;
		hasTarget = true;
		
	}
	*/
};