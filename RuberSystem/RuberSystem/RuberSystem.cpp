/*

CS 465 Project 2

Submitted by:
-Stephen Morse
-Alexander Markarian
-Alden Parel

*/

# define __Windows__
# include "../includes465/include465.hpp"
# include "Planet.cpp"
# include "Moon.cpp"
# include "Warship.cpp"
# include "Missile.cpp"

//	DEFINITIONS
//	
//	

// Is your program in debug mode?
bool debug = true;
// Are you using custom shaders?
bool customShaders = false;

// Viewport Info
const int INITIAL_WIDTH = 800, INITIAL_HEIGHT = 600;
// Is the camera in perspective mode?
bool perspective = true;
// The Viewport's Aspect Ratio
GLfloat aspectRatio;

// Number of models to be loaded
const int nModels = 7;
// Ruber, the star
Planet * ruber = new Planet("models/ruber.tri", 0.0f, 0.0f);
// Unum, the first planet
Planet * unum = new Planet("models/unum.tri", 4000.0f, 0.004f);
// Duo, the second planet
Planet * duo = new Planet("models/duo.tri", -9000.0f, 0.002f);
// Primus, Duo's first moon
Moon * primus = new Moon("models/primus.tri", duo, 900.0f, 0.01f);
// Secundus, Duo's second moon
Moon * secundus = new Moon("models/secundus.tri", duo, -1750.0f, 0.006f);
// Your Warbird
Warship * warbird = new Warship("models/warship.tri");
// A Missile
Missile * missile = new Missile("models/missile.tri");

// Window Title Start String
char startStr[25] = "Ruber System | Viewing: ";
// Window Title Camera Focus String
char focusStr[25] = "Top View";
// Window Title key Instructions
char endStr[35] = " | {Arrow keys, s, w, u, d} | ";
// Window Title Time String
char timeStr[10] = "";
// Window Title Full String
char titleStr[100];

// The Vertex Array Objects
GLuint vao[nModels];

// The Vertex Buffer Objects
GLuint buffer[nModels];

// The Model Buffer Vertices
GLuint vPosition[nModels], vColor[nModels], vNormal[nModels];

// The Shader Program
GLuint shaderProgram;

// The vertex shader file
char * vertexShaderFile = "simpleVertex.glsl";
// The fragment shader file
char * fragmentShaderFile = "simpleFragment.glsl";
// The custom vertex shader file
char * customVertexShaderFile = "customVertex.glsl";
// The custom fragment shader file
char * customFragmentShaderFile = "customFragment.glsl";
// Model View Projection
GLuint MVP;
// The Projection Matrix
glm::mat4 projectionMatrix;
// The Model Matrix
glm::mat4 modelMatrix;
// The View Matrix
glm::mat4 viewMatrix;
// The final MVP Matrix
glm::mat4 ModelViewProjectionMatrix;

// Camera Distance from object
float eyeDistance = 20000.0f;
// The camera data
glm::vec3 eye, at, up; // Camera location, orientation
// The Number of Cameras
int nCameras = 7;
// The Camera Index
int cIndex = 0;
// The Warp Index
int wIndex = 0;

// Movement Booleans
bool movingForward = false, movingBackward = false, turningRight = false, turningLeft = false;
bool pitchForward = false, pitchBackward = false, rollRight = false, rollLeft = false;
bool gravityOn = false;

// Alternate Controls Booleans
bool ctrlPressed = false;

// Timer Delay Variable
int timerDelay = 40;
// Timer Float Variable
double currentTime, lastTime, timeInterval;
// Is your program using an idle timer?
bool idleTimerFlag = false;
// Is your program running in wireframe draw mode?
bool wireframe = false;

