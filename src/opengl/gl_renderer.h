#pragma once

#include <nox/renderer.h>

namespace nox {

class GLRenderer final : public Renderer {
  public:
    GLRenderer() = default;

    RendererBackend getRendererBackend() const override;

    std::unique_ptr<Swapchain> createSwapchain(const SwapchainDescriptor &descriptor) override;

    std::unique_ptr<Buffer> createVertexBuffer(const VertexBufferDescriptor &descriptor) override;

    std::unique_ptr<Buffer> createIndexBuffer(const IndexBufferDescriptor &descriptor) override;

    std::unique_ptr<Shader> createShader(const ShaderDescriptor &descriptor, std::string_view source) override;

    std::unique_ptr<GraphicsPipelineState> createGraphicsPipelineState(GraphicsPipelineStateDescriptor &descriptor) override;

    std::unique_ptr<CommandList> createCommandList(const CommandListDescriptor &descriptor) override;

    std::shared_ptr<Texture> createTexture2D(const Texture2DDescriptor &descriptor) override;

    std::unique_ptr<RenderPass> createRenderPass(const RenderPassDescriptor &descriptor) override;

    std::unique_ptr<Framebuffer> createFramebuffer(const FramebufferDescriptor &descriptor) override;
};

} // namespace nox
