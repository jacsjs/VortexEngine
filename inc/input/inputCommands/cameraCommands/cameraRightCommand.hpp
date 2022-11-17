#pragma once

#include "../abstractInputCommand.hpp"

#include "graphics/core/renderManager.hpp"

namespace vortexInput
{
    class CameraRightCommand : public AbstractInputCommand
    {
    private:
    
        vortexGraphics::RenderManager * renderManager = &vortexGraphics::RenderManager::instance();
    
    public:
        CameraRightCommand();
        
        ~CameraRightCommand();
        
        void release() override;
        
        void press() override;
        
        void repeate() override;
        
    };
};
