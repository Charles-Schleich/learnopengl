#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <learnopengl/shader.h>
#include <stb_image/stb_image.h>
#include <cmath>

// Declarations 
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// shaders
 
// code
// VBO : vertex buffer objects 
// VAO : Vertex Array Object

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Setup Shaders using shader.h File
    Shader ourShader( "./shaders/vertex.shader"
                    , "./shaders/fragment.shader");

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Triangle verticies
    // float vertices[] = {
    //     // positions         // colors
    //      0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    //     -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
    //      0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    // };

    // Rectangle
    float vertices[] = {
        // positions         // colors          // Texture Coords
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // bottom left 
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, // top left
    };


    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    // textures
    float texCoors[] = {
        0.0f, 0.0f, // lower left corner 
        1.0f, 0.0f, // lower right corner
        0.5f, 1.0f, // top center
    };
    
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //load texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("./textures/container.jpg", &width, &height, &nrChannels,0);
    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout<< "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // VAO: Vertex Array Object 
    // Vertex Object 
    // EBO: 

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // co-ordinate attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // UNBIND VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    ourShader.use();


    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // input 
        processInput(window);

        //render commands 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // float timeValue = glfwGetTime();
        //float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        // float z_pos = (sin(timeValue) / 2.0f) +0.5f;
        //glUniform1f(vertexColorLocation, z_pos);

        // glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES,0,3);
 
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        //glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
        // are you really reading my code right now ? 

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}


// Input
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Input
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        std::cout << "1";
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        std::cout << "2";
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        std::cout << "3";
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }


}

