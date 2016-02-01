#ifndef SUNSHINE_ENGINE_OBJ_FILE_H_
#define SUNSHINE_ENGINE_OBJ_FILE_H_

#include <map>
#include <string>
#include <vector>
#include "objdata.h"
#include "../surface.h"
#include "../triangle.h"

namespace sunshine {
namespace engine {

/*!
    A Wavefront OBJ file class.
*/
class ObjFile {
public:
    ObjFile();
    ~ObjFile();
    void load(std::string objFileName);
    Surfaces getSurfaces();
    Materials getMaterials();

private:
    ObjData mObjData;
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_OBJ_FILE_H_