#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "cameraControl.h"

extern GLFWwindow* window;

void processInput(GLFWwindow* windows);

void framebuffer_size_callback(GLFWwindow* windows, int width, int height);

const unsigned int SCR_WIDTH = 1800;
const unsigned int SCR_HEIGHT = 900;



void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);



//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//
//
//bool firstMouse = true;

int Window();