//	INITIALIZE GL FUNCTIONS
void init(void) {

	if (customShaders) shaderProgram = loadShaders(customVertexShaderFile, customFragmentShaderFile);
	else shaderProgram = loadShaders(vertexShaderFile, fragmentShaderFile);
	
	glUseProgram(shaderProgram);

	glGenVertexArrays(nModels, vao);
	glGenBuffers(nModels, buffer);

	// Load Models
	int mIndex = 0;
	ruber->boundingRadius = loadModelBuffer(ruber->modelFile, ruber->nVertices,
		vao[mIndex], buffer[mIndex], shaderProgram, vPosition[mIndex], vColor[mIndex], vNormal[mIndex],
		"vPosition", "vColor", "vNormal");
	printf("Loaded Model: %s with %7.2f bounding radius \n", ruber->modelFile, ruber->boundingRadius);

	mIndex++;
	unum->boundingRadius = loadModelBuffer(unum->modelFile, unum->nVertices,
		vao[mIndex], buffer[mIndex], shaderProgram, vPosition[mIndex], vColor[mIndex], vNormal[mIndex],
		"vPosition", "vColor", "vNormal");
	printf("Loaded Model: %s with %7.2f bounding radius \n", unum->modelFile, unum->boundingRadius);

	mIndex++;
	duo->boundingRadius = loadModelBuffer(duo->modelFile, duo->nVertices,
		vao[mIndex], buffer[mIndex], shaderProgram, vPosition[mIndex], vColor[mIndex], vNormal[mIndex],
		"vPosition", "vColor", "vNormal");
	printf("Loaded Model: %s with %7.2f bounding radius \n", duo->modelFile, duo->boundingRadius);

	mIndex++;
	primus->boundingRadius = loadModelBuffer(primus->modelFile, primus->nVertices,
		vao[mIndex], buffer[mIndex], shaderProgram, vPosition[mIndex], vColor[mIndex], vNormal[mIndex],
		"vPosition", "vColor", "vNormal");
	printf("Loaded Model: %s with %7.2f bounding radius \n", primus->modelFile, primus->boundingRadius);

	mIndex++;
	secundus->boundingRadius = loadModelBuffer(secundus->modelFile, secundus->nVertices,
		vao[mIndex], buffer[mIndex], shaderProgram, vPosition[mIndex], vColor[mIndex], vNormal[mIndex],
		"vPosition", "vColor", "vNormal");
	printf("Loaded Model: %s with %7.2f bounding radius \n", secundus->modelFile, secundus->boundingRadius);

	mIndex++;
	warbird->boundingRadius = loadModelBuffer(warbird->modelFile, warbird->nVertices,
		vao[mIndex], buffer[mIndex], shaderProgram, vPosition[mIndex], vColor[mIndex], vNormal[mIndex],
		"vPosition", "vColor", "vNormal");
	printf("Loaded Model: %s with %7.2f bounding radius \n", warbird->modelFile, warbird->boundingRadius);

	MVP = glGetUniformLocation(shaderProgram, "ModelViewProjection");

	warbird->setLocation(5000.0f, 1000.0f, 5000.0f);

	printf("eyeDistance = %3.3f\n", eyeDistance);

	eye = glm::vec3(0.0f, eyeDistance, eyeDistance);
	at = glm::vec3(0.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	lastTime = glutGet(GLUT_ELAPSED_TIME);

}

//  WARP
void warp(void) {

	wIndex = (wIndex + 1) % 3;

	if (wIndex == 1) {

		warbird->setLocation(unum->getEye());
		glm::vec3 right = unum->getAt();
		right = glm::normalize(right);
		glm::vec3 newUp = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 facing = unum->getAt() - unum->getEye();
		facing = glm::normalize(facing);

		warbird->setRotation(right, newUp, facing);

	}
	else if (wIndex == 2) {

		warbird->setLocation(duo->getEye());
		glm::vec3 right = duo->getAt();
		right = glm::normalize(right);
		glm::vec3 newUp = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 facing = duo->getAt() - duo->getEye();
		facing = glm::normalize(facing);
		warbird->setRotation(right, newUp, facing);

	}
	else {

		warbird->setLocation(5000.0f, 1000.0f, 5000.0f);
		warbird->resetRotation();

	}

}

//	WINDOW RESIZE FUNCTION
void reshape(int width, int height) {

	glViewport(0, 0, width, height);
	aspectRatio = (GLfloat)width / (GLfloat)height;
	projectionMatrix = glm::perspective(glm::radians(45.0f), (GLfloat)width / (GLfloat)height, 1.0f, 100000.0f);

}

//	DISPLAY FUNCTION
void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewMatrix = glm::lookAt(eye, at, up);

	int mIndex = 0;
	modelMatrix = ruber->getModelMatrix();
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	glBindVertexArray(vao[mIndex]);
	glDrawArrays(GL_TRIANGLES, 0, ruber->nVertices);

	mIndex++;
	modelMatrix = unum->getModelMatrix();
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	glBindVertexArray(vao[mIndex]);
	glDrawArrays(GL_TRIANGLES, 0, unum->nVertices);

	mIndex++;
	modelMatrix = duo->getModelMatrix();
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	glBindVertexArray(vao[mIndex]);
	glDrawArrays(GL_TRIANGLES, 0, duo->nVertices);

	mIndex++;
	modelMatrix = primus->getModelMatrix();
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	glBindVertexArray(vao[mIndex]);
	glDrawArrays(GL_TRIANGLES, 0, primus->nVertices);

	mIndex++;
	modelMatrix = secundus->getModelMatrix();
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	glBindVertexArray(vao[mIndex]);
	glDrawArrays(GL_TRIANGLES, 0, secundus->nVertices);

	mIndex++;
	modelMatrix = warbird->getModelMatrix();
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	glBindVertexArray(vao[mIndex]);
	glDrawArrays(GL_TRIANGLES, 0, warbird->nVertices);

	glutSwapBuffers();

	currentTime = glutGet(GLUT_ELAPSED_TIME);
	timeInterval = currentTime - lastTime;

}

