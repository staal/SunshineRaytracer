#include <math.h>
#include <iostream>

#include "engine/renderer.h"

namespace sunshine {
namespace engine{


// *****************************************************************************
void Renderer::start()
{
    renderStart();
}


// *****************************************************************************
void Renderer::stop()
{
    renderStop();
}


// *****************************************************************************
bool Renderer::isRendering() const
{
    return rendering();
}


// *****************************************************************************
float Renderer::progress() const
{
    return renderProgress();
}

} // namespace engine
} // namespace sunshine