#include "Mesh.hpp"

template<typename T>
inline T* agora::Mesh::getVertexData(unsigned startLoc)
{
    return reinterpret_cast<T*>(&m_vertexBuffer[startLoc]);
}

template<typename T>
inline const T* agora::Mesh::getVertexData(unsigned startLoc) const
{
    return getVertexData(startLoc);
}

template<typename T>
inline T* agora::Mesh::releaseVertexData(unsigned startLoc)
{
#   ifdef AGORA_DEBUG
        m_VBOReleased = true;
#   endif

    std::ptrdiff_t diff = reinterpret_cast<std::uintptr_t>(m_vertexBuffer) - reinterpret_cast<std::uintptr_t>(m_attributes);
    return reinterpret_cast<T*>(glMapNamedBufferRange(m_VBO, diff + startLoc, m_vertexBufferSize - startLoc, GL_MAP_WRITE_BIT));
}