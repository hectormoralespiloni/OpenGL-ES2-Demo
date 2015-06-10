attribute vec4 position;
attribute vec4 color;
attribute vec3 normal;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform vec3 lightPosition;

varying vec4 v_color;
const vec4 ambientColor = vec4(0.1, 0.1, 0.1, 1.0);

void main()
{
	vec3 eyePos = vec3(modelViewMatrix * position);
	vec3 eyeNormal = vec3(modelViewMatrix * vec4(normal,0.0));
	vec3 lightVector = normalize(lightPosition - eyePos);

	float diffuse = max(dot(eyeNormal, lightVector), 0.0); 	
	v_color = ambientColor + color * diffuse;
	
	gl_Position = modelViewProjectionMatrix * position;
}
