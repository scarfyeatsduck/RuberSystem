/*
diffuseVertex.glsl

Fragment shader for light effects.
Adapted from OpenGL Programming Guide 8th edition sample code 
ch08_lightmodels.cpp function render_vs().

Mike Barnes
9/24/2015
*/

# version 330 core
        
in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewProjection;

out vec3 Position;
out vec3 Normal;
out vec4 Color;

void main(void) {
  Position = (ModelViewProjection * vPosition).xyz;
  Normal = normalize(NormalMatrix * vNormal);
  Color = vColor;
  }
 