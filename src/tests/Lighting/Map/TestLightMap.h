#pragma once
#include"../../Test.h"




class VertexArray;
class VertexBuffer;
class VertexBufferLayout;
class IndexBuffer;
class Texture;
class Shader;

extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;

namespace test {

	class TestLightMap :public TestNormal
	{
	public:
		TestLightMap();
		~TestLightMap();
		void OnUpdate(float deltaTime)override;
		void OnRender()override;
		void OnImGuiRender()override;

		//Ãÿ ‚
		glm::vec3 lightColor = { 1,1,1 };
		float time = 0;
	};
}



