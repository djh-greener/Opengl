#pragma once
#include "../../Test.h"

class VertexArray;
class VertexBuffer;
class VertexBufferLayout;
class IndexBuffer;
class Texture;
class Shader;

extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;

namespace test {
	class TestLightCaster :
		public TestNormal
	{
	public:
		TestLightCaster();
		~TestLightCaster();
		void OnRender()override;
		void OnImGuiRender()override;

		//Ãÿ ‚
		glm::vec3 lightColor = { 1,1,1 };
		glm::vec3 PointlightColor = { 1,1,1 };
		glm::vec3 DirlightColor = { 1,1,1 };
		glm::vec3 SpotlightColor = { 1,1,1 };

		glm::vec3 lightDir = { -0.2f, -1.0f, -0.3f };
	};
}


