#version 130

in vec3 vert;
in vec3 vertNormal;


in vec3 pixelLight;
in vec3 pixelCam;
in vec4 lightcolor;

uniform vec4 amb;
uniform vec4 def;
uniform vec4 spec;
uniform float skalar;
uniform bool lighton;


    void main() {
vec4 col;
	if(lighton){
	vec3 N = normalize (vert);
	vec3 L = normalize(pixelLight);
     	vec3 E = normalize(-pixelCam);
	vec3 H = normalize(L+E);

	vec4 ambient = amb* lightcolor;
	
	float ldiff = 1.0*(dot(L,N));
	vec4 ldiffuse = ldiff *lightcolor;
	
	float mdiff = max(dot(N,L),skalar);
	vec4 mdiffuse= mdiff * def;

	vec4 diffuse = ldiffuse* mdiffuse;

	float mspec =pow(max(dot(N,H),0.0),11);
	vec4 mspecular = mspec * spec;
	vec4 specular = mspecular;


        col = diffuse+ambient+specular;
	}
	else{
		 col = amb;
	}
	gl_FragColor = col;
    }

