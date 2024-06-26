#pragma once

#include <nox/buffer.h>
#include <nox/command_list.h>
#include <nox/framebuffer.h>
#include <nox/export.h>
#include <nox/graphics_pipeline_state.h>
#include <nox/render_pass.h>
#include <nox/shader.h>
#include <nox/swapchain.h>
#include <nox/texture.h>

#include <functional>
#include <memory>
#include <string_view>

namespace nox {

enum class RendererBackend {
    NONE,
    OPENGL
};

class Renderer;
using RendererDeleter = std::function<void(Renderer *)>;
using RendererPtr = std::unique_ptr<Renderer, RendererDeleter>;

class NOX_EXPORT Renderer {
  public:
    [[nodiscard]] static RendererPtr create(RendererBackend backend);

    [[nodiscard]] virtual RendererBackend getRendererBackend() const = 0;

    [[nodiscard]] virtual std::unique_ptr<Swapchain> createSwapchain(const SwapchainDescriptor &descriptor) = 0;

    [[nodiscard]] virtual std::unique_ptr<Buffer> createVertexBuffer(const VertexBufferDescriptor &descriptor) = 0;

    [[nodiscard]] virtual std::unique_ptr<Buffer> createIndexBuffer(const IndexBufferDescriptor &descriptor) = 0;

    [[nodiscard]] virtual std::unique_ptr<Shader> createShader(const ShaderDescriptor &descriptor, std::string_view source) = 0;

    [[nodiscard]] virtual std::unique_ptr<GraphicsPipelineState> createGraphicsPipelineState(GraphicsPipelineStateDescriptor &descriptor) = 0;

    [[nodiscard]] virtual std::unique_ptr<CommandList> createCommandList(const CommandListDescriptor &descriptor) = 0;

    [[nodiscard]] virtual std::shared_ptr<Texture> createTexture2D(const Texture2DDescriptor &descriptor) = 0;

    [[nodiscard]] virtual std::unique_ptr<RenderPass> createRenderPass(const RenderPassDescriptor &descriptor) = 0;

    [[nodiscard]] virtual std::unique_ptr<Framebuffer> createFramebuffer(const FramebufferDescriptor &descriptor) = 0;

  public:
    Renderer(const Renderer &) = delete;
    Renderer &operator=(const Renderer &) = delete;
    Renderer(Renderer &&) = delete;
    Renderer &operator=(Renderer &&) = delete;
    virtual ~Renderer() = default;

  protected:
    Renderer() = default;
};

} // namespace nox
