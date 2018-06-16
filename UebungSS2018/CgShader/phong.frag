#version 130

in vec3 vert;
in vec3 vertNormal;



in vec3 pixelCam;
in vec3 pixelView;

uniform vec4 mamb;
uniform vec4 mdif;
uniform vec4 mspec;
uniform float mshine;





in vec4 lspec;
in vec4 ldif;
in vec4 lamb;

void main() {

	vec4 col;
	
	//fragment normalisiert
	vec3 N = normalize (vert);
	//lichtstrahl normalisiert
	vec3 L = normalize(pixelView);
	vec3 V = normalize(pixelCam);

	/*AMBIENTE*/
	//lichtfarbe * ambient des Objektes = Ambiente
	vec4 ambiente =mamb*lamb;

	vec3 R = reflect (L,N);
	/*DIFFUSE*/
	// das scalarprodukt aus Lichtstrahl und Normalisierte nicht negativ
	float diff = max(dot(L,N),0.0);
	//lichtfarbe * diffintensität * material diffuse
	vec4 diffuse = diff*ldif;


	/*SPECULAR*/ 
	//reflectiere licht in gegenrichtung vom lichstrahl
	//vec3 reflectDir= reflect(-lightDir,N);

	//potenziere das maximum aus dem scalarprodukt von reflect und sichtwinkel mal dem 		materialspec 
	float specu = pow(max(dot(R,V),0.0),mshine);
	//lichtfarbe * specfaktor * materialspec	
	vec4 specular = specu  * lspec; 
	vec4 alle = specular*ambiente*diffuse;
	gl_FragColor=lspec;

} 
