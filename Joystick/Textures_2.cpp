//-----------------------------------------------------------------------------
// Textures_2.cpp by Steve Jones 
// Copyright (c) 2015-2019 Game Institute. All Rights Reserved.
//
// - Add another texture
// - fragment shader blending using GLSL mix()
//-----------------------------------------------------------------------------
#include <iostream>
#include <sstream>
#include <string>
#define GLEW_STATIC
#include "GL/glew.h"	// Important - this header must come before glfw3 header
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
//#include "glad/glad.h"
//#include "common/includes/KHR/khrplatform.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Joystick.h"
#include "Keyboard.h"
#include "Mouse.h"

// Global Variables
const char* APP_TITLE = "Introduction to Modern OpenGL - Textures";
const int gWindowWidth = 800;
const int gWindowHeight = 600;
GLFWwindow* gWindow = NULL;
bool gWireframe = false;
const std::string texture1Filename = "textures/crate.jpg";
const std::string texture2Filename = "textures/airplane.png";

// Function prototypes
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void glfw_onFramebufferSize(GLFWwindow* window, int width, int height);
void showFPS(GLFWwindow* window);
bool initOpenGL();

//void glfwSetKeyCallback(GLFWwindow* window, Keyboard::keyCallback);




float mixVal = 0.5f;

glm::mat4 transform = glm::mat4(1.0f);
Joystick mainJ(0);

//-----------------------------------------------------------------------------
// Main Application Entry Point
//-----------------------------------------------------------------------------
int main()
{
	if (!initOpenGL())
	{
		// An error occured
		std::cerr << "GLFW initialization failed" << std::endl;
		return -1;
	}

	// Set up our quad

	// 1. Set up an array of vertices for a quad (2 triangls) with an index buffer data
	//   (What is a vertex?)
	GLfloat vertices[] = {
		// position			 // tex coords
		-0.5f,  0.5f, 0.0f,	 0.0f, 1.0f,		// Top left
		 0.5f,  0.5f, 0.0f,	 1.0f, 1.0f,		// Top right
		 0.5f, -0.5f, 0.0f,	 1.0f, 0.0f,		// Bottom right
		-0.5f, -0.5f, 0.0f,	 0.0f, 0.0f			// Bottom left 
	};
	
	GLuint indices[] = {
		0, 1, 2,  // First Triangle
		0, 2, 3   // Second Triangle
	};

	// 2. Set up buffers on the GPU
	GLuint vbo, ibo, vao;

	glGenBuffers(1, &vbo);					// Generate an empty vertex buffer on the GPU
	glBindBuffer(GL_ARRAY_BUFFER, vbo);		// "bind" or set as the current buffer we are working with
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	// copy the data from CPU to GPU

	glGenVertexArrays(1, &vao);				// Tell OpenGL to create new Vertex Array Object
	glBindVertexArray(vao);					// Make it the current one

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0));	// Define a layout for the first vertex buffer "0"
	glEnableVertexAttribArray(0);			// Enable the first attribute or attribute "0"

	// Texture Coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Set up index buffer
	glGenBuffers(1, &ibo);	// Create buffer space on the GPU for the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);					// unbind to make sure other code doesn't change it

	ShaderProgram shaderProgram;
	shaderProgram.loadShaders("shaders/basic.vert", "shaders/basic_part2.frag");

	Texture2D texture1;
	texture1.loadTexture(texture1Filename);

	Texture2D texture2;
	texture2.loadTexture(texture2Filename);

	mainJ.update();
	if (mainJ.isPresent())
	{
		std::cout << mainJ.getName() << " is present." << std::endl;
	}
	else
	{
		std::cout << "Not present." << std::endl;
	}

	// Rendering loop
	while (!glfwWindowShouldClose(gWindow))
	{
		showFPS(gWindow);

		// Poll for and process events
		glfwPollEvents();

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		// Render the quad
		// Must be called BEFORE setting uniforms because setting uniforms is done
		// on the currently active shader program.
		shaderProgram.use();

		// Wait!  Why didn't we call glUniform1i for the texture in Part 1?  The answer is OpenGL uses the 
		// default texture unit of 0 for the first texture so if you only have one texture sampler in the fragment
		// shader then you do not need to explicitly set the sampler by calling glUniform1i.

		// --------------- Method 1 For Setting Texture Samplers -------------------------
		// #1 Method for setting uniform samplers
		texture1.bind(0);
		texture2.bind(1);	
		glUniform1i(glGetUniformLocation(shaderProgram.getProgram(), "texSampler1"), 0);
		glUniform1i(glGetUniformLocation(shaderProgram.getProgram(), "texSampler2"), 1);
		//--------------------------------------------------------------------------------


		// #2 Method for setting uniform samplers, basic_part2.frag shader changes:
		// Uncomment these lines and comment the 2 glUniform1i() calls in Method #1 above to test out the
		// second method of setting texture samplers.

		// --------------- Method 2 For Setting Texture Samplers -------------------------
		// layout (binding = 0) uniform sampler2D texSampler1;
		// layout (binding = 1) uniform sampler2D texSampler2;
		//texture1.bind(0);
		//texture2.bind(1);
		//--------------------------------------------------------------------------------
		
		glBindVertexArray(vao);

		shaderProgram.setUniform("mixVal", mixVal);
		shaderProgram.setUniform("transform", transform);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Swap front and back buffers
		glfwSwapBuffers(gWindow);
	}

	// Clean up
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	
	glfwTerminate();

	return 0;
}

