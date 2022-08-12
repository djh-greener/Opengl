#pragma once
#include<vector>
#include<GL/glew.h>
struct VertexBufferElement {
	int type;
	unsigned int count;
	unsigned char normalized;
	static const int GetSizeofType(unsigned int type) {
		switch (type)
		{
			case GL_FLOAT:					return 4;
			case GL_UNSIGNED_INT:		return 4;
			case GL_UNSIGNED_BYTE:	return 1;
			default:__debugbreak();
		}
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement>m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout() {}

	template<typename T>
	void Push(unsigned int count) {
		static_assert(false);
	}
	template<>
	void Push<float>(unsigned int count) {
		VertexBufferElement tmp = { GL_FLOAT, count, false };
		m_Elements.push_back(tmp);
		m_Stride += count*VertexBufferElement::GetSizeofType(GL_FLOAT);
	}
	template<>
	void Push<unsigned int>(unsigned int count) {
		VertexBufferElement tmp = { GL_UNSIGNED_INT, count, false };
		m_Elements.push_back(tmp);
		m_Stride += count * VertexBufferElement::GetSizeofType(GL_UNSIGNED_INT);
	}
	template<>
	void Push<unsigned char>(unsigned int count) {
		VertexBufferElement tmp = { GL_UNSIGNED_BYTE, count, true };
		m_Elements.push_back(tmp);
		m_Stride += count * VertexBufferElement::GetSizeofType(GL_UNSIGNED_BYTE);
	}
	inline std::vector<VertexBufferElement>GetElements()const { return m_Elements; }
	inline unsigned int GetStride()const { return m_Stride; }
};

