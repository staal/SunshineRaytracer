#ifndef SUNSHINE_ENGINE_SCENE_GRAPH_H_
#define SUNSHINE_ENGINE_SCENE_GRAPH_H_

#include "scene/bvh.h"
#include "scene/lightsource.h"
#include "geometry/surface.h"

namespace sunshine {
namespace engine{

class SceneGraph {
public:
    SceneGraph();

    void setEpsilon(float epsilon);
    const LightSource* getLight() const; //Only single light for now
    bool hit(const Ray& r, const float t0, const float t1, HitRecord& rec) const;
    bool visible(const HitRecord &recA, const HitRecord &recB) const;

    void addMesh(Surfaces surfaces, Materials mats);
    void clear();

private:
    std::unique_ptr<Bvh> mRoot;
    Materials mMaterials;
    Surfaces mSurfaces;
    std::unique_ptr<LightSource> mLight;
    float mEpsilon;
    int numNodes;

};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_SCENE_GRAPH_H_