//	TITLE UPDATE FUNCTION
void updateTitle(void) {

	strcpy(titleStr, startStr);
	strcat(titleStr, focusStr);
	strcat(titleStr, endStr);
	sprintf(timeStr, "%3.3f", (float)(0.001f * glutGet(GLUT_ELAPSED_TIME)));
	strcat(titleStr, timeStr);

	glutSetWindowTitle(titleStr);

}

//	UPDATE
void update(void) {

	if (movingForward) warbird->moveForward();
	if (movingBackward) warbird->moveBackward();
	if (turningLeft) warbird->turnLeft();
	if (turningRight) warbird->turnRight();

	if (pitchForward) warbird->tiltForward();
	if (pitchBackward) warbird->tiltBackward();
	if (rollRight) warbird->tiltRight();
	if (rollLeft) warbird->tiltLeft();

	if (gravityOn)warbird->gravityToggle();

	ruber->update();
	unum->update();
	duo->update();
	primus->update();
	secundus->update();
	warbird->update();
	updateTitle();

	up = glm::vec3(0.0f, 1.0f, 0.0f);

	switch (cIndex) {

	case 0:
		eye = glm::vec3(0.0f, 10000.0f, 20000.0f);
		at = glm::vec3(0.0f, 0.0f, 0.0f);
		break;
	case 1:
		eye = glm::vec3(0.0f, 20000.0f, 0.0f);
		at = glm::vec3(0.0f, 0.0f, 0.0f);
		up = glm::vec3(0.0f, 0.0f, -1.0f);
		break;
	case 2:
		eye = warbird->getEye();
		at = warbird->getAt();
		up = warbird->getShipUp();
		break;
	case 3:
		eye = warbird->getEyeAlt();
		at = warbird->getAt();
		up = warbird->getShipUp();
		break;
	case 4:
		eye = warbird->getEyeTop();
		at = warbird->getAt();
		up = warbird->getForward();
		break;
	case 5:
		eye = unum->getEye();
		at = unum->getAt();
		break;
	case 6:
		eye = duo->getEye();
		at = duo->getAt();
		break;

	}

}

//	INTERVAL TIMER
void intervalTimer(int i) {

	glutTimerFunc(timerDelay, intervalTimer, 1);
	if (!idleTimerFlag) update();

}

