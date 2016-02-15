
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>

#include "objfile.h"
#include "obj/objgrammar.hpp"

namespace sunshine {
namespace engine {

using namespace glm;


// *****************************************************************************
ObjFile::ObjFile(std::string filename) : mFilename(std::move(filename))
{}


// *****************************************************************************
void ObjFile::load()
{
    using namespace boost::filesystem;
    path objPath(mFilename);

    if (is_directory(objPath) || !exists(objPath)) {
        throw std::runtime_error(mFilename + " is not an obj file");
    }

    //Parent of canonical path is the place to load from if mtl libs are located
    //relative.
    auto objDir = canonical(objPath).parent_path().string();

    mObjData.clear(); //reset objdata
    mObjData.setParentDir(objDir);

    std::ifstream input(mFilename, std::ios_base::in);

    if (!input) {
        throw std::runtime_error("Could not open obj file: " + mFilename);
    }

    std::string objText;
    input.unsetf(std::ios::skipws); // Preserve all whitespaces
    std::copy(
        std::istream_iterator<char>(input),
        std::istream_iterator<char>(), //No args is an EOF iterator.
        std::back_inserter(objText));

    using Iterator = std::string::const_iterator;
    OBJGrammar<Iterator> grammar(mObjData);


    Iterator iter = objText.begin();
    Iterator end = objText.end();
    bool ok = phrase_parse(iter, end, grammar, grammar.skipper);

    if (!ok || iter != end) {
        std::string rest(iter, end);
        throw std::runtime_error(
            "Parsing MTL file failed, failed at: " + rest.substr(0, 50));
    }
}


// *****************************************************************************
Surfaces ObjFile::getSurfaces()
{
    auto surfaces = mObjData.getSurfaces();
    return std::move(surfaces);
}


// *****************************************************************************
Materials ObjFile::getMaterials()
{
    auto materials = mObjData.getMaterials();
    return std::move(materials);
}

} // namespace engine
} // namespace sunshine