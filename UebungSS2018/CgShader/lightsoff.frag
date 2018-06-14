#version 130

in vec3 vert;
in vec3 vertNormal;


in vec3 pixelLight;
in vec3 pixelCam;
in vec4 lightcolor;

uniform vec4 mamb;
uniform vec4 mdef;
uniform vec4 mspec;
uniform float mshine;


    void main() {
	gl_FragColor = mamb;
    }

