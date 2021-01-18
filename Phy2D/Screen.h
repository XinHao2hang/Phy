#pragma once
#include "glad.h"
#include <GLFW/glfw3.h>
#include <fstream>
#include<vector>
#include<iostream>
#include<tuple>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;
static GLFWwindow* openglInit()
{
    // glfw: initialize and configure
   // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    return window;
}
static int LoadShader(const char* vertexShaderSource, const char* fragmentShaderSource)
{
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}
class MakeShape
{
public:
    static unsigned int TexRectangle()
    {
        float vertices[] = {
            //     ---- 位置 ----    - 纹理坐标 -
                 1.0f,  1.0f, 0.0f,  1.0f, 1.0f,   // 右上
                 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,   // 右下
                -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,   // 左下
                -1.0f,  1.0f, 0.0f,  0.0f, 1.0f    // 左上
        };
        unsigned int indices[] = { // 注意索引从0开始! 
             0, 1, 3, // 第一个三角形
             1, 2, 3  // 第二个三角形
        };
        unsigned int VBO = 0, VAO = 0, EBO = 0;
        //构建矩形
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        // 2. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        // 4. 设定顶点属性指针
         // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        return VAO;
    }
    static unsigned int Rectangle()
    {
        float vertices[3 * 4] = {
               1.0f, 1.0f, 0.0f,   // 右上角
               1.0f, -1.0f, 0.0f,  // 右下角
               -1.0f, -1.0f, 0.0f, // 左下角
               -1.0f, 1.0f, 0.0f   // 左上角
        };
        unsigned int indices[] = { // 注意索引从0开始! 
             0, 1, 3, // 第一个三角形
             1, 2, 3  // 第二个三角形
        };
        unsigned int VBO=0, VAO=0,EBO=0;
        //构建矩形
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        // 2. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        // 4. 设定顶点属性指针
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        return VAO;
    }
    static unsigned int Circle()
    {
        float vertices[3 * 150];
        vertices[0] = 0;
        vertices[1] = 0;
        vertices[2] = 0;
        for (int i = 3; i < 120*3; i+=(3))
        {
            float theta = (i-1) * 3.141592654/180.0;
            vertices[i+0] = std::cos(theta);
            vertices[i+1] = std::sin(theta);
            vertices[i+2] = 0;
        }
        unsigned int indices[121];
        for (int i = 0; i < 120; i++)
        {
            indices[i] = i;
        }
        indices[120] = 1;
        unsigned int VBO = 0, VAO = 0, EBO = 0;
        //构建矩形
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        // 2. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        // 4. 设定顶点属性指针
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        return VAO;
    }
};
static char* readFile(const char* filename)
{
    FILE* fp = fopen(filename,"rb+");
    fseek(fp,0,SEEK_END);
    int length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* code = new char[length+1];
    memset(code,0,length+1);
    fread(code,1,length,fp);
    return code;
}
class DisplayShape
{
public:
    unsigned int VAO;
    int shaderProgram;
    unsigned int transformLoc, positionLoc;
    virtual void display() = 0;
};
class DisplayRect:public DisplayShape
{   
public: 
    DisplayRect() {}
    float x, y;
    float rotate = 0;
    glm::mat4 trans = glm::mat4(1.0f);
    glm::vec3 position = glm::vec3(0,0,0);
    void getShader(int shader) { shaderProgram = shader; }
    void setSize(float _x, float _y) 
    {
        x = _x; 
        y = _y;
        trans = glm::scale(trans, glm::vec3((x / (SCR_WIDTH/2)), (y / (SCR_HEIGHT/2)), 1.0));
    }
    DisplayRect(int shader,int _VAO) 
    {
        shaderProgram = shader;
        transformLoc = glGetUniformLocation(shaderProgram, "transform");
        positionLoc = glGetUniformLocation(shaderProgram, "position");
        VAO = _VAO;
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
    }
    void display()
    {
        glm::mat4 t = glm::rotate(trans, glm::radians(rotate), glm::vec3(0.0, 0.0, 1.0));
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(t));
        glUniform3f(positionLoc,position.x,position.y,position.z);
        glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    ~DisplayRect(){}
};
class DisplayCircle :public DisplayShape
{

public:
    float x, y;
    float rotate = 0;
    glm::mat4 trans = glm::mat4(1.0f);
    glm::vec3 position = glm::vec3(0, 0, 0);
    void getShader(int shader) { shaderProgram = shader; }
    void setSize(float _r)
    {
        x = _r;
        y = _r;
        trans = glm::scale(trans, glm::vec3((x / (SCR_WIDTH / 2)), (y / (SCR_HEIGHT / 2)), 1.0));
    }
    DisplayCircle(int shader, int _VAO)
    {
        shaderProgram = shader;
        transformLoc = glGetUniformLocation(shaderProgram, "transform");
        positionLoc = glGetUniformLocation(shaderProgram, "position");
        VAO = _VAO;
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
    }
    void display()
    {
        glm::mat4 t = glm::rotate(trans, glm::radians(rotate), glm::vec3(0.0, 0.0, 1.0));
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(t));
        glUniform3f(positionLoc, position.x, position.y, position.z);
        glDrawElements(GL_LINE_LOOP, 121, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    DisplayCircle() {}
    ~DisplayCircle() {}
};
class DisplayPixel:public DisplayShape
{
    unsigned char data[512][512][3];
    int width, height;
public:
    unsigned int texture;
    DisplayPixel(int w,int h)
    {
        width = w;
        height = h;
        memset(data,0,w*h*3);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 加载并生成纹理
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        int e = glGetError();
    }
    void setPixel(int x, int y, glm::i8vec3 color)
    {
        data[x][y][0] = color.r;
        data[x][y][1] = color.g;
        data[x][y][2] = color.b;
    }
    void updatePixel()
    {
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    void display()
    {
        glUseProgram(shaderProgram);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
};
class Screen
{
    std::vector<DisplayShape*> shapes;
public:
	Screen() 
	{
        /*if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            return;*/
	}
    void push_shape(DisplayShape* s)
    {
        shapes.push_back(s);
    }
    void run()
    {
        for (auto s : shapes)
        {
            s->display();
        }
    }
};

