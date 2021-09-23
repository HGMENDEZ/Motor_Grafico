#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "window.h"
#include "VersionYExtensiones.h"
#include "shaderGLSL.h"

GLFWwindow* window;  // "extern" de window.cpp


int main()
{
    Window();

    // version();




// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------



    Shader ourShader("D:/Dropbox/SECUENCIAL/ProyectorUno/verticesBasico.glsl", "d:/dropbox/secuencial/proyectoruno/fragmentBasico.glsl");

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
    GLuint positionBufferHandle = vboHandles[0];//
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


    glBindVertexBuffer(0, positionBufferHandle, 0, sizeof(GLfloat) * 3);
    glBindVertexBuffer(1, colorBufferHandle, 0, sizeof(GLfloat) * 3);

    glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(0, 0);

    glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(1, 1);



 
    //glUseProgram(shaderProgram);
    ourShader.use();

    // render loop
// -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
       processInput(window);   //

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
       
        glClear(GL_COLOR_BUFFER_BIT);
       // ourShader.use();














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
