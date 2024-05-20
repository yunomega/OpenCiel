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

    //shader.Bind();  为GPU绑定一个shader程序
    //va.Bind(); //包括VertexBuffer和IndexBuffer数据信息
    //starting at indices to construct a sequence of geometric primitives,已绑定ib故nullptr
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
void Renderer::Clear() const {
    glClear(GL_COLOR_BUFFER_BIT);
    //我们可以通过调用glClear函数来清空屏幕的颜色缓冲，它接受一个缓冲位(Buffer Bit)来指定要清空的缓冲，可能的缓冲位有GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT。由于现在我们只关心颜色值，所以我们只清空颜色缓冲。
}