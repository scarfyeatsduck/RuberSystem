/*
diffuseVertex.glsl

Fragment shader for light effects.
Adapted from OpenGL Programming Guide 8th edition sample code 
ch08_lightmodels.cpp function render_vs().

Mike Barnes
9/24/2015
*/

# version 330 core
        
layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec3 vNormal;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewProjection;
  
out vec4 vsColor;      
out vec3 vs_worldpos;
out vec3 vs_normal;
        
void main(void) {
  vec4 position = ModelViewProjection * vPosition;
  gl_Position = position;
  vs_worldpos = position.xyz;
  vs_normal = NormalMatrix * vNormal; 
  vsColor = vColor;
  }
 