#pragma once

#include "../abstractInputCommand.hpp"

#include "graphics/core/renderManager.hpp"

namespace vortexInput
{
    class CameraDownCommand : public AbstractInputCommand
    {
    private:
        
        vortexGraphics::RenderManager * renderManager = &vortexGraphics::RenderManager::instance();
        
    public:
        CameraDownCommand();
        
        ~CameraDownCommand();
        
        void release() override;
        
        void press() override;
        
        void repeate() override;
        
    };
};
