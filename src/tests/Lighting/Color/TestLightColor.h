#pragma once
#include"../../Test.h"
#include <memory>


class VertexArray;
class VertexBuffer;
class VertexBufferLayout;
class IndexBuffer;
class Texture;
class Shader;

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Object.h"

namespace test {
	
	class TestLightColor:public Test
	{
	public:
		TestLightColor();
		~TestLightColor();
		void OnUpdate(float deltaTime)override;
		void OnRender()override;
		void OnImGuiRender()override;
	private:
		//Õ®”√
		unsigned int SCR_WIDTH = 1000;
		unsigned int SCR_HEIGHT = 1000;

		glm::mat4 m_Proj, m_View;

		std::vector<Object*>m_objects;
		
		//Ãÿ ‚
		glm::vec3 lightColor = { 1,1,1 };
	};
}


