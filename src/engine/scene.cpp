
#include <fstream>
#include "scene.h"

namespace sunshine {


// *****************************************************************************
Scene::Scene()
    : seed(0), recursionDepth(0), samplesPerPixel(0), width(800), height(800), absorbtion(1.0f),
    epsilon(0.0005f), outFile(""), objFile(""), cameraViewDirection(glm::vec3(0.0)),
    cameraPosition(glm::vec3(0.0)), cameraUp(glm::vec3(0.0)), cameraFov(0.0f)
{}


// *****************************************************************************
Scene::~Scene()
{}


// *****************************************************************************
void Scene::loadScene(std::string sceneFile)
{
    //Simple file parser
    std::ifstream cfstream(sceneFile);
    std::string option;
    while (cfstream >> option) {
        if (option.at(0) == '#') {
            char buf[200];
            cfstream.getline(buf, 200);
            continue;
        }

        //Render configuration
        else if (option == "seed") { cfstream >> this->seed; }
        else if (option == "recursion_depth") { cfstream >> this->recursionDepth; }
        else if (option == "samples_per_pixel") { cfstream >> this->samplesPerPixel; }
        else if (option == "absorbtion") { cfstream >> this->absorbtion; }
        else if (option == "epsilon") { cfstream >> this->epsilon; }

        //Image configuration
        else if (option == "image_heigth") { cfstream >> this->height; }
        else if (option == "image_width") { cfstream >> this->width; }

        //Output input
        else if (option == "object_file") {
            cfstream >> this->objFile;
        }
        else if (option == "output_file") {
            cfstream >> this->outFile;
        }

        //Camera configuration
        else if (option == "camera_view_direction") {
            cfstream >> this->cameraViewDirection.x;
            cfstream >> this->cameraViewDirection.y;
            cfstream >> this->cameraViewDirection.z;
        }
        else if (option == "camera_up") {
            cfstream >> this->cameraUp.x;
            cfstream >> this->cameraUp.y;
            cfstream >> this->cameraUp.z;
        }
        else if (option == "camera_position") {
            cfstream >> this->cameraPosition.x;
            cfstream >> this->cameraPosition.y;
            cfstream >> this->cameraPosition.z;
        }
        else if (option == "camera_fov") { cfstream >> this->cameraFov; }
        else throw "File parse exception";
    }
}
} // namespace sunshine