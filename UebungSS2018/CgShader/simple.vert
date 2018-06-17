#version 130  

in vec3 vertex;
in vec3 normal;

out vec3 vert;
out vec3 vertNormal;

    uniform mat4 ndc;
    uniform mat3 normalMatrix;

    void main() {
       vert = vertex.xyz;
      vec4 vert4=vec4(vertex,1.0);  
       vertNormal = normalMatrix * normal;
       gl_Position = ndc * vert4;
    }
