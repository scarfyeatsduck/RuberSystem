# version 330 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec3 vNormal;

uniform mat4 ModelView;
uniform mat4 ModelViewProjection;

uniform vec3 PointLightPosition;
uniform vec3 PointLightIntensity;
uniform vec3 AmbientIntensity;
uniform bool Luminous;

out vec4 color;
out vec3 position;
out vec3 normal;

out vec3 PLP;
out vec3 PLI;
out vec3 Amb;

void main(void) {
	
	mat3 NormalMatrix = mat3(ModelView);
	
	position = vec3(ModelView * vPosition);
	normal = NormalMatrix * vNormal;
	color = vColor;
	
	PLP = PointLightPosition;
	
	if (Luminous) {
		
		PLI = vec3(0.0f);
		Amb = vec3(1.0f);
		
	}
	else {
		
		PLI = PointLightIntensity;
		Amb = AmbientIntensity;
		
	}
	
	gl_Position = ModelViewProjection * vPosition;
	
}