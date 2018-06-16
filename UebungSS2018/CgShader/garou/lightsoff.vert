#version 130  

in vec3 vertex;
in vec3 normal;

out vec3 vert;

out vec3 pixelLight;
out vec3 pixelCam;


uniform vec4 lightColor;
uniform mat4 projMatrix;
uniform mat4 lookatMatrix;
uniform mat4 worldMatrix;
uniform mat3 normalMatrix;
uniform mat4 rotations;

out vec4 color;
uniform sampler2D u_texture;   //diffuse map
uniform sampler2D u_normals;   //normal map


uniform vec3 adir;
uniform vec4 aspec;
uniform vec4 adif;
uniform vec4 aamb;



void main() {
	
	vert = vertex.xyz;
	vec4 vert4=vec4(vertex,1.0);  
	vec3 vertNormal = normalMatrix * normal;

	vec4 vertex_position_ndc = projMatrix * lookatMatrix * worldMatrix * vert4;
        vec4 light_position_ndc = projMatrix * lookatMatrix * worldMatrix* vec4(adir,1.0);

	vec3 light_vert = normalize(vec3(light_position_ndc-vertex_position_ndc));

	vec3 reflection = normalize(reflect(light_position_ndc,));	
	float diff = max(dot(light_vert,vertex_position_ndc),0.0);
	float specular = max(dot())
	float distance = lenght(adir-vertNormal)
	pixelLight = light;
	pixelCam = (lookatMatrix*worldMatrix*vert4).xyz;

	gl_Position = projMatrix * lookatMatrix * worldMatrix * vert4;
}
