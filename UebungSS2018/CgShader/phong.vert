#version 130 
#extension all : warn
in vec3 vertex;
in vec3 normal;
uniform mat4 projMatrix;
uniform mat4 lookatMatrix;
uniform mat4 worldMatrix;
uniform mat3 normalMatrix;
uniform mat4 rotations;

out vec3 vert;
out vec3 vertNormal;
out vec3 pixelCam;

out vec3 pixelView;


out vec4 ldif;
out vec4 lamb;
out vec4 lspec;

uniform vec3 adir;
uniform vec4 aspec;
uniform vec4 adif;
uniform vec4 aamb;





uniform sampler2D u_texture;   //diffuse map
uniform sampler2D u_normals;   //normal map


void main() {
	
	vert = vertex.xyz;
	vec4 vert4=vec4(vertex,1.0);  
	
	vertNormal = normalMatrix * normal;
	pixelCam = (lookatMatrix*worldMatrix*vert4).xyz;
	pixelView = adir - vec3(worldMatrix).xyz;
	ldif=adif;
	lamb = aamb;
	lspec = vec(.2,3,.3,1);
        gl_Position = projMatrix * lookatMatrix * worldMatrix * vert4;
	
}

