#pragma once

#include "ObjFile.h"
#include "SceneObject.h"

class FileSceneObject : public SceneObject
{
public:

    static FileSceneObject* LoadFromObjFile(const char* file, Shader shader, Material material)
    {
        tinyobj::ObjReaderConfig reader_config;
        //reader_config.mtl_search_path = "./"; // path to material files...

        tinyobj::ObjReader reader;

        // handle parser errors and warnings
        if (!reader.ParseFromFile("Models\\" + std::string(file), reader_config))
        {
            if (!reader.Error().empty())
            {
                std::cerr << "TinyObjReader: " << reader.Error();
                exit(1);
            }
        }
        if (!reader.Warning().empty())
        {
            std::cout << "TinyObjReader: " << reader.Warning();
        }

        auto& attrib = reader.GetAttrib();
        auto& shapes = reader.GetShapes();
        auto& materials = reader.GetMaterials();

        std::vector<float> f_verts;
        std::vector<float> f_norms;
        std::vector<float> f_texts;

        // Loop over shapes
        for (const auto& shape : shapes)
        {
            // Loop over faces
            size_t index_offset = 0;
            for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++)
            {
                int fv = shape.mesh.num_face_vertices[f];

                // Loop over vertices in the face.
                for (size_t v = 0; v < fv; v++)
                {
                    tinyobj::index_t idx = shape.mesh.indices[index_offset + v];

                    // optimize this crap... just for demo now

                    f_verts.push_back(attrib.vertices[3 * idx.vertex_index + 0]); // vx
                    f_verts.push_back(attrib.vertices[3 * idx.vertex_index + 1]); // vy
                    f_verts.push_back(attrib.vertices[3 * idx.vertex_index + 2]); // vz

                    f_norms.push_back(attrib.normals[3 * idx.normal_index + 0]); // nx
                    f_norms.push_back(attrib.normals[3 * idx.normal_index + 1]); // ny
                    f_norms.push_back(attrib.normals[3 * idx.normal_index + 2]); // nz

                    if (!attrib.texcoords.empty())
                    {
                        f_texts.push_back(attrib.texcoords[2 * idx.texcoord_index + 0]); // tv
                        f_texts.push_back(attrib.texcoords[2 * idx.texcoord_index + 1]); // tt    
                    }

                }
                index_offset += fv;
                // per-face material
                shape.mesh.material_ids[f];
            }
        }

        // use materials if found
        if (!materials.empty())
        {
            if (!attrib.texcoords.empty())
            {
                material = Material::create_texture(
                    "Models\\" + materials[0].diffuse_texname,
                    material.get_ambient_component(),
                    material.get_diffuse_component(),
                    material.get_specular_component(),
                    material.get_shininess());
            }            
        }

        auto obj = new FileSceneObject(f_verts, f_norms, shader, material);
        obj->set_texture_coordinates(f_texts);
        return obj;
    }

private:

    FileSceneObject(const std::vector<float>& vertices, const std::vector<float>& normals, Shader shader, Material material)
        : SceneObject(vertices, normals, STATIC, shader, material)
    {
    }
};
