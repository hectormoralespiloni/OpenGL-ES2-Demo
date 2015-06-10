attribute vec4 position;
attribute vec3 normal;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;

varying vec3 eyeNormal;
varying vec3 eyePosition;

void main()
{
	//Calculate position & normal in camera space
	eyePosition = vec3(modelViewMatrix * position);
	eyeNormal = vec3(modelViewMatrix * vec4(normal,0.0));
	eyeNormal = normalize(eyeNormal);

	//Transform vertices
	gl_Position = modelViewProjectionMatrix * position;
}
