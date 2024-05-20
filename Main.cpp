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
    GLFWwindow* window;//GLFWwindow ����ͬʱ��װ��һ�����ں�һ��������

    /* Initialize the library */
    if (!glfwInit())//GLFW��ʼ��
        return -1;
    //���ó�3.3 core mode 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//���ð汾����Ϊ3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//���ð汾�κ�Ϊ3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����Ϊ����ģʽ
    /* Create a windowed mode window and its OpenGL context */
    //                        ��   ��     ����      �Ƿ�ȫ�� �Ƿ�����Դ������
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window) //����ʧ��
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
        //glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��
        //������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
        
        //glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬
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