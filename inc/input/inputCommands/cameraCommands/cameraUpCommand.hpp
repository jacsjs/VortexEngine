#pragma once

#include "../abstractInputCommand.hpp"

#include "graphics/core/renderManager.hpp"

namespace vortexInput
{
    class CameraUpCommand : public AbstractInputCommand
    {
    private:
        
        vortexGraphics::RenderManager * renderManager = &vortexGraphics::RenderManager::instance();
        
    public:
        CameraUpCommand();
        
        ~CameraUpCommand();
        
        void release() override;
        
        void press() override;
        
        void repeate() override;
        
    };
};
