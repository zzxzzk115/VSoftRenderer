//
// Mesh.h
//
// Created or modified by Kexuan Zhang on 2023/11/2 3:01.
//

#pragma once

#include "VGL/Vector3.h"

#include <vector>

namespace VGL
{
    struct TriangleFace
    {
        std::vector<int>    Indices;
    };

    struct Vertex
    {
        Vector3Float Position;
        Vector3Float Normal;
        Vector2Float UV;
    };

    struct Mesh
    {
        std::vector<TriangleFace> Faces;
        std::vector<Vertex>       Vertices;
    };
} // namespace VGL