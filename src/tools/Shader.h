#pragma once

#include<string>
#include<unordered_map>
#include"glm/glm.hpp"
struct ShaderProgramSource {
	const std::string VretexShader;
	const std::string FragmentShader;
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	mutable std::unordered_map<std::string, int>m_UniformLocationCach;
public:
	Shader(const std::string& filename);
	~Shader();
	void Bind()const;
	void UnBind()const;

	void SetUniform1f(const std::string& name, float f0);
	void SetUniform1i(const std::string& name, int i0);
	void SetUniform4f(const std::string& name, const glm::vec4& vec);
	void SetUniform3f(const std::string& name, const glm::vec3& vec);
	void SetUniformMat4f(const std::string& name, const glm::mat4&matrix);
	void SetUniformMat3f(const std::string& name, const glm::mat3& matrix);

private:
	unsigned int CreateShader(const std::string& VertexShader, const std::string& FragmentShader);
	int GetUniformLocation(const std::string& name)const;
	unsigned int  CompileShader(unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader(const std::string& filepath);
	
};

