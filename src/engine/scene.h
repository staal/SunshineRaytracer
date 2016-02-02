#ifndef SUNSHINE_ENGINE_SCENE_H_
#define SUNSHINE_ENGINE_SCENE_H_

#include <string>
#include <glm/glm.hpp>

namespace sunshine {
namespace engine{

class Scene
{
public:
	unsigned int seed;
	int recursionDepth;
	int samplesPerPixel;

	int width;
	int height;

	float epsilon;
	float absorbtion;

	std::string objFile;
	std::string outFile;

	glm::vec3 cameraViewDirection;
	glm::vec3 cameraPosition;
	glm::vec3 cameraUp;
	float cameraFov;


    Scene();
	~Scene();

    void loadScene(std::string sceneFile);
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_SCENE_H_
