#include "Shader.h"

using namespace Engine;

const Material Material::Default{ {1, 1, 1}, {1, 1, 1}, 1.0F };

Shader::Shader() { ID = -1; }
Shader::Shader(const char* vertexPath, const char* fragmentPath) : Shader()
{
	setPaths(vertexPath, fragmentPath);
}
Shader::Shader(const char* vertexPath, const char* fragmentPath, Material m) : Shader(vertexPath, fragmentPath)
{
	setMaterial(m);
}

void Shader::setPaths(const char* vertexPath, const char* fragmentPath)
{
	/* READ SHADERS FROM FILE */
	std::string vertexCode{ readShaderFile(vertexPath) };
	std::string fragmentCode{ readShaderFile(fragmentPath) };

	// Convert to C strings for OpenGL compatability
	const char* vShaderCode{ vertexCode.c_str() };
	const char* fShaderCode{ fragmentCode.c_str() };

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

// Reads shader files into string array [vertexCode, fragmentCode]
std::string Shader::readShaderFile(const char* path) const
{
	std::string code;
	std::ifstream shaderFile;
	// Ensure ifstream objects can throw exceptions
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// Open files
		shaderFile.open(path);

		// Read file buffer contents into streams
		std::stringstream stream;
		stream << shaderFile.rdbuf();

		// Close file handlers
		shaderFile.close();

		// Preprocess code
		code = preprocess(stream);

		return code;
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}
}

std::string Shader::preprocess(std::stringstream& code) const
{
	std::string codeStr{};

	// Read through file
	char line[512];
	while (code.getline(line, 512))
	{
		// Check for #include declaration -> "{#include }file.glsl"
		if (line[0] == '#' && strncmp(line + 1, "include ", 8) == 0)
		{
			// Include specified file -> "#include {file.glsl}"
			char* filename = line + 9;

			// Append included code (excluding #version statement)
			std::string includedCode{ readShaderFile(filename) };
			codeStr += includedCode.substr(includedCode.find('\n'));
		}
		else
		{
			codeStr += line;
			codeStr += '\n';
		}
	}
	return codeStr;
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
void Shader::setFloat3(const std::string& name, glm::vec3 vec) const
{
	use();
	glUniform3f(glGetUniformLocation(ID, name.c_str()), vec.r, vec.g, vec.b);
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
void Shader::setMaterial(Material mat) const
{
	setFloat3("mat.color", mat.color);
	setFloat3("mat.ambient", mat.ambient);
	setFloat3("mat.diffuse", mat.diffuse);
	setFloat3("mat.specular", mat.specular);
	setFloat("mat.shininess", mat.shininess);
}