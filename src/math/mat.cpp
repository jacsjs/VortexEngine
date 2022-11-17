#include "math/mat.hpp"

vortexMath::Mat3::Mat3()
{
    mat = reinterpret_cast<float*>(vortexMemory::MemoryManager::instance().requestPoolMem(vortexMemory::TYPE_MAT3));
}

vortexMath::Mat3::Mat3(const float* data)
{
    mat = reinterpret_cast<float*>(vortexMemory::MemoryManager::instance().requestPoolMem(vortexMemory::TYPE_MAT3));
    for (int i = 0; i < 9; i++)
    {
        mat[i] = *(data + i);
    }
}

vortexMath::Mat3::Mat3(const float value)
{
    mat = reinterpret_cast<float*>(vortexMemory::MemoryManager::instance().requestPoolMem(vortexMemory::TYPE_MAT3));
    mat[0] = value;
    mat[4] = value;
    mat[8] = value;
}

vortexMath::Mat3::~Mat3()
{
    vortexMemory::MemoryManager::instance().freePoolMem(vortexMemory::TYPE_MAT3, mat);
}

void vortexMath::Mat3::orientate(const vortexMath::Quaternion& q)
{
    float w = q.getW();
    float x = q.getI();
    float y = q.getJ();
    float z = q.getK();
    
    mat[0]  = 1 - (2*y*y + 2*z*z);
    mat[4]  = 1 - (2*x*x + 2*z*z);
    mat[8] = 1 - (2*x*x + 2*y*y);
    
    mat[3]  = 2*x*y + 2*z*w;
    mat[6]  = 2*x*z - 2*y*w;
    
    mat[1]  = 2*x*y - 2*z*w;
    mat[7]  = 2*y*z + 2*x*w;
    
    mat[2]  = 2*x*z + 2*y*w;
    mat[5]  = 2*y*z - 2*x*w;
}

vortexMath::Mat3 vortexMath::Mat3::operator*(const vortexMath::Mat3& matrixB) const
{
    alignas(32) float retMat[9];

    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7, 
            xmm8, xmm9, xmm10, xmm11, xmm12;
    
    xmm10 = _mm_loadu_ps((float *) (mat + 0*3)); //a b c
    xmm11 = _mm_loadu_ps((float *) (mat + 1*3)); //d e f
    xmm12 = _mm_loadu_ps((float *) (mat + 2*3)); //g h i

    xmm0 = _mm_broadcast_ss(matrixB.mat + 0); //A
    xmm1 = _mm_broadcast_ss(matrixB.mat + 1); //B
    xmm2 = _mm_broadcast_ss(matrixB.mat + 2); //C
    
    xmm3 = _mm_broadcast_ss(matrixB.mat + 1*3 + 0); //D
    xmm4 = _mm_broadcast_ss(matrixB.mat + 1*3 + 1); //E
    xmm5 = _mm_broadcast_ss(matrixB.mat + 1*3 + 2); //F
    
    xmm6 = _mm_broadcast_ss(matrixB.mat + 2*3 + 0); //G
    xmm7 = _mm_broadcast_ss(matrixB.mat + 2*3 + 1); //H
    xmm8 = _mm_broadcast_ss(matrixB.mat + 2*3 + 2); //I

    xmm0 = _mm_mul_ps(xmm0, xmm10);
    xmm3 = _mm_mul_ps(xmm3, xmm10);
    xmm6 = _mm_mul_ps(xmm6, xmm10);
    
    xmm1 = _mm_fmadd_ps(xmm1, xmm11, xmm0);
    xmm4 = _mm_fmadd_ps(xmm4, xmm11, xmm3);
    xmm7 = _mm_fmadd_ps(xmm7, xmm11, xmm6);
    
    xmm2 = _mm_fmadd_ps(xmm2, xmm12, xmm1);
    xmm5 = _mm_fmadd_ps(xmm5, xmm12, xmm4);
    xmm8 = _mm_fmadd_ps(xmm8, xmm12, xmm7);
    
    _mm_storeu_ps((float *) (retMat + 0*3), xmm2);
    _mm_storeu_ps((float *) (retMat + 1*3), xmm5);
    _mm_storeu_ps((float *) (retMat + 2*3), xmm8);
    
    return vortexMath::Mat3(retMat);
}

