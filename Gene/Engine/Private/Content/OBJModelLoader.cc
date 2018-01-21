#include <Content/OBJModelLoader.h>
#include <IO/File.h>
#include <Math/Vector3.h>
#include <Platform/OpenGL.h>
#include <sstream>
#include <string>
#include <algorithm>
#include <Content/TinyObjLoader.h>

using namespace Gene::Content;
using namespace Gene;

GeneModel *OBJModelLoader::Load(const char * filepath)
{
    tinyobj::attrib_t attrib;
    Array<tinyobj::shape_t> shapes;
    Array<tinyobj::material_t> materials;
    std::string err;

    bool errCode = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filepath);

    GE_ASSERT(errCode, err.c_str());

    GeneModel *model = new GeneModel();
    
    Array<Vector3> vertices, normals;
    Array<Vector2> texCoords;
    Array<GLuint> indices;
    
    for (const tinyobj::shape_t& shape : shapes)
    {
        for (const tinyobj::index_t& index : shape.mesh.indices)
        {
            vertices.push_back({ 
                attrib.vertices[3 * index.vertex_index + 0], 
                attrib.vertices[3 * index.vertex_index + 1], 
                attrib.vertices[3 * index.vertex_index + 2] });

            texCoords.push_back({
                attrib.texcoords[2 * index.texcoord_index + 0],
                1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            });

            indices.push_back(indices.size());
        }
    }

    model->Indices = indices;
    model->Vertices = vertices;
    model->UVs = texCoords;

    return model;
}
