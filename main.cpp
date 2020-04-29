#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <learnopengl/shader.h>

// Declarations 
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// shaders
const char* vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor; "
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;"
"}\0";

const char* fragmentShaderSource = 
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;"
"void main()\n"
"{\n"
"    FragColor = vec4(ourColor,1.0);"
"}\0";


// code
// VBO : vertex buffer objects 
// VAO : Vertex Array Object

int main()
{

    //std::cout << "Hello world";
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
    ///////////////


    ///////////////

    // Begin setting up shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];

    Shader ourShader( "path/to/vertex.shader"
                    , "path/to/fragment.shader");

    // Coordinate Verticies 

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //float vertices[] = {
    // 0.5f, -0.5f, 0.0f,  // bottom right
    //-0.5f, -0.5f, 0.0f,  // bottom left
    // 0.0f, 0.75f, 0.0f   // peak
    //};

    //unsigned int indices[] = {  // note that we start from 0!
    //    0, 1, 2,    // first triangle
    //};

    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };


    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // VAO Vertex Array Object 
    // Vertex Object 

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // UNBIND VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //glUseProgram(shaderProgram);
    ourShader.use();


    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // input 
        processInput(window);

        //render commands 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        //float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        float z_pos= (sin(timeValue) / 2.0f) +0.5f;
        //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourPos");

        //glUniform1f(vertexColorLocation, z_pos);

        glBindVertexArray(VAO);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawArrays(GL_TRIANGLES,0,3);
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