void vortexMath::Mat3::transpose()
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4;
    
    xmm0 = _mm_load_ps((float* ) mat + 0*4);
    xmm1 = _mm_load_ps((float* ) mat + 1*4);
    xmm2 = _mm_load_ps((float* ) mat + 2*4);
    
    xmm3 = _mm_shuffle_ps(xmm0, xmm1, 0b01001001);
    xmm4 = _mm_shuffle_ps(xmm1, xmm2, 0b10011110);
    
    xmm0 = _mm_shuffle_ps(xmm0, xmm4, 0b11001100);
    xmm2 = _mm_shuffle_ps(xmm3, xmm2, 0b11001101);
    xmm1 = _mm_shuffle_ps(xmm3, xmm4, 0b11011000);
    
    _mm_storeu_ps((float *) (mat + 0), xmm0);
    _mm_storeu_ps((float *) (mat + 3), xmm1);
    _mm_storeu_ps((float *) (mat + 6), xmm2);
}

float vortexMath::Mat3::determinant() const
{
}

void vortexMath::Mat3::invert()
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7, 
            xmm8, xmm9, xmm10, xmm11, xmm12, xmm13;
    
    _mm256_zeroupper();
    xmm0 = _mm_broadcast_ss((float* ) mat + 0*3 + 0); //a
    xmm1 = _mm_broadcast_ss((float* ) mat + 0*3 + 1); //b
    xmm2 = _mm_broadcast_ss((float* ) mat + 0*3 + 2); //c
    
    xmm3 = _mm_broadcast_ss((float* ) mat + 1*3 + 0); //d
    xmm4 = _mm_broadcast_ss((float* ) mat + 1*3 + 1); //e
    xmm5 = _mm_broadcast_ss((float* ) mat + 1*3 + 2); //f
    
    xmm6 = _mm_broadcast_ss((float* ) mat + 2*3 + 0); //g
    xmm7 = _mm_broadcast_ss((float* ) mat + 2*3 + 1); //h
    xmm8 = _mm_broadcast_ss((float* ) mat + 2*3 + 2); //i
    
    xmm9 = _mm_set_ps(1.0f, 1.0f, -1.0f, 1.0f);
    xmm13 = _mm_set1_ps(-1.0f);
    
    xmm6 = _mm_blend_ps(xmm6, xmm3, 0xC); //g g d d
    xmm7 = _mm_blend_ps(xmm7, xmm4, 0xC); //h h e e
    xmm8 = _mm_blend_ps(xmm8, xmm5, 0xC); //i i f f
    
    xmm3 = _mm_blend_ps(xmm3, xmm0, 0xE); //d a a a
    xmm4 = _mm_blend_ps(xmm4, xmm1, 0xE); //e b b b
    xmm5 = _mm_blend_ps(xmm5, xmm2, 0xE); //f c c c
    
    xmm10= _mm_mul_ps(xmm5, xmm7);
    xmm11= _mm_mul_ps(xmm5, xmm6);
    xmm12= _mm_mul_ps(xmm4, xmm6);
    
    xmm10= _mm_fmsub_ps(xmm4, xmm8, xmm10);
    xmm11= _mm_fmsub_ps(xmm3, xmm8, xmm11);
    xmm12= _mm_fmsub_ps(xmm3, xmm7, xmm12);
    
    xmm0 = _mm_mul_ps(xmm0, xmm10);

    xmm1 = _mm_fmsub_ps(xmm1, xmm11, xmm0);
    xmm2 = _mm_fmsub_ps(xmm2, xmm12, xmm1); //det
    
    if (xmm2[0] < 0.00001f) { *this = {}; return; }
    
    xmm2 = _mm_broadcastss_ps(xmm2);
    
    xmm2 = _mm_div_ps(xmm9, xmm2);
    
    xmm10= _mm_mul_ps(xmm2, xmm10);
    xmm11= _mm_mul_ps(xmm2, xmm11);
    xmm12= _mm_mul_ps(xmm2, xmm12);
    
    xmm11= _mm_mul_ps(xmm11, xmm13);
    
    _mm_storeu_ps((float *) (mat + 0*3), xmm10);
    _mm_storeu_ps((float *) (mat + 1*3), xmm11);
    _mm_storeu_ps((float *) (mat + 2*3), xmm12);
}
vortexMath::Mat4::Mat4()
{
    mat = reinterpret_cast<float*>(vortexMemory::MemoryManager::instance().requestPoolMem(vortexMemory::TYPE_MAT4));
    __m256 ymm0 = _mm256_set1_ps(0.0f);
    _mm256_store_ps((float* ) mat + 0, ymm0);
    _mm256_store_ps((float* ) mat + 8, ymm0);
}

