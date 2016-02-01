
#include <stdexcept>
#include <fstream>
#include <sstream>

#include "objfile.h"
#include "objgrammar.hpp"

namespace sunshine {
namespace engine {

using namespace glm;


// *****************************************************************************
ObjFile::ObjFile()
{}


// *****************************************************************************
ObjFile::~ObjFile()
{}


// *****************************************************************************
void ObjFile::load(std::string objFileName)
{
    mObjData = ObjData(); //reset objdata

    std::ifstream input(objFileName, std::ios_base::in);

    if (!input) {
        throw std::runtime_error("Could not open obj file: " + objFileName);
    }

    std::string objData;
    input.unsetf(std::ios::skipws); // Preserve all whitespaces
    std::copy(
        std::istream_iterator<char>(input),
        std::istream_iterator<char>(), //No args is an EOF iterator.
        std::back_inserter(objData));

    using Iterator = std::string::const_iterator;
    OBJGrammar<Iterator> grammar(mObjData);


    std::map<std::string, Material> parsed;
    Iterator iter = objData.begin();
    Iterator end = objData.end();
    bool ok = phrase_parse(iter, end, grammar, grammar.skipper, parsed);

    if (!ok || iter != end) {
        std::string rest(iter, end);
        throw std::runtime_error(
            "Parsing MTL file failed, failed at: " + rest.substr(0, 50));

    }
}


//******************************************************************************
Surfaces ObjFile::getSurfaces()
{
    auto surfaces = mObjData.getSurfaces();
    return std::move(surfaces);
}


//******************************************************************************
Materials ObjFile::getMaterials()
{
    auto materials = mObjData.getMaterials();
    return std::move(materials);
}

} // namespace engine
} // namespace sunshine