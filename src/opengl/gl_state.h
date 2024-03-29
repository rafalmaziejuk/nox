#pragma once

#include "opengl/gl_vertex_array.h"

namespace nox {

struct GLState {
    GLVertexArrayRegistry vertexArrayRegistry;

    uint32_t indexType;
    uint32_t primitiveTopology;
};

class GLWithState {
  public:
    explicit GLWithState(GLState &state) : m_state{&state} {}
    virtual ~GLWithState() = default;

    GLState &getState() const { return *m_state; }

  public:
    GLWithState(const GLWithState &) = delete;
    GLWithState &operator=(const GLWithState &) = delete;

  private:
    GLState *m_state{nullptr};
};

} // namespace nox
