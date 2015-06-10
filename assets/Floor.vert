attribute vec4 position;
attribute vec3 normal;
attribute vec2 texCoords;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform vec3 lightPosition;

varying vec4 v_color;
varying vec2 v_texCoords;

void main()
{	
	vec3 eyePos = vec3(modelViewMatrix * position);
	vec3 eyeNormal = normalize(vec3(modelViewMatrix * vec4(normal,0.0)));
	vec3 lightVector = normalize(lightPosition - eyePos);

	float diffuse = max(dot(eyeNormal, lightVector), 0.3);	 	
	v_color = vec4(diffuse);
	v_texCoords = texCoords;

	gl_Position = modelViewProjectionMatrix * position;
}
