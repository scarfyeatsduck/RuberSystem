# version 330 core

in vec4 color;
out vec4 FragColor;

in vec3 position;
in vec3 normal;

in vec3 PLP;
in vec3 PLI;
in vec3 Amb;

void main (void) {
	
	vec3 fragValue = vec3(color) * Amb;
	vec3 colorBase = vec3(color);
	
	vec3 n = normalize(normal);
	vec3 s = normalize(PLP - position);
	float i = max(dot(s,n), 0.0f);
	//float i = abs(dot(s,n));
	colorBase *= i * PLI;
	
	fragValue += colorBase;
	FragColor = vec4(fragValue, 1.0f);
	
}
