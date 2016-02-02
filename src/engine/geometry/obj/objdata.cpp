
#include <boost/filesystem.hpp>
#include "mtlfile.h"
#include "objdata.h"

namespace sunshine {
namespace engine {

// *****************************************************************************
ObjData::ObjData() : currentMaterial(nullptr), mWorkingDir("")
{}


// *****************************************************************************
void ObjData::clear()
{
    mWorkingDir = "";
    vertices.clear();
    normals.clear();
    materials.clear();
    surfaces.clear();
    currentMaterial = nullptr;
}


// *****************************************************************************
void ObjData::loadMtlLib(const std::string& filename)
{
    using namespace boost::filesystem;
    
    //Find the final absolute filename from mWorkingDir and mtlPath.
    path mtlPath(filename);

    std::string absoluteFilename = filename;
    if (mtlPath.is_relative() && mWorkingDir != "") {
        auto finalPath = path(mWorkingDir).append(filename);
        absoluteFilename = canonical(finalPath).string();
    }

    MtlFile mtlFile(absoluteFilename);

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


    surfaces.push_back(std::make_unique<Triangle>(vs.at(0), vs.at(1), vs.at(2),
        currentMaterial));
}


// *****************************************************************************
Surfaces ObjData::getSurfaces()
{
    return std::move(surfaces);
}


// *****************************************************************************
Materials ObjData::getMaterials()
{
    return std::move(materials);
}


} // namespace engine
} // namespace sunshine