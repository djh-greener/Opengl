#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<vector>

#include"myDebug.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"VertexBufferLayout.h"
#include"Shader.h"
#include"Texture.h"
#include"Camera.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw_gl3.h"

using namespace std;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;

float deltaTime = 0;
float lastFrame = 0;

bool firstMouse = true;
float lastX = SCR_WIDTH / 2;
float lastY = SCR_HEIGHT / 2;

glm::vec3 lightPos = { 1,2,-2 };
glm::vec3 lightColor = { 1,1,1 };

int main(void)
{
	GLFWwindow* window;
	if (!glfwInit())
		return -1;
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewInit();
	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

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
	float AxisVectices[] = {
		0.0f,0.0f,0.0f,
		10.f,0.f,0.f,
		0.0f,0.0f,0.0f,
		0.f,10.f,0.f,
		0.0f,0.0f,0.0f,
		0.f,0.f,10.f
	};

	Shader objshader("res/shaders/obj.shader");
	VertexBuffer objVB(objvertices, sizeof(objvertices));
	VertexBufferLayout objLayout;
	objLayout.Push<float>(3);
	objLayout.Push<float>(3);
	VertexArray obj;
	obj.AddBuffer(objVB, objLayout);

	Shader lightshader("res/shaders/light.shader");
	VertexBuffer lightVB(lightvertices, sizeof(lightvertices));
	VertexBufferLayout lightLayout;
	lightLayout.Push<float>(3);
	VertexArray light;
	light.AddBuffer(lightVB, lightLayout);

	Shader axisShader("res/shaders/axis.shader");
	VertexBuffer axisVB(AxisVectices, sizeof(AxisVectices));
	VertexBufferLayout axisLayout;
	axisLayout.Push<float>(3);
	VertexArray axis;
	axis.AddBuffer(axisVB, axisLayout);

	glm::mat4 projection=glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 objPos = { 0,0,0 };
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		Camera::GetInstance()->ProcessKeyboard(window, deltaTime);
		view = Camera::GetInstance()->GetViewMatrix();

		lightColor.x = sin(glfwGetTime() * 2.0f) + 0.2;
		lightColor.y = sin(glfwGetTime() * 0.7f)+0.2;
		lightColor.z = sin(glfwGetTime() * 1.3f) + 0.2;

		ImGui_ImplGlfwGL3_NewFrame();
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		obj.Bind();
		objshader.Bind();
		objshader.SetUniformMat4f("u_projection", projection);
		objshader.SetUniformMat4f("u_view", view);
		
		glm::mat4 obj_model = glm::translate(model, objPos);
		objshader.SetUniformMat4f("u_model", obj_model);
		objshader.SetUniformMat3f("NormalMat", glm::transpose(glm::inverse(glm::mat3(view*obj_model))));

		objshader.SetUniform3f("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
		objshader.SetUniform3f("material.diffuse", glm::vec3(1.0f, 0.5f, 0.71f));
		objshader.SetUniform3f("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
		objshader.SetUniform1f("material.shininess", 32.0f);

		objshader.SetUniform3f("lightColor", lightColor);
		objshader.SetUniform3f("lightPos", lightPos);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		light.Bind();
		lightshader.Bind();
		lightshader.SetUniformMat4f("u_projection", projection);
		lightshader.SetUniformMat4f("u_view", view);
		glm::mat4 light_model = glm::translate(model, lightPos);
		lightshader.SetUniformMat4f("u_model", light_model);
		lightshader.SetUniform3f("lightColor", lightColor);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		axis.Bind();
		axisShader.Bind();
		axisShader.SetUniformMat4f("u_projection", projection);
		axisShader.SetUniformMat4f("u_view", view);
		glm::mat4 axisModel = glm::translate(model, -glm::vec3(0,0,0));
		axisShader.SetUniformMat4f("u_model", axisModel);
		for (int i = 0; i < 3; i++) {
			glm::vec3 tmp = { 0,0,0 };
			tmp[i] = 1;
			axisShader.SetUniform3f("objectColor", tmp);
			glDrawArrays(GL_LINES, 2 * i, 2);
		}

		{
			ImGui::SliderFloat3("objPos", &objPos.x, 0.0f, 1.0f);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse) // 这个bool变量初始时是设定为true的
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
	lastX = xpos;
	lastY = ypos;
	Camera::GetInstance()->ProcessMouseMovement(xoffset, yoffset);
}
