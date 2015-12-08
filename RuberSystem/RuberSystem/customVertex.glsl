# version 330 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec3 vNormal;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewProjection;

uniform vec3 PointLightPosition;
uniform vec3 PointLightIntensity;
uniform vec3 AmbientIntensity;

out vec4 color;
out vec3 position;
out vec3 normal;

out vec3 PLP;
out vec3 PLI;
out vec3 Amb;

void main(void) {
	
	position = (ModelViewProjection * vPosition).xyz;
	normal = NormalMatrix * vNormal;
	color = vColor;
	
	PLP = PointLightPosition;
	PLI = PointLightIntensity;
	Amb = AmbientIntensity;
	
	gl_Position = ModelViewProjection * vPosition;
	
}