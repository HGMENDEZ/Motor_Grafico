#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


const unsigned int SCR_WIDTH = 1800;
const unsigned int SCR_HEIGHT = 900;

int Window();

void processInput(GLFWwindow* windows);

void framebuffer_size_callback(GLFWwindow* windows, int width, int height);