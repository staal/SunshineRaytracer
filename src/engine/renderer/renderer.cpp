#include <math.h>
#include <iostream>

#include "engine/renderer.h"

namespace sunshine {
namespace engine{


// *****************************************************************************
void Renderer::renderStart()
{
    doRenderStart();
}


// *****************************************************************************
void Renderer::renderStop()
{
    doRenderStop();
}


// *****************************************************************************
bool Renderer::isRendering() const
{
    return rendering();
}


// *****************************************************************************
float Renderer::renderProgress() const
{
    return progress();
}

} // namespace engine
} // namespace sunshine