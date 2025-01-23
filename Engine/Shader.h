#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	unsigned int ID; // Program ID

	Shader();
	Shader(const char* vertexPath, const char* fragmentPath);

	// Use/activate shader
	void use() const;

	// Set paths after initializing
	void setPaths(const char* vertexPath, const char* fragmentPath);

	// Utility uniform setters
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setFloat4(const std::string& name, float a, float b, float c, float d) const;
	void setMat4(const std::string& name, glm::mat4 value) const;
};

#endif