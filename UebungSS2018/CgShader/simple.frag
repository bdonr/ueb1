#version 130

in vec3 vert;
in vec3 vertNormal;



in vec3 pixelCam;

uniform vec4 mamb;
uniform vec4 mdif;
uniform vec4 mspec;
uniform float mshine;


uniform vec4 lcolor;


uniform vec4 ldif;
uniform vec4 lamb;
uniform vec4 lspec;
uniform vec3 lDir;

void main() {

	vec4 col;

	//fragment normalisiert
	vec3 N = normalize (vert);
	//lichtstrahl normalisiert
	vec3 L = normalize(lDir);

	//winkel zwischen lichtstrahl und cam aufs pixel
	vec3 E = normalize(lDir-pixelCam);
	//halfway 
	vec3 H = normalize(L+E);
	/*AMBIENTE*/
	//lichtfarbe * ambient des Objektes = Ambiente
	vec4 ambiente =lamb*mamb;

	/*DIFFUSE*/
	// das scalarprodukt aus Lichtstrahl und Normalisierte nicht negativ
	float diff = max(dot(L,N),0.0);
	//lichtfarbe * diffintensität * material diffuse
	vec4 diffuse = mdif*diff * ldif;


	/*SPECULAR*/ 
	//reflectiere licht in gegenrichtung vom lichstrahl
	//vec3 reflectDir= reflect(-lightDir,N);

	//potenziere das maximum aus dem scalarprodukt von reflect und sichtwinkel mal dem 		materialspec 
	float specu = pow(max(dot(E,H),0.0),mshine);
	//lichtfarbe * specfaktor * materialspec	
	vec4 specular = specu * mspec * lspec; 

	gl_FragColor=ambiente+diffuse+specular;

}	