//-----------------------------------------------------------------------------
// Initialize GLFW and OpenGL
//-----------------------------------------------------------------------------
bool initOpenGL()
{
	// Intialize GLFW 
	// GLFW is configured.  Must be called before calling any GLFW functions
	if (!glfwInit())
	{
		// An error occured
		std::cerr << "GLFW initialization failed" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	// forward compatible with newer versions of OpenGL as they become available but not backward compatible (it will not run on devices that do not support OpenGL 3.3

	// Create an OpenGL 3.3 core, forward compatible context window
	gWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, APP_TITLE, NULL, NULL);
	if (gWindow == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	// Make the window's context the current one
	glfwMakeContextCurrent(gWindow);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return false;
	}

	// Set the required callback functions
	glfwSetKeyCallback(gWindow, glfw_onKey);
	glfwSetFramebufferSizeCallback(gWindow, glfw_onFramebufferSize);
	//glfwSetKeyCallback(gWindow, Keyboard::keyCallback);
	glfwSetKeyCallback(gWindow, Keyboard::keyCallback);
	glfwSetCursorPosCallback(gWindow, Mouse::cursorPosCallback);
	glfwSetScrollCallback(gWindow, Mouse::mouseWheelCallback);

	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

	// Define the viewport dimensions
	glViewport(0, 0, gWindowWidth, gWindowHeight);


	return true;
}

//-----------------------------------------------------------------------------
// Is called whenever a key is pressed/released via GLFW
//-----------------------------------------------------------------------------
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (Keyboard::key(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	
	/*if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		gWireframe = !gWireframe;
		if (gWireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}*/

	//change mix value
	if (Keyboard::key(GLFW_KEY_UP))
	{
		mixVal += 0.05f;
		if (mixVal > 1)
		{
			mixVal = 1.0f;
		}
	}
	if (Keyboard::key(GLFW_KEY_DOWN))
	{
		mixVal -= 0.05f;
		if (mixVal < 1)
		{
			mixVal = 0.0f;
		}
	}

	if (Keyboard::key(GLFW_KEY_W))
	{
		transform = glm::translate(transform, glm::vec3(0.0f, 0.1f, 0.0f));
	}
	if (Keyboard::key(GLFW_KEY_S))
	{
		transform = glm::translate(transform, glm::vec3(0.0f, -0.1f, 0.0f));
	}
	if (Keyboard::key(GLFW_KEY_A))
	{
		transform = glm::translate(transform, glm::vec3(-0.1f, 0.0f, 0.0f));
	}
	if (Keyboard::key(GLFW_KEY_D))
	{
		transform = glm::translate(transform, glm::vec3(0.1f, 0.0f, 0.0f));
	}
	mainJ.update();
}

//-----------------------------------------------------------------------------
// Is called when the window is resized
//-----------------------------------------------------------------------------
void glfw_onFramebufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//-----------------------------------------------------------------------------
// Code computes the average frames per second, and also the average time it takes
// to render one frame.  These stats are appended to the window caption bar.
//-----------------------------------------------------------------------------
void showFPS(GLFWwindow* window)
{
	static double previousSeconds = 0.0;
	static int frameCount = 0;
	double elapsedSeconds;
	double currentSeconds = glfwGetTime(); // returns number of seconds since GLFW started, as double float

	elapsedSeconds = currentSeconds - previousSeconds;

	// Limit text updates to 4 times per second
	if (elapsedSeconds > 0.25)
	{
		previousSeconds = currentSeconds;
		double fps = (double)frameCount / elapsedSeconds;
		double msPerFrame = 1000.0 / fps;

		// The C++ way of setting the window title
		std::ostringstream outs;
		outs.precision(3);	// decimal places
		outs << std::fixed
			<< APP_TITLE << "    "
			<< "FPS: " << fps << "    "
			<< "Frame Time: " << msPerFrame << " (ms)";
		glfwSetWindowTitle(window, outs.str().c_str());

		// Reset for next average.
		frameCount = 0;
	}

	frameCount++;
}