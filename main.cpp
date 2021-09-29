#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "window.h"
#include "VersionYExtensiones.h"
#include "shaderGLSL.h"
#include "cameraFija.h"
#include "cameraControl.h"
#include "model.h"

GLFWwindow* window;  // "extern" de window.cpp   ///

// Seteado del medidor de tiempo
float deltaTime = 0.0f;
float lastFrame = 0.0f;

cameraControl cameraFija(glm::vec3(0.0f, 0.0f, 3.0f));//


int main()
{
    Window();



    Shader lightingShader("D:/Dropbox/SECUENCIAL/Motor_Grafico/vertex_Lucess.glsl", "D:/Dropbox/SECUENCIAL/Motor_Grafico/fragment_Luces.glsl");

    Model ourModel1("D:/Dropbox/00PROYECTO/Importaciones/EsferaFBX.fbx");
       
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 


//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", cameraFija.Position);
        lightingShader.setFloat("material.shininess", 5.0f);

        // directional light
        lightingShader.setVec3("dirLight.direction", -3.0f, -3.0f, -3.0f);
        lightingShader.setVec3("dirLight.ambient", 0.55f, 0.55f, 0.55f);
        lightingShader.setVec3("dirLight.diffuse", 0.50f, 0.50f, 0.50f);
        lightingShader.setVec3("dirLight.specular", 0.3f, 0.3f, 0.3f);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(cameraFija.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f); 
        glm::mat4 view = cameraFija.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);



        // render the loaded model
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.0f));	// it's a bit too big for our scene, so scale it down
        lightingShader.setMat4("model", model);
        ourModel1.Draw(lightingShader);


//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------


        //glDrawArrays(GL_TRIANGLES, 0, 3);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}





void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraFija.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraFija.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraFija.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraFija.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        cameraFija.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        cameraFija.ProcessKeyboard(DOWN, deltaTime);



}
