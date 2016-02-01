#ifndef SUNSHINE_ENGINE_MTL_FILE_H_
#define SUNSHINE_ENGINE_MTL_FILE_H_

#include <map>
#include <string>

#include "../material.h"

namespace sunshine {
namespace engine {

/*!
A Wavefront MTL file class.
*/
class MtlFile {
public:
    MtlFile(std::string filename);

    std::map<std::string, Material> load();

private:
    std::string filename;
};

} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_MTL_FILE_H_
