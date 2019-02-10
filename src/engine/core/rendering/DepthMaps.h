//
// Created by Maksym Maisak on 2019-02-10.
//

#ifndef SAXION_Y2Q2_RENDERING_DEPTHMAPS_H
#define SAXION_Y2Q2_RENDERING_DEPTHMAPS_H

#include <GL/glew.h>
#include "glm.hpp"

namespace en {

    /// Owns the shadowmaps.
    class DepthMaps final {

    public:
        inline static const glm::vec<2, GLsizei> CUBEMAP_RESOLUTION = {1024, 1024};
        inline static const std::size_t MAX_NUM_LIGHTS = 10;

        DepthMaps();
        ~DepthMaps();

        GLuint getCubemapsFramebufferId() const;
        GLuint getCubemapsTextureId() const;

    private:

        GLuint m_cubemapsFBO = 0;
        GLuint m_cubemapsTexture = 0;
    };
}

#endif //SAXION_Y2Q2_RENDERING_DEPTHMAPS_H
