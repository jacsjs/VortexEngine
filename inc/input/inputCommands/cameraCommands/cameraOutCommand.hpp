#pragma once

#include "../abstractInputCommand.hpp"

#include "graphics/core/renderManager.hpp"

namespace vortexInput
{
    class CameraOutCommand : public AbstractInputCommand
    {
    private:
        
        vortexGraphics::RenderManager * renderManager = &vortexGraphics::RenderManager::instance();
        
    public:
        CameraOutCommand();
        
        ~CameraOutCommand();
        
        void release() override;
        
        void press() override;
        
        void repeate() override;
        
    };
};
