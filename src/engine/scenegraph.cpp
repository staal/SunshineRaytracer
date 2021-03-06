#include "scenegraph.h"

#include <iostream>
#include <iterator>

namespace sunshine {
namespace engine {

using namespace glm;


// *****************************************************************************
SceneGraph::SceneGraph()
    : mEpsilon(0.0f), numNodes(0), mRoot(nullptr), mLight(nullptr)
{}


// *****************************************************************************
void SceneGraph::setEpsilon(float epsilon)
{
    this->mEpsilon = epsilon;
}


// *****************************************************************************
const LightSource* SceneGraph::getLight() const
{
    return mLight.get();
}


// *****************************************************************************
bool SceneGraph::visible(const HitRecord &recA, const HitRecord &recB) const
{
    HitRecord rec;
    vec3 dir = recB.point - recA.point;
    vec3 normalizedDir = normalize(dir);
    Ray ray(recA.point, normalizedDir);

    if (mRoot) {
        return !mRoot->intersects(
            ray, this->mEpsilon, length(dir) - this->mEpsilon);
    }
    return true;
}


// *****************************************************************************
bool SceneGraph::hit(const Ray& r, const float t0, const float t1, HitRecord &rec)
const
{
    if (mRoot)
        return mRoot->hit(r, t0, t1, rec);
    return false;
}


// *****************************************************************************
void SceneGraph::addMesh(Surfaces surfaces, Materials mats)
{
    std::move(surfaces.begin(), surfaces.end(), std::back_inserter(mSurfaces));
    //std::move(mats.begin(), mats.end(), std::back_inserter(mMaterials));

    using it = std::map<std::string, std::unique_ptr<Material>>::iterator;
    using mv = std::move_iterator <it>;

    mMaterials.insert(mv(mats.begin()), mv(mats.end()));

    //mMaterials = std::move(mats);
    auto lightMat = std::make_unique<Material>();

    //Hardcoded light source
    lightMat->Ke = vec3(19.4,
        16.1,
        11.5);

    Vertex v1, v2, v3, v4;
    v1.normal = vec3(0.0f, -1.0f, 0.0f);
    v2.normal = vec3(0.0f, -1.0f, 0.0f);
    v3.normal = vec3(0.0f, -1.0f, 0.0f);
    v4.normal = vec3(0.0f, -1.0f, 0.0f);

    v1.v = vec3(213.0, 547.0, 227.0);
    v2.v = vec3(343.0, 547.0, 227.0);
    v3.v = vec3(343.0, 547.0, 332.0);
    v4.v = vec3(213.0, 547.0, 332.0);

    auto t1 = std::make_unique<Triangle>(v1, v2, v3, lightMat.get());
    auto t2 = std::make_unique<Triangle>(v3, v4, v1, lightMat.get());


    this->mLight = std::make_unique<LightSource>(t1.get(), t2.get());

    mSurfaces.emplace_back(std::move(t1));
    mSurfaces.emplace_back(std::move(t2));
    mMaterials["light"] = std::move(lightMat);
    this->mRoot = std::make_unique<Bvh>(mSurfaces.begin(), mSurfaces.end());
}

void SceneGraph::clear()
{
    mSurfaces.clear();
    mMaterials.clear();
    mRoot = nullptr;
}


} // namespace engine
} // namespace sunshine
