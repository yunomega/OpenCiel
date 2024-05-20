#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
VertexArray::VertexArray() {

    glGenVertexArrays(1, &m_RendererID);//指定要生成的顶点数组对象名称的数量，数组地址
    
}
VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const {
    glBindVertexArray(m_RendererID);
}
void VertexArray::Unbind() const {
    glBindVertexArray(0);
}


void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout layout) {
    Bind();
    // vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++ )
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        //例如：第一个顶点包含位置、纹理坐标、法线
        //则位置索引为0、纹理坐标索引为1...
        
        //index为0，count为2表示这个顶点的位置有2个类型为type的数据
        //stride表示第一个顶点与第二个顶点之间隔的字节数
        //offset表示该元素(位置或纹理坐标)的地址(以0开始)
        
        //例如第一个顶点存放2个int表示位置，3个char表示纹理坐标
        //那么位置就是（0,2,int,false,2*int+3*char,0)
        //纹理坐标就是（1,3,char,false,2*int+3*char,2*int)
        glVertexAttribPointer(i, element.count, element.type, element.normalized,
            layout.GetStride(),(const void*)offset);
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }

}