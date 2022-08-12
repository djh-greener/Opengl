#pragma once
#include "glm/glm.hpp"

#include<vector>

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
		std::vector<Texture*> textures;

		glm::vec3 pos = { 0,0,0 };

	};
}