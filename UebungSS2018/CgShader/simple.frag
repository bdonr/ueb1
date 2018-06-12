#version 130

in vec3 vert;
in vec3 vertNormal;

in vec4 col;

void main (void)
{
    gl_FragColor=col;
}
