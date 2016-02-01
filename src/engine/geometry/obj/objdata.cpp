
#include "mtlfile.h"
#include "objdata.h"

namespace sunshine {
namespace engine {

// *****************************************************************************
ObjData::ObjData() : currentMaterial(nullptr)
{}


// *****************************************************************************
void ObjData::loadMtlLib(const std::string& filename)
{
    MtlFile mtlFile(filename);

    std::map<std::string, Material> mats = mtlFile.load();

    for (auto& kv : mats) {
        materials[kv.first] = std::make_unique<Material>(kv.second);
    }
}


// *****************************************************************************
void ObjData::addVertice(const glm::vec3& v)
{
    vertices.push_back(v);
}


// *****************************************************************************
void ObjData::addNormal(const glm::vec3& n)
{
    normals.push_back(n);
}


// *****************************************************************************
void ObjData::useMtl(const std::string& mtlName)
{
    currentMaterial = nullptr;
    for (auto& kv : materials) {
        if (kv.first == mtlName) {
            currentMaterial = kv.second.get();
        }
    }
    if (!currentMaterial) {
        throw std::runtime_error("Could not find mtl: " + mtlName);
    }
}


// *****************************************************************************
void ObjData::addFace(std::vector<ObjFaceIndices> faceIndices)
{
    //Indices are 1 start based, not 0. If indice is -1 the indice points to the
    //last added vertex/texturecoord/normal.

    std::vector<Vertex> vs;
    for (auto &face : faceIndices) {
        Vertex v;

        //Vertex index
        int vIndex = face.v;
        if (vIndex == -1) {
            v.v = vertices.back();
        } else if (vIndex != 0) {
            v.v = vertices.at(vIndex - 1);
        }

        //Texture index
        int vtIndex = face.vt;
        if (vtIndex == -1) {
            //TODO: Implement vt
        } else if (vtIndex != 0) {
            //TODO: Implement vt
        }

        //Normal index
        int vnIndex = face.vn;
        if (vnIndex == -1) {
            v.normal = normals.back();
        } else if (vnIndex != 0) {
            v.normal = normals.at(vnIndex - 1);
        }

        vs.push_back(v);
    }


    if (vs.size() != 3) {
        throw std::runtime_error("No support for non triangle geometry");
    }


    faces.push_back(std::make_unique<Triangle>(vs.at(0), vs.at(1), vs.at(2), 
        currentMaterial));
}


// *****************************************************************************
Surfaces ObjData::getSurfaces()
{
    return std::move(faces);
}


// *****************************************************************************
Materials ObjData::getMaterials()
{
    return std::move(materials);
}


} // namespace engine
} // namespace sunshine