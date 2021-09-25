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

GLFWwindow* window;  // "extern" de window.cpp   

// Seteado del medidor de tiempo
float deltaTime = 0.0f;
float lastFrame = 0.0f;

cameraControl cameraFija(glm::vec3(0.0f, 0.0f, 3.0f));

int main()
{
    Window();

    // version();




// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------



    Shader ourShader("D:/Dropbox/SECUENCIAL/ProyectorUno/verticesBasico.glsl", "d:/dropbox/secuencial/proyectoruno/fragmentBasico.glsl");
    Shader lightingShader("D:\\Dropbox\\0_Libertad\\Libertad_6\\Vertex\\m_l_V.vs", "D:\\Dropbox\\0_Libertad\\Libertad_6\\Fragment\\m_l_F.vs");

    Model ourModel1("D:/Dropbox/00PROYECTO/Importaciones/EsferaFBX.fbx");

    GLuint vaoHandle;
    float positionData[] = {
        -0.8f, -0.8f, 0.0f,
        0.8f, -0.8f, 0.0f,
        0.0f,  0.8f, 0.0f };
    float colorData[] = {
          1.0f, 0.0f, 0.0f,
          0.0f, 1.0f, 0.0f,
          0.0f, 0.0f, 1.0f };

    // Crea y completa los objetos de búfer 
    GLuint vboHandles[2];
    glGenBuffers(2, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];

    // Llena el búfer de posición 
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData, GL_STATIC_DRAW);

    // Llena el búfer de color 
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData, GL_STATIC_DRAW);



    // Crear y configurar el objeto de matriz de vértices 
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);
    // Habilite las matrices de atributos de vértice 
    glEnableVertexAttribArray(0);  // Vertex position 
    glEnableVertexAttribArray(1);  // Vertex color 


    glBindVertexBuffer(0, positionBufferHandle, 0, sizeof(GLfloat) * 3);      //
    glBindVertexBuffer(1, colorBufferHandle, 0, sizeof(GLfloat) * 3);

    glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(0, 0);

    glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(1, 1);



 
    //glUseProgram(shaderProgram);

    lightingShader.use();
        ourShader.use();


    // render loop
// -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
       processInput(window); 

        // render
        // ------
        glClearColor(0.6f, 0.6f, 0.6f, 1.0f);      
        glClear(GL_COLOR_BUFFER_BIT);
       // ourShader.use();

    
        lightingShader.use();
        lightingShader.setVec3("viewPos", cameraFija.Position);
        lightingShader.setFloat("material.shininess", 32.0f);

        /*
           Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
           the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
           by defining light types as classes and set their values in there, or by using a more efficient uniform approach
           by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
        */
        // directional light
        lightingShader.setVec3("dirLight.direction", -0.5f, -0.5f, -0.5f);
        lightingShader.setVec3("dirLight.ambient", 0.4f, 0.4f, 0.4f);
        lightingShader.setVec3("dirLight.diffuse", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("dirLight.specular", 2.0f, 2.0f, 2.0f);

       // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.0f));	// it's a bit too big for our scene, so scale it down
        lightingShader.setMat4("model", model);
        ourModel1.Draw(lightingShader); //









        ourShader.use();
        glBindVertexArray(vaoHandle);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------











        glfwSwapBuffers(window);
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
