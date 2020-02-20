#include <iostream>

#include "utils/Log.h"
#include "platform/FreyaPlatform.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

void processInput(GLFWwindow* window);

void main(){
	fr_logd("Freya Begin");

	FREYA::FreyaPlatform test;
	test.setWH(500, 600);
	test.buildContext();
	test.makeCurrentContext();

	glViewport(0,0,500,600);

	while (!glfwWindowShouldClose((GLFWwindow *)test._glContext))
	{
		// input
		// -----
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.6f, 0.6f, 0.9f, 1.0f);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers((GLFWwindow*)test._glContext);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
