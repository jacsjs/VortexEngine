#pragma once

#include "../model/mesh.hpp"
#include "camera/camera.hpp"

namespace vortexGraphics
{
    class Scene
    {
    private:
        
        Camera * sceneCamera;
        
        std::vector<Mesh* > meshes; //temporary (will be replaced by a model class later, in which will handle the meshes instead)
        
        
    public:
        
        Scene();
        
        ~Scene();
        
        void update(float time); //Usage: our physics engine.
        
        void render(Shader * shader);
        
        inline void addMeshToScene(Mesh * mesh) 
        { 
            meshes.push_back(mesh); 
            
            for (int i = 0; i < meshes.size(); i++)
            {
                
            }
        }
        
        /**
         * @return Camera The active camera for this scene.
         */
        inline Camera * activeCamera() { return sceneCamera; }
    };
    
};
