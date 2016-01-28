
#include <stdexcept>
#include <fstream>
#include <sstream>

#include "objfile.h"
#include "mtlgrammar.hpp"

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
std::unique_ptr<Triangle> ObjFile::processFace(std::string line,
    const std::vector<glm::vec3> vertices, const std::vector<glm::vec3> normals)
{
    //Assuming triangles with only normals for now
    std::stringstream ss(line);
    int vi_1, vi_2, vi_3, ni_1, ni_2, ni_3;
    char c;
    ss >> c >> vi_1 >> c >> c >> ni_1;
    ss >> vi_2 >> c >> c >> ni_2;
    ss >> vi_3 >> c >> c >> ni_3;
    //0 index, not 1 index

    Vertex v1, v2, v3;
    v1.normal = normals.at(ni_1 - 1);
    v2.normal = normals.at(ni_2 - 1);
    v3.normal = normals.at(ni_3 - 1);

    v1.v = vertices.at(vi_1 - 1);
    v2.v = vertices.at(vi_2 - 1);
    v3.v = vertices.at(vi_3 - 1);

    return std::make_unique<Triangle>(v1, v2, v3, currentMaterial);
}


// *****************************************************************************
void ObjFile::processMTLLib(std::string filename)
{
    std::ifstream input(filename, std::ios_base::in);

    if (!input) {
        throw std::runtime_error("Could not open mtl file: " + filename);
    }

    std::string mtlText;
    input.unsetf(std::ios::skipws); // Preserve all whitespaces
    std::copy(
        std::istream_iterator<char>(input),
        std::istream_iterator<char>(), //No args is an EOF iterator.
        std::back_inserter(mtlText));

    using Iterator = std::string::const_iterator;
    MTLGrammar<Iterator> grammar;


    std::map<std::string, Material> parsed;
    Iterator iter = mtlText.begin();
    Iterator end = mtlText.end();
    bool ok = phrase_parse(iter, end, grammar, grammar.skipper, parsed);

    if (ok && iter == end) {
        //TODO Dont create a new map from scratch
        for (auto& kv : parsed) {
            auto mat = std::make_unique<Material>(kv.second);
            mMatDict[kv.first] = mat.get();
            mMaterials.push_back(std::move(mat));
        }
    } else {
        std::string rest(iter, end);
        throw std::runtime_error(
            "Parsing MTL file failed, failed at: " + rest.substr(0, 50));

    }
}

// *****************************************************************************
void ObjFile::load(std::string objFileName)
{
    mSurfaces.clear();
    mMaterials.clear();
    mMatDict.clear();

    std::vector<vec3> vertices;
    std::vector<vec3> normals;

    std::ifstream input(objFileName);
    std::string line;

    while (input.good() && getline(input, line)) {

        if (line.find("#") == 0) //First char
        {
            continue; //Comment
        }

        else if (line.size() > 0 && line.at(0) == 'o') {

        } else if (line.find("vn") == 0) {
            //Vertex normal
            std::stringstream ss(line);
            vec3 n;
            char c;
            ss >> c >> c >> n.x >> n.y >> n.z;
            normals.push_back(n);
        } else if (line.find("vt") == 0) {
            //vertex texture
        } else if (line.find("v") == 0) {
            //Vertex    
            std::stringstream ss(line);
            vec3 v;
            char c;
            ss >> c >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        } else if (line.find("f") == 0) {
            //Face
            mSurfaces.emplace_back(
                std::move(processFace(line, vertices, normals))
                );
        } else if (line.find("mtllib") == 0) {
            std::string mtlName = line.substr(7); //After "mtllib " (7)

            processMTLLib(mtlName);
        } else if (line.find("usemtl") == 0) {
            std::string mtlName = line.substr(7); //After "usemtl " (7)

            std::map<std::string, Material*>::iterator it;
            it = mMatDict.find(mtlName);
            if (it == mMatDict.end()) {
                throw "Error - Material not found";
            } else {
                currentMaterial = it->second;
            }
        }
    }
}

} // namespace engine
} // namespace sunshine