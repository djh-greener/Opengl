#include "TestLightColor.h"
#include<GL/glew.h>
#include"GLFW/glfw3.h"
#include<vector>

#include"imgui/imgui.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Shader.h"


#include"myDebug.h"

namespace test {
	TestLightColor::TestLightColor():
		m_Proj(glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f)),
		m_View(glm::mat4(1.0f))
	{
		float lightvertices[] = {
-0.5f, -0.5f, -0.5f,
 0.5f, -0.5f, -0.5f,
 0.5f,  0.5f, -0.5f,
 0.5f,  0.5f, -0.5f,
-0.5f,  0.5f, -0.5f,
-0.5f, -0.5f, -0.5f,

-0.5f, -0.5f,  0.5f,
 0.5f, -0.5f,  0.5f,
 0.5f,  0.5f,  0.5f,
 0.5f,  0.5f,  0.5f,
-0.5f,  0.5f,  0.5f,
-0.5f, -0.5f,  0.5f,

-0.5f,  0.5f,  0.5f,
-0.5f,  0.5f, -0.5f,
-0.5f, -0.5f, -0.5f,
-0.5f, -0.5f, -0.5f,
-0.5f, -0.5f,  0.5f,
-0.5f,  0.5f,  0.5f,

 0.5f,  0.5f,  0.5f,
 0.5f,  0.5f, -0.5f,
 0.5f, -0.5f, -0.5f,
 0.5f, -0.5f, -0.5f,
 0.5f, -0.5f,  0.5f,
 0.5f,  0.5f,  0.5f,

-0.5f, -0.5f, -0.5f,
 0.5f, -0.5f, -0.5f,
 0.5f, -0.5f,  0.5f,
 0.5f, -0.5f,  0.5f,
-0.5f, -0.5f,  0.5f,
-0.5f, -0.5f, -0.5f,

-0.5f,  0.5f, -0.5f,
 0.5f,  0.5f, -0.5f,
 0.5f,  0.5f,  0.5f,
 0.5f,  0.5f,  0.5f,
-0.5f,  0.5f,  0.5f,
-0.5f,  0.5f, -0.5f
		};
		float objvertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};
		float axisVectices[] = {
			0.0f,0.0f,0.0f,
			10.f,0.f,0.f,
			0.0f,0.0f,0.0f,
			0.f,10.f,0.f,
			0.0f,0.0f,0.0f,
			0.f,0.f,10.f
		};

		Object* obj = new Object;
		obj->shader=new Shader("res/shaders/obj.shader");
		obj->vertexBuffer=new VertexBuffer (objvertices, sizeof(objvertices));
		obj->vertexBufferLayout=new VertexBufferLayout;
		obj->vertexBufferLayout->Push<float>(3);
		obj->vertexBufferLayout->Push<float>(3);
		obj->vertexArray=new VertexArray;
		obj->vertexArray->AddBuffer(*obj->vertexBuffer, *obj->vertexBufferLayout);
		obj->pos = { 0,0,0 };
		m_objects.push_back(obj);

		Object* light = new Object;
		light->shader = new Shader("res/shaders/light.shader");
		light->vertexBuffer = new VertexBuffer(lightvertices, sizeof(lightvertices));
		light->vertexBufferLayout = new VertexBufferLayout;
		light->vertexBufferLayout->Push<float>(3);
		light->vertexArray = new VertexArray;
		light->vertexArray->AddBuffer(*light->vertexBuffer, *light->vertexBufferLayout);
		light->pos = { 1,2,-2 };
		m_objects.push_back(light);

		Object* axis = new Object;
		axis->shader = new Shader("res/shaders/axis.shader");
		axis->vertexBuffer = new VertexBuffer(axisVectices, sizeof(axisVectices));
		axis->vertexBufferLayout = new VertexBufferLayout;
		axis->vertexBufferLayout->Push<float>(3);
		axis->vertexArray = new VertexArray;
		axis->vertexArray->AddBuffer(*axis->vertexBuffer, *axis->vertexBufferLayout);
		axis->pos = { 0,0,0 };
		m_objects.push_back(axis);
	}

	TestLightColor::~TestLightColor()
	{
		for (auto it : m_objects)
			delete it;
	}

	void TestLightColor::OnUpdate(float deltaTime) {
		lightColor.x = sin(glfwGetTime() * 2.0f);
		lightColor.y = sin(glfwGetTime() * 0.7f);
		lightColor.z = sin(glfwGetTime() * 1.3f);
	}

	void TestLightColor::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		{//物体
			auto it=*m_objects[0];
			it.vertexArray->Bind();
			it.shader->Bind();

			it.shader->SetUniformMat4f("u_projection", m_Proj);
			it.shader->SetUniformMat4f("u_view", m_View);
			glm::mat4 m_Model = glm::translate(glm::mat4(1), it.pos);
			it.shader->SetUniformMat4f("u_model", m_Model);

			it.shader->SetUniformMat3f("NormalMat", glm::mat3(glm::transpose(glm::inverse(m_View * m_Model))));

			it.shader->SetUniform3f("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
			it.shader->SetUniform3f("material.diffuse", glm::vec3(1.0f, 0.5f, 0.71f));
			it.shader->SetUniform3f("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
			it.shader->SetUniform1f("material.shininess", 32.0f);

			it.shader->SetUniform3f("lightColor", lightColor);
			it.shader->SetUniform3f("lightPos", m_objects[1]->pos);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		}

		{//光源
			auto it = *m_objects[1];
			it.vertexArray->Bind();
			it.shader->Bind();

			it.shader->SetUniformMat4f("u_projection", m_Proj);
			it.shader->SetUniformMat4f("u_view", m_View);
			glm::mat4 m_Model = glm::translate(glm::mat4(1), it.pos);
			it.shader->SetUniformMat4f("u_model", m_Model);

			it.shader->SetUniform3f("lightColor", lightColor);
			glDrawArrays(GL_TRIANGLES, 0, 36);

		}
		{//坐标轴
			auto it = *m_objects[2];
			it.vertexArray->Bind();
			it.shader->Bind();

			it.shader->SetUniformMat4f("u_projection", m_Proj);
			it.shader->SetUniformMat4f("u_view", m_View);
			glm::mat4 m_Model = glm::translate(glm::mat4(1), it.pos);
			it.shader->SetUniformMat4f("u_model", m_Model);

			for (int i = 0; i < 3; i++) {
				glm::vec3 tmp = { 0,0,0 };
				tmp[i] = 1;
				it.shader->SetUniform3f("objectColor", tmp);
				glDrawArrays(GL_LINES, 2 * i, 2);
			}
		}
	}
	void TestLightColor::OnImGuiRender()
	{
		ImGui::SliderFloat3("ObjPos", &m_objects[0]->pos.x, -5, 5);
		ImGui::SliderFloat3("LightPos", &m_objects[1]->pos.x, -5, 5);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}