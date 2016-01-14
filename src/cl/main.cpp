#include <iostream>
#include <chrono>

#include "engine/io/tgafile.h"
#include "renderapplication.h"


int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "Please supply a .scene file" << std::endl;
        return 0;
    }

    //Load Scene
    std::string configFileName = argv[1];


    sunshine::RenderApplication app;
    std::cout << "Loading scene: " << configFileName << std::endl;
    app.loadScene(configFileName);

    //Ray tracing part
    std::cout << "Rendering" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    app.renderScene();

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    auto elapsedTimeMS = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Render complete, time spent: " << elapsedTime.count() << "s" << std::endl;
    std::cout << "Render complete, time spent: " << elapsedTimeMS.count() << "micro seconds" << std::endl;
    
    //Store image
    app.saveImage();
    
    return 0;
}