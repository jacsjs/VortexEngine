#define STB_IMAGE_IMPLEMENTATION

#include "window/windowManager.hpp"
#include "graphics/core/renderManager.hpp"
#include "input/inputManager.hpp"

#include "input/inputMapping/defaultInputMapping.hpp"

#include "graphics/model/mesh.hpp"

#include <iostream>

#include "memory/memoryManager.hpp"

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

int main(int argc, char **argv) {

    vortexMemory::MemoryManager * memoryManager = &vortexMemory::MemoryManager::instance();
    
    vortexWindow::WindowManager * windowManager = &vortexWindow::WindowManager::instance();
    
    windowManager->setupFrame(800, 600, "VortexEngine");
    
    vortexGraphics::RenderManager * renderManager = &vortexGraphics::RenderManager::instance();
    
    vortexInput::InputManager * inputManager = &vortexInput::InputManager::instance();
    
    inputManager->setCurrentInputMapping(new vortexInput::DefaultInputMapping(new vortexInput::InputCommandFactory()));

    vortexMath::Mat4 mat4{ 1.0f };
    vortexMath::Mat4 cube2{ 1.0f };
    mat4.data()[12] = 0.0f;
    mat4.data()[13] = 0.0f;
    mat4.data()[14] = -10.0f;
    
    vortexMath::Vec3x8 vec = vortexMath::Vec3x8::generateVecFromArray(vertices, 0, sizeof(vertices) / sizeof(float), 36);
    vortexMath::Vec2x8 tex = vortexMath::Vec2x8::generateVecFromArray(vertices, 3, sizeof(vertices) / sizeof(float), 36);
    
    vortexGraphics::Mesh * mesh = new vortexGraphics::Mesh(vec, vortexMath::Vec3x8{}, tex, vortexMath::AlignedVector<unsigned int, 32>(indices, 6), mat4);
    mesh->setupMesh();
    vortexGraphics::Mesh * otherCube = new vortexGraphics::Mesh(vec, vortexMath::Vec3x8{}, tex, vortexMath::AlignedVector<unsigned int, 32>(indices, 6), cube2);
    
    mesh->setupMesh();
    otherCube->setupMesh();
    
    vortexGraphics::Scene * scene = new vortexGraphics::Scene();
    
    
    scene->addMeshToScene(mesh);
    scene->addMeshToScene(otherCube);
    
    renderManager->setCurrentScene(scene);
    
    while (windowManager->getFrame()->isOpen())
    {
        glClearColor(0.0f, 0.3f, 0.4f, 1.0f); //The color is only updated when clearing the color buffer
        glClear(GL_COLOR_BUFFER_BIT);
        
        renderManager->render();
        
        glfwSwapBuffers(windowManager->getFrame()->getGLFWwindowInstance()); //Swap buffers (its in double buffering mode)
        glfwPollEvents();
    }
    
    delete scene;
    windowManager->getFrame()->close();
    return 0;
}
