#version 130

in vec3 vert;
in vec3 vertNormal;


	in vec4 color;


    void main() {
     
       gl_FragColor = color;
    }
