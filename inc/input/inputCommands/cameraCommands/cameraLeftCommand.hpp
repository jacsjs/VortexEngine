#pragma once

#include "../abstractInputCommand.hpp"

#include "graphics/core/renderManager.hpp"

namespace vortexInput
{
    class CameraLeftCommand : public AbstractInputCommand
    {
    private:
        
        vortexGraphics::RenderManager * renderManager = &vortexGraphics::RenderManager::instance();
        
    public:
        CameraLeftCommand();
        
        ~CameraLeftCommand();
        
        void release() override;
        
        void press() override;
        
        void repeate() override;
        
    };
};
