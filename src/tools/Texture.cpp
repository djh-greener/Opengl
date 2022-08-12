#include "Texture.h"
#include"myDebug.h"
#include"stb_image/stb_image.h"

Texture::Texture(const std::string& Path)
	:m_RendererID(0),m_FilePath(Path),m_LocalBuffer(nullptr),m_Width(0),m_Hight(0),m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);//OpenGL左下角是原点，png左上角是原点
	m_LocalBuffer = stbi_load(Path.c_str(), &m_Width, &m_Hight, &m_BPP, 4);
	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	//纹理最小最大线性过滤
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	//水平环绕，截断
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	//指定纹理存储读取格式，写入显存
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
		m_Width, m_Hight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
	//激活第slot个纹理插槽并绑定
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::UnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
