#ifndef SUNSHINE_ENGINE_OBJ_FILE_H_
#define SUNSHINE_ENGINE_OBJ_FILE_H_

#include <map>
#include <string>
#include <vector>
#include "obj/objdata.h"

namespace sunshine {
namespace engine {

/*!
    \brief A Wavefront OBJ file class.
*/
class ObjFile {
public:
    ObjFile(std::string filename);
    ~ObjFile();
    void load();
    Surfaces getSurfaces();
    Materials getMaterials();

private:
    ObjData mObjData;
    const std::string mFilename;
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_OBJ_FILE_H_