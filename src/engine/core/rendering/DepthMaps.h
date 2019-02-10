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
        using Resolution = glm::vec<2, GLsizei>;

        DepthMaps();
        ~DepthMaps();
        DepthMaps(const DepthMaps& other) = delete;
        DepthMaps& operator=(const DepthMaps& other) = delete;
        DepthMaps(DepthMaps&& other) = delete;
        DepthMaps& operator=(DepthMaps&& other) = delete;

        Resolution getCubemapResolution() const;
        GLsizei getMaxNumPositionalLights() const;
        GLuint getCubemapsFramebufferId() const;
        GLuint getCubemapsTextureId() const;

        Resolution getDirectionalMapResolution() const;
        GLsizei getMaxNumDirectionalLights() const;
        GLuint getDirectionalMapsFramebufferId() const;
        GLuint getDirectionalMapsTextureId() const;

    private:

        Resolution m_cubemapResolution = {512, 512};
        GLsizei m_maxNumPositionalLights = 10;
        GLuint m_cubemapsFBO     = 0;
        GLuint m_cubemapsTexture = 0;

        Resolution m_directionalMapResoltuion = {1024, 1024};
        GLsizei m_maxNumDirectionalLights = 4;
        GLuint m_directionalMapsFBO     = 0;
        GLuint m_directionalMapsTexture = 0;
    };
}

#endif //SAXION_Y2Q2_RENDERING_DEPTHMAPS_H
