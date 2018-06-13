#version 130  

in vec3 vertex;
in vec3 normal;

out vec3 vert;
out vec3 vertNormal;
out vec3 pixelLight;
out vec3 pixelCam;
out vec4 lightcolor;

uniform vec4 lightColor;
uniform mat4 projMatrix;
uniform mat4 lookatMatrix;
uniform mat4 worldMatrix;
uniform mat3 normalMatrix;
uniform mat4 rotations;
uniform vec4 mycolor;
uniform vec4 amb;
uniform vec4 def;
uniform vec4 spec;
uniform float skalar;

out vec4 color;
uniform sampler2D u_texture;   //diffuse map
uniform sampler2D u_normals;   //normal map

//values used for shading algorithm...
			      //resolution of screen
uniform vec3 light;        //light position, normalized
uniform vec4 LightColor;      //light RGBA -- alpha is intensity




void main() {
	
	vert = vertex.xyz;
	vec4 vert4=vec4(vertex,1.0);  
	vertNormal = normalMatrix * normal;
	pixelLight = light;
	pixelCam = (lookatMatrix*worldMatrix*vert4).xyz;
	color = mycolor;
	lightcolor = lightColor;
	gl_Position = projMatrix * lookatMatrix * worldMatrix * vert4;
}
