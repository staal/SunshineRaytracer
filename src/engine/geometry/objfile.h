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
    /*!
        Constructor.

        \param filename the path of the OBJ file to parse.
    */
    ObjFile(std::string filename);

    /*!
        Do the actual loading of the OBJ file.
    */
    void load();

    /*!
        Get the surfaces loaded from the OBJ file. Transfers ownership to 
        caller.
    */
    Surfaces getSurfaces();

    /*!
        Get the materials loaded from the OBJ file (and mtl files). 
        Transfers ownership to caller.
    */
    Materials getMaterials();

private:
    /*! The actual data of the OBJ file. */
    ObjData mObjData;

    /*! The filename of the OBJ file to parse. */
    const std::string mFilename;
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_OBJ_FILE_H_