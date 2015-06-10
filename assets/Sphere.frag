precision lowp float;
uniform vec3 lightPosition;

varying vec3 eyeNormal;
varying vec3 eyePosition;

const vec3 ambientColor = vec3(0.3, 0.0, 0.0);
const vec3 diffuseColor = vec3(0.5, 0.0, 0.0);
const vec3 specColor = vec3(1.0, 1.0, 1.0);

void main()
{
	vec3 normal = normalize(eyeNormal);
	vec3 lightDir = normalize(lightPosition - eyePosition);
	vec3 reflectDir = reflect(-lightDir, normal);
	vec3 viewDir = normalize(-eyePosition);

	float lambertian = max(dot(lightDir,normal), 0.0);
    float specular = 0.0;

	if(lambertian > 0.0) 
	{
		float specAngle = max(dot(reflectDir, viewDir), 0.0);
		specular = pow(specAngle, 10.0);
    }
	
	gl_FragColor = vec4(ambientColor + diffuseColor*lambertian + specular*specColor, 1.0);
}