vortexMath::Mat4::Mat4(const float* initData)
{
    mat = reinterpret_cast<float*>(vortexMemory::MemoryManager::instance().requestPoolMem(vortexMemory::TYPE_MAT4));
    _mm256_store_ps((float* ) mat + 0, _mm256_load_ps((float* ) initData + 0));
    _mm256_store_ps((float* ) mat + 8, _mm256_load_ps((float* ) initData + 8));
}

vortexMath::Mat4::Mat4(const float value)
{
    void* temp = vortexMemory::MemoryManager::instance().requestPoolMem(vortexMemory::TYPE_MAT4);
    
    mat = reinterpret_cast<float*>(temp);
    __m256 ymm0 = _mm256_set1_ps(0.0f);
    _mm256_store_ps((float* ) mat + 0, ymm0);
    _mm256_store_ps((float* ) mat + 8, ymm0);
    
    mat[0]  = value;
    mat[5]  = value;
    mat[10] = value; 
    mat[15] = value;
}

vortexMath::Mat4::Mat4(const float& col1, const float& col2, const float& col3, const float& col4)
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;
            
    xmm0 = _mm_load_ps((float* ) &col1);
    xmm1 = _mm_load_ps((float* ) &col2);
    xmm2 = _mm_load_ps((float* ) &col3);
    xmm3 = _mm_load_ps((float* ) &col4);
    
    xmm4 = _mm_unpacklo_ps(xmm0, xmm1);
    xmm5 = _mm_unpacklo_ps(xmm2, xmm3);
    xmm6 = _mm_unpackhi_ps(xmm0, xmm1);
    xmm7 = _mm_unpackhi_ps(xmm2, xmm3);
    
    xmm0 = _mm_shuffle_ps(xmm4, xmm5, 0b01000100);
    xmm1 = _mm_shuffle_ps(xmm4, xmm5, 0b11101110);
    xmm2 = _mm_shuffle_ps(xmm6, xmm7, 0b01000100);
    xmm3 = _mm_shuffle_ps(xmm6, xmm7, 0b11101110);
    
    _mm_store_ps((float* ) mat +  0, xmm0);
    _mm_store_ps((float* ) mat +  4, xmm1);
    _mm_store_ps((float* ) mat +  8, xmm2);
    _mm_store_ps((float* ) mat + 12, xmm3);
}