//	STANDARD KEYBOARD INPUT
void keyboard(unsigned char key, int x, int y) {

	if (debug) printf("Key Pressed: %c (code: %d)\nx: %d, y: %d\n", key, key, x, y);

	switch (key) {

	case 033: case 'q': case 'Q':
		exit(EXIT_SUCCESS);
		break;

	case 'x': case 'X':
		cIndex = (cIndex - 1) % nCameras;
		if (cIndex == -1) cIndex = nCameras - 1;
		break;

	case 'v': case 'V':
		cIndex = (cIndex + 1) % nCameras;
		break;

	case 'd': case 'D':
		printf("Warship Orientation:\n");
		showMat4("Warbird: ", warbird->orientation);
		printf("Camera Location:\n");
		showVec3("Eye: ", eye);
		showVec3("At: ", at);
		showVec3("Up: ", up);
		break;

	case 'b': case 'B':
		printf("Unum ");
		unum->printLocation();
		printf("Duo ");
		duo->printLocation();
		break;

	case 's': case 'S':
		warbird->changeSpeed();
		break;

	case 'k': case 'K':
		break;

	case 'w': case 'W':
		warp();
		break;

	case 'r': case 'R':
		warbird->resetRotation();
		break;

	case 'g': case 'G':
		//Toggle Gravity
		if (gravityOn) {
			gravityOn = false;
			printf("Gravity Off\n");
		}
		else {
			gravityOn = true;
			printf("Gravity On\n");
		}
		break;

	}

}

// SPECIAL KEY INPUT
void special(int key, int x, int y) {

	if (debug) printf("Special Key Pressed: %d\nx: %d, y: %d\n", key, x, y);

	if ((ctrlPressed) && ((cIndex >= 2) && (cIndex <= 4))) {

		switch (key) {

		case GLUT_KEY_UP:
			pitchForward = true;
			break;

		case GLUT_KEY_DOWN:
			pitchBackward = true;
			break;

		case GLUT_KEY_LEFT:
			rollLeft = true;
			break;

		case GLUT_KEY_RIGHT:
			rollRight = true;
			break;

		}

	}

	else if ((cIndex >= 2) && (cIndex <= 4)) {

		switch (key) {

		case 114:
			ctrlPressed = true;
			movingForward = false;
			movingBackward = false;
			turningLeft = false;
			turningRight = false;
			break;

		case GLUT_KEY_UP:
			movingForward = true;
			break;

		case GLUT_KEY_DOWN:
			movingBackward = true;
			break;

		case GLUT_KEY_LEFT:
			turningLeft = true;
			break;

		case GLUT_KEY_RIGHT:
			turningRight = true;
			break;

		}

	}

}

// SPECIAL KEY UP FUNCTION
void specialUp(int key, int x, int y) {

	switch (key) {

	case 114:
		ctrlPressed = false;
		pitchForward = false;
		pitchBackward = false;
		rollRight = false;
		rollLeft = false;
		break;

	case GLUT_KEY_UP:
		movingForward = false;
		pitchForward = false;
		break;

	case GLUT_KEY_DOWN:
		movingBackward = false;
		pitchBackward = false;
		break;

	case GLUT_KEY_LEFT:
		turningLeft = false;
		rollLeft = false;
		break;

	case GLUT_KEY_RIGHT:
		turningRight = false;
		rollRight = false;
		break;

	}

}

//	MAIN FUNCTION
int main(int argc, char * argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(INITIAL_WIDTH, INITIAL_HEIGHT);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Ruber System");

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	if (err != GLEW_OK) {

		printf("GLEW Error: %s\n", glewGetErrorString(err));

	}
	else {

		printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
		printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION),
			glGetString(GL_SHADING_LANGUAGE_VERSION));

	}

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutSpecialUpFunc(specialUp);
	glutTimerFunc(timerDelay, intervalTimer, 1);
	glutIdleFunc(display);
	glutMainLoop();
	printf("Processing Finished.\n");
	return 0;

}