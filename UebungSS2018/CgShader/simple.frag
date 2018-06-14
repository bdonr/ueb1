#version 130

in vec3 vert;
in vec3 vertNormal;



in vec3 pixelCam;

in vec4 Amb;
in vec4 Def;
in vec4 Spec;
in float Skalar;
uniform vec3 llight;
uniform vec4 lcolor;

in vec3 ll;
//lichtfarbe
in vec4 lc;

    void main() {
	
	vec4 col;
	
	vec3 N = normalize (vert);
	vec3 L = normalize(llight);
     	vec3 E = normalize(llight-pixelCam);
	vec3 H = normalize(L+E);
	float amblight = .15;
	vec4 ambiente = lcolor*amblight;
	
	float diff = max(dot(L,N),0.0)*.3;
	vec4 cdiff = diff * lcolor;
	
	gl_FragColor= (ambiente+cdiff)*Amb;

    }	
