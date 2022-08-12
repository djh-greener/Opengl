#include "TestLightCaster.h"

#include<GL/glew.h>
#include"GLFW/glfw3.h"

#include<vector>
#include<string>

#include"imgui/imgui.h"

#include "tools/VertexArray.h"
#include "tools/VertexBuffer.h"
#include "tools/VertexBufferLayout.h"
#include "tools/IndexBuffer.h"
#include "tools/Texture.h"
#include "tools/Shader.h"
#include"tools/myDebug.h"
#include"tools/Camera.h"

namespace test {
	TestLightCaster::TestLightCaster():TestNormal()
	{
		float objvertices[] = {
			// positions          // normals           // texture coords
			 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
			  0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
			  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			 -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
			 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

			 -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
			  0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
			  0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			  0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			 -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
			 -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

			 -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			 -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			 -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			 -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			  0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			  0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			 -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
			  0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
			  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			 -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
			 -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

			 -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
			  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
			  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			 -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
			 -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
		};
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
		float axisVectices[] = {
			0.0f,0.0f,0.0f,
			10.f,0.f,0.f,
			0.0f,0.0f,0.0f,
			0.f,10.f,0.f,
			0.0f,0.0f,0.0f,
			0.f,0.f,10.f
		};

		Object* obj = new Object;
		obj->shader = new Shader("res/shaders/lightcaster.shader");
		obj->vertexBuffer = new VertexBuffer(objvertices, sizeof(objvertices));
		obj->vertexBufferLayout = new VertexBufferLayout;
		obj->vertexBufferLayout->Push<float>(3);// positions
		obj->vertexBufferLayout->Push<float>(3);// normals
		obj->vertexBufferLayout->Push<float>(2);// texture coords
		obj->vertexArray = new VertexArray;
		obj->vertexArray->AddBuffer(*obj->vertexBuffer, *obj->vertexBufferLayout);
		obj->textures.push_back(new Texture("res/textures/container2.png"));
		obj->textures.push_back(new Texture("res/textures/container2_specular.png"));
		for (int i = 0; i < obj->textures.size(); i++)
			obj->textures[i]->Bind(i);
		obj->pos = { 0,0,0 };
		m_objects.push_back(obj);

		Object* light = new Object;
		light->shader = new Shader("res/shaders/light.shader");
		light->vertexBuffer = new VertexBuffer(lightvertices, sizeof(lightvertices));
		light->vertexBufferLayout = new VertexBufferLayout;
		light->vertexBufferLayout->Push<float>(3);
		light->vertexArray = new VertexArray;
		light->vertexArray->AddBuffer(*light->vertexBuffer, *light->vertexBufferLayout);
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
	TestLightCaster::~TestLightCaster()
	{
		for (auto it : m_objects)
			delete it;
	}
	void TestLightCaster::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};
		glm::vec3 pointLightPositions[] = {
			glm::vec3(0.7f,  0.2f,  2.0f),
			glm::vec3(2.3f, -3.3f, -4.0f),
			glm::vec3(-4.0f,  2.0f, -12.0f),
			glm::vec3(0.0f,  0.0f, -3.0f)
		};
		{//物体
			auto it = *m_objects[0];
			it.vertexArray->Bind();
			it.shader->Bind();

			it.shader->SetUniformMat4f("u_projection", m_Proj);
			it.shader->SetUniformMat4f("u_view", m_View);

			it.shader->SetUniform3f("ViewPos", Camera::GetInstance()->Position);

			it.shader->SetUniform1i("material.diffuse", 0);
			it.shader->SetUniform1i("material.specular", 1);
			it.shader->SetUniform1f("material.shininess", 32.0f);

			it.shader->SetUniform3f("dirLight.direction", lightDir);
			it.shader->SetUniform3f("dirLight.ambient", 0.05f* DirlightColor);
			it.shader->SetUniform3f("dirLight.diffuse", 0.4f* DirlightColor);
			it.shader->SetUniform3f("dirLight.specular",  0.5f* DirlightColor);

			for (int i = 0; i < 4; i++) {
				std::string tmp = std::to_string(i);
				it.shader->SetUniform3f("pointLights["+ tmp +"].position", pointLightPositions[i]);
				it.shader->SetUniform3f("pointLights["+ tmp +"].ambient", 0.05f* PointlightColor);
				it.shader->SetUniform3f("pointLights["+ tmp +"].diffuse", 0.8f* PointlightColor);
				it.shader->SetUniform3f("pointLights["+ tmp +"].specular", PointlightColor);
				it.shader->SetUniform1f("pointLights["+ tmp +"].constant", 1.0f);
				it.shader->SetUniform1f("pointLights["+ tmp +"].linear", 0.09f);
				it.shader->SetUniform1f("pointLights["+ tmp +"].quadratic", 0.032f);
			}
			it.shader->SetUniform3f("spotLight.position", Camera::GetInstance()->Position);
			it.shader->SetUniform3f("spotLight.direction", Camera::GetInstance()->Front);
			it.shader->SetUniform3f("spotLight.ambient", { 0.0f, 0.0f, 0.0f });
			it.shader->SetUniform3f("spotLight.diffuse", SpotlightColor);
			it.shader->SetUniform3f("spotLight.specular", SpotlightColor);
			it.shader->SetUniform1f("spotLight.constant", 1.0f);
			it.shader->SetUniform1f("spotLight.linear", 0.09f);
			it.shader->SetUniform1f("spotLight.quadratic", 0.032f);
			it.shader->SetUniform1f("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
			it.shader->SetUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

			for (int i = 0; i < 10; i++) {
				glm::mat4 m_Model = glm::translate(glm::mat4(1), cubePositions[i]);
				float angle = 20.0f * i;
				m_Model = glm::rotate(m_Model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				it.shader->SetUniformMat4f("u_model", m_Model);
				it.shader->SetUniformMat3f("NormalMat", glm::mat3(glm::transpose(glm::inverse(m_Model))));
				GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			}
		}

		{//光源
			auto it = *m_objects[1];
			it.vertexArray->Bind();
			it.shader->Bind();

			
			it.shader->SetUniformMat4f("u_projection", m_Proj);
			it.shader->SetUniformMat4f("u_view", m_View);
			it.pos = -lightDir;
			glm::mat4 m_Model = glm::translate(glm::mat4(1), it.pos);
			it.shader->SetUniformMat4f("u_model", m_Model);
			it.shader->SetUniform3f("lightColor", lightColor);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			for (int i = 0; i < 4; i++) {
				it.shader->SetUniformMat4f("u_projection", m_Proj);
				it.shader->SetUniformMat4f("u_view", m_View);
				it.pos = pointLightPositions[i];
				glm::mat4 m_Model = glm::translate(glm::mat4(1), it.pos);
				it.shader->SetUniformMat4f("u_model", m_Model);
				it.shader->SetUniform3f("lightColor", lightColor);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
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
	void TestLightCaster::OnImGuiRender()
	{
		//ImGui::SliderFloat3("ObjPos", &m_objects[0]->pos.x, -5, 5);
		ImGui::SliderFloat3("LightDir", &lightDir.x, -10, 10);

		ImGui::ColorEdit3("light Color", &lightColor.x);
		ImGui::ColorEdit3("Pointlight Color", &PointlightColor.x);
		ImGui::ColorEdit3("Dirlight Color", &DirlightColor.x);
		ImGui::ColorEdit3("Spotlight Color", &SpotlightColor.x);


		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}