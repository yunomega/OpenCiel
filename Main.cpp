#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui\imgui_impl_glfw_gl3.h"
#include "Tests\TestClearColor.h"
#include "Tests\Test.h"
#include "Tests\TestTexture2D.h"
int main(void)
{
    GLFWwindow* window;//GLFWwindow 对象同时封装了一个窗口和一个上下文

    /* Initialize the library */
    if (!glfwInit())//GLFW初始化
        return -1;
    //设置成3.3 core mode 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置版本主号为3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//设置版本次号为3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//设置为核心模式
    /* Create a windowed mode window and its OpenGL context */
    //                        宽   长     标题      是否全屏 是否共享资源上下文
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window) //创建失败
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    // glewInit
    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;
    
{// define 


    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    test::Test* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->RegisterTest<test::TestClearColor>("Clear Color");
    testMenu->RegisterTest<test::TestTexture2D>("Texture2D");
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        /* Render here */
        

        ImGui_ImplGlfwGL3_NewFrame();
        if(currentTest)
        {
            currentTest->OnUpdate(0.0f);
            currentTest->OnRender();
            ImGui::Begin("Test");
            if (currentTest != testMenu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->OnImGuiRender();
            ImGui::End();
        }
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        //glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），
        //它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
        
        //glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态
        /* Poll for and process events */
        glfwPollEvents();
    }
    delete currentTest;
    if (currentTest != testMenu)
        delete testMenu;
}   
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}