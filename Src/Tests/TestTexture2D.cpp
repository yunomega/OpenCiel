#include "TestTexture2D.h"
#include "Renderer.h"
#include "imgui\imgui.h"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace test {
	TestTexture2D::TestTexture2D()
        :m_Proj(glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f)), m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{
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
        //混合，alpha * src + (1-alpha) * dest
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        for (int i = 0; i < 4; i++)
        {
            m_Translation[i] = { 300+200*i,300,0 };
            m_Angel[i] = 0.0f;
            m_Scale[i] = 1.0f;
        }
        
        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        m_VAO = std::make_unique<VertexArray>();
        m_VAO->AddBuffer(*m_VertexBuffer, layout);//此处会调用VA.Bind();

        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

        m_Texture[0] = std::make_unique<Texture>("D:/CppBegin/OpenGL/Res/Textures/ChernoLogo.png");
        m_Texture[1] = std::make_unique<Texture>("D:/CppBegin/OpenGL/Res/Textures/i.png");
        m_Texture[2] = std::make_unique<Texture>("D:/CppBegin/OpenGL/Res/Textures/e.png");
        m_Texture[3] = std::make_unique<Texture>("D:/CppBegin/OpenGL/Res/Textures/l.png");
        m_Shader = std::make_unique<Shader>("D:/CppBegin/OpenGL/Res/Shaders/Basic.shader");
        m_Shader->SetUniform1i("u_Texture", 0);
        m_Shader->Bind();

        ImGui::CreateContext();
        ImGui::StyleColorsDark();
	}
	TestTexture2D::~TestTexture2D() {}
	
	void TestTexture2D::OnUpdate(float deltaTime){}
	void TestTexture2D::OnRender(){
        
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
        Renderer renderer;

        for (int i = 0; i < 4; i++)
        {
            m_Texture[i]->Bind();
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation[i]);

                //绕图片中心旋转
                glm::vec3 center = glm::vec3(m_Translation[i].x, m_Translation[i].y, 0.0f);
                glm::mat4 translation = glm::translate(glm::mat4(1.0f), -center);
                glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_Angel[i]), glm::vec3(0.0f, 0.0f, 1.0f));
                glm::mat4 reverseTranslation = glm::translate(glm::mat4(1.0f), center);
                glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(m_Scale[i], m_Scale[i], 1.0f));


                glm::mat4 mvp = m_Proj * reverseTranslation * scale * rotation * translation * model; //opengl 列优先存储
                m_Shader->SetUniformMat4f("u_MVP", mvp);

                renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
            }
        }

       //m_Texture[1]->Bind();
       ////shader.SetUniform4f("u_Color", r, 0.2f, 0.3f, 0.4f);
       //{
       //    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
       //
       //    //绕图片中心旋转
       //    glm::vec3 center = glm::vec3(m_TranslationB.x, m_TranslationB.y, 0.0f);
       //    glm::mat4 translation = glm::translate(glm::mat4(1.0f), -center);
       //    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_AngelB), glm::vec3(0.0f, 0.0f, 1.0f));
       //    glm::mat4 reverseTranslation = glm::translate(glm::mat4(1.0f), center);
       //    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(m_ScaleB, m_ScaleB, 1.0f));
       //
       //
       //    glm::mat4 mvp = m_Proj * reverseTranslation * scale * rotation * translation * model; //opengl 列优先存储
       //    m_Shader->SetUniformMat4f("u_MVP", mvp);
       //
       //    renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
       //}

	}
    //updata

	void TestTexture2D::OnImGuiRender(){

        for (int i = 0; i < 4; i++)
        {
            std::string A = "Translation " + std::to_string(i);
            std::string B = "Angel " + std::to_string(i);
            std::string C = "Scale " + std::to_string(i);
            ImGui::SliderFloat3(A.c_str(), &m_Translation[i].x, 0.0f, 1920.0f);
            ImGui::SliderFloat(B.c_str(), &m_Angel[i], 0.0f, 360.0f);
            ImGui::SliderFloat(C.c_str(), &m_Scale[i], 1.0f, 5.0f);
            
        }


        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	}
}