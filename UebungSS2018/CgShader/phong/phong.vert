#version 130 
#extension all : warn
in vec3 vertex;
in vec3 normal;
uniform mat4 ndc;
uniform mat3 normalMatrix;
uniform mat4 worldMatrix;
uniform mat4 mv;

out vec3 vert;
out vec3 vertNormal;

void main() {
	vert = vertex.xyz;
	vec4 vert4=vec4(vertex,1.0);  
	vertNormal = normalMatrix * normal;
        gl_Position = ndc*vert4;
	
}

