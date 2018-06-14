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


    void main() {
	gl_FragColor = amb;
    }

