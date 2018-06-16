#version 130

in vec3 vert;
in vec3 vertNormal;

uniform vec4 mamb;


    void main() {
     
       gl_FragColor = mamb;
    }
