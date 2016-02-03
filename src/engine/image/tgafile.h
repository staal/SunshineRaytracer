#ifndef SUNSHINE_ENGINE_TGA_FILE_H_
#define SUNSHINE_ENGINE_TGA_FILE_H_

#include <memory>
#include <string>
#include "../image.h"

namespace sunshine {
namespace engine{

/*!
    \brief A TGA File handler.
*/
class TgaFile {
public:
    TgaFile();

    bool save(std::string filename, const Image& image);
    bool load(std::string filename);
    std::unique_ptr<Image> getImage();
    
private:
    std::unique_ptr<Image> mImage;
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_TGA_FILE_H_
