#ifndef SUNSHINE_ENGINE_MTL_FILE_H_
#define SUNSHINE_ENGINE_MTL_FILE_H_

#include <map>
#include <string>
#include "../material.h"

namespace sunshine {
namespace engine {

/*!
    \brief A Wavefront MTL file class.
*/
class MtlFile {
public:
    /*!
        Constructor. Accepts \param filename as the file to be parsed. Should be
        passed as a complete path. Throws a runtime_error if filename is a
        directory or does not exist.
    */
    MtlFile(std::string filename);

    /*!
        load does the actual parsing of the file. Throws a runtime_error if
        filename cannot be opened.
    */
    std::map<std::string, Material> load();

private:
    /*! The filename of the file to be parsed. */
    const std::string filename;
};

} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_MTL_FILE_H_
