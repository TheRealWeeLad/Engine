#include "Shader.h"

Shader::Shader() { ID = -1; }
Shader::Shader(const char* vertexPath, const char* fragmentPath) : Shader()
{
	setPaths(vertexPath, fragmentPath);
}
Shader::Shader(const char* vertexPath, const char* fragmentPath, Material m) : Shader(vertexPath, fragmentPath)
{
	// TODO: implement material stuff
}

void Shader::setPaths(const char* vertexPath, const char* fragmentPath)
{
	/* READ SHADERS FROM FILE */
	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;
	// Ensure ifstream objects can throw exceptions
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// Open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		// Read file buffer contents into streams
		std::stringstream vStream, fStream;
		vStream << vShaderFile.rdbuf();
		fStream << fShaderFile.rdbuf();

		// Close file handlers
		vShaderFile.close();
		fShaderFile.close();

		// Convert stream into string
		vertexCode = vStream.str();
		fragmentCode = fStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}
	// Convert to C strings for OpenGL compatability
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	/* COMPILE AND LINK SHADERS */
	// Compile vert and frag shaders
	unsigned int vert{ glCreateShader(GL_VERTEX_SHADER) };
	glShaderSource(vert, 1, &vShaderCode, NULL);
	glCompileShader(vert);
	unsigned int frag{ glCreateShader(GL_FRAGMENT_SHADER) };
	glShaderSource(frag, 1, &fShaderCode, NULL);
	glCompileShader(frag);

	// Check for errors in compilation
	int success;
	char infoLog[512];
	glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vert, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(frag, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Link shaders to program
	ID = glCreateProgram();
	glAttachShader(ID, vert);
	glAttachShader(ID, frag);
	glLinkProgram(ID);

	// Check for linking errors
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Clean up shader objects
	glDeleteShader(vert);
	glDeleteShader(frag);
}

void Shader::use() const
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
	use();
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
	use();
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const
{
	use();
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat3(const std::string& name, float a, float b, float c) const
{
	use();
	glUniform3f(glGetUniformLocation(ID, name.c_str()), a, b, c);
}
void Shader::setFloat4(const std::string& name, float a, float b, float c, float d) const
{
	use();
	glUniform4f(glGetUniformLocation(ID, name.c_str()), a, b, c, d);
}
void Shader::setFloat4(const std::string& name, glm::vec4 vec) const
{
	use();
	glUniform4f(glGetUniformLocation(ID, name.c_str()), vec.r, vec.g, vec.b, vec.a);
}
void Shader::setMat4(const std::string& name, glm::mat4 value) const
{
	use();
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}