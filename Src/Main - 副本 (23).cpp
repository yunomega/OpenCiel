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
    float positions[] = {
        -50.0f, -50.0f, 0.0f, 0.0f,
         50.0f, -50.0f, 1.0f, 0.0f,
         50.0f,  50.0f, 1.0f, 1.0f,
        -50.0f,  50.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    //��ϣ�alpha * src + (1-alpha) * dest
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);//�˴������VA.Bind();
    IndexBuffer ib(indices, 6);

    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::vec3 translationA(200, 200, 0);
    glm::vec3 translationB(400, 200, 0);
    Shader shader("D:/CppBegin/OpenGL/Res/Shaders/Basic.shader");
    Renderer renderer;
    Texture texture("D:/CppBegin/OpenGL/Res/Textures/ChernoLogo.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);
    //float r = 0.0f;
    //float increment = 0.01f;
    //va.Bind();
    //ib.Bind();
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();
    shader.Bind();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        ImGui_ImplGlfwGL3_NewFrame();
        
 /**/ {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
            glm::mat4 mvp = proj * view * model; //opengl �����ȴ洢
            shader.SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(va, ib, shader);
        }
        //shader.SetUniform4f("u_Color", r, 0.2f, 0.3f, 0.4f);
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
            glm::mat4 mvp = proj * view * model; //opengl �����ȴ洢
            shader.SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(va, ib, shader);
        }

        //if (r > 1.0f)
        //    increment = -0.01f;
        //else if (r < 0.0f)
        //    increment = 0.01f;
        //r += increment;

        {
            ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
            ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 960.0f);
 
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
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
}
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}