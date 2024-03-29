#pragma once

#include "opengl/gl_state.h"

#include <nox/buffer.h>

namespace nox {

class GLBuffer : public Buffer, public GLWithState {
  public:
    GLBuffer(const BufferDescriptor &descriptor, GLState &state);
    ~GLBuffer() override;

    [[nodiscard]] uint32_t getHandle() const { return m_handle; }

  protected:
    [[nodiscard]] static bool validateInput(const BufferDescriptor &descriptor);

  private:
    uint32_t m_handle{0u};
};

class GLVertexBuffer final : public GLBuffer {
  public:
    [[nodiscard]] static bool validateInput(const VertexBufferDescriptor &descriptor);

    using GLBuffer::GLBuffer;

    void bind() override;

    void setVertexArrayIndex(uint32_t index);

  private:
    uint32_t m_vertexArrayIndex{0u};
};

class GLIndexBuffer final : public GLBuffer {
  public:
    [[nodiscard]] static bool validateInput(const IndexBufferDescriptor &descriptor);

    using GLBuffer::GLBuffer;

    void bind() override;

    void setIndexType(VertexAttributeFormat format);

  private:
    uint32_t m_indexType{0u};
};

} // namespace nox
