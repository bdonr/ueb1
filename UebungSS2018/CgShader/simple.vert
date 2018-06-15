#version 130  

in vec3 vertex;
in vec3 normal;

out vec3 vert;
out vec3 vertNormal;
out vec3 pixelCam;
out vec3 pixelview;
out vec3 ldir;

uniform mat4 projMatrix;
uniform mat4 lookatMatrix;
uniform mat4 worldMatrix;
uniform mat3 normalMatrix;
uniform mat4 rotations;
uniform vec3 lDir;

uniform vec4 mamb;
out vec3 fragColor;
out vec3 fragViewVec;
out vec3 fragLightVec;


uniform sampler2D u_texture;   //diffuse map
uniform sampler2D u_normals;   //normal map


void main() {
	vec4 vert4=vec4(vertex,1.0);  
	gl_Position = projMatrix * lookatMatrix * worldMatrix * vert4;
	
	vec4 worldPos = worldMatrix*vert4;
	fragColor = mamb.xyz;
	vertNormal = normalMatrix * normal;
	fragViewVec = (lookatMatrix*worldMatrix*vert4).xyz;
	fragLightVec = lDir -vec3(worldPos);	

}
/*
vert = vertex.xyz;	
	vertNormal = normalMatrix * normal;
	
	pixelCam = -(lookatMatrix*worldMatrix*vert4).xyz;
	ldir = lDir -pixelCam;
*/	