vortexMath::Mat4::Mat4(const vortexMath::Vec4<float>& col1, const vortexMath::Vec4<float>& col2, const vortexMath::Vec4<float>& col3, const vortexMath::Vec4<float>& col4)
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;
            
    //TODO: Vec4 must use my own aligned allocator, so using loadu instructions instead of load, will be much slower, but its temp
    xmm0 = _mm_loadu_ps((float* ) col1.data());
    xmm1 = _mm_loadu_ps((float* ) col2.data());
    xmm2 = _mm_loadu_ps((float* ) col3.data());
    xmm3 = _mm_loadu_ps((float* ) col4.data());
    
    xmm4 = _mm_unpacklo_ps(xmm0, xmm1);
    xmm5 = _mm_unpacklo_ps(xmm2, xmm3);
    xmm6 = _mm_unpackhi_ps(xmm0, xmm1);
    xmm7 = _mm_unpackhi_ps(xmm2, xmm3);
    
    xmm0 = _mm_shuffle_ps(xmm4, xmm5, 0b01000100);
    xmm1 = _mm_shuffle_ps(xmm4, xmm5, 0b11101110);
    xmm2 = _mm_shuffle_ps(xmm6, xmm7, 0b01000100);
    xmm3 = _mm_shuffle_ps(xmm6, xmm7, 0b11101110);
    
    _mm_storeu_ps((float* ) mat +  0, xmm0);
    _mm_storeu_ps((float* ) mat +  4, xmm1);
    _mm_storeu_ps((float* ) mat +  8, xmm2);
    _mm_storeu_ps((float* ) mat + 12, xmm3);
}

vortexMath::Mat4::~Mat4()
{
    vortexMemory::MemoryManager::instance().freePoolMem(vortexMemory::TYPE_MAT4, mat);
}

#include <memory>
vortexMath::Mat4 * vortexMath::Mat4::projection(const float fov, const float near, const float far)
{
    vortexMath::Mat4 * mat = new vortexMath::Mat4{};
    float s = 1.0f / tan(fov/2 * 3.14159265f / 180.0f);
    float f = far - near;

    mat->mat[0]  = s;
    mat->mat[5]  = s;
    mat->mat[10] = -far / f;
    mat->mat[11] = -1.0f;
    mat->mat[14] = -(far * near) / f;
    
    return mat;
}

void vortexMath::Mat4::translate(const Vec4<float>& vec)
{
    _mm_store_ps((float* ) mat + 12, _mm_load_ps((float* ) vec.data()));
}

void vortexMath::Mat4::translate(const Vec3<float>& vec)
{
    _mm_store_ps((float* ) mat + 12, _mm_load_ps((float* ) vec.data()));
    mat[15] = 1.0f;
}


