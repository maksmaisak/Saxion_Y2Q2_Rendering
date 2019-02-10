//
// Created by Maksym Maisak on 2019-02-10.
//

#include "DepthMaps.h"
#include <iostream>
#include "GLHelpers.h"

using namespace en;

DepthMaps::DepthMaps() {

    glGenTextures(1, &m_cubemapsTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, m_cubemapsTexture);
    {
        glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, 0, GL_DEPTH_COMPONENT, CUBEMAP_RESOLUTION.x, CUBEMAP_RESOLUTION.y, 6 * MAX_NUM_LIGHTS, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    }
    glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, 0);

    glCheckError();

    glGenFramebuffers(1, &m_cubemapsFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_cubemapsFBO);
    {
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_cubemapsTexture, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);

        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE) {
            std::cerr << "Failed to create the framebuffer for depth cubemaps" << std::endl;
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glCheckError();
}

DepthMaps::~DepthMaps() {

    glDeleteTextures(1, &m_cubemapsTexture);
    glDeleteFramebuffers(1, &m_cubemapsFBO);
}

GLuint DepthMaps::getCubemapsFramebufferId() const {
    return m_cubemapsFBO;
}

GLuint DepthMaps::getCubemapsTextureId() const {
    return m_cubemapsTexture;
}
