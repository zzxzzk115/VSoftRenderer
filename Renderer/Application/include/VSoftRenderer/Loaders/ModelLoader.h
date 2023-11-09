//
// ModelLoader.h
//
// Created or modified by Kexuan Zhang on 2023/11/9 0:24.
//

#pragma once

#include "VSoftRenderer/Resource/Model.h"

#include <VGL/Mesh.h>

#include <filesystem>
#include <memory>

namespace VSoftRenderer
{
    class ModelLoader
    {
    public:
        static std::shared_ptr<Model> LoadModel(const std::filesystem::path& modelPath);
    };
} // namespace VSoftRenderer