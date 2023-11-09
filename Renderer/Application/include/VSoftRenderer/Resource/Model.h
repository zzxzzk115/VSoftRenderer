//
// Model.h
//
// Created or modified by Kexuan Zhang on 2023/11/9 0:28.
//

#pragma once

#include <VGL/Mesh.h>

namespace VSoftRenderer
{
    class Model
    {
    public:
        Model(const std::vector<VGL::Mesh*>& meshes) : m_Meshes(meshes) {}
        ~Model()
        {
            for(auto& mesh : m_Meshes)
            {
                delete mesh;
                mesh = nullptr;
            }
        }

        const std::vector<VGL::Mesh*>& GetMeshes() const { return m_Meshes; }

    private:
        std::vector<VGL::Mesh*> m_Meshes;
    };
} // namespace VSoftRenderer