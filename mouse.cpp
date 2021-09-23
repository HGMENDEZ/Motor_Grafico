#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "mouse.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    ////////////cameraSC.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    //    std::cout << "                          O  P  E  R  A  N  D  O  " << std::endl;
    ////////////cameraSC.ProcessMouseScroll(yoffset);
}