#ifndef SCENE_GRAPH_H_
#define SCENE_GRAPH_H_

#include "scene/bvh.h"
#include "scene/lightsource.h"
#include "scene/surface.h"

namespace staal {

class SceneGraph {
public:
    SceneGraph();
    ~SceneGraph();

    LightSource* getLight(); //Only single light for now
    void setEpsilon(float epsilon);
    bool hit(const Ray& r, const float t0, const float t1, HitRecord& rec);
    bool visible(HitRecord &recX, HitRecord &recY);

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


} // namespace staal
#endif // !SCENE_GRAPH_H_
