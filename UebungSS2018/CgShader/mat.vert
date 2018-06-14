#version 130  

in vec3 vertex;
in vec3 normal;

out vec3 vert;
out vec3 vertNormal;
out vec3 pixelCam;


uniform mat4 projMatrix;
uniform mat4 lookatMatrix;
uniform mat4 worldMatrix;
uniform mat3 normalMatrix;
uniform mat4 rotations;

uniform sampler2D u_texture;   //diffuse map
uniform sampler2D u_normals;   //normal map


void main() {
	
	vert = vertex.xyz;
	vec4 vert4=vec4(vertex,1.0);  
	vertNormal = normalMatrix * normal;
	pixelCam = (lookatMatrix*worldMatrix*vert4).xyz;
	gl_Position = projMatrix * lookatMatrix * worldMatrix * vert4;
}
