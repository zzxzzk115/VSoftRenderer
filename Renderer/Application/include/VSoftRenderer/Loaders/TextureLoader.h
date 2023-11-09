//
// TextureLoader.h
//
// Created or modified by Kexuan Zhang on 2023/11/9 0:14.
//

#pragma once

#include <VGL/Texture2D.h>

#include <filesystem>
#include <memory>

namespace VSoftRenderer
{
    class TextureLoader
    {
    public:
        static std::shared_ptr<VGL::Texture2D> LoadTexture2D(const std::filesystem::path& texturePath);
    };
} // namespace VSoftRenderer