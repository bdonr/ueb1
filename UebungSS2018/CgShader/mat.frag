#version 130

in vec3 vert;
in vec3 vertNormal;



in vec3 pixelCam;

uniform vec4 diffuse;
uniform vec4 amb;
uniform vec4 lightintense;
uniform vec4 spec;
uniform float scalar;

uniform vec3 llight;
//lichtfarbe
uniform vec4 lcolor;

    void main() {
	
	vec4 col;
	
	vec3 N = normalize (vert);
	vec3 L = normalize(llight);
     	vec3 E = normalize(llight-pixelCam);
	vec3 H = normalize(L+E);
	
	vec4 ambiente = lcolor*lightintense;
	
	float diff = max(dot(L,N),0.0);
	vec4 cdiff = diffuse * diff*lcolor;
	
	float inte = pow(max(dot(H,L),0.0),scalar);
	vec4 specular = spec *inte * lcolor *5; 

	gl_FragColor= (ambiente+cdiff+specular)*amb;

    }	