void vortexMath::Mat4::orientate(const vortexMath::Quaternion& q)
{
    float w = q.getW();
    float x = q.getI();
    float y = q.getJ();
    float z = q.getK();
    
    mat[0]  = 1 - (2*y*y + 2*z*z);
    mat[5]  = 1 - (2*x*x + 2*z*z);
    mat[10] = 1 - (2*x*x + 2*y*y);
    
    mat[4]  = 2*x*y + 2*z*w;
    mat[8]  = 2*x*z - 2*y*w;
    
    mat[1]  = 2*x*y - 2*z*w;
    mat[9]  = 2*y*z + 2*x*w;
    
    mat[2]  = 2*x*z + 2*y*w;
    mat[6]  = 2*y*z - 2*x*w;
}
vortexMath::Mat4 vortexMath::Mat4::operator*(const vortexMath::Mat4& matrixB) const
{
    __m128 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7, 
            ymm10, ymm11, ymm12, ymm13, ymm14, ymm15;

    
    alignas(32) float retMat[16];
    
    ymm12 = _mm_load_ps((float *) (mat + 0*4)); //a b c d
    ymm13 = _mm_load_ps((float *) (mat + 1*4)); //e f g h
    ymm14 = _mm_load_ps((float *) (mat + 2*4)); //i j k l
    ymm15 = _mm_load_ps((float *) (mat + 3*4)); //m n o p

    ymm0 = _mm_broadcast_ss(matrixB.mat + 0); //A
    ymm1 = _mm_broadcast_ss(matrixB.mat + 1); //B
    ymm2 = _mm_broadcast_ss(matrixB.mat + 2); //C
    ymm3 = _mm_broadcast_ss(matrixB.mat + 3); //D
    ymm4 = _mm_broadcast_ss(matrixB.mat + 1*4 + 0); //E
    ymm5 = _mm_broadcast_ss(matrixB.mat + 1*4 + 1); //F
    ymm6 = _mm_broadcast_ss(matrixB.mat + 1*4 + 2); //G
    ymm7 = _mm_broadcast_ss(matrixB.mat + 1*4 + 3); //H
    
    ymm0  = _mm_mul_ps(ymm0, ymm12);
    ymm4  = _mm_mul_ps(ymm4, ymm12);
    ymm1  = _mm_fmadd_ps(ymm1, ymm13, ymm0);
    ymm5  = _mm_fmadd_ps(ymm5, ymm13, ymm4);
    ymm2  = _mm_fmadd_ps(ymm2, ymm14, ymm1);
    ymm6  = _mm_fmadd_ps(ymm6, ymm14, ymm5);
    ymm10 = _mm_fmadd_ps(ymm3, ymm15, ymm2); //Final row0
    ymm11 = _mm_fmadd_ps(ymm7, ymm15, ymm6); //Final row1
    
    _mm_store_ps((float *) (retMat + 0*4), ymm10);
    _mm_store_ps((float *) (retMat + 1*4), ymm11);
    
    ymm0 = _mm_broadcast_ss(matrixB.mat + 2*4 + 0); //I
    ymm1 = _mm_broadcast_ss(matrixB.mat + 2*4 + 1); //J
    ymm2 = _mm_broadcast_ss(matrixB.mat + 2*4 + 2); //K
    ymm3 = _mm_broadcast_ss(matrixB.mat + 2*4 + 3); //L
    ymm4 = _mm_broadcast_ss(matrixB.mat + 3*4 + 0); //M    
    ymm5 = _mm_broadcast_ss(matrixB.mat + 3*4 + 1); //N
    ymm6 = _mm_broadcast_ss(matrixB.mat + 3*4 + 2); //O
    ymm7 = _mm_broadcast_ss(matrixB.mat + 3*4 + 3); //P

    ymm0 = _mm_mul_ps(ymm0, ymm12);
    ymm4 = _mm_mul_ps(ymm4, ymm12);
    ymm1 = _mm_fmadd_ps(ymm1, ymm13, ymm0);
    ymm5 = _mm_fmadd_ps(ymm5, ymm13, ymm4);
    ymm2 = _mm_fmadd_ps(ymm2, ymm14, ymm1);
    ymm6 = _mm_fmadd_ps(ymm6, ymm14, ymm5);
    ymm3 = _mm_fmadd_ps(ymm3, ymm15, ymm2); //Final row0
    ymm7 = _mm_fmadd_ps(ymm7, ymm15, ymm6); //Final row1
    _mm_store_ps((float *) (retMat + 2*4), ymm3);
    _mm_store_ps((float *) (retMat + 3*4), ymm7);
    
    return vortexMath::Mat4(retMat);
}

