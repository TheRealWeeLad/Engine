#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "vector"
#include "Engine/Shader.h"
#include "Engine/Camera.h"
#include "Engine/MeshRenderer.h"
#include "Engine/Component.h"
#include "Engine/GameObject.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Default camera
Camera* cam{ Camera::MainCamera };

// DELTA TIME
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// For first mouse movement
bool firstMouse{ true };

#pragma region Setup
// Callback to resize window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// INPUT
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Camera Movement
	const float camSpeed = 20 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam->translate(camSpeed * cam->forward);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam->translate(camSpeed * -cam->forward);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam->translate(camSpeed * -cam->right);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam->translate(camSpeed * cam->right);
}
float lastX = 400, lastY = 300;
void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos, lastY = ypos;
		firstMouse = false;
	}

	float dx = xpos - lastX, dy = ypos - lastY;
	lastX = xpos, lastY = ypos;

	const float sensitivity = 0.001f;
	float yaw = sensitivity * dx;
	float pitch = sensitivity * dy;

	//// Constrain angles
	//if (cam.pitch > 89.9f) cam.pitch = 89.9f;
	//if (cam.pitch < -89.9f) cam.pitch = -89.9f;

	// Adjust camera rotation
	cam->rotate(glm::vec3(pitch, yaw, 0));
}
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	const float sensitivity = 5;
	cam->fov -= sensitivity * (float)yOffset;
	if (cam->fov < 1.0f) cam->fov = 1.0f;
	else if (cam->fov > 135.0f) cam->fov = 135.0f;
}
#pragma endregion

int main()
{
	// Initialize Window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "GooGoo", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Set up viewport
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Set mouse input
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);

	// Light Source
	MeshRenderer lightRend{ Mesh::CUBE, };
	glm::vec4 lightColor{ 0.5, 0.5, 0, 1 };
	GameObject lightSource{ glm::vec3{1, 1, 3} };
	lightSource.addComponent(&lightRend);

	// Create objects
	MeshRenderer rend{ Mesh::CUBE };
	Material objectMat{ {1, 0, 0}, {1, 0, 0}, 1.0F };
	rend.setMaterial(objectMat);
	GameObject x{};
	x.addComponent(&rend);

	// Render Loop
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);

		// Clear screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Rendering Commands
		float time = glfwGetTime();
		GameObject::UpdateAll(time);

		// Check/Call Events and Swap Buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		// Update Delta Time
		deltaTime = time - lastFrame;
		lastFrame = time;
	}

	// Clean up
	glfwTerminate();
	return 0;
}