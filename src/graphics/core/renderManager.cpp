#include "graphics/core/renderManager.hpp"

vortexGraphics::RenderManager::RenderManager()
{
    shader = new vortexGraphics::Shader{std::string{"/home/jacob/projects/VortexEngine/inc/graphics/shaders/shader.vert"}, 
                                        std::string{"/home/jacob/projects/VortexEngine/inc/graphics/shaders/shader.frag"}};
                                        
    shader->use();
}


void vortexGraphics::RenderManager::setCurrentScene(vortexGraphics::Scene* newScene)
{
    this->currentScene = newScene;
}


vortexGraphics::RenderManager& vortexGraphics::RenderManager::instance()
{
    static vortexGraphics::RenderManager singletonInstance;
    return singletonInstance;
}

vortexGraphics::RenderManager::~RenderManager()
{
    delete shader;
}

void vortexGraphics::RenderManager::render()
{
    currentScene->render(shader);
}

