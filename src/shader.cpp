#include "shader.h"

#include <fstream> // filestream - ifstream, ofstream, fstream
#include <sstream> // stringstream - istringstream, ostringstream , stringstream
#include <streambuf>
#include <iostream>
#include <memory>
#include <vector>

Shader::Shader()
= default;

Shader::~Shader()
{
	if (m_RendererID)
		glDeleteProgram(m_RendererID);
}

void Shader::loadProgram(const char* filePath)
{
	std::ifstream shaderFile;

	std::string shaderCode;
	std::string tmp_shaderCode;

	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::cerr << "\nLoading and compiling shader [" << filePath << "]: ";

	try
	{
		std::streambuf* buffer;
		shaderFile.open(filePath);

		buffer = shaderFile.rdbuf();

		std::streamsize size = buffer->pubseekoff(0, shaderFile.end);
		buffer->pubseekoff(0, shaderFile.beg);

		std::unique_ptr<char[]> ptr = std::make_unique<char[]>(size);

		buffer->sgetn(&ptr[0], size);

		tmp_shaderCode.reserve(size);
		tmp_shaderCode.assign(&ptr[0]);
		tmp_shaderCode.shrink_to_fit();

		shaderFile.close();
	}
	catch (const std::ifstream::failure e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << "\n";
		return;
	}

	GLuint result = 0;
	std::vector<GLuint> shader_v;
	GLint compiled = 0;

	shader_v.reserve(6);

	// position of beginning and end of shader code
	size_t pos_start;
	size_t pos_end;

	size_t length;

	m_RendererID = glCreateProgram();

	// looking for vertex shader code
	pos_start = tmp_shaderCode.find("<<<VSTEXT>>>");
	if (pos_start != std::string::npos)
	{
		pos_start += 12;
		pos_end = tmp_shaderCode.find("<<<", pos_start);
		if (pos_end == std::string::npos)
			pos_end = tmp_shaderCode.length();

		length = pos_end - pos_start;

		shaderCode.clear();
		shaderCode.reserve(length);
		shaderCode.assign(tmp_shaderCode, pos_start, length);

		result = compileShader(shaderCode.data(), GL_VERTEX_SHADER);
		if (result)
		{
			shader_v.push_back(result);
			glAttachShader(m_RendererID, result);
			glDeleteShader(result);
		}
		else
			return;
	}

	// looking for fragment shader code
	pos_start = tmp_shaderCode.find("<<<FSTEXT>>>");
	if (pos_start != std::string::npos)
	{
		pos_start += 12;
		pos_end = tmp_shaderCode.find("<<<", pos_start);
		if (pos_end == std::string::npos)
			pos_end = tmp_shaderCode.length();

		length = pos_end - pos_start;

		shaderCode.clear();
		shaderCode.reserve(length);
		shaderCode.assign(tmp_shaderCode, pos_start, length);

		result = compileShader(shaderCode.data(), GL_FRAGMENT_SHADER);
		if (result)
		{
			shader_v.push_back(result);
			glAttachShader(m_RendererID, result);
			glDeleteShader(result);
		}
		else
			return;
	}

	// looking for tessellation control shader code
	pos_start = tmp_shaderCode.find("<<<TCTEXT>>>");
	if (pos_start != std::string::npos)
	{
		pos_start += 12;
		pos_end = tmp_shaderCode.find("<<<", pos_start);
		if (pos_end == std::string::npos)
			pos_end = tmp_shaderCode.length();

		length = pos_end - pos_start;

		shaderCode.clear();
		shaderCode.reserve(length);
		shaderCode.assign(tmp_shaderCode, pos_start, length);

		result = compileShader(shaderCode.data(), GL_TESS_CONTROL_SHADER);
		if (result)
		{
			shader_v.push_back(result);
			glAttachShader(m_RendererID, result);
			glDeleteShader(result);
		}
		else
			return;
	}

	// looking for tessellation evaluation shader code
	pos_start = tmp_shaderCode.find("<<<TETEXT>>>");
	if (pos_start != std::string::npos)
	{
		pos_start += 12;
		pos_end = tmp_shaderCode.find("<<<", pos_start);
		if (pos_end == std::string::npos)
			pos_end = tmp_shaderCode.length();

		length = pos_end - pos_start;

		shaderCode.clear();
		shaderCode.reserve(length);
		shaderCode.assign(tmp_shaderCode, pos_start, length);

		result = compileShader(shaderCode.data(), GL_TESS_EVALUATION_SHADER);
		if (result)
		{
			shader_v.push_back(result);
			glAttachShader(m_RendererID, result);
			glDeleteShader(result);
		}
		else
			return;
	}

	// looking for geometry shader code
	pos_start = tmp_shaderCode.find("<<<GSTEXT>>>");
	if (pos_start != std::string::npos)
	{
		pos_start += 12;
		pos_end = tmp_shaderCode.find("<<<", pos_start);
		if (pos_end == std::string::npos)
			pos_end = tmp_shaderCode.length();

		length = pos_end - pos_start;

		shaderCode.clear();
		shaderCode.reserve(length);
		shaderCode.assign(tmp_shaderCode, pos_start, length);

		result = compileShader(shaderCode.data(), GL_GEOMETRY_SHADER);
		if (result)
		{
			shader_v.push_back(result);
			glAttachShader(m_RendererID, result);
			glDeleteShader(result);
		}
		else
			return;
	}

	// looking for compute shader code
	pos_start = tmp_shaderCode.find("<<<CSTEXT>>>");
	if (pos_start != std::string::npos)
	{
		pos_start += 12;
		pos_end = tmp_shaderCode.find("<<<", pos_start);
		if (pos_end == std::string::npos)
			pos_end = tmp_shaderCode.length();

		length = pos_end - pos_start;

		shaderCode.clear();
		shaderCode.reserve(length);
		shaderCode.assign(tmp_shaderCode, pos_start, length);

		result = compileShader(shaderCode.data(), GL_COMPUTE_SHADER);
		if (result)
		{
			shader_v.push_back(result);
			glAttachShader(m_RendererID, result);
			glDeleteShader(result);
		}
		else
			return;
	}

	glLinkProgram(m_RendererID);

	glGetProgramiv(m_RendererID, GL_LINK_STATUS, &compiled);
	if (!compiled)
	{
		GLint logLength;
		glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<GLchar> infoLog;

		infoLog.reserve(logLength);

		glGetProgramInfoLog(m_RendererID, logLength, nullptr, infoLog.data());
		std::cerr << "\n\nERROR::PROGRAM_LINKING_ERROR : \n" << infoLog.data() << "\n";

		glDeleteProgram(m_RendererID);

		m_RendererID = 0;

		return;
	}

	for (const GLuint& s : shader_v)
		glDetachShader(m_RendererID, s);

	std::cerr << "Ok" << "\n";
}