void vortexMath::Mat4::transpose()
{
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7;
    
    ymm0 = _mm256_insertf128_ps(_mm256_castps128_ps256(_mm_load_ps((float* ) mat + 0*4)), _mm_load_ps((float* ) mat + 0*4 + 1), 1); //11 12 13 14 12 13 14 21
    ymm1 = _mm256_insertf128_ps(_mm256_castps128_ps256(_mm_load_ps((float* ) mat + 1*4)), _mm_load_ps((float* ) mat + 1*4 + 1), 1); //21 22 23 24 22 23 24 31

    ymm2 = _mm256_insertf128_ps(_mm256_castps128_ps256(_mm_set1_ps(1.0f)), _mm_load_ps((float* ) mat + 1*4 + 3), 0); //31 32 33 34 32 33 34 41
    ymm3 = _mm256_insertf128_ps(_mm256_castps128_ps256(_mm_set1_ps(1.0f)), _mm_load_ps((float* ) mat + 2*4 + 3), 0); //41 42 43 44 42 43 44 00

    ymm2 = _mm256_insertf128_ps(ymm2, _mm_load_ps((float* ) mat + 2*4), 1); //24 31 32 33  31 32 33 34
    ymm3 = _mm256_insertf128_ps(ymm3, _mm_load_ps((float* ) mat + 3*4), 1); //34 41 42 43  41 42 43 44

    ymm4 = _mm256_unpacklo_ps(ymm0, ymm1); //11 21 12 22   12 22 13 23 
    ymm5 = _mm256_unpackhi_ps(ymm0, ymm1); //13 23 14 24   14 24 21 31 
    ymm6 = _mm256_unpacklo_ps(ymm2, ymm3); //24 34 31 41   31 41 32 42 
    ymm7 = _mm256_unpackhi_ps(ymm2, ymm3); //32 42 33 43   33 43 34 44 

    ymm0 = _mm256_blend_ps(ymm4, ymm6, 0b11001100);
    ymm1 = _mm256_blend_ps(ymm5, ymm7, 0b11001100);

    _mm256_store_ps((float* ) mat + 0*8, ymm0);
    _mm256_store_ps((float* ) mat + 1*8, ymm1);
}

float vortexMath::Mat4::determinant() const
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7, xmm8, xmm9, xmm10, xmm11, xmm12, xmm13, xmm14, xmm15;
    
    xmm15 = _mm_load_ps((float* ) mat + 0*4 + 0); //a b c d
    
    xmm0 = _mm_broadcast_ss((float* ) mat + 1*4 + 0); //e
    xmm1 = _mm_broadcast_ss((float* ) mat + 1*4 + 1); //f
    xmm2 = _mm_broadcast_ss((float* ) mat + 1*4 + 2); //g
    xmm3 = _mm_broadcast_ss((float* ) mat + 1*4 + 3); //h
    
    xmm4 = _mm_broadcast_ss((float* ) mat + 2*4 + 0); //i
    xmm5 = _mm_broadcast_ss((float* ) mat + 2*4 + 1); //j
    xmm6 = _mm_broadcast_ss((float* ) mat + 2*4 + 2); //k
    xmm7 = _mm_broadcast_ss((float* ) mat + 2*4 + 3); //l

    xmm8 = _mm_broadcast_ss((float* ) mat + 3*4 + 0); //m
    xmm9 = _mm_broadcast_ss((float* ) mat + 3*4 + 1); //n
    xmm10= _mm_broadcast_ss((float* ) mat + 3*4 + 2); //o
    xmm11= _mm_broadcast_ss((float* ) mat + 3*4 + 3); //p
    
    xmm12 = _mm_blend_ps(xmm1, xmm2, 0x3); //g g f f
    xmm13 = _mm_blend_ps(xmm5, xmm6, 0x3); //k k j j
    xmm14 = _mm_blend_ps(xmm9, xmm10,0x3); //o o n n
    
    xmm0 = _mm_blend_ps(xmm1, xmm0, 0xE); //f e e e
    xmm2 = _mm_blend_ps(xmm3, xmm2, 0x8); //h h h g 
    
    xmm4 = _mm_blend_ps(xmm5, xmm4, 0xE); //j i i i
    xmm6 = _mm_blend_ps(xmm7, xmm6, 0x8); //l l l k
    
    xmm8 = _mm_blend_ps(xmm9, xmm8, 0xE); //n m m m
    xmm10= _mm_blend_ps(xmm11,xmm10,0x8); //p p p o
    
    xmm1 = _mm_mul_ps(xmm6,  xmm14); 
    xmm3 = _mm_mul_ps(xmm6,  xmm8 );
    xmm5 = _mm_mul_ps(xmm13, xmm8 ); 
    
    xmm7 = _mm_fmsub_ps(xmm13, xmm10, xmm1); //1
    xmm9 = _mm_fmsub_ps(xmm4,  xmm10, xmm3); //2
    xmm11= _mm_fmsub_ps(xmm4,  xmm14, xmm5); //3

    xmm1 = _mm_mul_ps(xmm2, xmm11);
    
    xmm2 = _mm_fmsub_ps(xmm12, xmm9, xmm1);
    
    xmm3 = _mm_fmsub_ps(xmm0, xmm7, xmm2);
    
    xmm3 = _mm_mul_ps(xmm3, xmm15);
    
    return xmm3[0] - xmm3[1] + xmm3[2] - xmm3[3];
}

