#version 460 core
out vec4 FragColor;

struct Material
{
	vec3 color;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
}

uniform Material mat;

void main()
{
	// http://devernay.free.fr/cours/opengl/materials.html
	float ambientIntensity = (0.212671 * mat.ambient.r + 0.715160 * mat.ambient.g + 
		0.072169 * mat.ambient.b) / (0.212671 * mat.diffuse.r +
		0.715160 * mat.diffuse.g + 0.072169 * mat.diffuse.b);
	vec3 ambient = ambientIntensity * mat.ambient;

	vec3 result = ambient * mat.color;
	FragColor = vec4(result, 1.0);
}