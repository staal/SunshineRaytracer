
#include <boost/filesystem.hpp>
#include <fstream>

#include "mtlfile.h"
#include "mtlgrammar.hpp"

namespace sunshine {
namespace engine {

// *****************************************************************************
MtlFile::MtlFile(std::string filename) : filename(filename)
{
    using namespace boost::filesystem;

    path mtlPath(filename);
    if (is_directory(mtlPath) || !exists(mtlPath)) {
        throw std::runtime_error(filename + " is not an mtl file");
    }
}


// *****************************************************************************
std::map<std::string, Material> MtlFile::load()
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


    std::map<std::string, Material> mats;
    Iterator iter = mtlText.begin();
    Iterator end = mtlText.end();
    bool ok = phrase_parse(iter, end, grammar, grammar.skipper, mats);

    if (!ok || iter != end) {
        std::string rest(iter, end);
        throw std::runtime_error(
            "Parsing MTL file failed, failed at: " + rest.substr(0, 50));

    }
    return mats;
}


} // namespace engine
} // namespace sunshine