#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
VertexArray::VertexArray() {

    glGenVertexArrays(1, &m_RendererID);//ָ��Ҫ���ɵĶ�������������Ƶ������������ַ
    
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
        //���磺��һ���������λ�á��������ꡢ����
        //��λ������Ϊ0��������������Ϊ1...
        
        //indexΪ0��countΪ2��ʾ��������λ����2������Ϊtype������
        //stride��ʾ��һ��������ڶ�������֮������ֽ���
        //offset��ʾ��Ԫ��(λ�û���������)�ĵ�ַ(��0��ʼ)
        
        //�����һ��������2��int��ʾλ�ã�3��char��ʾ��������
        //��ôλ�þ��ǣ�0,2,int,false,2*int+3*char,0)
        //����������ǣ�1,3,char,false,2*int+3*char,2*int)
        glVertexAttribPointer(i, element.count, element.type, element.normalized,
            layout.GetStride(),(const void*)offset);
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }

}