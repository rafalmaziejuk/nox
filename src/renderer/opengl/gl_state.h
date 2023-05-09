#pragma once

#include <vector>

namespace NOX {

class GLBuffer;
class GLVertexArray;
struct VertexFormat;

struct GLState {
    std::vector<VertexFormat> vertexFormats;
    std::vector<std::unique_ptr<GLVertexArray>> vertexArrays;

    uint32_t indexType;
    uint32_t currentlyBoundVertexArrayIndex;
    uint32_t primitiveTopology;
};

} // namespace NOX