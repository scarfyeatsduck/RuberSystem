/*
diffuseFragment.glsl

Fragment shader for light effects.
Adapted from OpenGL Programming Guide 8th edition sample code 
ch08_lightmodels.cpp function render_fs().

There is a single "headlamp" light source directed into the scene.

Mike Barnes
9/24/2015
*/

# version 330 core

in vec3 Position;
in vec3 Normal;
in vec4 Color;

uniform vec3 PointLightPosition;
uniform vec3 PointLightIntensity;
uniform float AmbientIntensity;

out vec4 FragColor;

vec3 vLight (vec3 LightPosition, vec3 LightIntensity) {
   
   vec3 n = normalize(Normal), s = normalize(LightPosition - Position);
   float diffuse = max(dot(s,n), 0.0);
   
   return diffuse * LightIntensity;
   
}

void main (void) {

   vec3 TempColor = vec3(Color) * AmbientIntensity;
   TempColor += vLight(PointLightPosition, PointLightIntensity);
   FragColor = vec4(TempColor, 1.0f);   
}
