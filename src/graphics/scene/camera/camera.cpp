#include "graphics/scene/camera/camera.hpp"
vortexGraphics::Camera::Camera(const float fieldOfView)
{
    m_orientation = new vortexMath::Quaternion{};
    m_posMat = new vortexMath::Mat4{ 1.0f };
    m_dirMat = new vortexMath::Mat4{ 1.0f };
    m_projectionMat = vortexMath::Mat4::projection(90.0f, 0.1f, 100.0f);
    
    m_posState = new float[8]{0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    
    m_cameraVelocity = reinterpret_cast<float*>( vortexMemory::MemoryManager::instance().requestPoolMem(vortexMemory::TYPE_VEC4) );
    
    m_cameraSpeed = 0.1f;
}

vortexGraphics::Camera::Camera(const vortexMath::Mat4& viewMat, const float fieldOfView)
{
    //m_viewMat = viewMat;
    
    //m_projectionMat = vortexMath::Mat4::projection(fieldOfView, 0.1f, 100.0f);
}

vortexGraphics::Camera::~Camera()
{
    vortexMemory::MemoryManager::instance().freePoolMem(vortexMemory::TYPE_VEC4, m_cameraVelocity); 
    delete m_orientation;
    delete m_posState;
    delete m_posMat;
    delete m_projectionMat;
}

void vortexGraphics::Camera::setCameraSpeed(float speed)
{
}

void vortexGraphics::Camera::updateDirection(CAMERA_DIRECTION direction)
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7, xmm8, xmm9;

    m_posState[direction] = !m_posState[direction];
    
    xmm0 = _mm_set1_ps(-0.0f);
    
    xmm1 = _mm_load_ps((float* ) m_posState + 0); //Positive axis
    xmm2 = _mm_load_ps((float* ) m_posState + 4); //Negative axis

    xmm3 = _mm_xor_ps(xmm2, xmm0);
    
    xmm4 = _mm_xor_ps(xmm2, xmm1); //Abs

    xmm0 = _mm_set1_ps(xmm4[0]);
    xmm2 = _mm_set1_ps(xmm4[1]);
    xmm5 = _mm_set1_ps(xmm4[2]);
    
    xmm3 = _mm_add_ps(xmm1, xmm3); //Final offset position (needs normalizing and then translation).
    xmm0 = _mm_add_ps(xmm0, xmm2);
    xmm0 = _mm_add_ps(xmm5, xmm0); //squaredMag
    
    xmm0 = _mm_sqrt_ps(xmm0); //mag
    
    if (xmm0[0] != 0.0f)
    {
        xmm0 = _mm_div_ps(xmm3, xmm0); //normalized
    }

    _mm_store_ps((float* ) m_cameraVelocity, xmm0);
}

void vortexGraphics::Camera::updateOrientation(const vortexMath::Vec3<float>& direction)
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6;

    vortexMath::Quaternion temp{direction, 5.0f * m_PIOVER180};
    
    *m_orientation *= temp;

    m_orientation->normalize();
    
    m_dirMat->orientate(*m_orientation);
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4 ; j++)
        {
            std::cout << m_dirMat->data()[i*4 + j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
void vortexGraphics::Camera::updateToRederEngine(Shader * shader)
{
    _mm_store_ps((float* ) m_posMat->data() + 12, _mm_fmadd_ps(_mm_set1_ps(m_cameraSpeed), _mm_load_ps((float* ) m_cameraVelocity), _mm_load_ps((float* ) m_posMat->data() + 12)));
    m_posMat->data()[15] = 1.0f;

    //TODO: Allocate this viewMat with a frame allocator
    vortexMath::Mat4 viewMat = *m_dirMat * *m_posMat;

    shader->setMat4("viewMat", viewMat);
    shader->setMat4("projectionMat", *m_projectionMat);
}
