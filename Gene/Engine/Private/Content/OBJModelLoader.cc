// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Content/OBJModelLoader.h>
#include <Content/TinyObjLoader.h>

#include <Math/Vector3.h>
#include <Platform/OpenGL.h>

#include <Core/Array.h>
#include <Core/String.h>

#include <GeneCommon.h>
#include <sstream>

using namespace gene::runtime;
using namespace gene;

GeneModel *OBJModelLoader::LoadFromData(const tinyobj::attrib_t& attrib, const Array<tinyobj::shape_t>& shapes, const Array<tinyobj::material_t>& materials)
{
    GeneModel *model = new GeneModel();

    Array<Vector3>& vertices = model->Vertices;
    Array<Vector3>& normals = model->Normals;
    Array<Vector2>& texCoords = model->UVs;
    Array<GLuint>& indices = model->Indices;

    for (const tinyobj::shape_t& shape : shapes)
    {
        for (const tinyobj::index_t& index : shape.mesh.indices)
        {
            int vindex = index.vertex_index * 3;
            vertices.push_back({
                attrib.vertices[vindex + 0],
                attrib.vertices[vindex + 1],
                attrib.vertices[vindex + 2]
            });

            int nindex = index.normal_index * 3;
            normals.push_back({
                attrib.normals[nindex + 0],
                attrib.normals[nindex + 1],
                attrib.normals[nindex + 2]
            });

            int tindex = index.texcoord_index * 2;
            texCoords.push_back({
                attrib.texcoords[tindex + 0],
                1.0f - attrib.texcoords[tindex + 1] // Invert the Y coordinate
            });

            indices.push_back(indices.size());
        }
    }

    return model;
}

GeneModel *OBJModelLoader::LoadFromMemory(const char *str)
{
    tinyobj::attrib_t attrib;
    Array<tinyobj::shape_t> shapes;
    Array<tinyobj::material_t> materials;
    String err;

    std::stringstream sstream;
    sstream << str;

    bool errCode = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, &sstream);

    GE_ASSERT(errCode, err.c_str());

    return LoadFromData(attrib, shapes, materials);
}

GeneModel *OBJModelLoader::Load(const char * filepath)
{
    tinyobj::attrib_t attrib;
    Array<tinyobj::shape_t> shapes;
    Array<tinyobj::material_t> materials;
    String err;

    bool errCode = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filepath);

    GE_ASSERT(errCode, err.c_str());
    return LoadFromData(attrib, shapes, materials);
}
