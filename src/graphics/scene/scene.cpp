#include "graphics/scene/scene.hpp"

vortexGraphics::Scene::Scene()
{
    sceneCamera = new Camera{ 90.0f };
}

vortexGraphics::Scene::~Scene()
{
    delete sceneCamera;
}


void vortexGraphics::Scene::render(vortexGraphics::Shader* shader)
{
    sceneCamera->updateToRederEngine(shader);
    
    for (vortexGraphics::Mesh * mesh : meshes)
    {
        mesh->draw(shader);
    }
}
