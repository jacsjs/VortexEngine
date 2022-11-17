#pragma once

#include "window/frame.hpp"

namespace vortexWindow
{
    class WindowManager
    {
    private:
        
        Frame * frame;
        
    public:
        WindowManager();
        
        ~WindowManager();
        
        void setupFrame(int width, int height, const char* title);
        
        /**
         * @return VideoManager Singleton instance of this class.
         */
        static WindowManager & instance();
        
        /**
         * Get the current frame instance.
         */
        inline Frame * getFrame() { return frame; }
    };
    
};
