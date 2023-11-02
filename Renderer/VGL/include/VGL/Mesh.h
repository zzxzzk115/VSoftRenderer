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
        std::vector<int> VertexIndices;
        std::vector<int> TextureCoordIndices;
        std::vector<int> NormalIndices;
    };

    struct Mesh
    {
        std::vector<TriangleFace> Faces;
        std::vector<Vector3Float> Vertices;
        std::vector<Vector3Float> Normals;
        std::vector<Vector2Float> TextureCoords;

        Vector2Float GetUV(int faceIndex, int vertexIndexInFace)
        {
            return TextureCoords[Faces[faceIndex].TextureCoordIndices[vertexIndexInFace]];
        }
    };
} // namespace VGL