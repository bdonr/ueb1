#version 130  

in vec3 vertex;
in vec3 normal;

out vec3 vert;
out vec3 vertNormal;
out vec4 color;
uniform mat4 projMatrix;
uniform mat4 lookatMatrix;
uniform mat4 worldMatrix;
uniform mat3 normalMatrix;

uniform sampler2D u_texture;   //diffuse map
uniform sampler2D u_normals;   //normal map

//values used for shading algorithm...
			      //resolution of screen
uniform vec3 light;        //light position, normalized
uniform vec4 LightColor;      //light RGBA -- alpha is intensity
uniform vec4 AmbientColor;    //ambient RGBA -- alpha is intensity 
uniform vec3 Falloff;         //attenuation coefficients
uniform vec4 mycolor;	//color of object when reflecting
uniform vec3 LightDir;


/*P Punkt auf Objektoberfläche,

N Flächennormalenvektor in P,normiert,

L Vektor von P zu einer Punktlichtquelle, normiert, 

V Vektor von P zum Augpunkt (View), normiert,*/

/* ambien=alight∗amat */ 

/* ob ein Oberflächenpunkt der Lichtquelle
zugewandt ist, d.h. der Einfallswinkel des Lichtes im Intervall
[−90,+90]liegt/  Skalarprodukt>0*/
void main() {
	vert = vertex.xyz;
	vec4 vert4=vec4(vertex,1.0); 
	vec3 lightVector = normalize(u_LightPos - modelViewVertex);
 
    // Calculate the dot product of the light vector and vertex normal. If the normal and light vector are
    // pointing in the same direction then it will get max illumination.
    float diffuse = max(dot(normal, light), 0.1);
 
    // Attenuate the light based on distance.
    diffuse = diffuse * (1.0 / (1.0 + (0.25 * distance * distance)));
 
    // Multiply the color by the illumination level. It will be interpolated across the triangle.
    color = a_Color * diffuse;
                    
 
    // transform the vertex coordinates
    gl_Position = worldMatrix * vec4(vertex, 1.0f);
	gl_Position = lookatMatrix * gl_Position;
	gl_Position = projMatrix * gl_Position; 
}
