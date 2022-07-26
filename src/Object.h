#pragma once
#include "glm/glm.hpp"

class VertexArray;
class IndexBuffer;
class VertexBuffer;
class Shader;
class Texture;
class VertexBufferLayout;

namespace test {
	class Object {
	public:
		VertexArray* vertexArray;
		IndexBuffer* indexBuffer;
		VertexBuffer* vertexBuffer;
		VertexBufferLayout* vertexBufferLayout;
		Shader* shader;
		Texture* texture;

		glm::vec3 pos = { 0,0,0 };
	};
}