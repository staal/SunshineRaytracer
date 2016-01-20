#ifndef SUNSHINE_ENGINE_OBJ_FILE_H_
#define SUNSHINE_ENGINE_OBJ_FILE_H_

#include <map>
#include <string>
#include <vector>
#include "../scene/surface.h"
#include "../scene/triangle.h"

namespace sunshine {
namespace engine{

//! A Wavefront OBJ file class. 
/*!
  A more elaborate class description.
*/
class ObjFile {
public:
    ObjFile();
    ~ObjFile();
    void load(std::string objFileName);
    Surfaces getSurfaces() { return std::move(mSurfaces); }
    Materials getMaterials() { return std::move(mMaterials); }

private:
    void processMTLLib(std::string filename);

    std::unique_ptr<Triangle> processFace(std::string line,
        const std::vector<glm::vec3> vertices,
        const std::vector<glm::vec3> normals);

    Surfaces mSurfaces;
    Materials mMaterials;
    std::map<std::string, Material*> mMatDict;
    Material* currentMaterial;
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_OBJ_FILE_H_