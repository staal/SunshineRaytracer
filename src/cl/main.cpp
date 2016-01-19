#include <iostream>

#include "renderapplication.h"

// *****************************************************************************
int main(int argc, char *argv[])
{
    std::cout << "Sunshine Ray Tracer(SRT)" << std::endl;
    std::cout << "------------------------" << std::endl;
    
    try {
        //Create the application
        sunshine::RenderApplication app(argc, argv);

        //Pass control to the application
        return app.run();
    }
    catch (std::exception& e) {
        std::cout << "Error, " << e.what() << "." << std::endl;
        return -1;
    }
}