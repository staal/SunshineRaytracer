#ifndef SUNSHINE_ENGINE_OBJ_DATA_H_
#define SUNSHINE_ENGINE_OBJ_DATA_H_

#include <map>
#include <string>
#include <vector>
#include <boost/fusion/include/adapt_struct.hpp>

#include "../surface.h"
#include "../triangle.h"

namespace sunshine {
namespace engine {

/*!
    \brief A single set of indices for a face.

    Default values are 0, an unused index in obj format.
    Indices are 1 indexed and -1 means the latest added vertex/normal/texture.
*/
struct ObjFaceIndices {
    int v, vt, vn;
    ObjFaceIndices() : v(0), vn(0), vt(0) {};
};

/*!
    \brief The data of a parsed Obj File.

    This is used by ObjGrammar to parse an obj file and transform into
    usable data. The functions on this is called from different rules in the
    grammar.
*/
class ObjData {
public:
    /*!
        Constructor.
    */
    ObjData();

    /*!
        Resets the object to initial state.
    */
    void clear();

    /*!
        \param workingDir Set the working dir for the obj file being parsed.
        This is used for any mtl libraries specified using relative paths.
    */
    void setParentDir(std::string workingDir)
    {
        mWorkingDir = workingDir;
    };

    /*!
        Adds a vertice to the obj data. Called from ObjGrammar parsing an obj
        file.

        \sa sunshine::engine::ObjGrammar
    */
    void addVertice(const glm::vec3& v);

    /*!
        Adds a normal to the obj data. Called from ObjGrammar parsing an obj
        file.

        \sa sunshine::engine::ObjGrammar
    */
    void addNormal(const glm::vec3& n);

    /*!
        Loads a mtl lib. Called from ObjGrammar parsing an obj file. The Mtl lib
        will be loaded immidately and the materials are thus avilable at later
        calls.

        \sa sunshine::engine::ObjGrammar
        \sa useMtl
    */
    void loadMtlLib(const std::string& filename);

    /*!
        Attempts to set current material to the mtlName param. If found, any
        face created will be associated with this material. If not found will
        throw a runtime_error.

        TODO:Check if runtime_error perhaps should be an assignment to a
        standard material.

        \param mtlName the material to use from this point.

        \sa sunshine::engine::ObjGrammar
        \sa loadMtlLib
    */
    void useMtl(const std::string& mtlName);

    /*!
        Will create a new surface from the faceIndices. Will throw a
        runtime_error if faceIndices.size() is not exactly 3. Only supporting
        triangles for now.

        TODO: Specialized exception, obj_parse_exception(std::string what).

        \param faceIndices the indices to use for creating the geometry.
    */
    void addFace(std::vector<ObjFaceIndices> faceIndices);

    /*!
        Moves the surfaces from this object to caller.
    */
    Surfaces getSurfaces();

    /*!
        Moves the materials from this object to caller.
    */
    Materials getMaterials();

private:
    /*! Vertices used to create faces/triangles. */
    std::vector<glm::vec3> vertices;

    /*! Normals used to create faces/triangles. */
    std::vector<glm::vec3> normals;

    /*! Map of materials parsed so far. */
    Materials materials;

    /*! Map of surfaces parsed so far. */
    Surfaces surfaces;

    /*! The current material, set through "usemtl material". Will be applied
        to all faces created from this point forward. Not the owner, don't
        delete this. */
    Material *currentMaterial;

    /*! The working dir of the obj file. This is used for relative path mtl
    files. */
    std::string mWorkingDir;
};


} // namespace engine
} // namespace sunshine


/*
    Call macro to allow ObjFaceIndices to be used in Boost.spirit parsers.
    Must be called in the global namespace.
*/
BOOST_FUSION_ADAPT_STRUCT(
    sunshine::engine::ObjFaceIndices,
    (int, v)
    (int, vt)
    (int, vn)
    );

#endif // !SUNSHINE_ENGINE_OBJ_DATA_H_