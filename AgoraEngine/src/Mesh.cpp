#include "Mesh.hpp"

agora::Mesh::Mesh() :
    m_attributes(nullptr),
    m_vertexBuffer(nullptr),
    m_vertexBufferSize(0),
    m_indexBuffer(nullptr),
    m_indexBufferSize(0),
    m_VAO(0),
    m_VBO(0),
    m_EBO(0)
{
}

agora::Mesh::~Mesh()
{
#ifdef AGORA_DEBUG
    assert(!m_VBOReleased);
#endif

    assert(m_attributes == nullptr);
    assert(m_vertexBuffer == nullptr);
    assert(m_indexBuffer == nullptr);
    releaseFromGPU();
}

agora::Mesh::Mesh(Mesh&& mesh) :
    m_attributes(mesh.m_attributes),
    m_vertexBuffer(mesh.m_vertexBuffer),
    m_vertexBufferSize(mesh.m_vertexBufferSize),
    m_indexBuffer(mesh.m_indexBuffer),
    m_indexBufferSize(mesh.m_indexBufferSize),
    m_VAO(mesh.m_VAO)
{
    mesh.m_attributes = nullptr;
    mesh.m_vertexBuffer = nullptr;
    mesh.m_vertexBufferSize = 0;
    mesh.m_indexBuffer = nullptr;
    mesh.m_indexBufferSize = 0;
    mesh.m_VAO = 0;
}

unsigned agora::Mesh::getVertexBufferSize() const
{
    return m_vertexBufferSize;
}

unsigned agora::Mesh::prepare(void* const baseLocation, const unsigned vertexBuffSize, const unsigned numAttrib, const unsigned stride, const unsigned indexBuffSize)
{
    m_numAttributes         = numAttrib;
    m_vertexBufferSize      = vertexBuffSize;
    m_vertexStride          = stride;
    m_indexBufferSize       = indexBuffSize;

    const unsigned attribBuffSize = numAttrib * sizeof(VertexAttrib);
    m_attributes            = reinterpret_cast<VertexAttrib*>(baseLocation);
    m_indexBuffer           = reinterpret_cast<GLuint*>(m_attributes + attribBuffSize);
    m_vertexBuffer          = reinterpret_cast<aByte*>(m_indexBuffer + m_indexBufferSize);

    return attribBuffSize + m_indexBufferSize + m_vertexBufferSize;
}

GLuint* agora::Mesh::getIndexData(const unsigned startLoc)
{
    return &m_indexBuffer[startLoc];
}

const GLuint* agora::Mesh::getIndexData(const unsigned startLoc) const
{
    return getIndexData(startLoc);
}

unsigned agora::Mesh::getIndexBufferSize() const
{
    return m_indexBufferSize;
}

unsigned agora::Mesh::getNumIndices() const
{
    return m_indexBufferSize / sizeof(GLuint);
}

void agora::Mesh::addAttrib(unsigned index, VertexAttrib attrib)
{
    assert(index < m_numAttributes);
    m_attributes[index] = attrib;
}

void agora::Mesh::returnVertexData()
{
#ifdef AGORA_DEBUG
    m_VBOReleased = false;
#endif

    assert(glUnmapNamedBuffer(m_VBO));
}

GLuint* agora::Mesh::releaseIndexData(unsigned startLoc)
{
#ifdef AGORA_DEBUG
    m_EBOReleased = true;
#endif

    std::ptrdiff_t diff = reinterpret_cast<std::uintptr_t>(m_vertexBuffer) - reinterpret_cast<std::uintptr_t>(m_attributes);
    return reinterpret_cast<GLuint*>(glMapNamedBufferRange(m_EBO, startLoc, m_indexBufferSize, GL_MAP_WRITE_BIT));
}

void agora::Mesh::returnIndexData()
{
#ifdef AGORA_DEBUG
    m_EBOReleased = false;
#endif

    assert(glUnmapNamedBuffer(m_EBO));
}

void agora::Mesh::sendToGPU(GLenum usage)
{
    if (m_VAO == 0)
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        // load into GPU:
        glNamedBufferData(m_VBO, m_vertexBufferSize, m_vertexBuffer, usage);
        glNamedBufferData(m_EBO, m_indexBufferSize, m_indexBuffer, usage);

        std::ptrdiff_t diff = reinterpret_cast<std::uintptr_t>(m_vertexBuffer) - reinterpret_cast<std::uintptr_t>(m_attributes);
        glVertexArrayVertexBuffer(m_VAO, 0, m_VBO, diff, m_vertexStride);
        for (unsigned i = 0; i < m_numAttributes; i++)
        {
            glEnableVertexAttribArray(i);
            glVertexArrayAttribFormat(m_VAO, i, m_attributes[i].m_size, m_attributes[i].m_type, m_attributes[i].m_normalized, m_attributes[i].m_offset);
            glVertexAttribBinding(i, 0);
        }
    }
}

void agora::Mesh::releaseFromGPU()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

bool agora::Mesh::isInGPU() const
{
    return m_VAO != 0;
}

GLuint agora::Mesh::VAO() const
{
    return m_VAO;
}