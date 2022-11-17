#pragma once

#include "../abstractInputCommand.hpp"

#include "graphics/core/renderManager.hpp"

namespace vortexInput
{
    class CameraInCommand : public AbstractInputCommand
    {
    private:
        
        vortexGraphics::RenderManager * renderManager = &vortexGraphics::RenderManager::instance();
        
    public:
        CameraInCommand();
        
        ~CameraInCommand();
        
        void release() override;
        
        void press() override;
        
        void repeate() override;
        
    };
};
