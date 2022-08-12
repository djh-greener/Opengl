#include "Renderer.h"
#include "myDebug.h"
#include "GL/glew.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind(); /* ΪGPU����ɫ������ */
	va.Bind(); /* ����ʵ�ʴ������ݵ����� */
	ib.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}