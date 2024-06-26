#pragma once

#include "opengl/gl_state.h"

#include <nox/command_list.h>

namespace nox {

class GLCommandList final : public CommandList {
  public:
    [[nodiscard]] static bool validateInput(const RenderPassBeginDescriptor &descriptor);

    explicit GLCommandList(const CommandListDescriptor &descriptor);

    void setViewport(const Viewport &viewport) override;

    void beginRenderPass(const RenderPassBeginDescriptor &descriptor) override;
    void endRenderPass() override;

    void bindGraphicsPipelineState(const GraphicsPipelineState &pipelineState) override;
    void bindVertexBuffer(const Buffer &buffer) override;
    void bindIndexBuffer(const Buffer &buffer) override;

    void draw(uint32_t firstVertexIndex, uint32_t vertexCount) override;
    void drawIndexed(uint32_t firstVertexIndex, uint32_t vertexCount) override;

  private:
    GLState m_state;
};

} // namespace nox
