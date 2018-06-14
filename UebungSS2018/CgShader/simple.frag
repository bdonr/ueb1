#version 130

in vec3 vert;
in vec3 vertNormal;


uniform vec3 light;
in vec3 pixelCam;
uniform vec4 lightcolor;

uniform vec4 amb;
uniform vec4 def;
uniform vec4 spec;
uniform float skalar;


    void main() {
	
	vec4 col;
	
	vec3 N = normalize (vert);
	vec3 L = normalize(light);
     	vec3 E = normalize(-pixelCam);
	vec3 H = normalize(L+E);

	vec4 ambient = lightcolor*amb;
	
	float ldiff = 1.0*(dot(L,N));
	vec4 ldiffuse = ldiff *lightcolor;
	
	float mdiff = max(dot(N,L),skalar);
	vec4 mdiffuse= mdiff * def;

	vec4 diffuse = ldiffuse* mdiffuse;

	float mspec =pow(max(dot(N,H),0.0),11);
	vec4 mspecular = mspec * spec;
	vec4 specular = mspecular;


        col = ambient;
	
	gl_FragColor = amb*.15;
    }