void Shader::use()
{
	glUseProgram(m_RendererID);
}
// ------------------------------------------------------------------------

void Shader::setBool(const std::string & name, GLboolean value) const
{
	glUniform1i(glGetUniformLocation(m_RendererID, name.data()), (int)value);
}

// ------------------------------------------------------------------------

void Shader::setInt(const std::string & name, GLint value) const
{
	glUniform1i(glGetUniformLocation(m_RendererID, name.data()), value);
}

// ------------------------------------------------------------------------

void Shader::setFloat(const std::string & name, GLfloat value) const
{
	glUniform1f(glGetUniformLocation(m_RendererID, name.data()), value);
}

// ------------------------------------------------------------------------

void Shader::setVec2(const std::string & name, const glm::vec2 & value) const
{
	glUniform2fv(glGetUniformLocation(m_RendererID, name.data()), 1, &value[0]);
}

// ------------------------------------------------------------------------

void Shader::setVec2(const std::string & name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(m_RendererID, name.data()), x, y);
}

// ------------------------------------------------------------------------

void Shader::setVec3(const std::string & name, const glm::vec3 & value) const
{
	glUniform3fv(glGetUniformLocation(m_RendererID, name.data()), 1, &value[0]);
}

// ------------------------------------------------------------------------

void Shader::setVec3(const std::string & name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(m_RendererID, name.data()), x, y, z);
}

// ------------------------------------------------------------------------

void Shader::setVec4(const std::string & name, const glm::vec4 & value) const
{
	glUniform4fv(glGetUniformLocation(m_RendererID, name.data()), 1, &value[0]);
}

// ------------------------------------------------------------------------

void Shader::setVec4(const std::string & name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(m_RendererID, name.data()), x, y, z, w);
}

// ------------------------------------------------------------------------

void Shader::setMat2(const std::string & name, const glm::mat2 & mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(m_RendererID, name.data()), 1, GL_FALSE, &mat[0][0]);
}

// ------------------------------------------------------------------------

void Shader::setMat3(const std::string & name, const glm::mat3 & mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(m_RendererID, name.data()), 1, GL_FALSE, &mat[0][0]);
}

// ------------------------------------------------------------------------

void Shader::setMat4(const std::string & name, const glm::mat4 & matrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.data()), 1, GL_FALSE, &matrix[0][0]);
}

// ------------------------------------------------------------------------

// return shader id or 0 if error
auto Shader::compileShader(const char* shaderCode, const GLenum & type) -> const GLuint
{
	GLint compiled;
	GLuint shader = 0;

	shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderCode, nullptr);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLint logLength;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<GLchar> infoLog;

		infoLog.reserve(logLength);

		glGetShaderInfoLog(shader, logLength, nullptr, infoLog.data());
		std::cerr << "ERROR::SHADER_COMPILATION_ERROR : \n" << "\n -- ----------------------------------------------------- \n" << shaderCode << "\n" << infoLog.data() << "\n";

		glDeleteShader(shader);

		return 0;
	}
	return shader;
}
