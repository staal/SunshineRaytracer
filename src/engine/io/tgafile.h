#ifndef TGA_FILE_H_
#define TGA_FILE_H_

#include <memory>
#include <string>
#include "../image.h"

namespace sunshine {

class TgaFile {
public:
    TgaFile();
    ~TgaFile();

    bool save(std::string filename, const Image& image);
    bool load(std::string filename);
    std::unique_ptr<Image> getImage();
    
private:
    std::unique_ptr<Image> mImage;
};


} // namespace sunshine
#endif // !TGA_FILE_H_