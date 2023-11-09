//
// main.cpp
//
// Created or modified by Kexuan Zhang on 2023/10/28 15:50.
//

#include "VSoftRenderer/Loaders/ModelLoader.h"
#include "VSoftRenderer/Loaders/TextureLoader.h"

#include <VGL/DirectionalLight.h>
#include <VGL/FrameBuffer.h>
#include <VGL/Matrix4.h>
#include <VGL/Shaders/Phong.h>
#include <VGL/VGL.h>

#include <raylib-cpp.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <iostream>

using namespace VGL;
using namespace VSoftRenderer;

const int ScreenWidth = 800;
const int ScreenHeight = 800;

void DrawFrameBuffer()
{
    auto frameBufferSize = FrameBuffer::GetInstance()->GetSize();
    for (int i = 0; i < frameBufferSize.X; ++i)
    {
        for (int j = 0; j < frameBufferSize.Y; ++j)
        {
            auto color = FrameBuffer::GetInstance()->GetPixel(i, j).PixelColor;
            DrawPixel(i, j, {color.R, color.G, color.B, color.A});
        }
    }
}

int main()
{
    raylib::Window window(ScreenWidth, ScreenHeight, "VSoftRenderer");
    raylib::RenderTexture2D renderTexture(ScreenWidth, ScreenHeight);
    raylib::Texture targetTexture(renderTexture.GetTexture());

    // Load a head model from disk
    auto headModel = ModelLoader::LoadModel("Resources/Models/african_head/african_head.obj");
    // Load inner eye model from disk
    auto innerEyeModel = ModelLoader::LoadModel("Resources/Models/african_head/african_head_eye_inner.obj");
    std::vector<std::shared_ptr<VSoftRenderer::Model>> models = { headModel, innerEyeModel };

    SetTargetFPS(60);

    // Load texture images from disk
    auto headDiff = TextureLoader::LoadTexture2D("Resources/Textures/african_head/african_head_diffuse.tga");
    auto headNorm = TextureLoader::LoadTexture2D("Resources/Textures/african_head/african_head_nm.tga");
    auto headSpec = TextureLoader::LoadTexture2D("Resources/Textures/african_head/african_head_spec.tga");
    auto innerEyeDiff = TextureLoader::LoadTexture2D("Resources/Textures/african_head/african_head_eye_inner_diffuse.tga");
    auto innerEyeNorm = TextureLoader::LoadTexture2D("Resources/Textures/african_head/african_head_eye_inner_nm.tga");
    auto innerEyeSpec = TextureLoader::LoadTexture2D("Resources/Textures/african_head/african_head_eye_inner_spec.tga");
    std::vector<std::shared_ptr<VGL::Texture2D>> textures = { headDiff, headNorm, headSpec, innerEyeDiff, innerEyeNorm, innerEyeSpec };

    DirectionalLight light(Vector3Float(1, 1, 1).Normalized());

    // Camera parameters
    Vector3Float eye(1 , 1, 3);
    Vector3Float center(0 , 0, 0);
    Vector3Float up(0, 1, 0);

    Matrix4 modelMatrix = Matrix4::Identity();
    Matrix4 viewMatrix = glLookAt(eye, center, up);
    Matrix4 projectionMatrix = glProjection(eye, center);

    Matrix4 mvp = projectionMatrix * viewMatrix * modelMatrix;

    for (int i = 0; i < textures.size(); ++i)
    {
        glBindTexture(i, textures[i].get());
    }

    PhongShader* shader = new PhongShader();
    shader->UniformMVP = mvp;
    shader->UniformMVPIT = mvp.InverseTranspose();
    shader->UniformLightDirection = light.GetDirection();
    glBindShader(0, shader);
    glUseShaderProgram(0);

    int meshId = 0;
    for (int i = 0; i < models.size(); ++i)
    {
        const auto& model = models[i];
        for (const auto& mesh : model->GetMeshes())
        {
            glBindMesh(meshId++, mesh);
        }
    }

    while (!window.ShouldClose())
    {
        glViewPort(0, 0, ScreenWidth, ScreenHeight);

        glClearColor({50, 50, 50, 255});
        glClear();

        if (IsKeyDown(KEY_A))
        {
            eye.X -= 1;
        }
        if (IsKeyDown(KEY_D))
        {
            eye.X += 1;
        }
        if (IsKeyDown(KEY_W))
        {
            eye.Y += 1;
        }
        if (IsKeyDown(KEY_S))
        {
            eye.Y -= 1;
        }

        // update matrix
        viewMatrix = glLookAt(eye, center, up);
        projectionMatrix = glProjection(eye, center);
        mvp = projectionMatrix * viewMatrix * modelMatrix;

        // update shader parameters
        shader->UniformMVP = mvp;
        shader->UniformMVPIT = mvp.InverseTranspose();

        // draw mesh
        int meshId = 0;
        for (int i = 0; i < models.size(); ++i)
        {
            const auto& model = models[i];
            for (const auto& mesh : model->GetMeshes())
            {
                shader->BindDiffuseTextureSlot = 3 * i;
                shader->BindNormalTextureSlot = 3 * i + 1;
                shader->BindSpecularTextureSlot = 3 * i + 2;
                glDrawMeshIndexed(meshId++);
            }
        }

        renderTexture.BeginMode();
        // Draw FrameBuffer
        DrawFrameBuffer();
        renderTexture.EndMode();

        BeginDrawing();
        window.ClearBackground(raylib::Color::Black());
        targetTexture.Draw(0, 0);
        EndDrawing();
    }

    return 0;
}