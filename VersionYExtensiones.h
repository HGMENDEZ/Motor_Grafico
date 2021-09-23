#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void version()
{
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glslVersion =
		glGetString(GL_SHADING_LANGUAGE_VERSION);

	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);

	printf("GL Vendor            : %s\n", vendor);
	printf("GL Renderer          : %s\n", renderer);
	printf("GL Version (string)  : %s\n", version);
	printf("GL Version (integer) : %d.%d\n", major, minor);
	printf("GLSL Version         : %s\n", glslVersion);

	///////////// EXTENCIONES COMPATIBLES CON LA IMPLEMENTACION ACTUAL DE OpenGL ////////
	GLint nExtensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);

	for (int i = 0; i < nExtensions; i++)
		printf("%s\n", glGetStringi(GL_EXTENSIONS, i));

	GLint formats = 0;
	glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &formats);
	if (formats < 1) {
		std::cerr << "Driver does not support any binary formats." << std::endl;
		exit(EXIT_FAILURE);
	}
	else 
		std::cerr << " formats.  " << formats << std::endl;
}
