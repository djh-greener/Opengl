#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<vector>

#include"tools/myDebug.h"

#include"tests/Lighting/Color/TestLightColor.h"
#include"tests/Lighting/Map/TestLightMap.h"
#include"tests/Lighting/Caster/TestLightCaster.h"

#include"tools/Camera.h"

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw_gl3.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

unsigned int SCR_WIDTH = 1000;
unsigned int SCR_HEIGHT = 1000;

float lastX;
float lastY;
float deltaTime = 0;
float lastFrame = 0;


test::Test* currentTest = nullptr;
int main(void)
{
	GLFWwindow* window;
	{

		if (!glfwInit())return -1;
		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);
		glewInit();
		glfwSwapInterval(1);
		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_NORMAL);
		
		glfwSetCursorPosCallback(window, mouse_callback);
	}

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

	test::TestMenu* testMenu = new test::TestMenu(currentTest);
	currentTest = testMenu;

	testMenu->RegisterTest<test::TestLightColor>("Light Color"); 
	testMenu->RegisterTest<test::TestLightMap>("Light Map"); 
	testMenu->RegisterTest<test::TestLightCaster>("Light Caster");
	while (!glfwWindowShouldClose(window))
	{
		GLCall(glClearColor(0, 0, 0, 1));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		
		if (auto it = dynamic_cast<test::TestNormal*>(currentTest)) {
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			Camera::GetInstance()->ProcessKeyboard(window, deltaTime);
			it->m_View = Camera::GetInstance()->GetViewMatrix();
		}

		ImGui_ImplGlfwGL3_NewFrame();

		
		if (currentTest) {
			currentTest->OnUpdate(deltaTime);
			currentTest->OnRender();
			ImGui::Begin("Test");
			if (ImGui::Button("<-") && currentTest != testMenu) {
				delete currentTest;
				currentTest = testMenu;
			}
			currentTest->OnImGuiRender();
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete currentTest;
	if (currentTest != testMenu)
		delete testMenu;

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
	glViewport(0, 0, width, height);

	if (auto it = dynamic_cast<test::TestNormal*>(currentTest)) 
		it->m_Proj = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
	lastX = xpos;
	lastY = ypos;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) 
		Camera::GetInstance()->ProcessMouseMovement(xoffset, yoffset);
}