#version 130

in vec3 vert;
in vec3 vertNormal;


struct Material{
 vec4 mamb;
 vec4 mdif;
 vec4 mspec;
 float mshine;
};
 uniform Material material;
struct Light {
    vec3 lamb;
    vec3 ldir;
    vec3 ldif;
    vec3 lspec;
};
uniform Light light; 
uniform vec4 viewPos;
void main() {

vec3 norm = normalize(vertNormal);
vec3 lightDir = normalize(light.ldir - vert);

vec3 viewDir = normalize(viewPos.xyz - vert);
vec3 reflectDir = reflect(-lightDir, vert); 


float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.mshine);
float diff = max(dot(norm, lightDir), 0.0);


vec3 ambient  = light.lamb * material.mamb.xyz;
vec3 diffuse  = light.ldif * (diff * material.mdif.xyz);
vec3 specular = light.lspec * (spec * material.mspec.xyz);
vec3 alle = (ambient+diffuse+specular);
	gl_FragColor=vec4(ambient,1.0);

} 
