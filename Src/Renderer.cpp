#include "Renderer.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}
bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL_Error] (" << error << ")" << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}
void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {

    //shader.Bind();  ΪGPU��һ��shader����
    //va.Bind(); //����VertexBuffer��IndexBuffer������Ϣ
    //starting at indices to construct a sequence of geometric primitives,�Ѱ�ib��nullptr
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
void Renderer::Clear() const {
    glClear(GL_COLOR_BUFFER_BIT);
    //���ǿ���ͨ������glClear�����������Ļ����ɫ���壬������һ������λ(Buffer Bit)��ָ��Ҫ��յĻ��壬���ܵĻ���λ��GL_COLOR_BUFFER_BIT��GL_DEPTH_BUFFER_BIT��GL_STENCIL_BUFFER_BIT��������������ֻ������ɫֵ����������ֻ�����ɫ���塣
}