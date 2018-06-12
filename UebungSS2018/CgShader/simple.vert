#version 130  

in vec3 vertex;
in vec3 normal;


out vec3 vert;
out vec3 vertNormal;
out vec4 col;


    uniform mat4 projMatrix;
    uniform mat4 lookatMatrix;
    uniform mat4 worldMatrix;
    uniform mat3 normalMatrix;
    uniform vec4 color;
    uniform vec4 lightpos;
     vec4 Cd = vec4(0,.5,.0,0);

    const vec3 light= normalice(lightpos);
    void main() {
       vert = vertex.xyz;
      vec4 vert4=vec4(vertex,1.0);
       vertNormal = normalMatrix * normal;
       float Id = max(dot(light,normal),0);
       col = color+Cd*Id;
       gl_Position = projMatrix * lookatMatrix * worldMatrix * vert4;
    }
