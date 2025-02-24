#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct Material
{
	glm::vec3 color;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

	Material(glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
		float shininess)
	{
		this->color = color;
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->shininess = shininess;
	}
	// Sets ambient and diffuse color to the object's color
	Material(glm::vec3 color, glm::vec3 specular, float shininess) : Material(color, color, color, specular, shininess)
	{ }
};

class Shader
{
public:
	unsigned int ID; // Program ID

	Shader();
	Shader(const char* vertexPath, const char* fragmentPath);
	Shader(const char* vertexPath, const char* fragmentPath, Material m);

	// Use/activate shader
	void use() const;

	// Set paths after initializing
	void setPaths(const char* vertexPath, const char* fragmentPath);

	// Utility uniform setters
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setFloat3(const std::string& name, float a, float b, float c) const;
	void setFloat3(const std::string& name, glm::vec3 vec) const;
	void setFloat4(const std::string& name, float a, float b, float c, float d) const;
	void setFloat4(const std::string& name, glm::vec4 vec) const;
	void setMat4(const std::string& name, glm::mat4 value) const;
	void setMaterial(Material mat) const;
};

#endif