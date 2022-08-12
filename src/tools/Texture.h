#pragma once
#include<string>

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Hight, m_BPP;
public:
	Texture(const std::string& Path);
	~Texture();

	void Bind(unsigned int slot=0)const;
	void UnBind()const;

	inline int GetWidth()const { return m_Width; }
	inline int GetHight()const { return m_Hight; }
	inline int GetID()const { return m_RendererID; }
};

