#include "Shader.h"
#include<GL/glew.h>
#include"myDebug.h"

#include<iostream>
#include<fstream>
#include<sstream>


Shader::Shader(const std::string& filename) :m_FilePath(filename),m_RendererID(0)
{
	ShaderProgramSource sps = ParseShader(filename);
	m_RendererID = CreateShader(sps.VretexShader, sps.FragmentShader);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::UnBind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1f(const std::string& name, float f0)
{
	GLCall(glUniform1f(GetUniformLocation(name), f0));
}

void Shader::SetUniform1i(const std::string& name, int i0)
{
	GLCall(glUniform1i(GetUniformLocation(name), i0));
}

void Shader::SetUniform4f(const std::string& name, const glm::vec4& vec)
{
	GLCall(glUniform4f(GetUniformLocation(name), vec[0], vec[1], vec[2], vec[3]));
}

void Shader::SetUniform3f(const std::string& name, const glm::vec3& vec)
{
	GLCall(glUniform3f(GetUniformLocation(name), vec[0], vec[1], vec[2]));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SetUniformMat3f(const std::string& name, const glm::mat3& matrix)
{
	GLCall(glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

 int Shader::GetUniformLocation(const std::string& name)const
{
	if (m_UniformLocationCach.find(name) != m_UniformLocationCach.end())
		return m_UniformLocationCach[name];
	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "Warning Uniform: " << name << "doesn't exist!" << std::endl;
	m_UniformLocationCach[name] = location;
	return location;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);//分配一个空余shaderID
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);//为此ID指定源码位置和读取方式
	glCompileShader(id);//编译成机器码

	//编译debug
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Shader Compile Error!" << std::endl;
		std::cout << "id: " << id << std::endl;
		std::cout << "message: " << message << std::endl;
	}

	return id;//返回ID，此时OpenGL已经在存放shader机器码的地方添加了此ID对应的机器码
	//后续即可在shader机器码存放区根据ID找到对应shader
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	std::ifstream stream(m_FilePath);
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
			ss[int(type)] << line << '\n';
	}
	return { ss[0].str(),ss[1].str() };
}

unsigned int Shader::CreateShader(const std::string& VertexShader, const std::string& FragmentShader)
{
	unsigned int program = glCreateProgram();//分配一个空余代码区ID
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, VertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}