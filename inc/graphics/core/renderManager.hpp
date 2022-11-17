#pragma once

#include "shader.hpp"
#include "../scene/scene.hpp"

namespace vortexGraphics
{
    class RenderManager
    {
    private:
        
        Shader * shader;
        
        Scene * currentScene;
    public:
        
        RenderManager();
    
        ~RenderManager();
        
        /**
         * @return RenderManager Singleton instance of this class.
         */
        static RenderManager & instance();
        
        void setCurrentScene(Scene * newScene);
        
        void render();
        
        inline Scene * getCurrentScene() { return currentScene; }
        
        inline Shader * getShader() { return shader; }
        
        
        //Delete these methods to avoid object copying, making it safer
        RenderManager(RenderManager const&)  = delete;
        void operator=(RenderManager const&) = delete;
    };
    
};