void vortexMath::Mat4::invert()
{
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7, ymm8, ymm9, ymm10, ymm11, ymm12, ymm13, ymm14, ymm15;

    ymm0 = _mm256_broadcast_ss((float* ) mat + 0*8 + 4); //e
    ymm1 = _mm256_broadcast_ss((float* ) mat + 0*8 + 5); //f
    ymm2 = _mm256_broadcast_ss((float* ) mat + 0*8 + 6); //g
    ymm3 = _mm256_broadcast_ss((float* ) mat + 0*8 + 7); //h
    
    ymm8 = _mm256_broadcast_ss((float* ) mat + 1*8 + 0); //i
    ymm9 = _mm256_broadcast_ss((float* ) mat + 1*8 + 1); //j
    ymm10= _mm256_broadcast_ss((float* ) mat + 1*8 + 2); //k
    ymm11= _mm256_broadcast_ss((float* ) mat + 1*8 + 3); //l
    
    ymm12= _mm256_broadcast_ss((float* ) mat + 1*8 + 4); //m
    ymm13= _mm256_broadcast_ss((float* ) mat + 1*8 + 5); //n
    ymm14= _mm256_broadcast_ss((float* ) mat + 1*8 + 6); //o
    ymm15= _mm256_broadcast_ss((float* ) mat + 1*8 + 7); //p

    ymm4 = _mm256_blend_ps(ymm8,  ymm0, 0xCC); //i i e e  i i e e
    ymm5 = _mm256_blend_ps(ymm9 , ymm1, 0xCC); //j j f f  j j f f
    ymm6 = _mm256_blend_ps(ymm10, ymm2, 0xCC); //k k g g  k k g g
    ymm7 = _mm256_blend_ps(ymm11, ymm3, 0xCC); //l l h h  l l h h
    
    ymm12 = _mm256_blend_ps(ymm12, ymm8, 0x88); //m m m i  m m m i
    ymm13 = _mm256_blend_ps(ymm13, ymm9, 0x88); //n n n j  n n n j
    ymm14 = _mm256_blend_ps(ymm14, ymm10,0x88); //o o o k  o o o k 
    ymm15 = _mm256_blend_ps(ymm15, ymm11,0x88); //p p p l  p p p l
    
    //Compounds
    ymm8 = _mm256_blend_ps(ymm5,  ymm4, 0xF0); //j j f f  i i e e
    ymm9 = _mm256_blend_ps(ymm7,  ymm6, 0xF0); //l l h h  k k g g
    ymm10= _mm256_blend_ps(ymm13, ymm12,0xF0); //n n n j  m m m i
    
    //Recycle old registers
    ymm5 = _mm256_blend_ps(ymm6,  ymm5, 0xF0); //k k g g  j j f f
    ymm6 = _mm256_blend_ps(ymm15, ymm14,0xF0); //p p p l  o o o k
    ymm13= _mm256_blend_ps(ymm14, ymm13,0xF0); //o o o k  n n n j
    
    ymm11 = _mm256_mul_ps(ymm7, ymm13); //lo row1 col1
    ymm14 = _mm256_mul_ps(ymm9, ymm13); //lo row1 col2
    ymm7  = _mm256_mul_ps(ymm7, ymm10); //lo row2 col1
    ymm9  = _mm256_mul_ps(ymm9, ymm12); //lo row2 col2
    ymm10 = _mm256_mul_ps(ymm5, ymm10); //lo row3 col1
    ymm12 = _mm256_mul_ps(ymm5, ymm12); //lo row3 col2
    
    ymm11 = _mm256_fmsub_ps(ymm5, ymm15, ymm11); //row1 col1
    ymm14 = _mm256_fmsub_ps(ymm5, ymm6 , ymm14); //row1 col2
    ymm7  = _mm256_fmsub_ps(ymm8, ymm15, ymm7 ); //row2 col1
    ymm9  = _mm256_fmsub_ps(ymm4, ymm6 , ymm9 ); //row2 col2
    ymm10 = _mm256_fmsub_ps(ymm8, ymm13, ymm10); //row3 col1
    ymm12 = _mm256_fmsub_ps(ymm4, ymm13, ymm12); //row3 col2

    ymm4 = _mm256_broadcast_ss((float* ) mat + 0*8 + 0); //a
    ymm5 = _mm256_broadcast_ss((float* ) mat + 0*8 + 1); //b
    ymm6 = _mm256_broadcast_ss((float* ) mat + 0*8 + 2); //c
    ymm13= _mm256_broadcast_ss((float* ) mat + 0*8 + 3); //d

    ymm0 = _mm256_blend_ps(ymm0, ymm4,  0xEE); //e a a a  e a a a 
    ymm1 = _mm256_blend_ps(ymm1, ymm5,  0xEE); //f b b b  f b b b
    ymm2 = _mm256_blend_ps(ymm2, ymm6,  0xEE); //g c c c  g c c c 
    ymm3 = _mm256_blend_ps(ymm3, ymm13, 0xEE); //h d d d  h d d d
    
    ymm4 = _mm256_blend_ps(ymm4, ymm6, 0xF0);
    ymm5 = _mm256_blend_ps(ymm5, ymm13, 0xF0);
    
    ymm15= _mm256_blend_ps(ymm2, ymm1, 0xF0); //g c c c  f b b b
    ymm1 = _mm256_blend_ps(ymm1, ymm0, 0xF0); //f b b b  e a a a
    ymm2 = _mm256_blend_ps(ymm3, ymm2, 0xF0); //h d d d  g c c c

    ymm10 = _mm256_mul_ps(ymm3, ymm10);
    ymm12 = _mm256_mul_ps(ymm2, ymm12);
    
    ymm10 = _mm256_fmsub_ps(ymm15, ymm7, ymm10);
    ymm12 = _mm256_fmsub_ps(ymm15, ymm9, ymm12);
    
    ymm10 = _mm256_fmsub_ps(ymm1, ymm11, ymm10);
    ymm12 = _mm256_fmsub_ps(ymm0, ymm14, ymm12);
    
    
    ymm0 = _mm256_mul_ps(ymm5, ymm12);
    ymm0 = _mm256_fmsub_ps(ymm4, ymm10, ymm0);

    ymm1 = _mm256_permute2f128_ps(ymm0, ymm0, 1);
    ymm2 = _mm256_permute2f128_ps(ymm10, ymm12, 32); //a b
    ymm3 = _mm256_permute2f128_ps(ymm12, ymm10, 23); //c d

    ymm1 = _mm256_add_ps(ymm1, ymm0);
    
    if (ymm1[0] < 0.00001f) { *this = {}; return; }
    
    ymm1 = _mm256_set1_ps(ymm1[0]); //det
    ymm4 = _mm256_set_ps(1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    
    ymm1 = _mm256_div_ps(ymm4, ymm1);
    
    ymm2 = _mm256_mul_ps(ymm2, ymm1);
    ymm3 = _mm256_mul_ps(ymm3, ymm1);
    
    _mm256_store_ps((float* ) mat + 0*8, ymm2);
    _mm256_store_ps((float* ) mat + 1*8, ymm3);
}
