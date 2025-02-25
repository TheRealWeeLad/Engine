#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 project;

void main()
{
	gl_Position = project * view * model * vec4(pos, 1.0);
	// Send world space coords to frag shader
	FragPos = vec3(model * vec4(pos, 1.0));
	Normal = normal;
}