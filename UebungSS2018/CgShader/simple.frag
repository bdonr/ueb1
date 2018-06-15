#version 130

in vec3 vert;
in vec3 vertNormal;



in vec3 pixelCam;


uniform vec4 mdif;
uniform vec4 mspec;
uniform float mshine;


uniform vec4 lcolor;

in vec3 ldir;
uniform vec4 lspec;
uniform vec4 ldif;
uniform vec4 lamb;


in vec3 fragColor;
in vec3 fragViewVec;
in vec3 fragLightVec;


void main() {
vec3 specular=vec3(1.0);
vec3 diffuse =vec3(1.0);
vec3 ambiente;

	vec3 N = normalize(vertNormal);
	vec3 L = normalize(fragLightVec);
	vec3 V = normalize(fragViewVec);
	vec3 R = reflect (L,N);
	 ambiente = fragColor.xyz*.1;
	vec3 h = fragColor*lamb.xyz;
	 diffuse = max(dot(N,L),0.0)* h;
	float k = pow(max(dot(R,V),0.0),12);
	vec3 a = lspec.xyz;
	vec3 b = mspec.xyz;
	vec3 s = (a*b);

	vec3 spec = k*s;
	vec3 alle = spec + diffuse+ambiente;
	gl_FragColor = vec4(spec,1.0);
	
}
