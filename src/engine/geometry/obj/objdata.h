#ifndef SUNSHINE_ENGINE_OBJ_DATA_H_
#define SUNSHINE_ENGINE_OBJ_DATA_H_

#include <boost/fusion/include/adapt_struct.hpp>

#include <map>
#include <string>
#include <vector>

#include "../surface.h"
#include "../triangle.h"

namespace sunshine {
namespace engine {

/*!
    A single set of indices for a face
*/
struct ObjFaceIndices {
    int v, vt, vn;
    ObjFaceIndices() : v(0), vn(0), vt(0) {};
};

/*!
    The data of a parsed Obj File.
*/
class ObjData {    
public:
    ObjData();

    void clear();
    void setParentDir(std::string parentDir)
    {
        mParentDir = parentDir;
    };

    /*Functions to work with the grammar*/
    void addVertice(const glm::vec3& v);
    void addNormal(const glm::vec3& n);

    void loadMtlLib(const std::string& filename);
    void useMtl(const std::string& mtlName);

    void addFace(std::vector<ObjFaceIndices> faceIndices);

    Surfaces getSurfaces();
    Materials getMaterials();

private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    Materials materials;
    Surfaces faces;
    Material *currentMaterial;
    std::string mParentDir;
};


} // namespace engine
} // namespace sunshine


BOOST_FUSION_ADAPT_STRUCT(
    sunshine::engine::ObjFaceIndices,
    (int, v)
    (int, vt)
    (int, vn)
    );

#endif // !SUNSHINE_ENGINE_OBJ_DATA_H_