#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<vector>

#include"myDebug.h"

#include"tests/Samples/TestClearColor.h"
#include"tests/Samples/TestTexture2D.h"
#include"tests/Test.h"
#include"Camera.h"

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw_gl3.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

float lastX;
float lastY;

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
		glEnable(GL_DEPTH_TEST);


		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	}

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

	test::Test* currentTest = nullptr;
	test::TestMenu* testMenu = new test::TestMenu(currentTest);
	currentTest = testMenu;

	testMenu->RegisterTest<test::TestClearColor>("Clear Color");
	testMenu->RegisterTest<test::TestTexture2D>("2D Texture");

	while (!glfwWindowShouldClose(window))
	{
		GLCall(glClearColor(0, 0, 0, 1));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		
		ImGui_ImplGlfwGL3_NewFrame();

		if (currentTest) {
			currentTest->OnUpdate(0.0F);
			currentTest->OnRender();
			ImGui::Begin("Test");
			if (currentTest != testMenu && ImGui::Button("<-")) {
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
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
	lastX = xpos;
	lastY = ypos;
	Camera::GetInstance()->ProcessMouseMovement(xoffset, yoffset);
}
