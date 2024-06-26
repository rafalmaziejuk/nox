#include "asserts.h"
#include "opengl/gl_framebuffer.h"
#include "opengl/gl_graphics_pipeline_state.h"
#include "opengl/gl_render_pass.h"
#include "opengl/gl_shader.h"

#include <glad/gl.h>

#include <algorithm>

namespace nox {

namespace {

GLbitfield mapShaderTypeToBitfield(ShaderType type) {
    switch (type) {
    case ShaderType::VERTEX: return GL_VERTEX_SHADER_BIT;
    case ShaderType::FRAGMENT: return GL_FRAGMENT_SHADER_BIT;
    case ShaderType::TESS_CONTROL: return GL_TESS_CONTROL_SHADER_BIT;
    case ShaderType::TESS_EVALUATION: return GL_TESS_EVALUATION_SHADER_BIT;
    case ShaderType::GEOMETRY: return GL_GEOMETRY_SHADER_BIT;
    case ShaderType::COMPUTE: return GL_COMPUTE_SHADER_BIT;

    default: break;
    }

    NOX_ASSERT(false);
    return GL_NONE;
}

GLenum mapPrimitiveTopologyToEnum(PrimitiveTopology topology) {
    switch (topology) {
    case PrimitiveTopology::TRIANGLE_LIST: return GL_TRIANGLES;

    default: break;
    }

    NOX_ASSERT(false);
    return GL_NONE;
}

} // namespace

bool GLGraphicsPipelineState::validateInput(const GraphicsPipelineStateDescriptor &descriptor) {
    auto validateShader = [](const Shader *shader) -> bool {
        if (shader == nullptr) {
            return false;
        }

        const auto &glShader = static_cast<const GLShader *>(shader);
        return (mapShaderTypeToBitfield(glShader->getType()) != GL_NONE);
    };
    bool result = true;

    result &= (GLPipelineLayout::validateInput(descriptor.pipelineLayoutDescriptor));
    result &= (descriptor.renderPass != nullptr);
    result &= (std::all_of(descriptor.shaderStages.begin(), descriptor.shaderStages.end(), validateShader));
    result &= (mapPrimitiveTopologyToEnum(descriptor.primitiveTopology) != GL_NONE);

    return result;
}

GLGraphicsPipelineState::GLGraphicsPipelineState(GraphicsPipelineStateDescriptor &descriptor) : m_pipelineLayout{descriptor.pipelineLayoutDescriptor},
                                                                                                m_subpassIndex{descriptor.subpassIndex},
                                                                                                m_primitiveTopology{mapPrimitiveTopologyToEnum(descriptor.primitiveTopology)} {
    glCreateProgramPipelines(1, &m_handle);
}

GLGraphicsPipelineState::~GLGraphicsPipelineState() {
    glDeleteProgramPipelines(1, &m_handle);
}

void GLGraphicsPipelineState::bind() const {
    glBindProgramPipeline(m_handle);
}

bool GLGraphicsPipelineState::bindShaderStages(const ShaderStages &shaderStages) const {
    GLbitfield stages = GL_NONE;
    for (const auto *shader : shaderStages) {
        const auto *glShader = static_cast<const GLShader *>(shader);
        m_program.attachShader(glShader->getHandle());
        stages |= mapShaderTypeToBitfield(glShader->getType());
    }

    if (!m_program.link()) {
        return false;
    }

    glUseProgramStages(m_handle, stages, m_program.getHandle());
    return true;
}

} // namespace nox
