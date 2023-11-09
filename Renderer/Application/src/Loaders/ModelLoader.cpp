//
// ModelLoader.cpp
//
// Created or modified by Kexuan Zhang on 2023/11/9 0:25.
//

#include "VSoftRenderer/Loaders/ModelLoader.h"

#include <tiny_obj_loader.h>

namespace VSoftRenderer
{
    std::shared_ptr<Model> ModelLoader::LoadModel(const std::filesystem::path& modelPath)
    {
        std::shared_ptr<Model> model = nullptr;

        if (modelPath.extension() == ".obj")
        {
            // Load a model from disk
            std::string modelFile = modelPath.string();
            tinyobj::ObjReaderConfig readerConfig;
            readerConfig.mtl_search_path = "./"; // Path to material files

            tinyobj::ObjReader reader;

            if (!reader.ParseFromFile(modelFile, readerConfig))
            {
                if (!reader.Error().empty())
                {
                    std::cerr << "TinyObjReader: " << reader.Error();
                }
                return nullptr;
            }

            if (!reader.Warning().empty())
            {
                std::cout << "TinyObjReader: " << reader.Warning();
            }

            auto& attrib = reader.GetAttrib();
            auto& shapes = reader.GetShapes();
            auto& materials = reader.GetMaterials();

            std::vector<VGL::Mesh*> meshes;

            // Loop over shapes
            for (size_t s = 0; s < shapes.size(); s++)
            {
                VGL::Mesh* mesh = new VGL::Mesh();
                mesh->Vertices.resize(attrib.vertices.size());
                mesh->Normals.resize(attrib.normals.size());
                mesh->TextureCoords.resize(attrib.texcoords.size());

                // Loop over faces(polygon)
                size_t indexOffset = 0;
                for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
                {
                    VGL::TriangleFace face = {};

                    size_t fv = static_cast<size_t>(shapes[s].mesh.num_face_vertices[f]);

                    // Loop over vertices in the face.
                    int vertexIndex = 0;
                    for (size_t v = 0; v < fv; v++)
                    {
                        // access to vertex
                        tinyobj::index_t idx = shapes[s].mesh.indices[indexOffset + v];
                        vertexIndex = static_cast<size_t>(idx.vertex_index);

                        tinyobj::real_t vx = attrib.vertices[3*static_cast<size_t>(idx.vertex_index)+0];
                        tinyobj::real_t vy = attrib.vertices[3*static_cast<size_t>(idx.vertex_index)+1];
                        tinyobj::real_t vz = attrib.vertices[3*static_cast<size_t>(idx.vertex_index)+2];

                        mesh->Vertices[vertexIndex] = { vx, vy, vz };
                        face.VertexIndices.push_back(vertexIndex);

                        // Check if `normal_index` is zero or positive. negative = no normal data
                        if (idx.normal_index >= 0)
                        {
                            tinyobj::real_t nx = attrib.normals[3*static_cast<size_t>(idx.normal_index)+0];
                            tinyobj::real_t ny = attrib.normals[3*static_cast<size_t>(idx.normal_index)+1];
                            tinyobj::real_t nz = attrib.normals[3*static_cast<size_t>(idx.normal_index)+2];

                            auto normalIndex = static_cast<size_t>(idx.normal_index);

                            mesh->Normals[normalIndex] = { nx, ny, nz };
                            face.NormalIndices.push_back(normalIndex);
                        }

                        // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                        if (idx.texcoord_index >= 0)
                        {
                            tinyobj::real_t tx = attrib.texcoords[2*static_cast<size_t>(idx.texcoord_index)+0];
                            tinyobj::real_t ty = attrib.texcoords[2*static_cast<size_t>(idx.texcoord_index)+1];

                            auto texCoordIndex = static_cast<size_t>(idx.texcoord_index);

                            mesh->TextureCoords[texCoordIndex] = { tx, ty };
                            face.TextureCoordIndices.push_back(texCoordIndex);
                        }

                        // Optional: vertex colors
                        // tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
                        // tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
                        // tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
                    }
                    indexOffset += fv;
                    mesh->Faces.push_back(face);

                    // per-face material
                    shapes[s].mesh.material_ids[f];
                }

                meshes.push_back(mesh);
            }

            // construct a model
            model = std::make_shared<Model>(meshes);
        }

        return model;
    }
} // namespace VSoftRenderer