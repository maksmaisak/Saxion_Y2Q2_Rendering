//
// Created by Maksym Maisak on 2019-02-13.
//

#include "VertexRenderer.h"
#include "GLHelpers.h"
#include <algorithm>
#include <cassert>

VertexRenderer::VertexRenderer(std::size_t maxNumVerticesPerDrawCall) :
    m_maxNumVerticesPerDrawCall(maxNumVerticesPerDrawCall) {

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glBindVertexArray(m_vao);
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * m_maxNumVerticesPerDrawCall, nullptr, GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, nullptr);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);

    glCheckError();
}

void VertexRenderer::renderVertices(const std::vector<glm::vec3>& vertices) {

    const std::size_t numPositions = vertices.size() * 3;
    auto positions = std::make_unique<GLfloat[]>(numPositions);
    for (std::size_t i = 0; i < vertices.size(); ++i) {
        const glm::vec3& position = vertices[i];
        positions[i * 3 + 0] = position.x;
        positions[i * 3 + 1] = position.y;
        positions[i * 3 + 2] = position.z;
    }

    glBindVertexArray(m_vao);
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * numPositions, positions.get());
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glCheckError();
    }
    glBindVertexArray(0);
}
