//
// Created by Maksym Maisak on 2019-03-06.
//

#include "Model.h"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.hpp"

using namespace en;

namespace en {

    struct ModelImpl {

        using index_t = unsigned int;

        inline static void addNode(Model& model, const aiScene* scene, const aiNode* node) {

            for (index_t i = 0; i < node->mNumMeshes; ++i) {

                const index_t index = node->mMeshes[i];
                const aiMesh* aiMesh = scene->mMeshes[index];
                model.m_meshes.emplace_back(aiMesh);
            }

            for (index_t i = 0; i < node->mNumChildren; ++i) {
                addNode(model, scene, node->mChildren[i]);
            }
        }
    };
}

std::shared_ptr<Model> Model::load(const std::string& filepath) {

    auto model = std::make_shared<Model>();
    model->m_filepath = filepath;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_OptimizeMeshes);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {

        std::cerr << "Could not load model from " << filepath << std::endl;
        return nullptr;
    }

    ModelImpl::addNode(*model, scene, scene->mRootNode);

    std::cout << "Loaded model from " << filepath << ", " << model->m_meshes.size() << " mesh(es)." << std::endl;

    return model;
}

const std::vector<Mesh>& Model::getMeshes() const {
    return m_meshes;
}
