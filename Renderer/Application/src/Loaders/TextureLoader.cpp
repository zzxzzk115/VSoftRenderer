//
// TextureLoader.cpp
//
// Created or modified by Kexuan Zhang on 2023/11/9 0:17.
//

#include "VSoftRenderer/Loaders/TextureLoader.h"

#include <raylib-cpp.hpp>

#include <VGL/Color.h>

#include <iostream>

namespace VSoftRenderer
{
    std::shared_ptr<VGL::Texture2D> TextureLoader::LoadTexture2D(const std::filesystem::path& texturePath)
    {
        auto textureImageData = raylib::Image(texturePath.string());
        if (!textureImageData.IsReady())
        {
            std::cerr << "Failed to load texture!!!" << std::endl;
            return nullptr;
        }

        int textureImageWidth  = textureImageData.width;
        int textureImageHeight = textureImageData.height;
        VGL::Color* specularTextureColors = (VGL::Color*)LoadImageColors(textureImageData);
        auto texture2D = std::make_shared<VGL::Texture2D>(textureImageWidth, textureImageHeight, specularTextureColors);

        return texture2D;
    }
} // namespace VSoftRenderer