#version 130

in vec3 vert;
in vec3 vertNormal;


in vec3 pixelLight;
in vec3 pixelCam;
in vec4 lightcolor;

	in vec4 color;


    void main() {
	vec3 N = normalize (vert);
	vec3 L = normalize(pixelLight);
     	vec3 E = normalize(-pixelCam);
	vec3 H = normalize(L+E);

	float diff = max(dot(N,L),0);
	vec4 diffuse = diff * color;

	float spec =pow(max(dot(N,H),0.0),200);
	vec4 specular = spec * lightcolor;
       gl_FragColor = diffuse+specular;
    }
>>>>>>> 9764ec9c3baf9b578f3a569805e43666acedaa6e
