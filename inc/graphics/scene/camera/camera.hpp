#pragma once

#include "../../../math/vecSOA.hpp"
#include "../../core/shader.hpp"

#include "memory/memoryManager.hpp"
namespace vortexGraphics
{
    enum CAMERA_DIRECTION
    {
        CAMERA_LEFT = 0,  
        CAMERA_DOWN,
        CAMERA_IN,
        CAMERA_RIGHT = 4,
        CAMERA_UP,
        CAMERA_OUT
    };
        
    class Camera
    {
    private:
        
        vortexMath::Quaternion * m_orientation;
        vortexMath::Mat4 * m_posMat;
        
        vortexMath::Mat4 * m_dirMat;
        
        vortexMath::Mat4 * m_projectionMat;
        
        float * m_posState;
        
        float * m_cameraVelocity;
        
        float m_cameraSpeed;
        
        const float m_PIOVER180 =  3.141593 / 180;

    public:
        
        Camera(const float fieldOfView = 90.0f);
        
        Camera(const vortexMath::Mat4& viewMat, const float fieldOfView = 90.0f);
        
        virtual ~Camera();
        
        /**
         * Set / update the camera speed with the given speed.
         */
        void setCameraSpeed(float speed);
        
        /**
         * Update the camera position given a CAMERA_DIRECTION.
         */
        void updateDirection(CAMERA_DIRECTION direction);
        
        /**
         * Update the camera orientation.
         */
        void updateOrientation(const vortexMath::Vec3<float>& direction);
        
        /**
         * Updates the given shader with new camera information.
         */
        void updateToRederEngine(Shader* shader);
    };
}
