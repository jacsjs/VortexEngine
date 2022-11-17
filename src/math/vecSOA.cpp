#include "math/vecSOA.hpp"

vortexMath::Vec2x4::Vec2x4(const int vectors)
{
    if (vectors < 4) return; 
    vecData.reserve(vectors * 2);
    vecCount = vectors; 
}

vortexMath::Vec2x4::Vec2x4(const float* data, int vectors)
{
    if (vectors < 4) return;
    vecData.insert(ITERATOR_BEGIN, 0, data, vectors * 2);
    vecCount = vectors; 
}

vortexMath::Vec2x4::Vec2x4(const float value, int vectors)
{
    if (vectors < 4) return;
    vecData.insert(ITERATOR_BEGIN, 0, std::vector<float>(vectors * 2, value));
    vecCount = vectors; 
}

vortexMath::Vec2x4::Vec2x4(const AlignedVector<float, 16>& x, const AlignedVector<float, 16>& y, const int vectors)
{
    if (vectors < 4) return;
    vecData.reserve(vectors * 2);
    vecCount = vectors;
    __m128 xmm0, xmm1;
    for (int i = 0; i < vecAmount(); i+=4)
    {
        xmm0 = _mm_load_ps((float* ) x.data() + i);
        xmm1 = _mm_load_ps((float* ) y.data() + i);
        
        _mm_store_ps((float* ) vecData.data() + (i * 2) +  0, xmm0);
        _mm_store_ps((float* ) vecData.data() + (i * 2) +  4, xmm1);
    }
}

vortexMath::Vec2x4 vortexMath::Vec2x4::vec2x4(const vortexMath::Vec3x4& vec)
{
    return Vec2x4(vec.get(VEC_ELEMENT_X), vec.get(VEC_ELEMENT_Y), vec.vecAmount());
}

vortexMath::Vec2x4 vortexMath::Vec2x4::vec2x4(const vortexMath::Vec4x4& vec)
{
    return Vec2x4(vec.get(VEC_ELEMENT_X), vec.get(VEC_ELEMENT_Y), vec.vecAmount());
}

void vortexMath::Vec2x4::operator+=(const vortexMath::Vec2x4& vec)
{
    __m128 xmm0, xmm1, xmm2, xmm3;
    for(int i = 0; i < size(); i+=8)
    {
        xmm0 = _mm_load_ps((float* ) data()     + i + 0);
        xmm1 = _mm_load_ps((float* ) data()     + i + 4);
        xmm2 = _mm_load_ps((float* ) vec.data() + i + 0);
        xmm3 = _mm_load_ps((float* ) vec.data() + i + 4);
        xmm0 = _mm_add_ps(xmm0, xmm2);
        xmm1 = _mm_add_ps(xmm1, xmm3);
        _mm_store_ps((float* ) data() + i + 0, xmm0);
        _mm_store_ps((float* ) data() + i + 4, xmm1);
    }
}

void vortexMath::Vec2x4::operator-=(const vortexMath::Vec2x4& vec)
{
    __m128 xmm0, xmm1, xmm2, xmm3;
    for(int i = 0; i < size(); i+=8)
    {
        xmm0 = _mm_load_ps((float* ) data()     + i + 0);
        xmm1 = _mm_load_ps((float* ) data()     + i + 4);
        xmm2 = _mm_load_ps((float* ) vec.data() + i + 0);
        xmm3 = _mm_load_ps((float* ) vec.data() + i + 4);
        xmm0 = _mm_sub_ps(xmm0, xmm2);
        xmm1 = _mm_sub_ps(xmm1, xmm3);
        _mm_store_ps((float* ) data() + i + 0, xmm0);
        _mm_store_ps((float* ) data() + i + 4, xmm1);
    }
}

void vortexMath::Vec2x4::operator<<=(const vortexMath::Vec2x4& vec)
{
    __m128 xmm0, xmm1, xmm2, xmm3;
    for(int i = 0; i < size(); i+=8)
    {
        xmm0 = _mm_load_ps((float* ) data()     + i + 0);
        xmm1 = _mm_load_ps((float* ) data()     + i + 4);
        xmm2 = _mm_load_ps((float* ) vec.data() + i + 0);
        xmm3 = _mm_load_ps((float* ) vec.data() + i + 4);
        xmm0 = _mm_mul_ps(xmm0, xmm2);
        xmm1 = _mm_mul_ps(xmm1, xmm3);
        _mm_store_ps((float* ) data() + i + 0, xmm0);
        _mm_store_ps((float* ) data() + i + 4, xmm1);
    }
}

void vortexMath::Vec2x4::operator>>=(const vortexMath::Vec2x4& vec)
{
    __m128 xmm0, xmm1, xmm2, xmm3;
    for(int i = 0; i < size(); i+=8)
    {
        xmm0 = _mm_load_ps((float* ) data()     + i + 0);
        xmm1 = _mm_load_ps((float* ) data()     + i + 4);
        xmm2 = _mm_load_ps((float* ) vec.data() + i + 0);
        xmm3 = _mm_load_ps((float* ) vec.data() + i + 4);
        xmm0 = _mm_div_ps(xmm0, xmm2);
        xmm1 = _mm_div_ps(xmm1, xmm3);
        _mm_store_ps((float* ) data() + i + 0, xmm0);
        _mm_store_ps((float* ) data() + i + 4, xmm1);
    }
}

void vortexMath::Vec2x4::operator*=(const float value)
{
    __m128 xmm0, xmm1, xmm2, xmm3;
    xmm3 = _mm_set1_ps(value);
    for(int i = 0; i < size(); i+=12)
    {
        xmm0 = _mm_load_ps((float* ) data() + i + 0);
        xmm1 = _mm_load_ps((float* ) data() + i + 4);
        xmm0 = _mm_mul_ps(xmm0, xmm3);
        xmm1 = _mm_mul_ps(xmm1, xmm3);
        _mm_store_ps((float* ) data() + i + 0, xmm0);
        _mm_store_ps((float* ) data() + i + 4, xmm1);
    }
}

vortexMath::Vec2x4 vortexMath::Vec2x4::operator+(const vortexMath::Vec2x4& vec) const
{
    float * ret = (float* ) aligned_alloc(16, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3;
    for(int i = 0; i < size(); i+=8)
    {
        xmm0 = _mm_load_ps((float* ) data()     + i + 0);
        xmm1 = _mm_load_ps((float* ) data()     + i + 4);
        xmm2 = _mm_load_ps((float* ) vec.data() + i + 0);
        xmm3 = _mm_load_ps((float* ) vec.data() + i + 4);
        xmm0 = _mm_add_ps(xmm0, xmm2);
        xmm1 = _mm_add_ps(xmm1, xmm3);
        _mm_store_ps((float* ) ret + i + 0, xmm0);
        _mm_store_ps((float* ) ret + i + 4, xmm1);
    }
    Vec2x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec2x4 vortexMath::Vec2x4::operator-(const vortexMath::Vec2x4& vec) const
{
    float * ret = (float* ) aligned_alloc(16, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3;
    for(int i = 0; i < size(); i+=8)
    {
        xmm0 = _mm_load_ps((float* ) data()     + i + 0);
        xmm1 = _mm_load_ps((float* ) data()     + i + 4);
        xmm2 = _mm_load_ps((float* ) vec.data() + i + 0);
        xmm3 = _mm_load_ps((float* ) vec.data() + i + 4);
        xmm0 = _mm_add_ps(xmm0, xmm2);
        xmm1 = _mm_add_ps(xmm1, xmm3);
        _mm_store_ps((float* ) ret + i + 0, xmm0);
        _mm_store_ps((float* ) ret + i + 4, xmm1);
    }
    Vec2x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec2x4 vortexMath::Vec2x4::operator<<(const vortexMath::Vec2x4& vec) const
{
    float * ret = (float* ) aligned_alloc(16, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3;
    for(int i = 0; i < size(); i+=8)
    {
        xmm0 = _mm_load_ps((float* ) data()     + i + 0);
        xmm1 = _mm_load_ps((float* ) data()     + i + 4);
        xmm2 = _mm_load_ps((float* ) vec.data() + i + 0);
        xmm3 = _mm_load_ps((float* ) vec.data() + i + 4);
        xmm0 = _mm_mul_ps(xmm0, xmm2);
        xmm1 = _mm_mul_ps(xmm1, xmm3);
        _mm_store_ps((float* ) ret + i + 0, xmm0);
        _mm_store_ps((float* ) ret + i + 4, xmm1);
    }
    Vec2x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}



vortexMath::Vec2x4 vortexMath::Vec2x4::operator>>(const vortexMath::Vec2x4& vec) const
{
    float * ret = (float* ) aligned_alloc(16, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3;
    for(int i = 0; i < size(); i+=8)
    {
        xmm0 = _mm_load_ps((float* ) data()     + i + 0);
        xmm1 = _mm_load_ps((float* ) data()     + i + 4);
        xmm2 = _mm_load_ps((float* ) vec.data() + i + 0);
        xmm3 = _mm_load_ps((float* ) vec.data() + i + 4);
        xmm0 = _mm_div_ps(xmm0, xmm2);
        xmm1 = _mm_div_ps(xmm1, xmm3);
        _mm_store_ps((float* ) ret + i + 0, xmm0);
        _mm_store_ps((float* ) ret + i + 4, xmm1);
    }
    Vec2x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec2x4 vortexMath::Vec2x4::operator*(const float value) const
{
    float * ret = (float* ) aligned_alloc(16, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3;
    xmm3 = _mm_set1_ps(value);
    for(int i = 0; i < size(); i+=8)
    {
        xmm0 = _mm_load_ps((float* ) data() + i + 0);
        xmm1 = _mm_load_ps((float* ) data() + i + 4);
        xmm0 = _mm_mul_ps(xmm0, xmm3);
        xmm1 = _mm_mul_ps(xmm1, xmm3);
        _mm_store_ps((float* ) ret + i + 0, xmm0);
        _mm_store_ps((float* ) ret + i + 4, xmm1);
    }
    Vec2x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::AlignedVector<float, 16> vortexMath::Vec2x4::magnitude() const
{
    vortexMath::AlignedVector<float, 16> retVec(vecAmount());
    __m128 xmm0, xmm1, xmm2;
    for(int i = 0; i < vecAmount(); i+=4)
    {
        xmm0 = _mm_load_ps((float* ) data() + (i * 2) + 0);
        xmm1 = _mm_load_ps((float* ) data() + (i * 2) + 4);
        xmm2 = _mm_mul_ps(xmm1, xmm1);
        xmm2 = _mm_fmadd_ps(xmm0, xmm0, xmm2);
        xmm2 = _mm_sqrt_ps(xmm2);
        _mm_store_ps((float* ) retVec.data() + i, xmm2);
    }
    return retVec;
}

vortexMath::AlignedVector<float, 16> vortexMath::Vec2x4::squareMagnitude() const
{
    vortexMath::AlignedVector<float, 16> retVec(vecAmount());
    __m128 xmm0, xmm1, xmm2;
    for(int i = 0; i < vecAmount(); i+=4)
    {
        xmm0 = _mm_load_ps((float* ) data() + (i * 2) + 0);
        xmm1 = _mm_load_ps((float* ) data() + (i * 2) + 4);
        xmm2 = _mm_mul_ps(xmm1, xmm1);
        xmm2 = _mm_fmadd_ps(xmm0, xmm0, xmm2);
        _mm_store_ps((float* ) retVec.data() + i, xmm2);
    }
    return retVec;
}

void vortexMath::Vec2x4::normalize()
{
    __m128 xmm0, xmm1, xmm2, xmm3;
    xmm3 = _mm_set1_ps(1.0f);
    for(int i = 0; i < size(); i+=8)
    {
        xmm0 = _mm_load_ps((float* ) data() + i + 0);
        xmm1 = _mm_load_ps((float* ) data() + i + 4);
        xmm2 = _mm_mul_ps(xmm1, xmm1);
        xmm2 = _mm_fmadd_ps(xmm0, xmm0, xmm2);
        xmm2 = _mm_sqrt_ps(xmm2);
        xmm2 = _mm_div_ps(xmm3, xmm2);
        xmm0 = _mm_mul_ps(xmm0, xmm2);
        xmm1 = _mm_mul_ps(xmm1, xmm2);
        _mm_store_ps((float* ) data() + i + 0, xmm0);
        _mm_store_ps((float* ) data() + i + 4, xmm1);
    }
}

void vortexMath::Vec2x4::addScaledVector(const vortexMath::Vec2x4& vec, float scale)
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4;
    xmm4 = _mm_set1_ps(scale);
    for(int i = 0; i < size(); i+=8)
    {
        xmm0 = _mm_load_ps((float* ) data()     + i + 0);
        xmm1 = _mm_load_ps((float* ) data()     + i + 4);
        xmm2 = _mm_load_ps((float* ) vec.data() + i + 0);
        xmm3 = _mm_load_ps((float* ) vec.data() + i + 4);
        xmm0 = _mm_fmadd_ps(xmm2, xmm4, xmm0);
        xmm1 = _mm_fmadd_ps(xmm3, xmm4, xmm1);
        _mm_store_ps((float* ) data() + i + 0, xmm0);
        _mm_store_ps((float* ) data() + i + 4, xmm1);
    }
}

void vortexMath::Vec2x4::convertToSOA()
{
    __m128 xmm0, xmm1, xmm2, xmm3;

    for (int i = 0; i < size(); i+=8)
    {
        xmm0 = _mm_load_ps((float* ) data() + i + 0);
        xmm1 = _mm_load_ps((float* ) data() + i + 4);
        
        xmm2 = _mm_shuffle_ps(xmm0, xmm1, 0b10001000);
        xmm3 = _mm_shuffle_ps(xmm0, xmm1, 0b11011101);
        
        _mm_store_ps((float* ) data() + i + 0, xmm2);
        _mm_store_ps((float* ) data() + i + 4, xmm3);
    }
}

void vortexMath::Vec2x4::convertToAOS()
{
    __m128 xmm0, xmm1, xmm2, xmm3;

    for (int i = 0; i < size(); i+=8)
    {
        xmm0 = _mm_load_ps((float* ) data() + i + 0);
        xmm1 = _mm_load_ps((float* ) data() + i + 4);
        
        xmm2 = _mm_unpacklo_ps(xmm0, xmm1);
        xmm3 = _mm_unpackhi_ps(xmm0, xmm1);
        
        _mm_store_ps((float* ) data() + i + 0, xmm2);
        _mm_store_ps((float* ) data() + i + 4, xmm3);
    }
}

vortexMath::Vec2x4 vortexMath::Vec2x4::retrieveSOAForm() const
{
    float * ret = (float*) aligned_alloc(16, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3;
    for (int i = 0; i < size(); i+=8)
    {
        xmm0 = _mm_load_ps((float* ) data() + i + 0);
        xmm1 = _mm_load_ps((float* ) data() + i + 4);
        xmm2 = _mm_shuffle_ps(xmm0, xmm1, 0b10001000);
        xmm3 = _mm_shuffle_ps(xmm0, xmm1, 0b11011101);
        _mm_store_ps((float* ) ret + i + 0, xmm2);
        _mm_store_ps((float* ) ret + i + 4, xmm3);
    }
    Vec2x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec2x4 vortexMath::Vec2x4::retrieveAOSForm() const
{
    float * ret = (float*) aligned_alloc(16, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3;
    for (int i = 0; i < size(); i+=8)
    {
        xmm0 = _mm_load_ps((float* ) data() + i + 0);
        xmm1 = _mm_load_ps((float* ) data() + i + 4);
        xmm2 = _mm_unpacklo_ps(xmm0, xmm1);
        xmm3 = _mm_unpackhi_ps(xmm0, xmm1);
        _mm_store_ps((float* ) ret + i + 0, xmm2);
        _mm_store_ps((float* ) ret + i + 4, xmm3);
    }
    Vec2x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::AlignedVector<float, 16> vortexMath::Vec2x4::get(const vortexMath::VecElementType t) const
{
    vortexMath::AlignedVector<float, 16> retVec(vecAmount());
    for(int i = 0; i < vecAmount(); i+=4)
    {
        _mm_store_ps((float* ) retVec.data() + i, _mm_load_ps((float* ) data() + (i * 2) + t));
    }
    return retVec;
}

void vortexMath::Vec2x4::set(const vortexMath::VecElementType t, float val)
{
    __m128 xmm0 = _mm_set1_ps(val);
    for(int i = 0; i < vecAmount(); i+=4)
    {
        _mm_store_ps((float* ) data() + (i * 2) + t, xmm0);
    }
}

void vortexMath::Vec2x4::set(const vortexMath::VecElementType t, const vortexMath::AlignedVector<float, 16>& values)
{
    for(int i = 0; i < vecAmount(); i+=4)
    {
        _mm_store_ps((float* ) data() + (i * 2) + t, _mm_load_ps((float* ) values.data() + i));
    }
}

vortexMath::Vec3x4::Vec3x4(const int vectors)
{
    if (vectors < 4) return; 
    vecData.reserve(vectors * 3);
    vecCount = vectors; 
}

vortexMath::Vec3x4::Vec3x4(const float* data, int vectors)
{
    if (vectors < 4) return;
    vecData.insert(ITERATOR_BEGIN, 0, data, vectors * 3);
    vecCount = vectors; 
}

vortexMath::Vec3x4::Vec3x4(const float value, int vectors)
{
    if (vectors < 4) return;
    vecData.insert(ITERATOR_BEGIN, 0, std::vector<float>(vectors * 3, value));
    vecCount = vectors; 
}

vortexMath::Vec3x4::Vec3x4(const AlignedVector<float, 16>& x, const AlignedVector<float, 16>& y, const AlignedVector<float, 16>& z, const int vectors)
{
    if (vectors < 4) return;
    vecData.reserve(vectors * 3);
    vecCount = vectors;
    __m128 xmm0, xmm1, xmm2;
    for (int i = 0; i < vecAmount(); i+=4)
    {
        xmm0 = _mm_load_ps((float* ) x.data() + i);
        xmm1 = _mm_load_ps((float* ) y.data() + i);
        xmm2 = _mm_load_ps((float* ) z.data() + i);
        
        _mm_store_ps((float* ) vecData.data() + (i * 3) +  0, xmm0);
        _mm_store_ps((float* ) vecData.data() + (i * 3) +  4, xmm1);
        _mm_store_ps((float* ) vecData.data() + (i * 3) +  8, xmm2);
    }
}


vortexMath::Vec3x4 vortexMath::Vec3x4::vec3x4(const vortexMath::Vec2x4& vec, const vortexMath::AlignedVector<float, 16>& z)
{
    return Vec3x4(vec.get(VEC_ELEMENT_X), vec.get(VEC_ELEMENT_Y), z, vec.vecAmount());
}

vortexMath::Vec3x4 vortexMath::Vec3x4::vec3x4(const vortexMath::Vec4x4& vec)
{
    return Vec3x4(vec.get(VEC_ELEMENT_X), vec.get(VEC_ELEMENT_Y), vec.get(VEC_ELEMENT_Z), vec.vecAmount());
}

void vortexMath::Vec3x4::operator+=(const vortexMath::Vec3x4& vec)
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5;
    for(int i = 0; i < size(); i+=12)
    {
        xmm0 = _mm_load_ps((float* ) data()     + i + 0);
        xmm1 = _mm_load_ps((float* ) data()     + i + 4);
        xmm2 = _mm_load_ps((float* ) data()     + i + 8);
        xmm3 = _mm_load_ps((float* ) vec.data() + i + 0);
        xmm4 = _mm_load_ps((float* ) vec.data() + i + 4);
        xmm5 = _mm_load_ps((float* ) vec.data() + i + 8);
        xmm0 = _mm_add_ps(xmm0, xmm3);
        xmm1 = _mm_add_ps(xmm1, xmm4);
        xmm2 = _mm_add_ps(xmm2, xmm5);
        _mm_store_ps((float* ) data() + i + 0, xmm0);
        _mm_store_ps((float* ) data() + i + 4, xmm1);
        _mm_store_ps((float* ) data() + i + 8, xmm2);
    }
}

void vortexMath::Vec3x4::operator-=(const vortexMath::Vec3x4& vec)
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5;
    for(int i = 0; i < size(); i+=12)
    {
        xmm0 = _mm_load_ps((float* ) data()     + i + 0);
        xmm1 = _mm_load_ps((float* ) data()     + i + 4);
        xmm2 = _mm_load_ps((float* ) data()     + i + 8);
        xmm3 = _mm_load_ps((float* ) vec.data() + i + 0);
        xmm4 = _mm_load_ps((float* ) vec.data() + i + 4);
        xmm5 = _mm_load_ps((float* ) vec.data() + i + 8);
        xmm0 = _mm_sub_ps(xmm0, xmm3);
        xmm1 = _mm_sub_ps(xmm1, xmm4);
        xmm2 = _mm_sub_ps(xmm2, xmm5);
        _mm_store_ps((float* ) data() + i + 0, xmm0);
        _mm_store_ps((float* ) data() + i + 4, xmm1);
        _mm_store_ps((float* ) data() + i + 8, xmm2);
    }
}

void vortexMath::Vec3x4::operator<<=(const vortexMath::Vec3x4& vec)
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5;
    for(int i = 0; i < size(); i+=12)
    {
        xmm0 = _mm_load_ps((float* ) data()     + i + 0);
        xmm1 = _mm_load_ps((float* ) data()     + i + 4);
        xmm2 = _mm_load_ps((float* ) data()     + i + 8);
        xmm3 = _mm_load_ps((float* ) vec.data() + i + 0);
        xmm4 = _mm_load_ps((float* ) vec.data() + i + 4);
        xmm5 = _mm_load_ps((float* ) vec.data() + i + 8);
        xmm0 = _mm_mul_ps(xmm0, xmm3);
        xmm1 = _mm_mul_ps(xmm1, xmm4);
        xmm2 = _mm_mul_ps(xmm2, xmm5);
        _mm_store_ps((float* ) data() + i + 0, xmm0);
        _mm_store_ps((float* ) data() + i + 4, xmm1);
        _mm_store_ps((float* ) data() + i + 8, xmm2);
    }
}

void vortexMath::Vec3x4::operator>>=(const vortexMath::Vec3x4& vec)
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5;
    for(int i = 0; i < size(); i+=12)
    {
        xmm0 = _mm_load_ps((float* ) data()     + i + 0);
        xmm1 = _mm_load_ps((float* ) data()     + i + 4);
        xmm2 = _mm_load_ps((float* ) data()     + i + 8);
        xmm3 = _mm_load_ps((float* ) vec.data() + i + 0);
        xmm4 = _mm_load_ps((float* ) vec.data() + i + 4);
        xmm5 = _mm_load_ps((float* ) vec.data() + i + 8);
        xmm0 = _mm_div_ps(xmm0, xmm3);
        xmm1 = _mm_div_ps(xmm1, xmm4);
        xmm2 = _mm_div_ps(xmm2, xmm5);
        _mm_store_ps((float* ) data() + i + 0, xmm0);
        _mm_store_ps((float* ) data() + i + 4, xmm1);
        _mm_store_ps((float* ) data() + i + 8, xmm2);
    }
}

void vortexMath::Vec3x4::operator*=(const float value)
{
    __m128 xmm0, xmm1, xmm2, xmm3;
    xmm3 = _mm_set1_ps(value);
    for(int i = 0; i < size(); i+=12)
    {
        xmm0 = _mm_load_ps((float* ) data() + i + 0);
        xmm1 = _mm_load_ps((float* ) data() + i + 4);
        xmm2 = _mm_load_ps((float* ) data() + i + 8);
        xmm0 = _mm_mul_ps(xmm0, xmm3);
        xmm1 = _mm_mul_ps(xmm1, xmm3);
        xmm2 = _mm_mul_ps(xmm2, xmm3);
        _mm_store_ps((float* ) data() + i + 0, xmm0);
        _mm_store_ps((float* ) data() + i + 4, xmm1);
        _mm_store_ps((float* ) data() + i + 8, xmm2);
    }
}

void vortexMath::Vec3x4::operator%=(const vortexMath::Vec3x4& vec)
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7, xmm8;

    for (int i = 0; i < size(); i+=12)
    {
        xmm0 = _mm_load_ps((float* ) data()     + i + 0);
        xmm1 = _mm_load_ps((float* ) data()     + i + 4);
        xmm2 = _mm_load_ps((float* ) data()     + i + 8);
        xmm3 = _mm_load_ps((float* ) vec.data() + i + 0);
        xmm4 = _mm_load_ps((float* ) vec.data() + i + 4);
        xmm5 = _mm_load_ps((float* ) vec.data() + i + 8);
        xmm6 = _mm_mul_ps(xmm2, xmm4);
        xmm7 = _mm_mul_ps(xmm0, xmm5);
        xmm8 = _mm_mul_ps(xmm1, xmm3);
        xmm6 = _mm_fmsub_ps(xmm1, xmm5, xmm6);
        xmm7 = _mm_fmsub_ps(xmm2, xmm3, xmm7);
        xmm8 = _mm_fmsub_ps(xmm0, xmm4, xmm8);
        _mm_store_ps((float* ) data() + i + 0, xmm6);
        _mm_store_ps((float* ) data() + i + 4, xmm7);
        _mm_store_ps((float* ) data() + i + 8, xmm8);
    }
}

vortexMath::Vec3x4 vortexMath::Vec3x4::operator+(const vortexMath::Vec3x4& vec) const
{
    float * ret = (float* ) aligned_alloc(16, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5;
    for(int i = 0; i < size(); i+=12)
    {
        xmm0 = _mm_load_ps((float* ) data()     + i + 0);
        xmm1 = _mm_load_ps((float* ) data()     + i + 4);
        xmm2 = _mm_load_ps((float* ) data()     + i + 8);
        xmm3 = _mm_load_ps((float* ) vec.data() + i + 0);
        xmm4 = _mm_load_ps((float* ) vec.data() + i + 4);
        xmm5 = _mm_load_ps((float* ) vec.data() + i + 8);
        xmm0 = _mm_add_ps(xmm0, xmm3);
        xmm1 = _mm_add_ps(xmm1, xmm4);
        xmm2 = _mm_add_ps(xmm2, xmm5);
        _mm_store_ps((float* ) ret + i + 0, xmm0);
        _mm_store_ps((float* ) ret + i + 4, xmm1);
        _mm_store_ps((float* ) ret + i + 8, xmm2);
    }
    Vec3x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec3x4 vortexMath::Vec3x4::operator-(const vortexMath::Vec3x4& vec) const
{
    float * ret = (float* ) aligned_alloc(16, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5;
    for(int i = 0; i < size(); i+=12)
    {
        xmm0 = _mm_load_ps((float* ) data()     + i + 0);
        xmm1 = _mm_load_ps((float* ) data()     + i + 4);
        xmm2 = _mm_load_ps((float* ) data()     + i + 8);
        xmm3 = _mm_load_ps((float* ) vec.data() + i + 0);
        xmm4 = _mm_load_ps((float* ) vec.data() + i + 4);
        xmm5 = _mm_load_ps((float* ) vec.data() + i + 8);
        xmm0 = _mm_sub_ps(xmm0, xmm3);
        xmm1 = _mm_sub_ps(xmm1, xmm4);
        xmm2 = _mm_sub_ps(xmm2, xmm5);
        _mm_store_ps((float* ) ret + i + 0, xmm0);
        _mm_store_ps((float* ) ret + i + 4, xmm1);
        _mm_store_ps((float* ) ret + i + 8, xmm2);
    }
    Vec3x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec3x4 vortexMath::Vec3x4::operator<<(const vortexMath::Vec3x4& vec) const
{
    float * ret = (float* ) aligned_alloc(16, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5;
    for(int i = 0; i < size(); i+=12)
    {
        xmm0 = _mm_load_ps((float* ) data()     + i + 0);
        xmm1 = _mm_load_ps((float* ) data()     + i + 4);
        xmm2 = _mm_load_ps((float* ) data()     + i + 8);
        xmm3 = _mm_load_ps((float* ) vec.data() + i + 0);
        xmm4 = _mm_load_ps((float* ) vec.data() + i + 4);
        xmm5 = _mm_load_ps((float* ) vec.data() + i + 8);
        xmm0 = _mm_mul_ps(xmm0, xmm3);
        xmm1 = _mm_mul_ps(xmm1, xmm4);
        xmm2 = _mm_mul_ps(xmm2, xmm5);
        _mm_store_ps((float* ) ret + i + 0, xmm0);
        _mm_store_ps((float* ) ret + i + 4, xmm1);
        _mm_store_ps((float* ) ret + i + 8, xmm2);
    }
    Vec3x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec3x4 vortexMath::Vec3x4::operator>>(const vortexMath::Vec3x4& vec) const
{
    float * ret = (float* ) aligned_alloc(16, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5;
    for(int i = 0; i < size(); i+=12)
    {
        xmm0 = _mm_load_ps((float* ) data()     + i + 0);
        xmm1 = _mm_load_ps((float* ) data()     + i + 4);
        xmm2 = _mm_load_ps((float* ) data()     + i + 8);
        xmm3 = _mm_load_ps((float* ) vec.data() + i + 0);
        xmm4 = _mm_load_ps((float* ) vec.data() + i + 4);
        xmm5 = _mm_load_ps((float* ) vec.data() + i + 8);
        xmm0 = _mm_div_ps(xmm0, xmm3);
        xmm1 = _mm_div_ps(xmm1, xmm4);
        xmm2 = _mm_div_ps(xmm2, xmm5);
        _mm_store_ps((float* ) ret + i + 0, xmm0);
        _mm_store_ps((float* ) ret + i + 4, xmm1);
        _mm_store_ps((float* ) ret + i + 8, xmm2);
    }
    Vec3x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec3x4 vortexMath::Vec3x4::operator*(const float value) const
{
    float * ret = (float* ) aligned_alloc(16, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3;
    xmm3 = _mm_set1_ps(value);
    for(int i = 0; i < size(); i+=12)
    {
        xmm0 = _mm_load_ps((float* ) data() + i + 0);
        xmm1 = _mm_load_ps((float* ) data() + i + 4);
        xmm2 = _mm_load_ps((float* ) data() + i + 8);
        xmm0 = _mm_mul_ps(xmm0, xmm3);
        xmm1 = _mm_mul_ps(xmm1, xmm3);
        xmm2 = _mm_mul_ps(xmm2, xmm3);
        _mm_store_ps((float* ) ret + i + 0, xmm0);
        _mm_store_ps((float* ) ret + i + 4, xmm1);
        _mm_store_ps((float* ) ret + i + 8, xmm2);
    }
    Vec3x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::AlignedVector<float, 16> vortexMath::Vec3x4::operator*(const vortexMath::Vec3x4& vec) const
{
    vortexMath::AlignedVector<float, 16> retVec(vecAmount());
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5;
    for(int i = 0; i < vecAmount(); i+=4)
    {
        xmm0 = _mm_load_ps((float* ) data() + (i * 3) +  0);
        xmm1 = _mm_load_ps((float* ) data() + (i * 3) +  4);
        xmm2 = _mm_load_ps((float* ) data() + (i * 3) +  8);
        xmm3 = _mm_load_ps((float* ) vec.data() + (i * 3) +  0);
        xmm4 = _mm_load_ps((float* ) vec.data() + (i * 3) +  4);
        xmm5 = _mm_load_ps((float* ) vec.data() + (i * 3) +  8);
        xmm0 = _mm_mul_ps(xmm0, xmm3);
        xmm1 = _mm_fmadd_ps(xmm1, xmm4, xmm0);
        xmm2 = _mm_fmadd_ps(xmm2, xmm5, xmm1);
        _mm_store_ps((float* ) retVec.data() + i, xmm2);

    }
    return retVec;
}


vortexMath::Vec3x4 vortexMath::Vec3x4::operator%(const vortexMath::Vec3x4& vec) const
{
    float * ret = (float* ) aligned_alloc(32, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7, xmm8;
    for (int i = 0; i < size(); i+=12)
    {
        xmm0 = _mm_load_ps((float* ) data()     + i + 0);
        xmm1 = _mm_load_ps((float* ) data()     + i + 4);
        xmm2 = _mm_load_ps((float* ) data()     + i + 8);
        xmm3 = _mm_load_ps((float* ) vec.data() + i + 0);
        xmm4 = _mm_load_ps((float* ) vec.data() + i + 4);
        xmm5 = _mm_load_ps((float* ) vec.data() + i + 8);
        xmm6 = _mm_mul_ps(xmm2, xmm4);
        xmm7 = _mm_mul_ps(xmm0, xmm5);
        xmm8 = _mm_mul_ps(xmm1, xmm3);
        xmm6 = _mm_fmsub_ps(xmm1, xmm5, xmm6);
        xmm7 = _mm_fmsub_ps(xmm2, xmm3, xmm7);
        xmm8 = _mm_fmsub_ps(xmm0, xmm4, xmm8);
        _mm_store_ps((float* ) ret + i + 0, xmm6);
        _mm_store_ps((float* ) ret + i + 4, xmm7);
        _mm_store_ps((float* ) ret + i + 8, xmm8);
    }
    Vec3x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::AlignedVector<float, 16> vortexMath::Vec3x4::magnitude() const
{
    vortexMath::AlignedVector<float, 16> retVec(vecAmount());
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4;
    xmm4 = _mm_set1_ps(1.0f);
    for(int i = 0; i < vecAmount(); i+=4)
    {
        xmm0 = _mm_load_ps((float* ) data() + (i * 3) + 0);
        xmm1 = _mm_load_ps((float* ) data() + (i * 3) + 4);
        xmm2 = _mm_load_ps((float* ) data() + (i * 3) + 8);
        xmm3 = _mm_mul_ps(xmm2, xmm2);
        xmm3 = _mm_fmadd_ps(xmm1, xmm1, xmm3);
        xmm3 = _mm_fmadd_ps(xmm0, xmm0, xmm3);
        xmm3 = _mm_sqrt_ps(xmm3);
        _mm_store_ps((float* ) retVec.data() + i, xmm3);
    }
    return retVec;
}

vortexMath::AlignedVector<float, 16> vortexMath::Vec3x4::squareMagnitude() const
{
    vortexMath::AlignedVector<float, 16> retVec(vecAmount());
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4;
    xmm4 = _mm_set1_ps(1.0f);
    for(int i = 0; i < vecAmount(); i+=4)
    {
        xmm0 = _mm_load_ps((float* ) data() + (i * 3) + 0);
        xmm1 = _mm_load_ps((float* ) data() + (i * 3) + 4);
        xmm2 = _mm_load_ps((float* ) data() + (i * 3) + 8);
        xmm3 = _mm_mul_ps(xmm2, xmm2);
        xmm3 = _mm_fmadd_ps(xmm1, xmm1, xmm3);
        xmm3 = _mm_fmadd_ps(xmm0, xmm0, xmm3);
        _mm_store_ps((float* ) retVec.data() + i, xmm3);
    }
    return retVec;
}

void vortexMath::Vec3x4::normalize()
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4;
    xmm4 = _mm_set1_ps(1.0f);
    for(int i = 0; i < size(); i+=12)
    {
        xmm0 = _mm_load_ps((float* ) data() + i + 0);
        xmm1 = _mm_load_ps((float* ) data() + i + 4);
        xmm2 = _mm_load_ps((float* ) data() + i + 8);
        xmm3 = _mm_mul_ps(xmm2, xmm2);
        xmm3 = _mm_fmadd_ps(xmm1, xmm1, xmm3);
        xmm3 = _mm_fmadd_ps(xmm0, xmm0, xmm3);
        xmm3 = _mm_sqrt_ps(xmm3);
        xmm3 = _mm_div_ps(xmm4, xmm3);
        xmm0 = _mm_mul_ps(xmm0, xmm3);
        xmm1 = _mm_mul_ps(xmm1, xmm3);
        xmm2 = _mm_mul_ps(xmm2, xmm3);
        _mm_store_ps((float* ) data() + i + 0, xmm0);
        _mm_store_ps((float* ) data() + i + 4, xmm1);
        _mm_store_ps((float* ) data() + i + 8, xmm2);
    }
}

void vortexMath::Vec3x4::addScaledVector(const vortexMath::Vec3x4& vec, float scale)
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6;
    xmm6 = _mm_set1_ps(scale);
    for(int i = 0; i < size(); i+=12)
    {
        xmm0 = _mm_load_ps((float* ) data() + i + 0);
        xmm1 = _mm_load_ps((float* ) data() + i + 4);
        xmm2 = _mm_load_ps((float* ) data() + i + 8);
        xmm3 = _mm_load_ps((float* ) vec.data() + i + 0);
        xmm4 = _mm_load_ps((float* ) vec.data() + i + 4);
        xmm5 = _mm_load_ps((float* ) vec.data() + i + 8);
        xmm0 = _mm_fmadd_ps(xmm3, xmm6, xmm0);
        xmm1 = _mm_fmadd_ps(xmm4, xmm6, xmm1);
        xmm2 = _mm_fmadd_ps(xmm5, xmm6, xmm2);
        _mm_store_ps((float* ) data() + i + 0, xmm0);
        _mm_store_ps((float* ) data() + i + 4, xmm1);
        _mm_store_ps((float* ) data() + i + 8, xmm2);
    }
}

void vortexMath::Vec3x4::generateOrthonormalBasis(const int endIndex)
{
    float x = *(&vecData[endIndex +  0]);
    float y = *(&vecData[endIndex +  8]);
    float z = *(&vecData[endIndex + 16]);

    float sign = std::copysignf(1.0f, z);
        
    const float a = -1.0f / (sign + z);
    const float b = y * y * a;
        
    *(&vecData[endIndex -  2]) = 1.0f + sign * x * x * a;
    *(&vecData[endIndex +  6]) = sign * b;
    *(&vecData[endIndex + 14]) = -sign * x;

    *(&vecData[endIndex -  1]) = b;
    *(&vecData[endIndex +  7]) = sign + y * y * a;
    *(&vecData[endIndex + 15]) = -y;
}

void vortexMath::Vec3x4::convertToSOA()
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4;

    for (int i = 0; i < size(); i+=12)
    {
        xmm0 = _mm_load_ps((float* ) data() + i + 0);
        xmm1 = _mm_load_ps((float* ) data() + i + 4);
        xmm2 = _mm_load_ps((float* ) data() + i + 8);
        xmm3 = _mm_shuffle_ps(xmm0, xmm1, 0b01001001);
        xmm4 = _mm_shuffle_ps(xmm1, xmm2, 0b10011110);
        xmm0 = _mm_shuffle_ps(xmm0, xmm4, 0b10001100);
        xmm2 = _mm_shuffle_ps(xmm3, xmm2, 0b11001101);
        xmm1 = _mm_shuffle_ps(xmm3, xmm4, 0b11011000);
        _mm_store_ps((float* ) data() + i + 0, xmm0);
        _mm_store_ps((float* ) data() + i + 4, xmm1);
        _mm_store_ps((float* ) data() + i + 8, xmm2);
    }
}

void vortexMath::Vec3x4::convertToAOS()
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5;

    for (int i = 0; i < size(); i+=12)
    {
        xmm0 = _mm_load_ps((float* ) data() + i + 0);
        xmm1 = _mm_load_ps((float* ) data() + i + 4);
        xmm2 = _mm_load_ps((float* ) data() + i + 8);
        xmm3 = _mm_shuffle_ps(xmm0, xmm1, 0b10001000); //evenX evenY
        xmm4 = _mm_shuffle_ps(xmm2, xmm0, 0b11011000); //evenZ oddX
        xmm5 = _mm_shuffle_ps(xmm2, xmm1, 0b11011101); //oddZ  oddY
        xmm0 = _mm_shuffle_ps(xmm3, xmm4, 0b10001000); //0 3
        xmm1 = _mm_shuffle_ps(xmm5, xmm3, 0b11010010); //1 4
        xmm2 = _mm_shuffle_ps(xmm4, xmm5, 0b01111101); //2 5
        _mm_store_ps((float* ) data() + i + 0, xmm0);
        _mm_store_ps((float* ) data() + i + 4, xmm1);
        _mm_store_ps((float* ) data() + i + 8, xmm2);
    }
}

vortexMath::Vec3x4 vortexMath::Vec3x4::retrieveSOAForm() const
{
    float * ret = (float*) aligned_alloc(16, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4;
    for (int i = 0; i < size(); i+=12)
    {
        xmm0 = _mm_load_ps((float* ) data() + i + 0);
        xmm1 = _mm_load_ps((float* ) data() + i + 4);
        xmm2 = _mm_load_ps((float* ) data() + i + 8);
        xmm3 = _mm_shuffle_ps(xmm0, xmm1, 0b01001001);
        xmm4 = _mm_shuffle_ps(xmm1, xmm2, 0b10011110);
        xmm0 = _mm_shuffle_ps(xmm0, xmm4, 0b10001100);
        xmm2 = _mm_shuffle_ps(xmm3, xmm2, 0b11001101);
        xmm1 = _mm_shuffle_ps(xmm3, xmm4, 0b11011000);
        _mm_store_ps((float* ) ret + i + 0, xmm0);
        _mm_store_ps((float* ) ret + i + 4, xmm1);
        _mm_store_ps((float* ) ret + i + 8, xmm2);
    }
    Vec3x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec3x4 vortexMath::Vec3x4::retrieveAOSForm() const
{
    float * ret = (float*) aligned_alloc(16, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5;
    for (int i = 0; i < size(); i+=12)
    {
        xmm0 = _mm_load_ps((float* ) data() + i + 0);
        xmm1 = _mm_load_ps((float* ) data() + i + 4);
        xmm2 = _mm_load_ps((float* ) data() + i + 8);
        xmm3 = _mm_shuffle_ps(xmm0, xmm1, 0b10001000); //evenX evenY
        xmm4 = _mm_shuffle_ps(xmm2, xmm0, 0b11011000); //evenZ oddX
        xmm5 = _mm_shuffle_ps(xmm2, xmm1, 0b11011101); //oddZ  oddY
        xmm0 = _mm_shuffle_ps(xmm3, xmm4, 0b10001000); //0 3
        xmm1 = _mm_shuffle_ps(xmm5, xmm3, 0b11010010); //1 4
        xmm2 = _mm_shuffle_ps(xmm4, xmm5, 0b01111101); //2 5
        _mm_store_ps((float* ) ret + i + 0, xmm0);
        _mm_store_ps((float* ) ret + i + 4, xmm1);
        _mm_store_ps((float* ) ret + i + 8, xmm2);
    }
    Vec3x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::AlignedVector<float, 16> vortexMath::Vec3x4::get(const vortexMath::VecElementType t) const
{
    vortexMath::AlignedVector<float, 16> retVec(vecAmount());
    for(int i = 0; i < vecAmount(); i+=4)
    {
        _mm_store_ps((float* ) retVec.data() + i, _mm_load_ps((float* ) data() + (i * 3) + t));
    }
    return retVec;
}


void vortexMath::Vec3x4::set(const vortexMath::VecElementType t, float val)
{
    __m128 xmm0 = _mm_set1_ps(val);
    for(int i = 0; i < vecAmount(); i+=4)
    {
        _mm_store_ps((float* ) data() + (i * 3) + t, xmm0);
    }
}

void vortexMath::Vec3x4::set(const vortexMath::VecElementType t, const vortexMath::AlignedVector<float, 16>& values)
{
    for(int i = 0; i < vecAmount(); i+=4)
    {
        _mm_store_ps((float* ) data() + (i * 3) + t, _mm_load_ps((float* ) values.data() + i));
    }
}

vortexMath::Vec4x4::Vec4x4(const int vectors)
{
    if (vectors < 4) return; 
    vecData.reserve(vectors * 4);
    vecCount = vectors; 
}

vortexMath::Vec4x4::Vec4x4(const float* data, int vectors)
{
    if (vectors < 4) return;
    vecData.insert(ITERATOR_BEGIN, 0, data, vectors * 4);
    vecCount = vectors; 
}

vortexMath::Vec4x4::Vec4x4(const float value, int vectors)
{
    if (vectors < 4) return;
    vecData.insert(ITERATOR_BEGIN, 0, std::vector<float>(vectors * 4, value));
    vecCount = vectors; 
}

vortexMath::Vec4x4::Vec4x4(const AlignedVector<float, 16>& x, const AlignedVector<float, 16>& y, const AlignedVector<float, 16>& z, const AlignedVector<float, 16>& w, const int vectors)
{
    if (vectors < 4) return;
    vecData.reserve(vectors * 4);
    vecCount = vectors;
    __m128 xmm0, xmm1, xmm2, xmm3;
    for (int i = 0; i < vecAmount(); i+=4)
    {
        xmm0 = _mm_load_ps((float* ) x.data() + i);
        xmm1 = _mm_load_ps((float* ) y.data() + i);
        xmm2 = _mm_load_ps((float* ) z.data() + i);
        xmm3 = _mm_load_ps((float* ) w.data() + i);
        
        _mm_store_ps((float* ) vecData.data() + (i * 4) +  0, xmm0);
        _mm_store_ps((float* ) vecData.data() + (i * 4) +  4, xmm1);
        _mm_store_ps((float* ) vecData.data() + (i * 4) +  8, xmm2);
        _mm_store_ps((float* ) vecData.data() + (i * 4) + 12, xmm3);
    }
}

vortexMath::Vec4x4 vortexMath::Vec4x4::vec4x4(const vortexMath::Vec2x4& vec, const vortexMath::AlignedVector<float, 16>& z, const vortexMath::AlignedVector<float, 16>& w)
{
    return Vec4x4(vec.get(VEC_ELEMENT_X), vec.get(VEC_ELEMENT_Y), z, w, vec.vecAmount());
}

vortexMath::Vec4x4 vortexMath::Vec4x4::vec4x4(const vortexMath::Vec3x4& vec, const vortexMath::AlignedVector<float, 16>& w)
{
    return Vec4x4(vec.get(VEC_ELEMENT_X), vec.get(VEC_ELEMENT_Y), vec.get(VEC_ELEMENT_Z), w, vec.vecAmount());
}

void vortexMath::Vec4x4::operator+=(const vortexMath::Vec4x4& vec)
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;
    for(int i = 0; i < size(); i+=16)
    {
        xmm0 = _mm_load_ps((float* ) data() + i +  0);
        xmm1 = _mm_load_ps((float* ) data() + i +  4);
        xmm2 = _mm_load_ps((float* ) data() + i +  8);
        xmm3 = _mm_load_ps((float* ) data() + i + 12);
        xmm4 = _mm_load_ps((float* ) vec.data() + i +  0);
        xmm5 = _mm_load_ps((float* ) vec.data() + i +  4);
        xmm6 = _mm_load_ps((float* ) vec.data() + i +  8);
        xmm7 = _mm_load_ps((float* ) vec.data() + i + 12);
        xmm0 = _mm_add_ps(xmm0, xmm4);
        xmm1 = _mm_add_ps(xmm1, xmm5);
        xmm2 = _mm_add_ps(xmm2, xmm6);
        xmm3 = _mm_add_ps(xmm3, xmm7);
        _mm_store_ps((float* ) data() + i +  0, xmm0);
        _mm_store_ps((float* ) data() + i +  4, xmm1);
        _mm_store_ps((float* ) data() + i +  8, xmm2);
        _mm_store_ps((float* ) data() + i + 12, xmm3);
    }
}

void vortexMath::Vec4x4::operator-=(const vortexMath::Vec4x4& vec)
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;
    for(int i = 0; i < size(); i+=16)
    {
        xmm0 = _mm_load_ps((float* ) data() + i +  0);
        xmm1 = _mm_load_ps((float* ) data() + i +  4);
        xmm2 = _mm_load_ps((float* ) data() + i +  8);
        xmm3 = _mm_load_ps((float* ) data() + i + 12);
        xmm4 = _mm_load_ps((float* ) vec.data() + i +  0);
        xmm5 = _mm_load_ps((float* ) vec.data() + i +  4);
        xmm6 = _mm_load_ps((float* ) vec.data() + i +  8);
        xmm7 = _mm_load_ps((float* ) vec.data() + i + 12);
        xmm0 = _mm_sub_ps(xmm0, xmm4);
        xmm1 = _mm_sub_ps(xmm1, xmm5);
        xmm2 = _mm_sub_ps(xmm2, xmm6);
        xmm3 = _mm_sub_ps(xmm3, xmm7);
        _mm_store_ps((float* ) data() + i +  0, xmm0);
        _mm_store_ps((float* ) data() + i +  4, xmm1);
        _mm_store_ps((float* ) data() + i +  8, xmm2);
        _mm_store_ps((float* ) data() + i + 12, xmm3);
    }
}

void vortexMath::Vec4x4::operator<<=(const vortexMath::Vec4x4& vec)
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;
    for(int i = 0; i < size(); i+=16)
    {
        xmm0 = _mm_load_ps((float* ) data() + i +  0);
        xmm1 = _mm_load_ps((float* ) data() + i +  4);
        xmm2 = _mm_load_ps((float* ) data() + i +  8);
        xmm3 = _mm_load_ps((float* ) data() + i + 12);
        xmm4 = _mm_load_ps((float* ) vec.data() + i +  0);
        xmm5 = _mm_load_ps((float* ) vec.data() + i +  4);
        xmm6 = _mm_load_ps((float* ) vec.data() + i +  8);
        xmm7 = _mm_load_ps((float* ) vec.data() + i + 12);
        xmm0 = _mm_mul_ps(xmm0, xmm4);
        xmm1 = _mm_mul_ps(xmm1, xmm5);
        xmm2 = _mm_mul_ps(xmm2, xmm6);
        xmm3 = _mm_mul_ps(xmm3, xmm7);
        _mm_store_ps((float* ) data() + i +  0, xmm0);
        _mm_store_ps((float* ) data() + i +  4, xmm1);
        _mm_store_ps((float* ) data() + i +  8, xmm2);
        _mm_store_ps((float* ) data() + i + 12, xmm3);
    }
}

void vortexMath::Vec4x4::operator>>=(const vortexMath::Vec4x4& vec)
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;
    for(int i = 0; i < size(); i+=16)
    {
        xmm0 = _mm_load_ps((float* ) data() + i +  0);
        xmm1 = _mm_load_ps((float* ) data() + i +  4);
        xmm2 = _mm_load_ps((float* ) data() + i +  8);
        xmm3 = _mm_load_ps((float* ) data() + i + 12);
        xmm4 = _mm_load_ps((float* ) vec.data() + i +  0);
        xmm5 = _mm_load_ps((float* ) vec.data() + i +  4);
        xmm6 = _mm_load_ps((float* ) vec.data() + i +  8);
        xmm7 = _mm_load_ps((float* ) vec.data() + i + 12);
        xmm0 = _mm_div_ps(xmm0, xmm4);
        xmm1 = _mm_div_ps(xmm1, xmm5);
        xmm2 = _mm_div_ps(xmm2, xmm6);
        xmm3 = _mm_div_ps(xmm3, xmm7);
        _mm_store_ps((float* ) data() + i +  0, xmm0);
        _mm_store_ps((float* ) data() + i +  4, xmm1);
        _mm_store_ps((float* ) data() + i +  8, xmm2);
        _mm_store_ps((float* ) data() + i + 12, xmm3);
    }
}

void vortexMath::Vec4x4::operator*=(const float value)
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4;
    xmm4 = _mm_set1_ps(value);
    for(int i = 0; i < size(); i+=16)
    {
        xmm0 = _mm_load_ps((float* ) data() + i +  0);
        xmm1 = _mm_load_ps((float* ) data() + i +  4);
        xmm2 = _mm_load_ps((float* ) data() + i +  8);
        xmm3 = _mm_load_ps((float* ) data() + i + 12);
        xmm0 = _mm_mul_ps(xmm0, xmm4);
        xmm1 = _mm_mul_ps(xmm1, xmm4);
        xmm2 = _mm_mul_ps(xmm2, xmm4);
        xmm3 = _mm_mul_ps(xmm3, xmm4);
        _mm_store_ps((float* ) data() + i +  0, xmm0);
        _mm_store_ps((float* ) data() + i +  4, xmm1);
        _mm_store_ps((float* ) data() + i +  8, xmm2);
        _mm_store_ps((float* ) data() + i + 12, xmm3);
    }
}
vortexMath::Vec4x4 vortexMath::Vec4x4::operator+(const vortexMath::Vec4x4& vec) const
{
    float * ret = (float* ) aligned_alloc(16, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;
    for(int i = 0; i < size(); i+=16)
    {
        xmm0 = _mm_load_ps((float* ) data() + i +  0);
        xmm1 = _mm_load_ps((float* ) data() + i +  4);
        xmm2 = _mm_load_ps((float* ) data() + i +  8);
        xmm3 = _mm_load_ps((float* ) data() + i + 12);
        xmm4 = _mm_load_ps((float* ) vec.data() + i +  0);
        xmm5 = _mm_load_ps((float* ) vec.data() + i +  4);
        xmm6 = _mm_load_ps((float* ) vec.data() + i +  8);
        xmm7 = _mm_load_ps((float* ) vec.data() + i + 12);
        xmm0 = _mm_add_ps(xmm0, xmm4);
        xmm1 = _mm_add_ps(xmm1, xmm5);
        xmm2 = _mm_add_ps(xmm2, xmm6);
        xmm3 = _mm_add_ps(xmm3, xmm7);
        _mm_store_ps((float* ) ret + i +  0, xmm0);
        _mm_store_ps((float* ) ret + i +  4, xmm1);
        _mm_store_ps((float* ) ret + i +  8, xmm2);
        _mm_store_ps((float* ) ret + i + 12, xmm3);
    }
    Vec4x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec4x4 vortexMath::Vec4x4::operator-(const vortexMath::Vec4x4& vec) const
{
    float * ret = (float* ) aligned_alloc(16, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;
    for(int i = 0; i < size(); i+=16)
    {
        xmm0 = _mm_load_ps((float* ) data() + i +  0);
        xmm1 = _mm_load_ps((float* ) data() + i +  4);
        xmm2 = _mm_load_ps((float* ) data() + i +  8);
        xmm3 = _mm_load_ps((float* ) data() + i + 12);
        xmm4 = _mm_load_ps((float* ) vec.data() + i +  0);
        xmm5 = _mm_load_ps((float* ) vec.data() + i +  4);
        xmm6 = _mm_load_ps((float* ) vec.data() + i +  8);
        xmm7 = _mm_load_ps((float* ) vec.data() + i + 12);
        xmm0 = _mm_sub_ps(xmm0, xmm4);
        xmm1 = _mm_sub_ps(xmm1, xmm5);
        xmm2 = _mm_sub_ps(xmm2, xmm6);
        xmm3 = _mm_sub_ps(xmm3, xmm7);
        _mm_store_ps((float* ) ret + i +  0, xmm0);
        _mm_store_ps((float* ) ret + i +  4, xmm1);
        _mm_store_ps((float* ) ret + i +  8, xmm2);
        _mm_store_ps((float* ) ret + i + 12, xmm3);
    }
    Vec4x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec4x4 vortexMath::Vec4x4::operator<<(const vortexMath::Vec4x4& vec) const
{
    float * ret = (float* ) aligned_alloc(16, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;
    for(int i = 0; i < size(); i+=16)
    {
        xmm0 = _mm_load_ps((float* ) data() + i +  0);
        xmm1 = _mm_load_ps((float* ) data() + i +  4);
        xmm2 = _mm_load_ps((float* ) data() + i +  8);
        xmm3 = _mm_load_ps((float* ) data() + i + 12);
        xmm4 = _mm_load_ps((float* ) vec.data() + i +  0);
        xmm5 = _mm_load_ps((float* ) vec.data() + i +  4);
        xmm6 = _mm_load_ps((float* ) vec.data() + i +  8);
        xmm7 = _mm_load_ps((float* ) vec.data() + i + 12);
        xmm0 = _mm_mul_ps(xmm0, xmm4);
        xmm1 = _mm_mul_ps(xmm1, xmm5);
        xmm2 = _mm_mul_ps(xmm2, xmm6);
        xmm3 = _mm_mul_ps(xmm3, xmm7);
        _mm_store_ps((float* ) ret + i +  0, xmm0);
        _mm_store_ps((float* ) ret + i +  4, xmm1);
        _mm_store_ps((float* ) ret + i +  8, xmm2);
        _mm_store_ps((float* ) ret + i + 12, xmm3);
    }
    Vec4x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec4x4 vortexMath::Vec4x4::operator>>(const vortexMath::Vec4x4& vec) const
{
    float * ret = (float* ) aligned_alloc(16, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;
    for(int i = 0; i < size(); i+=16)
    {
        xmm0 = _mm_load_ps((float* ) data() + i +  0);
        xmm1 = _mm_load_ps((float* ) data() + i +  4);
        xmm2 = _mm_load_ps((float* ) data() + i +  8);
        xmm3 = _mm_load_ps((float* ) data() + i + 12);
        xmm4 = _mm_load_ps((float* ) vec.data() + i +  0);
        xmm5 = _mm_load_ps((float* ) vec.data() + i +  4);
        xmm6 = _mm_load_ps((float* ) vec.data() + i +  8);
        xmm7 = _mm_load_ps((float* ) vec.data() + i + 12);
        xmm0 = _mm_div_ps(xmm0, xmm4);
        xmm1 = _mm_div_ps(xmm1, xmm5);
        xmm2 = _mm_div_ps(xmm2, xmm6);
        xmm3 = _mm_div_ps(xmm3, xmm7);
        _mm_store_ps((float* ) ret + i +  0, xmm0);
        _mm_store_ps((float* ) ret + i +  4, xmm1);
        _mm_store_ps((float* ) ret + i +  8, xmm2);
        _mm_store_ps((float* ) ret + i + 12, xmm3);
    }
    Vec4x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec4x4 vortexMath::Vec4x4::operator*(const float value) const
{
    float * ret = (float* ) aligned_alloc(16, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4;
    xmm4 = _mm_set1_ps(value);
    for(int i = 0; i < size(); i+=16)
    {
        xmm0 = _mm_load_ps((float* ) data() + i +  0);
        xmm1 = _mm_load_ps((float* ) data() + i +  4);
        xmm2 = _mm_load_ps((float* ) data() + i +  8);
        xmm3 = _mm_load_ps((float* ) data() + i + 12);
        xmm0 = _mm_mul_ps(xmm0, xmm4);
        xmm1 = _mm_mul_ps(xmm1, xmm4);
        xmm2 = _mm_mul_ps(xmm2, xmm4);
        xmm3 = _mm_mul_ps(xmm3, xmm4);
        _mm_store_ps((float* ) ret + i +  0, xmm0);
        _mm_store_ps((float* ) ret + i +  4, xmm1);
        _mm_store_ps((float* ) ret + i +  8, xmm2);
        _mm_store_ps((float* ) ret + i + 12, xmm3);
    }
    Vec4x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::AlignedVector<float, 16> vortexMath::Vec4x4::operator*(const vortexMath::Vec4x4& vec) const
{
    vortexMath::AlignedVector<float, 16> retVec(vecAmount());
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;
    for(int i = 0; i < vecAmount(); i+=4)
    {
        xmm0 = _mm_load_ps((float* ) data() + (i * 4) +  0);
        xmm1 = _mm_load_ps((float* ) data() + (i * 4) +  4);
        xmm2 = _mm_load_ps((float* ) data() + (i * 4) +  8);
        xmm3 = _mm_load_ps((float* ) data() + (i * 4) + 12);
        xmm4 = _mm_load_ps((float* ) vec.data() + (i * 4) +  0);
        xmm5 = _mm_load_ps((float* ) vec.data() + (i * 4) +  4);
        xmm6 = _mm_load_ps((float* ) vec.data() + (i * 4) +  8);
        xmm7 = _mm_load_ps((float* ) vec.data() + (i * 4) + 12);
        
        xmm0 = _mm_mul_ps(xmm0, xmm4);
        xmm1 = _mm_fmadd_ps(xmm1, xmm5, xmm0);
        xmm2 = _mm_fmadd_ps(xmm2, xmm6, xmm1);
        xmm3 = _mm_fmadd_ps(xmm3, xmm7, xmm2);
        _mm_store_ps((float* ) retVec.data() + i, xmm3);
    }
    return retVec;
}


vortexMath::AlignedVector<float, 16> vortexMath::Vec4x4::magnitude() const
{
    vortexMath::AlignedVector<float, 16> retVec(vecAmount());
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4;
    for(int i = 0; i < vecAmount(); i+=4)
    {
        xmm0 = _mm_load_ps((float* ) data() + (i * 4) +  0);
        xmm1 = _mm_load_ps((float* ) data() + (i * 4) +  4);
        xmm2 = _mm_load_ps((float* ) data() + (i * 4) +  8);
        xmm3 = _mm_load_ps((float* ) data() + (i * 4) + 12);
        xmm4 = _mm_mul_ps(xmm3, xmm3);
        xmm4 = _mm_fmadd_ps(xmm2, xmm2, xmm4);
        xmm4 = _mm_fmadd_ps(xmm1, xmm1, xmm4);
        xmm4 = _mm_fmadd_ps(xmm0, xmm0, xmm4);
        xmm4 = _mm_sqrt_ps(xmm4);
        _mm_store_ps((float* ) retVec.data() + i, xmm4);
    }
    return retVec;
}

vortexMath::AlignedVector<float, 16> vortexMath::Vec4x4::squareMagnitude() const
{
    vortexMath::AlignedVector<float, 16> retVec(vecAmount());
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4;
    for(int i = 0; i < vecAmount(); i+=4)
    {
        xmm0 = _mm_load_ps((float* ) data() + (i * 4) +  0);
        xmm1 = _mm_load_ps((float* ) data() + (i * 4) +  4);
        xmm2 = _mm_load_ps((float* ) data() + (i * 4) +  8);
        xmm3 = _mm_load_ps((float* ) data() + (i * 4) + 12);
        xmm4 = _mm_mul_ps(xmm3, xmm3);
        xmm4 = _mm_fmadd_ps(xmm2, xmm2, xmm4);
        xmm4 = _mm_fmadd_ps(xmm1, xmm1, xmm4);
        xmm4 = _mm_fmadd_ps(xmm0, xmm0, xmm4);
        _mm_store_ps((float* ) retVec.data() + i, xmm4);
    }
    return retVec;
}

void vortexMath::Vec4x4::normalize()
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5;
    xmm5 = _mm_set1_ps(1.0f);
    for(int i = 0; i < size(); i+=16)
    {
        xmm0 = _mm_load_ps((float* ) data() + i +  0);
        xmm1 = _mm_load_ps((float* ) data() + i +  4);
        xmm2 = _mm_load_ps((float* ) data() + i +  8);
        xmm3 = _mm_load_ps((float* ) data() + i + 12);
        xmm4 = _mm_mul_ps(xmm3, xmm3);
        xmm4 = _mm_fmadd_ps(xmm2, xmm2, xmm4);
        xmm4 = _mm_fmadd_ps(xmm1, xmm1, xmm4);
        xmm4 = _mm_fmadd_ps(xmm0, xmm0, xmm4);
        xmm4 = _mm_sqrt_ps(xmm4);
        xmm4 = _mm_div_ps(xmm5, xmm4);
        xmm0 = _mm_mul_ps(xmm0, xmm4);
        xmm1 = _mm_mul_ps(xmm1, xmm4);
        xmm2 = _mm_mul_ps(xmm2, xmm4);
        xmm3 = _mm_mul_ps(xmm3, xmm4);
        _mm_store_ps((float* ) data() + i +  0, xmm0);
        _mm_store_ps((float* ) data() + i +  4, xmm1);
        _mm_store_ps((float* ) data() + i +  8, xmm2);
        _mm_store_ps((float* ) data() + i + 12, xmm3);
    }
}

void vortexMath::Vec4x4::addScaledVector(const vortexMath::Vec4x4& vec, float scale)
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7, xmm8;
    xmm8 = _mm_set1_ps(scale);
    for(int i = 0; i < size(); i+=16)
    {
        xmm0 = _mm_load_ps((float* ) data() + i +  0);
        xmm1 = _mm_load_ps((float* ) data() + i +  4);
        xmm2 = _mm_load_ps((float* ) data() + i +  8);
        xmm3 = _mm_load_ps((float* ) data() + i + 12);
        xmm4 = _mm_load_ps((float* ) vec.data() + i +  0);
        xmm5 = _mm_load_ps((float* ) vec.data() + i +  4);
        xmm6 = _mm_load_ps((float* ) vec.data() + i +  8);
        xmm7 = _mm_load_ps((float* ) vec.data() + i + 12);
        xmm0 = _mm_fmadd_ps(xmm4, xmm8, xmm0);
        xmm1 = _mm_fmadd_ps(xmm5, xmm8, xmm1);
        xmm2 = _mm_fmadd_ps(xmm6, xmm8, xmm2);
        xmm3 = _mm_fmadd_ps(xmm7, xmm8, xmm3);
        _mm_store_ps((float* ) data() + i +  0, xmm0);
        _mm_store_ps((float* ) data() + i +  4, xmm1);
        _mm_store_ps((float* ) data() + i +  8, xmm2);
        _mm_store_ps((float* ) data() + i + 12, xmm3);
    }
}

void vortexMath::Vec4x4::convertToSOA()
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;
    for (int i = 0; i < size(); i+=16)
    {
        xmm0 = _mm_load_ps((float* ) data() + i +  0);
        xmm1 = _mm_load_ps((float* ) data() + i +  4);
        xmm2 = _mm_load_ps((float* ) data() + i +  8);
        xmm3 = _mm_load_ps((float* ) data() + i + 12);
        
        xmm4 = _mm_unpacklo_ps(xmm0, xmm1); //x0 x1 y0 y1  x4 x5 y4 y5
        xmm5 = _mm_unpacklo_ps(xmm2, xmm3); //x2 x3 y2 y3  x6 y6 x7 y7
        xmm6 = _mm_unpackhi_ps(xmm0, xmm1); //z0 z1 w0 w1  z4 z5 w4 w5
        xmm7 = _mm_unpackhi_ps(xmm2, xmm3); //z2 z3 w2 w3  z6 z6 w7 w7
        
        xmm0 = _mm_shuffle_ps(xmm4, xmm5, 0b01000100); //x
        xmm1 = _mm_shuffle_ps(xmm4, xmm5, 0b11101110); //y
        xmm2 = _mm_shuffle_ps(xmm6, xmm7, 0b01000100); //x
        xmm3 = _mm_shuffle_ps(xmm6, xmm7, 0b11101110); //x
        
        _mm_store_ps((float* ) data() + i +  0, xmm0);
        _mm_store_ps((float* ) data() + i +  4, xmm1);
        _mm_store_ps((float* ) data() + i +  8, xmm2);
        _mm_store_ps((float* ) data() + i + 12, xmm3);
    }
}

void vortexMath::Vec4x4::convertToAOS()
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;

    for (int i = 0; i < size(); i+=16)
    {
        xmm0 = _mm_load_ps((float* ) data() + i +  0);
        xmm1 = _mm_load_ps((float* ) data() + i +  4);
        xmm2 = _mm_load_ps((float* ) data() + i +  8);
        xmm3 = _mm_load_ps((float* ) data() + i + 12);
        
        xmm4 = _mm_unpacklo_ps(xmm0, xmm1); 
        xmm5 = _mm_unpacklo_ps(xmm2, xmm3);
        xmm6 = _mm_unpackhi_ps(xmm0, xmm1);
        xmm7 = _mm_unpackhi_ps(xmm2, xmm3);
        
        xmm0 = _mm_shuffle_ps(xmm4, xmm5, 0b01000100);
        xmm1 = _mm_shuffle_ps(xmm4, xmm5, 0b11101110);
        xmm2 = _mm_shuffle_ps(xmm6, xmm7, 0b01000100);
        xmm3 = _mm_shuffle_ps(xmm6, xmm7, 0b11101110);
        
        _mm_store_ps((float* ) data() + i +  0, xmm0);
        _mm_store_ps((float* ) data() + i +  4, xmm1);
        _mm_store_ps((float* ) data() + i +  8, xmm2);
        _mm_store_ps((float* ) data() + i + 12, xmm3);
    }
}

vortexMath::Vec4x4 vortexMath::Vec4x4::retrieveSOAForm() const
{
    float * ret = (float*) aligned_alloc(16, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;
    for (int i = 0; i < size(); i+=16)
    {
        xmm0 = _mm_load_ps((float* ) data() + i +  0);
        xmm1 = _mm_load_ps((float* ) data() + i +  4);
        xmm2 = _mm_load_ps((float* ) data() + i +  8);
        xmm3 = _mm_load_ps((float* ) data() + i + 12);
        xmm4 = _mm_unpacklo_ps(xmm0, xmm1); //x0 x1 y0 y1  x4 x5 y4 y5
        xmm5 = _mm_unpacklo_ps(xmm2, xmm3); //x2 x3 y2 y3  x6 y6 x7 y7
        xmm6 = _mm_unpackhi_ps(xmm0, xmm1); //z0 z1 w0 w1  z4 z5 w4 w5
        xmm7 = _mm_unpackhi_ps(xmm2, xmm3); //z2 z3 w2 w3  z6 z6 w7 w7
        xmm0 = _mm_shuffle_ps(xmm4, xmm5, 0b01000100); //x
        xmm1 = _mm_shuffle_ps(xmm4, xmm5, 0b11101110); //y
        xmm2 = _mm_shuffle_ps(xmm6, xmm7, 0b01000100); //x
        xmm3 = _mm_shuffle_ps(xmm6, xmm7, 0b11101110); //x
        _mm_store_ps((float* ) ret + i +  0, xmm0);
        _mm_store_ps((float* ) ret + i +  4, xmm1);
        _mm_store_ps((float* ) ret + i +  8, xmm2);
        _mm_store_ps((float* ) ret + i + 12, xmm3);
    }
    Vec4x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec4x4 vortexMath::Vec4x4::retrieveAOSForm() const
{
    float * ret = (float*) aligned_alloc(16, size() * sizeof(float));
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;
    for (int i = 0; i < size(); i+=16)
    {
        xmm0 = _mm_load_ps((float* ) data() + i +  0);
        xmm1 = _mm_load_ps((float* ) data() + i +  4);
        xmm2 = _mm_load_ps((float* ) data() + i +  8);
        xmm3 = _mm_load_ps((float* ) data() + i + 12);
        xmm4 = _mm_unpacklo_ps(xmm0, xmm1); 
        xmm5 = _mm_unpacklo_ps(xmm2, xmm3);
        xmm6 = _mm_unpackhi_ps(xmm0, xmm1);
        xmm7 = _mm_unpackhi_ps(xmm2, xmm3);
        xmm0 = _mm_shuffle_ps(xmm4, xmm5, 0b01000100);
        xmm1 = _mm_shuffle_ps(xmm4, xmm5, 0b11101110);
        xmm2 = _mm_shuffle_ps(xmm6, xmm7, 0b01000100);
        xmm3 = _mm_shuffle_ps(xmm6, xmm7, 0b11101110);
        _mm_store_ps((float* ) ret + i +  0, xmm0);
        _mm_store_ps((float* ) ret + i +  4, xmm1);
        _mm_store_ps((float* ) ret + i +  8, xmm2);
        _mm_store_ps((float* ) ret + i + 12, xmm3);
    }
    Vec4x4 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

void vortexMath::Vec4x4::generateOrthonormalBasis(const int endIndex)
{
    float x = *(&vecData[endIndex +  0]);
    float y = *(&vecData[endIndex +  8]);
    float z = *(&vecData[endIndex + 16]);

    float sign = std::copysignf(1.0f, z);
        
    const float a = -1.0f / (sign + z);
    const float b = y * y * a;
        
    *(&vecData[endIndex -  2]) = 1.0f + sign * x * x * a;
    *(&vecData[endIndex +  6]) = sign * b;
    *(&vecData[endIndex + 14]) = -sign * x;

    *(&vecData[endIndex -  1]) = b;
    *(&vecData[endIndex +  7]) = sign + y * y * a;
    *(&vecData[endIndex + 15]) = -y;
}

vortexMath::AlignedVector<float, 16> vortexMath::Vec4x4::get(const vortexMath::VecElementType t) const
{
    vortexMath::AlignedVector<float, 16> retVec(vecAmount());
    for(int i = 0; i < vecAmount(); i+=4)
    {
        _mm_store_ps((float* ) retVec.data() + i, _mm_load_ps((float* ) data() + (i * 4) + t));
    }
    return retVec;
}

void vortexMath::Vec4x4::set(const vortexMath::VecElementType t, float val)
{
    __m128 xmm0 = _mm_set1_ps(val);
    for(int i = 0; i < vecAmount(); i+=4)
    {   
        _mm_store_ps((float* ) data() + (i * 4) + t, xmm0);
    }
}

void vortexMath::Vec4x4::set(const VecElementType t, const vortexMath::AlignedVector<float, 16>& values)
{
    for(int i = 0; i < vecAmount(); i+=4)
    {
        _mm_store_ps((float* ) data() + (i * 4) + t, _mm_load_ps((float* ) values.data() + i));
    }
}

vortexMath::Vec2x8::Vec2x8(const int vectors)
{
    if (vectors < 8) return; 
    vecData.reserve(vectors * 2);
    vecCount = vectors; 
}

vortexMath::Vec2x8::Vec2x8(const float* data, int vectors)
{
    if (vectors < 8) return;
    vecData.insert(ITERATOR_BEGIN, 0, data, vectors * 2);
    vecCount = vectors; 
}

vortexMath::Vec2x8::Vec2x8(const float value, int vectors)
{
    if (vectors < 8) return;
    vecData.insert(ITERATOR_BEGIN, 0, std::vector<float>(vectors * 2, value));
    vecCount = vectors; 
}

vortexMath::Vec2x8::Vec2x8(const AlignedVector<float, 32>& x, const AlignedVector<float, 32>& y, const int vectors)
{
    if (vectors < 8) return;
    vecData.reserve(vectors * 2);
    vecCount = vectors;
    __m256 ymm0, ymm1;
    for (int i = 0; i < vecAmount(); i+=8)
    {
        ymm0 = _mm256_load_ps((float* ) x.data() + i);
        ymm1 = _mm256_load_ps((float* ) y.data() + i);
        
        _mm256_store_ps((float* ) vecData.data() + (i * 2) +  0, ymm0);
        _mm256_store_ps((float* ) vecData.data() + (i * 2) +  8, ymm1);
    }
}

vortexMath::Vec2x8 vortexMath::Vec2x8::vec2x8(const vortexMath::Vec3x8& vec)
{
    return Vec2x8(vec.get(VEC_ELEMENT_X), vec.get(VEC_ELEMENT_Y), vec.vecAmount());
}

vortexMath::Vec2x8 vortexMath::Vec2x8::vec2x8(const vortexMath::Vec4x8& vec)
{
    return Vec2x8(vec.get(VEC_ELEMENT_X), vec.get(VEC_ELEMENT_Y), vec.vecAmount());
}

vortexMath::Vec2x8 vortexMath::Vec2x8::generateVecFromArray(const float* inputBuffer, const int startIndex, const int size, const int vectors)
{
    float* ret = (float* ) aligned_alloc(32, size * sizeof(float));
            
    int offset = size / vectors;
    int space = 8 - ((vectors * 2) % 8); //Space required to fill for proper avx alignment (in elements NOT vectors)
    int retIndex = 0;
    for (int i = startIndex; i < size; i+=offset)
    {
        for (int j = 0; j < 2; j++)
        {
            ret[retIndex++] = inputBuffer[i+j];
        }
    }
    
    //Set additional elements to zero (so the array size becomes a multiple of 8)
    for (int k = 0; k < space; k++)
    {
        ret[retIndex++] = 0.0f;
    }
    Vec2x8 retVec{ ret, vectors + (space / 2) };
    free(ret);
    return retVec;
}


void vortexMath::Vec2x8::operator+=(const vortexMath::Vec2x8& vec)
{
    __m256 ymm0, ymm1, ymm2, ymm3;
    for(int i = 0; i < size(); i+=16)
    {
        ymm0 = _mm256_load_ps((float* ) data()     + i + 0);
        ymm1 = _mm256_load_ps((float* ) data()     + i + 8);
        ymm2 = _mm256_load_ps((float* ) vec.data() + i + 0);
        ymm3 = _mm256_load_ps((float* ) vec.data() + i + 8);
        ymm0 = _mm256_add_ps(ymm0, ymm2);
        ymm1 = _mm256_add_ps(ymm1, ymm3);
        _mm256_store_ps((float* ) data() + i + 0, ymm0);
        _mm256_store_ps((float* ) data() + i + 8, ymm1);
    }
}

void vortexMath::Vec2x8::operator-=(const vortexMath::Vec2x8& vec)
{
    __m256 ymm0, ymm1, ymm2, ymm3;
    for(int i = 0; i < size(); i+=16)
    {
        ymm0 = _mm256_load_ps((float* ) data()     + i + 0);
        ymm1 = _mm256_load_ps((float* ) data()     + i + 8);
        ymm2 = _mm256_load_ps((float* ) vec.data() + i + 0);
        ymm3 = _mm256_load_ps((float* ) vec.data() + i + 8);
        ymm0 = _mm256_sub_ps(ymm0, ymm2);
        ymm1 = _mm256_sub_ps(ymm1, ymm3);
        _mm256_store_ps((float* ) data() + i + 0, ymm0);
        _mm256_store_ps((float* ) data() + i + 8, ymm1);
    }
}

void vortexMath::Vec2x8::operator<<=(const vortexMath::Vec2x8& vec)
{
    __m256 ymm0, ymm1, ymm2, ymm3;
    for(int i = 0; i < size(); i+=16)
    {
        ymm0 = _mm256_load_ps((float* ) data()     + i + 0);
        ymm1 = _mm256_load_ps((float* ) data()     + i + 8);
        ymm2 = _mm256_load_ps((float* ) vec.data() + i + 0);
        ymm3 = _mm256_load_ps((float* ) vec.data() + i + 8);
        ymm0 = _mm256_mul_ps(ymm0, ymm2);
        ymm1 = _mm256_mul_ps(ymm1, ymm3);
        _mm256_store_ps((float* ) data() + i + 0, ymm0);
        _mm256_store_ps((float* ) data() + i + 8, ymm1);
    }
}

void vortexMath::Vec2x8::operator>>=(const vortexMath::Vec2x8& vec)
{
    __m256 ymm0, ymm1, ymm2, ymm3;
    for(int i = 0; i < size(); i+=16)
    {
        ymm0 = _mm256_load_ps((float* ) data()     + i + 0);
        ymm1 = _mm256_load_ps((float* ) data()     + i + 8);
        ymm2 = _mm256_load_ps((float* ) vec.data() + i + 0);
        ymm3 = _mm256_load_ps((float* ) vec.data() + i + 8);
        ymm0 = _mm256_div_ps(ymm0, ymm2);
        ymm1 = _mm256_div_ps(ymm1, ymm3);
        _mm256_store_ps((float* ) data() + i + 0, ymm0);
        _mm256_store_ps((float* ) data() + i + 8, ymm1);
    }
}

void vortexMath::Vec2x8::operator*=(const float value)
{
    __m256 ymm0, ymm1, ymm2, ymm3;
    ymm3 = _mm256_set1_ps(value);
    for(int i = 0; i < size(); i+=16)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i + 0);
        ymm1 = _mm256_load_ps((float* ) data() + i + 8);
        ymm0 = _mm256_mul_ps(ymm0, ymm3);
        ymm1 = _mm256_mul_ps(ymm1, ymm3);
        _mm256_store_ps((float* ) data() + i + 0, ymm0);
        _mm256_store_ps((float* ) data() + i + 8, ymm1);
    }
}

vortexMath::Vec2x8 vortexMath::Vec2x8::operator+(const vortexMath::Vec2x8& vec) const
{
    float * ret = (float* ) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3;
    for(int i = 0; i < size(); i+=16)
    {
        ymm0 = _mm256_load_ps((float* ) data()     + i + 0);
        ymm1 = _mm256_load_ps((float* ) data()     + i + 8);
        ymm2 = _mm256_load_ps((float* ) vec.data() + i + 0);
        ymm3 = _mm256_load_ps((float* ) vec.data() + i + 8);
        ymm0 = _mm256_add_ps(ymm0, ymm2);
        ymm1 = _mm256_add_ps(ymm1, ymm3);
        _mm256_store_ps((float* ) ret + i + 0, ymm0);
        _mm256_store_ps((float* ) ret + i + 8, ymm1);
    }
    Vec2x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec2x8 vortexMath::Vec2x8::operator-(const vortexMath::Vec2x8& vec) const
{
    float * ret = (float* ) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3;
    for(int i = 0; i < size(); i+=16)
    {
        ymm0 = _mm256_load_ps((float* ) data()     + i + 0);
        ymm1 = _mm256_load_ps((float* ) data()     + i + 8);
        ymm2 = _mm256_load_ps((float* ) vec.data() + i + 0);
        ymm3 = _mm256_load_ps((float* ) vec.data() + i + 8);
        ymm0 = _mm256_add_ps(ymm0, ymm2);
        ymm1 = _mm256_add_ps(ymm1, ymm3);
        _mm256_store_ps((float* ) ret + i + 0, ymm0);
        _mm256_store_ps((float* ) ret + i + 8, ymm1);
    }
    Vec2x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec2x8 vortexMath::Vec2x8::operator<<(const vortexMath::Vec2x8& vec) const
{
    float * ret = (float* ) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3;
    for(int i = 0; i < size(); i+=16)
    {
        ymm0 = _mm256_load_ps((float* ) data()     + i + 0);
        ymm1 = _mm256_load_ps((float* ) data()     + i + 8);
        ymm2 = _mm256_load_ps((float* ) vec.data() + i + 0);
        ymm3 = _mm256_load_ps((float* ) vec.data() + i + 8);
        ymm0 = _mm256_mul_ps(ymm0, ymm2);
        ymm1 = _mm256_mul_ps(ymm1, ymm3);
        _mm256_store_ps((float* ) ret + i + 0, ymm0);
        _mm256_store_ps((float* ) ret + i + 8, ymm1);
    }
    Vec2x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}



vortexMath::Vec2x8 vortexMath::Vec2x8::operator>>(const vortexMath::Vec2x8& vec) const
{
    float * ret = (float* ) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3;
    for(int i = 0; i < size(); i+=16)
    {
        ymm0 = _mm256_load_ps((float* ) data()     + i + 0);
        ymm1 = _mm256_load_ps((float* ) data()     + i + 8);
        ymm2 = _mm256_load_ps((float* ) vec.data() + i + 0);
        ymm3 = _mm256_load_ps((float* ) vec.data() + i + 8);
        ymm0 = _mm256_div_ps(ymm0, ymm2);
        ymm1 = _mm256_div_ps(ymm1, ymm3);
        _mm256_store_ps((float* ) ret + i + 0, ymm0);
        _mm256_store_ps((float* ) ret + i + 8, ymm1);
    }
    Vec2x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec2x8 vortexMath::Vec2x8::operator*(const float value) const
{
    float * ret = (float* ) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3;
    ymm3 = _mm256_set1_ps(value);
    for(int i = 0; i < size(); i+=16)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i + 0);
        ymm1 = _mm256_load_ps((float* ) data() + i + 8);
        ymm0 = _mm256_mul_ps(ymm0, ymm3);
        ymm1 = _mm256_mul_ps(ymm1, ymm3);
        _mm256_store_ps((float* ) ret + i + 0, ymm0);
        _mm256_store_ps((float* ) ret + i + 8, ymm1);
    }
    Vec2x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::AlignedVector<float, 32> vortexMath::Vec2x8::magnitude() const
{
    vortexMath::AlignedVector<float, 32> retVec(vecAmount());
    __m256 ymm0, ymm1, ymm2;
    for(int i = 0; i < vecAmount(); i+=8)
    {
        ymm0 = _mm256_load_ps((float* ) data() + (i * 2) + 0);
        ymm1 = _mm256_load_ps((float* ) data() + (i * 2) + 8);
        ymm2 = _mm256_mul_ps(ymm1, ymm1);
        ymm2 = _mm256_fmadd_ps(ymm0, ymm0, ymm2);
        ymm2 = _mm256_sqrt_ps(ymm2);
        _mm256_store_ps((float* ) retVec.data() + i, ymm2);
    }
    return retVec;
}

vortexMath::AlignedVector<float, 32> vortexMath::Vec2x8::squareMagnitude() const
{
    vortexMath::AlignedVector<float, 32> retVec(vecAmount());
    __m256 ymm0, ymm1, ymm2;
    for(int i = 0; i < vecAmount(); i+=8)
    {
        ymm0 = _mm256_load_ps((float* ) data() + (i * 2) + 0);
        ymm1 = _mm256_load_ps((float* ) data() + (i * 2) + 8);
        ymm2 = _mm256_mul_ps(ymm1, ymm1);
        ymm2 = _mm256_fmadd_ps(ymm0, ymm0, ymm2);
        _mm256_store_ps((float* ) retVec.data() + i, ymm2);
    }
    return retVec;
}

void vortexMath::Vec2x8::normalize()
{
    __m256 ymm0, ymm1, ymm2, ymm3;
    ymm3 = _mm256_set1_ps(1.0f);
    for(int i = 0; i < size(); i+=16)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i + 0);
        ymm1 = _mm256_load_ps((float* ) data() + i + 8);
        ymm2 = _mm256_mul_ps(ymm1, ymm1);
        ymm2 = _mm256_fmadd_ps(ymm0, ymm0, ymm2);
        ymm2 = _mm256_sqrt_ps(ymm2);
        ymm2 = _mm256_div_ps(ymm3, ymm2);
        ymm0 = _mm256_mul_ps(ymm0, ymm2);
        ymm1 = _mm256_mul_ps(ymm1, ymm2);
        _mm256_store_ps((float* ) data() + i + 0, ymm0);
        _mm256_store_ps((float* ) data() + i + 8, ymm1);
    }
}

void vortexMath::Vec2x8::addScaledVector(const vortexMath::Vec2x8& vec, float scale)
{
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4;
    ymm4 = _mm256_set1_ps(scale);
    for(int i = 0; i < size(); i+=16)
    {
        ymm0 = _mm256_load_ps((float* ) data()     + i + 0);
        ymm1 = _mm256_load_ps((float* ) data()     + i + 8);
        ymm2 = _mm256_load_ps((float* ) vec.data() + i + 0);
        ymm3 = _mm256_load_ps((float* ) vec.data() + i + 8);
        ymm0 = _mm256_fmadd_ps(ymm2, ymm4, ymm0);
        ymm1 = _mm256_fmadd_ps(ymm3, ymm4, ymm1);
        _mm256_store_ps((float* ) data() + i + 0, ymm0);
        _mm256_store_ps((float* ) data() + i + 8, ymm1);
    }
}

void vortexMath::Vec2x8::convertToSOA()
{
    __m256 ymm0, ymm1, ymm2, ymm3;

    for (int i = 0; i < size(); i+=16)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i + 0);
        ymm1 = _mm256_load_ps((float* ) data() + i + 8);
        
        ymm2 = _mm256_shuffle_ps(ymm0, ymm1, 0b10001000);
        ymm3 = _mm256_shuffle_ps(ymm0, ymm1, 0b11011101);
        
        _mm256_store_ps((float* ) data() + i + 0, ymm2);
        _mm256_store_ps((float* ) data() + i + 8, ymm3);
    }
}

void vortexMath::Vec2x8::convertToAOS()
{
    __m256 ymm0, ymm1, ymm2, ymm3;

    for (int i = 0; i < size(); i+=16)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i + 0);
        ymm1 = _mm256_load_ps((float* ) data() + i + 8);
        
        ymm2 = _mm256_unpacklo_ps(ymm0, ymm1);
        ymm3 = _mm256_unpackhi_ps(ymm0, ymm1);
        
        _mm256_store_ps((float* ) data() + i + 0, ymm2);
        _mm256_store_ps((float* ) data() + i + 8, ymm3);
    }
}

vortexMath::Vec2x8 vortexMath::Vec2x8::retrieveSOAForm() const
{
    float * ret = (float*) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3;
    for (int i = 0; i < size(); i+=16)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i + 0);
        ymm1 = _mm256_load_ps((float* ) data() + i + 8);
        ymm2 = _mm256_shuffle_ps(ymm0, ymm1, 0b10001000);
        ymm3 = _mm256_shuffle_ps(ymm0, ymm1, 0b11011101);
        _mm256_store_ps((float* ) ret + i + 0, ymm2);
        _mm256_store_ps((float* ) ret + i + 8, ymm3);
    }
    Vec2x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec2x8 vortexMath::Vec2x8::retrieveAOSForm() const
{
    float * ret = (float*) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3;
    for (int i = 0; i < size(); i+=16)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i + 0);
        ymm1 = _mm256_load_ps((float* ) data() + i + 8);
        ymm2 = _mm256_unpacklo_ps(ymm0, ymm1);
        ymm3 = _mm256_unpackhi_ps(ymm0, ymm1);
        _mm256_store_ps((float* ) ret + i + 0, ymm2);
        _mm256_store_ps((float* ) ret + i + 8, ymm3);
    }
    Vec2x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::AlignedVector<float, 32> vortexMath::Vec2x8::get(const vortexMath::VecElementType t) const
{
    vortexMath::AlignedVector<float, 32> retVec(vecAmount());
    for(int i = 0; i < vecAmount(); i+=8)
    {
        _mm256_store_ps((float* ) retVec.data() + i, _mm256_load_ps((float* ) data() + (i * 2) + (t * 2)));
    }
    return retVec;
}

void vortexMath::Vec2x8::set(const vortexMath::VecElementType t, float val)
{
    __m256 ymm0 = _mm256_set1_ps(val);
    for(int i = 0; i < vecAmount(); i+=8)
    {
        _mm256_store_ps((float* ) data() + (i * 2) + (t * 2), ymm0);
    }
}

void vortexMath::Vec2x8::set(const vortexMath::VecElementType t, const vortexMath::AlignedVector<float, 32>& values)
{
    for(int i = 0; i < vecAmount(); i+=8)
    {
        _mm256_store_ps((float* ) data() + (i * 2) + (t * 2), _mm256_load_ps((float* ) values.data() + i));
    }
}

vortexMath::Vec3x8::Vec3x8(const int vectors)
{
    if (vectors < 8) return; 
    vecData.reserve(vectors * 3);
    vecCount = vectors; 
}

vortexMath::Vec3x8::Vec3x8(const float* data, int vectors)
{
    if (vectors < 8) return;
    vecData.insert(ITERATOR_BEGIN, 0, data, vectors * 3);
    vecCount = vectors; 
}

vortexMath::Vec3x8::Vec3x8(const float value, int vectors)
{
    if (vectors < 8) return;
    vecData.insert(ITERATOR_BEGIN, 0, std::vector<float>(vectors * 3, value));
    vecCount = vectors; 
}

vortexMath::Vec3x8::Vec3x8(const AlignedVector<float, 32>& x, const AlignedVector<float, 32>& y, const AlignedVector<float, 32>& z, const int vectors)
{
    if (vectors < 8) return;
    vecData.reserve(vectors * 3);
    vecCount = vectors;
    __m256 ymm0, ymm1, ymm2;
    for (int i = 0; i < vecAmount(); i+=8)
    {
        ymm0 = _mm256_load_ps((float* ) x.data() + i);
        ymm1 = _mm256_load_ps((float* ) y.data() + i);
        ymm2 = _mm256_load_ps((float* ) z.data() + i);
        
        _mm256_store_ps((float* ) vecData.data() + (i * 3) +   0, ymm0);
        _mm256_store_ps((float* ) vecData.data() + (i * 3) +   8, ymm1);
        _mm256_store_ps((float* ) vecData.data() + (i * 3) +  16, ymm2);
    }
}

vortexMath::Vec3x8 vortexMath::Vec3x8::vec3x8(const vortexMath::Vec2x8& vec, const vortexMath::AlignedVector<float, 32>& z)
{
    return Vec3x8(vec.get(VEC_ELEMENT_X), vec.get(VEC_ELEMENT_Y), z, vec.vecAmount());
}

vortexMath::Vec3x8 vortexMath::Vec3x8::vec3x8(const vortexMath::Vec4x8& vec)
{
    return Vec3x8(vec.get(VEC_ELEMENT_X), vec.get(VEC_ELEMENT_Y), vec.get(VEC_ELEMENT_Z), vec.vecAmount());
}

vortexMath::Vec3x8 vortexMath::Vec3x8::generateVecFromArray(const float* inputBuffer, const int startIndex, const int size, const int vectors)
{
    float* ret = (float* ) aligned_alloc(32, size * sizeof(float));
            
    int offset = size / vectors;
    int space = 8 - ((vectors * 3) % 8); //Space required to fill for proper avx alignment (in elements NOT vectors)
    int retIndex = 0;
    for (int i = startIndex; i < size; i+=offset)
    {
        for (int j = 0; j < 3; j++)
        {
            ret[retIndex++] = inputBuffer[i+j];
        }
    }
    
    for (int k = 0; k < space; k++)
    {
        ret[retIndex++] = 0.0f;
    }
    
    Vec3x8 retVec{ ret, vectors + (space / 3) };
    free(ret);
    return retVec;
}

void vortexMath::Vec3x8::operator+=(const vortexMath::Vec3x8& vec)
{
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5;
    for(int i = 0; i < size(); i+=24)
    {
        ymm0 = _mm256_load_ps((float* ) data()     + i +  0);
        ymm1 = _mm256_load_ps((float* ) data()     + i +  8);
        ymm2 = _mm256_load_ps((float* ) data()     + i + 16);
        ymm3 = _mm256_load_ps((float* ) vec.data() + i +  0);
        ymm4 = _mm256_load_ps((float* ) vec.data() + i +  8);
        ymm5 = _mm256_load_ps((float* ) vec.data() + i + 16);
        ymm0 = _mm256_add_ps(ymm0, ymm3);
        ymm1 = _mm256_add_ps(ymm1, ymm4);
        ymm2 = _mm256_add_ps(ymm2, ymm5);
        _mm256_store_ps((float* ) data() + i +  0, ymm0);
        _mm256_store_ps((float* ) data() + i +  8, ymm1);
        _mm256_store_ps((float* ) data() + i + 16, ymm2);
    }
}

void vortexMath::Vec3x8::operator-=(const vortexMath::Vec3x8& vec)
{
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5;
    for(int i = 0; i < size(); i+=24)
    {
        ymm0 = _mm256_load_ps((float* ) data()     + i +  0);
        ymm1 = _mm256_load_ps((float* ) data()     + i +  8);
        ymm2 = _mm256_load_ps((float* ) data()     + i + 16);
        ymm3 = _mm256_load_ps((float* ) vec.data() + i +  0);
        ymm4 = _mm256_load_ps((float* ) vec.data() + i +  8);
        ymm5 = _mm256_load_ps((float* ) vec.data() + i + 16);
        ymm0 = _mm256_sub_ps(ymm0, ymm3);
        ymm1 = _mm256_sub_ps(ymm1, ymm4);
        ymm2 = _mm256_sub_ps(ymm2, ymm5);
        _mm256_store_ps((float* ) data() + i +  0, ymm0);
        _mm256_store_ps((float* ) data() + i +  8, ymm1);
        _mm256_store_ps((float* ) data() + i + 16, ymm2);
    }
}

void vortexMath::Vec3x8::operator<<=(const vortexMath::Vec3x8& vec)
{
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5;
    for(int i = 0; i < size(); i+=24)
    {
        ymm0 = _mm256_load_ps((float* ) data()     + i +  0);
        ymm1 = _mm256_load_ps((float* ) data()     + i +  8);
        ymm2 = _mm256_load_ps((float* ) data()     + i + 16);
        ymm3 = _mm256_load_ps((float* ) vec.data() + i +  0);
        ymm4 = _mm256_load_ps((float* ) vec.data() + i +  8);
        ymm5 = _mm256_load_ps((float* ) vec.data() + i + 16);
        ymm0 = _mm256_mul_ps(ymm0, ymm3);
        ymm1 = _mm256_mul_ps(ymm1, ymm4);
        ymm2 = _mm256_mul_ps(ymm2, ymm5);
        _mm256_store_ps((float* ) data() + i +  0, ymm0);
        _mm256_store_ps((float* ) data() + i +  8, ymm1);
        _mm256_store_ps((float* ) data() + i + 16, ymm2);
    }
}

void vortexMath::Vec3x8::operator>>=(const vortexMath::Vec3x8& vec)
{
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5;
    for(int i = 0; i < size(); i+=24)
    {
        ymm0 = _mm256_load_ps((float* ) data()     + i +  0);
        ymm1 = _mm256_load_ps((float* ) data()     + i +  8);
        ymm2 = _mm256_load_ps((float* ) data()     + i + 16);
        ymm3 = _mm256_load_ps((float* ) vec.data() + i +  0);
        ymm4 = _mm256_load_ps((float* ) vec.data() + i +  8);
        ymm5 = _mm256_load_ps((float* ) vec.data() + i + 16);
        ymm0 = _mm256_div_ps(ymm0, ymm3);
        ymm1 = _mm256_div_ps(ymm1, ymm4);
        ymm2 = _mm256_div_ps(ymm2, ymm5);
        _mm256_store_ps((float* ) data() + i +  0, ymm0);
        _mm256_store_ps((float* ) data() + i +  8, ymm1);
        _mm256_store_ps((float* ) data() + i + 16, ymm2);
    }
}

void vortexMath::Vec3x8::operator*=(const float value)
{
    __m256 ymm0, ymm1, ymm2, ymm3;
    ymm3 = _mm256_set1_ps(value);
    for(int i = 0; i < size(); i+=24)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +  0);
        ymm1 = _mm256_load_ps((float* ) data() + i +  8);
        ymm2 = _mm256_load_ps((float* ) data() + i + 16);
        ymm0 = _mm256_mul_ps(ymm0, ymm3);
        ymm1 = _mm256_mul_ps(ymm1, ymm3);
        ymm2 = _mm256_mul_ps(ymm2, ymm3);
        _mm256_store_ps((float* ) data() + i +  0, ymm0);
        _mm256_store_ps((float* ) data() + i +  8, ymm1);
        _mm256_store_ps((float* ) data() + i + 16, ymm2);
    }
}

void vortexMath::Vec3x8::operator%=(const vortexMath::Vec3x8& vec)
{
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7, ymm8;

    for (int i = 0; i < size(); i+=24)
    {
        ymm0 = _mm256_load_ps((float* ) data()     + i +  0);
        ymm1 = _mm256_load_ps((float* ) data()     + i +  8);
        ymm2 = _mm256_load_ps((float* ) data()     + i + 16);
        ymm3 = _mm256_load_ps((float* ) vec.data() + i +  0);
        ymm4 = _mm256_load_ps((float* ) vec.data() + i +  8);
        ymm5 = _mm256_load_ps((float* ) vec.data() + i + 16);
        ymm6 = _mm256_mul_ps(ymm2, ymm4);
        ymm7 = _mm256_mul_ps(ymm0, ymm5);
        ymm8 = _mm256_mul_ps(ymm1, ymm3);
        ymm6 = _mm256_fmsub_ps(ymm1, ymm5, ymm6);
        ymm7 = _mm256_fmsub_ps(ymm2, ymm3, ymm7);
        ymm8 = _mm256_fmsub_ps(ymm0, ymm4, ymm8);
        _mm256_store_ps((float* ) data() + i +  0, ymm6);
        _mm256_store_ps((float* ) data() + i +  8, ymm7);
        _mm256_store_ps((float* ) data() + i + 16, ymm8);
    }
}

vortexMath::Vec3x8 vortexMath::Vec3x8::operator+(const vortexMath::Vec3x8& vec) const
{
    float * ret = (float* ) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5;
    for(int i = 0; i < size(); i+=24)
    {
        ymm0 = _mm256_load_ps((float* ) data()     + i +  0);
        ymm1 = _mm256_load_ps((float* ) data()     + i +  8);
        ymm2 = _mm256_load_ps((float* ) data()     + i + 16);
        ymm3 = _mm256_load_ps((float* ) vec.data() + i +  0);
        ymm4 = _mm256_load_ps((float* ) vec.data() + i +  8);
        ymm5 = _mm256_load_ps((float* ) vec.data() + i + 16);
        ymm0 = _mm256_add_ps(ymm0, ymm3);
        ymm1 = _mm256_add_ps(ymm1, ymm4);
        ymm2 = _mm256_add_ps(ymm2, ymm5);
        _mm256_store_ps((float* ) ret + i +  0, ymm0);
        _mm256_store_ps((float* ) ret + i +  8, ymm1);
        _mm256_store_ps((float* ) ret + i + 16, ymm2);
    }
    Vec3x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec3x8 vortexMath::Vec3x8::operator-(const vortexMath::Vec3x8& vec) const
{
    float * ret = (float* ) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5;
    for(int i = 0; i < size(); i+=24)
    {
        ymm0 = _mm256_load_ps((float* ) data()     + i +  0);
        ymm1 = _mm256_load_ps((float* ) data()     + i +  8);
        ymm2 = _mm256_load_ps((float* ) data()     + i + 16);
        ymm3 = _mm256_load_ps((float* ) vec.data() + i +  0);
        ymm4 = _mm256_load_ps((float* ) vec.data() + i +  8);
        ymm5 = _mm256_load_ps((float* ) vec.data() + i + 16);
        ymm0 = _mm256_sub_ps(ymm0, ymm3);
        ymm1 = _mm256_sub_ps(ymm1, ymm4);
        ymm2 = _mm256_sub_ps(ymm2, ymm5);
        _mm256_store_ps((float* ) ret + i +  0, ymm0);
        _mm256_store_ps((float* ) ret + i +  8, ymm1);
        _mm256_store_ps((float* ) ret + i + 16, ymm2);
    }
    Vec3x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec3x8 vortexMath::Vec3x8::operator<<(const vortexMath::Vec3x8& vec) const
{
    float * ret = (float* ) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5;
    for(int i = 0; i < size(); i+=24)
    {
        ymm0 = _mm256_load_ps((float* ) data()     + i +  0);
        ymm1 = _mm256_load_ps((float* ) data()     + i +  8);
        ymm2 = _mm256_load_ps((float* ) data()     + i + 16);
        ymm3 = _mm256_load_ps((float* ) vec.data() + i +  0);
        ymm4 = _mm256_load_ps((float* ) vec.data() + i +  8);
        ymm5 = _mm256_load_ps((float* ) vec.data() + i + 16);
        ymm0 = _mm256_mul_ps(ymm0, ymm3);
        ymm1 = _mm256_mul_ps(ymm1, ymm4);
        ymm2 = _mm256_mul_ps(ymm2, ymm5);
        _mm256_store_ps((float* ) ret + i +  0, ymm0);
        _mm256_store_ps((float* ) ret + i +  8, ymm1);
        _mm256_store_ps((float* ) ret + i + 16, ymm2);
    }
    Vec3x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec3x8 vortexMath::Vec3x8::operator>>(const vortexMath::Vec3x8& vec) const
{
    float * ret = (float* ) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5;
    for(int i = 0; i < size(); i+=24)
    {
        ymm0 = _mm256_load_ps((float* ) data()     + i +  0);
        ymm1 = _mm256_load_ps((float* ) data()     + i +  8);
        ymm2 = _mm256_load_ps((float* ) data()     + i + 16);
        ymm3 = _mm256_load_ps((float* ) vec.data() + i +  0);
        ymm4 = _mm256_load_ps((float* ) vec.data() + i +  8);
        ymm5 = _mm256_load_ps((float* ) vec.data() + i + 16);
        ymm0 = _mm256_div_ps(ymm0, ymm3);
        ymm1 = _mm256_div_ps(ymm1, ymm4);
        ymm2 = _mm256_div_ps(ymm2, ymm5);
        _mm256_store_ps((float* ) ret + i +  0, ymm0);
        _mm256_store_ps((float* ) ret + i +  8, ymm1);
        _mm256_store_ps((float* ) ret + i + 16, ymm2);
    }
    Vec3x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec3x8 vortexMath::Vec3x8::operator*(const float value) const
{
    float * ret = (float* ) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3;
    ymm3 = _mm256_set1_ps(value);
    for(int i = 0; i < size(); i+=24)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +  0);
        ymm1 = _mm256_load_ps((float* ) data() + i +  8);
        ymm2 = _mm256_load_ps((float* ) data() + i + 16);
        ymm0 = _mm256_mul_ps(ymm0, ymm3);
        ymm1 = _mm256_mul_ps(ymm1, ymm3);
        ymm2 = _mm256_mul_ps(ymm2, ymm3);
        _mm256_store_ps((float* ) ret + i +  0, ymm0);
        _mm256_store_ps((float* ) ret + i +  8, ymm1);
        _mm256_store_ps((float* ) ret + i + 16, ymm2);
    }
    Vec3x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::AlignedVector<float, 32> vortexMath::Vec3x8::operator*(const vortexMath::Vec3x8& vec) const
{
    vortexMath::AlignedVector<float, 32> retVec(vecAmount());
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5;
    for(int i = 0; i < vecAmount(); i+=8)
    {
        ymm0 = _mm256_load_ps((float* ) data() + (i * 3) +   0);
        ymm1 = _mm256_load_ps((float* ) data() + (i * 3) +   8);
        ymm2 = _mm256_load_ps((float* ) data() + (i * 3) +  16);
        ymm3 = _mm256_load_ps((float* ) vec.data() + (i * 3) +   0);
        ymm4 = _mm256_load_ps((float* ) vec.data() + (i * 3) +   8);
        ymm5 = _mm256_load_ps((float* ) vec.data() + (i * 3) +  16);
        ymm0 = _mm256_mul_ps(ymm0, ymm3);
        ymm1 = _mm256_fmadd_ps(ymm1, ymm4, ymm0);
        ymm2 = _mm256_fmadd_ps(ymm2, ymm5, ymm1);
        _mm256_store_ps((float* ) retVec.data() + i, ymm2);

    }
    return retVec;
}


vortexMath::Vec3x8 vortexMath::Vec3x8::operator%(const vortexMath::Vec3x8& vec) const
{
    float * ret = (float* ) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7, ymm8;
    for (int i = 0; i < size(); i+=24)
    {
        ymm0 = _mm256_load_ps((float* ) data()     + i +  0);
        ymm1 = _mm256_load_ps((float* ) data()     + i +  8);
        ymm2 = _mm256_load_ps((float* ) data()     + i + 16);
        ymm3 = _mm256_load_ps((float* ) vec.data() + i +  0);
        ymm4 = _mm256_load_ps((float* ) vec.data() + i +  8);
        ymm5 = _mm256_load_ps((float* ) vec.data() + i + 16);
        ymm6 = _mm256_mul_ps(ymm2, ymm4);
        ymm7 = _mm256_mul_ps(ymm0, ymm5);
        ymm8 = _mm256_mul_ps(ymm1, ymm3);
        ymm6 = _mm256_fmsub_ps(ymm1, ymm5, ymm6);
        ymm7 = _mm256_fmsub_ps(ymm2, ymm3, ymm7);
        ymm8 = _mm256_fmsub_ps(ymm0, ymm4, ymm8);
        _mm256_store_ps((float* ) ret + i +  0, ymm6);
        _mm256_store_ps((float* ) ret + i +  8, ymm7);
        _mm256_store_ps((float* ) ret + i + 16, ymm8);
    }
    Vec3x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::AlignedVector<float, 32> vortexMath::Vec3x8::magnitude() const
{
    vortexMath::AlignedVector<float, 32> retVec(vecAmount());
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4;
    ymm4 = _mm256_set1_ps(1.0f);
    for(int i = 0; i < vecAmount(); i+=8)
    {
        ymm0 = _mm256_load_ps((float* ) data() + (i * 3) +  0);
        ymm1 = _mm256_load_ps((float* ) data() + (i * 3) +  8);
        ymm2 = _mm256_load_ps((float* ) data() + (i * 3) + 16);
        ymm3 = _mm256_mul_ps(ymm2, ymm2);
        ymm3 = _mm256_fmadd_ps(ymm1, ymm1, ymm3);
        ymm3 = _mm256_fmadd_ps(ymm0, ymm0, ymm3);
        ymm3 = _mm256_sqrt_ps(ymm3);
        _mm256_store_ps((float* ) retVec.data() + i, ymm3);
    }
    return retVec;
}

vortexMath::AlignedVector<float, 32> vortexMath::Vec3x8::squareMagnitude() const
{
    vortexMath::AlignedVector<float, 32> retVec(vecAmount());
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4;
    ymm4 = _mm256_set1_ps(1.0f);
    for(int i = 0; i < vecAmount(); i+=8)
    {
        ymm0 = _mm256_load_ps((float* ) data() + (i * 3) +  0);
        ymm1 = _mm256_load_ps((float* ) data() + (i * 3) +  8);
        ymm2 = _mm256_load_ps((float* ) data() + (i * 3) + 16);
        ymm3 = _mm256_mul_ps(ymm2, ymm2);
        ymm3 = _mm256_fmadd_ps(ymm1, ymm1, ymm3);
        ymm3 = _mm256_fmadd_ps(ymm0, ymm0, ymm3);
        _mm256_store_ps((float* ) retVec.data() + i, ymm3);
    }
    return retVec;
}

void vortexMath::Vec3x8::normalize()
{
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4;
    ymm4 = _mm256_set1_ps(1.0f);
    for(int i = 0; i < size(); i+=24)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +  0);
        ymm1 = _mm256_load_ps((float* ) data() + i +  8);
        ymm2 = _mm256_load_ps((float* ) data() + i + 16);
        ymm3 = _mm256_mul_ps(ymm2, ymm2);
        ymm3 = _mm256_fmadd_ps(ymm1, ymm1, ymm3);
        ymm3 = _mm256_fmadd_ps(ymm0, ymm0, ymm3);
        ymm3 = _mm256_sqrt_ps(ymm3);
        ymm3 = _mm256_div_ps(ymm4, ymm3);
        ymm0 = _mm256_mul_ps(ymm0, ymm3);
        ymm1 = _mm256_mul_ps(ymm1, ymm3);
        ymm2 = _mm256_mul_ps(ymm2, ymm3);
        _mm256_store_ps((float* ) data() + i +  0, ymm0);
        _mm256_store_ps((float* ) data() + i +  8, ymm1);
        _mm256_store_ps((float* ) data() + i + 16, ymm2);
    }
}

void vortexMath::Vec3x8::addScaledVector(const vortexMath::Vec3x8& vec, float scale)
{
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6;
    ymm6 = _mm256_set1_ps(scale);
    for(int i = 0; i < size(); i+=24)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +  0);
        ymm1 = _mm256_load_ps((float* ) data() + i +  8);
        ymm2 = _mm256_load_ps((float* ) data() + i + 16);
        ymm3 = _mm256_load_ps((float* ) vec.data() + i +  0);
        ymm4 = _mm256_load_ps((float* ) vec.data() + i +  8);
        ymm5 = _mm256_load_ps((float* ) vec.data() + i + 16);
        ymm0 = _mm256_fmadd_ps(ymm3, ymm6, ymm0);
        ymm1 = _mm256_fmadd_ps(ymm4, ymm6, ymm1);
        ymm2 = _mm256_fmadd_ps(ymm5, ymm6, ymm2);
        _mm256_store_ps((float* ) data() + i +  0, ymm0);
        _mm256_store_ps((float* ) data() + i +  8, ymm1);
        _mm256_store_ps((float* ) data() + i + 16, ymm2);
    }
}

void vortexMath::Vec3x8::generateOrthonormalBasis(const int endIndex)
{
    //TODO: Not tested
    float x = *(&vecData[endIndex +  0]);
    float y = *(&vecData[endIndex +  8]);
    float z = *(&vecData[endIndex + 16]);

    float sign = std::copysignf(1.0f, z);
        
    const float a = -1.0f / (sign + z);
    const float b = y * y * a;
        
    *(&vecData[endIndex -  2]) = 1.0f + sign * x * x * a;
    *(&vecData[endIndex +  6]) = sign * b;
    *(&vecData[endIndex + 14]) = -sign * x;

    *(&vecData[endIndex -  1]) = b;
    *(&vecData[endIndex +  7]) = sign + y * y * a;
    *(&vecData[endIndex + 15]) = -y;
}


void vortexMath::Vec3x8::convertToSOA()
{
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4;

    for (int i = 0; i < size(); i+=24)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +  0);
        ymm1 = _mm256_load_ps((float* ) data() + i +  8);
        ymm2 = _mm256_load_ps((float* ) data() + i + 16);
        ymm3 = _mm256_shuffle_ps(ymm0, ymm1, 0b01001001);
        ymm4 = _mm256_shuffle_ps(ymm1, ymm2, 0b10011110);
        ymm0 = _mm256_shuffle_ps(ymm0, ymm4, 0b10001100);
        ymm2 = _mm256_shuffle_ps(ymm3, ymm2, 0b11001101);
        ymm1 = _mm256_shuffle_ps(ymm3, ymm4, 0b11011000);
        _mm256_store_ps((float* ) data() + i +  0, ymm0);
        _mm256_store_ps((float* ) data() + i +  8, ymm1);
        _mm256_store_ps((float* ) data() + i + 16, ymm2);
    }
}

void vortexMath::Vec3x8::convertToAOS()
{
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5;

    for (int i = 0; i < size(); i+=24)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +  0);
        ymm1 = _mm256_load_ps((float* ) data() + i +  8);
        ymm2 = _mm256_load_ps((float* ) data() + i + 16);
        ymm3 = _mm256_shuffle_ps(ymm0, ymm1, 0b10001000); //evenX evenY
        ymm4 = _mm256_shuffle_ps(ymm2, ymm0, 0b11011000); //evenZ oddX
        ymm5 = _mm256_shuffle_ps(ymm2, ymm1, 0b11011101); //oddZ  oddY
        ymm0 = _mm256_shuffle_ps(ymm3, ymm4, 0b10001000); //0 3
        ymm1 = _mm256_shuffle_ps(ymm5, ymm3, 0b11010010); //1 4
        ymm2 = _mm256_shuffle_ps(ymm4, ymm5, 0b01111101); //2 5
        _mm256_store_ps((float* ) data() + i +  0, ymm0);
        _mm256_store_ps((float* ) data() + i +  8, ymm1);
        _mm256_store_ps((float* ) data() + i + 16, ymm2);
    }
}

vortexMath::Vec3x8 vortexMath::Vec3x8::retrieveSOAForm() const
{
    float * ret = (float*) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4;
    for (int i = 0; i < size(); i+=24)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +  0);
        ymm1 = _mm256_load_ps((float* ) data() + i +  8);
        ymm2 = _mm256_load_ps((float* ) data() + i + 16);
        ymm3 = _mm256_shuffle_ps(ymm0, ymm1, 0b01001001);
        ymm4 = _mm256_shuffle_ps(ymm1, ymm2, 0b10011110);
        ymm0 = _mm256_shuffle_ps(ymm0, ymm4, 0b10001100);
        ymm2 = _mm256_shuffle_ps(ymm3, ymm2, 0b11001101);
        ymm1 = _mm256_shuffle_ps(ymm3, ymm4, 0b11011000);
        _mm256_store_ps((float* ) ret + i +  0, ymm0);
        _mm256_store_ps((float* ) ret + i +  8, ymm1);
        _mm256_store_ps((float* ) ret + i + 16, ymm2);
    }
    Vec3x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec3x8 vortexMath::Vec3x8::retrieveAOSForm() const
{
    float * ret = (float*) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5;
    for (int i = 0; i < size(); i+=24)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +  0);
        ymm1 = _mm256_load_ps((float* ) data() + i +  8);
        ymm2 = _mm256_load_ps((float* ) data() + i + 16);
        ymm3 = _mm256_shuffle_ps(ymm0, ymm1, 0b10001000); //evenX evenY
        ymm4 = _mm256_shuffle_ps(ymm2, ymm0, 0b11011000); //evenZ oddX
        ymm5 = _mm256_shuffle_ps(ymm2, ymm1, 0b11011101); //oddZ  oddY
        ymm0 = _mm256_shuffle_ps(ymm3, ymm4, 0b10001000); //0 3
        ymm1 = _mm256_shuffle_ps(ymm5, ymm3, 0b11010010); //1 4
        ymm2 = _mm256_shuffle_ps(ymm4, ymm5, 0b01111101); //2 5
        _mm256_store_ps((float* ) ret + i +  0, ymm0);
        _mm256_store_ps((float* ) ret + i +  8, ymm1);
        _mm256_store_ps((float* ) ret + i + 16, ymm2);
    }
    Vec3x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::AlignedVector<float, 32> vortexMath::Vec3x8::get(const vortexMath::VecElementType t) const
{
    vortexMath::AlignedVector<float, 32> retVec(vecAmount());
    for(int i = 0; i < vecAmount(); i+=8)
    {
        _mm256_store_ps((float* ) retVec.data() + i, _mm256_load_ps((float* ) data() + (i * 3) + (t * 2)));
    }
    return retVec;
}


void vortexMath::Vec3x8::set(const vortexMath::VecElementType t, float val)
{
    __m256 ymm0 = _mm256_set1_ps(val);
    for(int i = 0; i < vecAmount(); i+=8)
    {
        _mm256_store_ps((float* ) data() + (i * 3) + (t * 2), ymm0);
    }
}

void vortexMath::Vec3x8::set(const vortexMath::VecElementType t, const vortexMath::AlignedVector<float, 32>& values)
{
    for(int i = 0; i < vecAmount(); i+=8)
    {
        _mm256_store_ps((float* ) data() + (i * 3) + (t * 2), _mm256_load_ps((float* ) values.data() + i));
    }
}

vortexMath::Vec4x8::Vec4x8(const int vectors)
{
    if (vectors < 8) return; 
    vecData.reserve(vectors * 4);
    vecCount = vectors; 
}

vortexMath::Vec4x8::Vec4x8(const float* data, int vectors)
{
    if (vectors < 8) return;
    vecData.insert(ITERATOR_BEGIN, 0, data, vectors * 4);
    vecCount = vectors; 
}

vortexMath::Vec4x8::Vec4x8(const float value, int vectors)
{
    if (vectors < 8) return;
    vecData.insert(ITERATOR_BEGIN, 0, std::vector<float>(vectors * 4, value));
    vecCount = vectors; 
}

vortexMath::Vec4x8::Vec4x8(const AlignedVector<float, 32>& x, const AlignedVector<float, 32>& y, const AlignedVector<float, 32>& z, const AlignedVector<float, 32>& w, const int vectors)
{
    if (vectors < 8) return;
    vecData.reserve(vectors * 4);
    vecCount = vectors;
    __m256 ymm0, ymm1, ymm2, ymm3;
    for (int i = 0; i < vecAmount(); i+=8)
    {
        ymm0 = _mm256_load_ps((float* ) x.data() + i);
        ymm1 = _mm256_load_ps((float* ) y.data() + i);
        ymm2 = _mm256_load_ps((float* ) z.data() + i);
        ymm3 = _mm256_load_ps((float* ) w.data() + i);
        
        _mm256_store_ps((float* ) vecData.data() + (i * 4) +  0, ymm0);
        _mm256_store_ps((float* ) vecData.data() + (i * 4) +  8, ymm1);
        _mm256_store_ps((float* ) vecData.data() + (i * 4) + 16, ymm2);
        _mm256_store_ps((float* ) vecData.data() + (i * 4) + 24, ymm3);
    }
}


vortexMath::Vec4x8 vortexMath::Vec4x8::vec4x8(const vortexMath::Vec2x8& vec, const vortexMath::AlignedVector<float, 32>& z, const vortexMath::AlignedVector<float, 32>& w)
{
    return Vec4x8(vec.get(VEC_ELEMENT_X), vec.get(VEC_ELEMENT_Y), z, w, vec.vecAmount());
}

vortexMath::Vec4x8 vortexMath::Vec4x8::vec4x8(const vortexMath::Vec3x8& vec, const vortexMath::AlignedVector<float, 32>& w)
{
    return Vec4x8(vec.get(VEC_ELEMENT_X), vec.get(VEC_ELEMENT_Y), vec.get(VEC_ELEMENT_Z), w, vec.vecAmount());
}

void vortexMath::Vec4x8::operator+=(const vortexMath::Vec4x8& vec)
{
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7;
    for(int i = 0; i < size(); i+=32)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +   0);
        ymm1 = _mm256_load_ps((float* ) data() + i +   8);
        ymm2 = _mm256_load_ps((float* ) data() + i +  16);
        ymm3 = _mm256_load_ps((float* ) data() + i +  24);
        ymm4 = _mm256_load_ps((float* ) vec.data() + i +  0);
        ymm5 = _mm256_load_ps((float* ) vec.data() + i +  8);
        ymm6 = _mm256_load_ps((float* ) vec.data() + i + 16);
        ymm7 = _mm256_load_ps((float* ) vec.data() + i + 24);
        ymm0 = _mm256_add_ps(ymm0, ymm4);
        ymm1 = _mm256_add_ps(ymm1, ymm5);
        ymm2 = _mm256_add_ps(ymm2, ymm6);
        ymm3 = _mm256_add_ps(ymm3, ymm7);
        _mm256_store_ps((float* ) data() + i +  0, ymm0);
        _mm256_store_ps((float* ) data() + i +  8, ymm1);
        _mm256_store_ps((float* ) data() + i + 16, ymm2);
        _mm256_store_ps((float* ) data() + i + 24, ymm3);
    }
}

void vortexMath::Vec4x8::operator-=(const vortexMath::Vec4x8& vec)
{
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7;
    for(int i = 0; i < size(); i+=32)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +   0);
        ymm1 = _mm256_load_ps((float* ) data() + i +   8);
        ymm2 = _mm256_load_ps((float* ) data() + i +  16);
        ymm3 = _mm256_load_ps((float* ) data() + i +  24);
        ymm4 = _mm256_load_ps((float* ) vec.data() + i +  0);
        ymm5 = _mm256_load_ps((float* ) vec.data() + i +  8);
        ymm6 = _mm256_load_ps((float* ) vec.data() + i + 16);
        ymm7 = _mm256_load_ps((float* ) vec.data() + i + 24);
        ymm0 = _mm256_sub_ps(ymm0, ymm4);
        ymm1 = _mm256_sub_ps(ymm1, ymm5);
        ymm2 = _mm256_sub_ps(ymm2, ymm6);
        ymm3 = _mm256_sub_ps(ymm3, ymm7);
        _mm256_store_ps((float* ) data() + i +  0, ymm0);
        _mm256_store_ps((float* ) data() + i +  8, ymm1);
        _mm256_store_ps((float* ) data() + i + 16, ymm2);
        _mm256_store_ps((float* ) data() + i + 24, ymm3);
    }
}

void vortexMath::Vec4x8::operator<<=(const vortexMath::Vec4x8& vec)
{
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7;
    for(int i = 0; i < size(); i+=32)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +   0);
        ymm1 = _mm256_load_ps((float* ) data() + i +   8);
        ymm2 = _mm256_load_ps((float* ) data() + i +  16);
        ymm3 = _mm256_load_ps((float* ) data() + i +  24);
        ymm4 = _mm256_load_ps((float* ) vec.data() + i +  0);
        ymm5 = _mm256_load_ps((float* ) vec.data() + i +  8);
        ymm6 = _mm256_load_ps((float* ) vec.data() + i + 16);
        ymm7 = _mm256_load_ps((float* ) vec.data() + i + 24);
        ymm0 = _mm256_mul_ps(ymm0, ymm4);
        ymm1 = _mm256_mul_ps(ymm1, ymm5);
        ymm2 = _mm256_mul_ps(ymm2, ymm6);
        ymm3 = _mm256_mul_ps(ymm3, ymm7);
        _mm256_store_ps((float* ) data() + i +  0, ymm0);
        _mm256_store_ps((float* ) data() + i +  8, ymm1);
        _mm256_store_ps((float* ) data() + i + 16, ymm2);
        _mm256_store_ps((float* ) data() + i + 24, ymm3);
    }
}

void vortexMath::Vec4x8::operator>>=(const vortexMath::Vec4x8& vec)
{
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7;
    for(int i = 0; i < size(); i+=32)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +   0);
        ymm1 = _mm256_load_ps((float* ) data() + i +   8);
        ymm2 = _mm256_load_ps((float* ) data() + i +  16);
        ymm3 = _mm256_load_ps((float* ) data() + i +  24);
        ymm4 = _mm256_load_ps((float* ) vec.data() + i +  0);
        ymm5 = _mm256_load_ps((float* ) vec.data() + i +  8);
        ymm6 = _mm256_load_ps((float* ) vec.data() + i + 16);
        ymm7 = _mm256_load_ps((float* ) vec.data() + i + 24);
        ymm0 = _mm256_div_ps(ymm0, ymm4);
        ymm1 = _mm256_div_ps(ymm1, ymm5);
        ymm2 = _mm256_div_ps(ymm2, ymm6);
        ymm3 = _mm256_div_ps(ymm3, ymm7);
        _mm256_store_ps((float* ) data() + i +  0, ymm0);
        _mm256_store_ps((float* ) data() + i +  8, ymm1);
        _mm256_store_ps((float* ) data() + i + 16, ymm2);
        _mm256_store_ps((float* ) data() + i + 24, ymm3);
    }
}

void vortexMath::Vec4x8::operator*=(const float value)
{
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4;
    ymm4 = _mm256_set1_ps(value);
    for(int i = 0; i < size(); i+=32)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +  0);
        ymm1 = _mm256_load_ps((float* ) data() + i +  8);
        ymm2 = _mm256_load_ps((float* ) data() + i + 16);
        ymm3 = _mm256_load_ps((float* ) data() + i + 24);
        ymm0 = _mm256_mul_ps(ymm0, ymm4);
        ymm1 = _mm256_mul_ps(ymm1, ymm4);
        ymm2 = _mm256_mul_ps(ymm2, ymm4);
        ymm3 = _mm256_mul_ps(ymm3, ymm4);
        _mm256_store_ps((float* ) data() + i +  0, ymm0);
        _mm256_store_ps((float* ) data() + i +  8, ymm1);
        _mm256_store_ps((float* ) data() + i + 16, ymm2);
        _mm256_store_ps((float* ) data() + i + 24, ymm3);
    }
}
vortexMath::Vec4x8 vortexMath::Vec4x8::operator+(const vortexMath::Vec4x8& vec) const
{
    float * ret = (float* ) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7;
    for(int i = 0; i < size(); i+=32)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +   0);
        ymm1 = _mm256_load_ps((float* ) data() + i +   8);
        ymm2 = _mm256_load_ps((float* ) data() + i +  16);
        ymm3 = _mm256_load_ps((float* ) data() + i +  24);
        ymm4 = _mm256_load_ps((float* ) vec.data() + i +  0);
        ymm5 = _mm256_load_ps((float* ) vec.data() + i +  8);
        ymm6 = _mm256_load_ps((float* ) vec.data() + i + 16);
        ymm7 = _mm256_load_ps((float* ) vec.data() + i + 24);
        ymm0 = _mm256_add_ps(ymm0, ymm4);
        ymm1 = _mm256_add_ps(ymm1, ymm5);
        ymm2 = _mm256_add_ps(ymm2, ymm6);
        ymm3 = _mm256_add_ps(ymm3, ymm7);
        _mm256_store_ps((float* ) ret + i +  0, ymm0);
        _mm256_store_ps((float* ) ret + i +  8, ymm1);
        _mm256_store_ps((float* ) ret + i + 16, ymm2);
        _mm256_store_ps((float* ) ret + i + 24, ymm3);
    }
    Vec4x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec4x8 vortexMath::Vec4x8::operator-(const vortexMath::Vec4x8& vec) const
{
    float * ret = (float* ) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7;
    for(int i = 0; i < size(); i+=32)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +   0);
        ymm1 = _mm256_load_ps((float* ) data() + i +   8);
        ymm2 = _mm256_load_ps((float* ) data() + i +  16);
        ymm3 = _mm256_load_ps((float* ) data() + i +  24);
        ymm4 = _mm256_load_ps((float* ) vec.data() + i +  0);
        ymm5 = _mm256_load_ps((float* ) vec.data() + i +  8);
        ymm6 = _mm256_load_ps((float* ) vec.data() + i + 16);
        ymm7 = _mm256_load_ps((float* ) vec.data() + i + 24);
        ymm0 = _mm256_sub_ps(ymm0, ymm4);
        ymm1 = _mm256_sub_ps(ymm1, ymm5);
        ymm2 = _mm256_sub_ps(ymm2, ymm6);
        ymm3 = _mm256_sub_ps(ymm3, ymm7);
        _mm256_store_ps((float* ) ret + i +  0, ymm0);
        _mm256_store_ps((float* ) ret + i +  8, ymm1);
        _mm256_store_ps((float* ) ret + i + 16, ymm2);
        _mm256_store_ps((float* ) ret + i + 24, ymm3);
    }
    Vec4x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec4x8 vortexMath::Vec4x8::operator<<(const vortexMath::Vec4x8& vec) const
{
    float * ret = (float* ) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7;
    for(int i = 0; i < size(); i+=32)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +   0);
        ymm1 = _mm256_load_ps((float* ) data() + i +   8);
        ymm2 = _mm256_load_ps((float* ) data() + i +  16);
        ymm3 = _mm256_load_ps((float* ) data() + i +  24);
        ymm4 = _mm256_load_ps((float* ) vec.data() + i +  0);
        ymm5 = _mm256_load_ps((float* ) vec.data() + i +  8);
        ymm6 = _mm256_load_ps((float* ) vec.data() + i + 16);
        ymm7 = _mm256_load_ps((float* ) vec.data() + i + 24);
        ymm0 = _mm256_mul_ps(ymm0, ymm4);
        ymm1 = _mm256_mul_ps(ymm1, ymm5);
        ymm2 = _mm256_mul_ps(ymm2, ymm6);
        ymm3 = _mm256_mul_ps(ymm3, ymm7);
        _mm256_store_ps((float* ) ret + i +  0, ymm0);
        _mm256_store_ps((float* ) ret + i +  8, ymm1);
        _mm256_store_ps((float* ) ret + i + 16, ymm2);
        _mm256_store_ps((float* ) ret + i + 24, ymm3);
    }
    Vec4x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec4x8 vortexMath::Vec4x8::operator>>(const vortexMath::Vec4x8& vec) const
{
    float * ret = (float* ) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7;
    for(int i = 0; i < size(); i+=32)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +   0);
        ymm1 = _mm256_load_ps((float* ) data() + i +   8);
        ymm2 = _mm256_load_ps((float* ) data() + i +  16);
        ymm3 = _mm256_load_ps((float* ) data() + i +  24);
        ymm4 = _mm256_load_ps((float* ) vec.data() + i +  0);
        ymm5 = _mm256_load_ps((float* ) vec.data() + i +  8);
        ymm6 = _mm256_load_ps((float* ) vec.data() + i + 16);
        ymm7 = _mm256_load_ps((float* ) vec.data() + i + 24);
        ymm0 = _mm256_div_ps(ymm0, ymm4);
        ymm1 = _mm256_div_ps(ymm1, ymm5);
        ymm2 = _mm256_div_ps(ymm2, ymm6);
        ymm3 = _mm256_div_ps(ymm3, ymm7);
        _mm256_store_ps((float* ) ret + i +  0, ymm0);
        _mm256_store_ps((float* ) ret + i +  8, ymm1);
        _mm256_store_ps((float* ) ret + i + 16, ymm2);
        _mm256_store_ps((float* ) ret + i + 24, ymm3);
    }
    Vec4x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec4x8 vortexMath::Vec4x8::operator*(const float value) const
{
    float * ret = (float* ) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4;
    ymm4 = _mm256_set1_ps(value);
    for(int i = 0; i < size(); i+=32)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +  0);
        ymm1 = _mm256_load_ps((float* ) data() + i +  8);
        ymm2 = _mm256_load_ps((float* ) data() + i + 16);
        ymm3 = _mm256_load_ps((float* ) data() + i + 24);
        ymm0 = _mm256_mul_ps(ymm0, ymm4);
        ymm1 = _mm256_mul_ps(ymm1, ymm4);
        ymm2 = _mm256_mul_ps(ymm2, ymm4);
        ymm3 = _mm256_mul_ps(ymm3, ymm4);
        _mm256_store_ps((float* ) ret + i +  0, ymm0);
        _mm256_store_ps((float* ) ret + i +  8, ymm1);
        _mm256_store_ps((float* ) ret + i + 16, ymm2);
        _mm256_store_ps((float* ) ret + i + 24, ymm3);
    }
    Vec4x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::AlignedVector<float, 32> vortexMath::Vec4x8::operator*(const vortexMath::Vec4x8& vec) const
{
    vortexMath::AlignedVector<float, 32> retVec(vecAmount());
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7;
    for(int i = 0; i < vecAmount(); i+=8)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +   0);
        ymm1 = _mm256_load_ps((float* ) data() + i +   8);
        ymm2 = _mm256_load_ps((float* ) data() + i +  16);
        ymm3 = _mm256_load_ps((float* ) data() + i +  24);
        ymm4 = _mm256_load_ps((float* ) vec.data() + i +  0);
        ymm5 = _mm256_load_ps((float* ) vec.data() + i +  8);
        ymm6 = _mm256_load_ps((float* ) vec.data() + i + 16);
        ymm7 = _mm256_load_ps((float* ) vec.data() + i + 24);
        ymm0 = _mm256_mul_ps(ymm0, ymm4);
        ymm1 = _mm256_fmadd_ps(ymm1, ymm5, ymm0);
        ymm2 = _mm256_fmadd_ps(ymm2, ymm6, ymm1);
        ymm3 = _mm256_fmadd_ps(ymm3, ymm7, ymm2);
        _mm256_store_ps((float* ) retVec.data() + i, ymm3);
    }
    return retVec;
}


vortexMath::AlignedVector<float, 32> vortexMath::Vec4x8::magnitude() const
{
    vortexMath::AlignedVector<float, 32> retVec(vecAmount());
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4;
    for(int i = 0; i < vecAmount(); i+=8)
    {
        ymm0 = _mm256_load_ps((float* ) data() + (i * 4) +  0);
        ymm1 = _mm256_load_ps((float* ) data() + (i * 4) +  8);
        ymm2 = _mm256_load_ps((float* ) data() + (i * 4) + 16);
        ymm3 = _mm256_load_ps((float* ) data() + (i * 4) + 24);
        ymm4 = _mm256_mul_ps(ymm3, ymm3);
        ymm4 = _mm256_fmadd_ps(ymm2, ymm2, ymm4);
        ymm4 = _mm256_fmadd_ps(ymm1, ymm1, ymm4);
        ymm4 = _mm256_fmadd_ps(ymm0, ymm0, ymm4);
        ymm4 = _mm256_sqrt_ps(ymm4);
        _mm256_store_ps((float* ) retVec.data() + i, ymm4);
    }
    return retVec;
}

vortexMath::AlignedVector<float, 32> vortexMath::Vec4x8::squareMagnitude() const
{
    vortexMath::AlignedVector<float, 32> retVec(vecAmount());
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4;
    for(int i = 0; i < vecAmount(); i+=8)
    {
        ymm0 = _mm256_load_ps((float* ) data() + (i * 4) +  0);
        ymm1 = _mm256_load_ps((float* ) data() + (i * 4) +  8);
        ymm2 = _mm256_load_ps((float* ) data() + (i * 4) + 16);
        ymm3 = _mm256_load_ps((float* ) data() + (i * 4) + 24);
        ymm4 = _mm256_mul_ps(ymm3, ymm3);
        ymm4 = _mm256_fmadd_ps(ymm2, ymm2, ymm4);
        ymm4 = _mm256_fmadd_ps(ymm1, ymm1, ymm4);
        ymm4 = _mm256_fmadd_ps(ymm0, ymm0, ymm4);
        _mm256_store_ps((float* ) retVec.data() + i, ymm4);
    }
    return retVec;
}

void vortexMath::Vec4x8::normalize()
{
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5;
    ymm5 = _mm256_set1_ps(1.0f);
    for(int i = 0; i < size(); i+=32)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +  0);
        ymm1 = _mm256_load_ps((float* ) data() + i +  8);
        ymm2 = _mm256_load_ps((float* ) data() + i + 16);
        ymm3 = _mm256_load_ps((float* ) data() + i + 24);
        ymm4 = _mm256_mul_ps(ymm3, ymm3);
        ymm4 = _mm256_fmadd_ps(ymm2, ymm2, ymm4);
        ymm4 = _mm256_fmadd_ps(ymm1, ymm1, ymm4);
        ymm4 = _mm256_fmadd_ps(ymm0, ymm0, ymm4);
        ymm4 = _mm256_sqrt_ps(ymm4);
        ymm4 = _mm256_div_ps(ymm5, ymm4);
        ymm0 = _mm256_mul_ps(ymm0, ymm4);
        ymm1 = _mm256_mul_ps(ymm1, ymm4);
        ymm2 = _mm256_mul_ps(ymm2, ymm4);
        ymm3 = _mm256_mul_ps(ymm3, ymm4);
        _mm256_store_ps((float* ) data() + i +  0, ymm0);
        _mm256_store_ps((float* ) data() + i +  8, ymm1);
        _mm256_store_ps((float* ) data() + i + 16, ymm2);
        _mm256_store_ps((float* ) data() + i + 24, ymm3);
    }
}

void vortexMath::Vec4x8::addScaledVector(const vortexMath::Vec4x8& vec, float scale)
{
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7, ymm8;
    ymm8 = _mm256_set1_ps(scale);
    for(int i = 0; i < size(); i+=32)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +   0);
        ymm1 = _mm256_load_ps((float* ) data() + i +   8);
        ymm2 = _mm256_load_ps((float* ) data() + i +  16);
        ymm3 = _mm256_load_ps((float* ) data() + i +  24);
        ymm4 = _mm256_load_ps((float* ) vec.data() + i +  0);
        ymm5 = _mm256_load_ps((float* ) vec.data() + i +  8);
        ymm6 = _mm256_load_ps((float* ) vec.data() + i + 16);
        ymm7 = _mm256_load_ps((float* ) vec.data() + i + 24);
        ymm0 = _mm256_fmadd_ps(ymm4, ymm8, ymm0);
        ymm1 = _mm256_fmadd_ps(ymm5, ymm8, ymm1);
        ymm2 = _mm256_fmadd_ps(ymm6, ymm8, ymm2);
        ymm3 = _mm256_fmadd_ps(ymm7, ymm8, ymm3);
        _mm256_store_ps((float* ) data() + i +  0, ymm0);
        _mm256_store_ps((float* ) data() + i +  8, ymm1);
        _mm256_store_ps((float* ) data() + i + 16, ymm2);
        _mm256_store_ps((float* ) data() + i + 24, ymm3);
    }
}

void vortexMath::Vec4x8::convertToSOA()
{
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7;
    for (int i = 0; i < size(); i+=32)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +  0);
        ymm1 = _mm256_load_ps((float* ) data() + i +  8);
        ymm2 = _mm256_load_ps((float* ) data() + i + 16);
        ymm3 = _mm256_load_ps((float* ) data() + i + 24);
        
        ymm4 = _mm256_unpacklo_ps(ymm0, ymm1); //x0 x1 y0 y1  x4 x5 y4 y5
        ymm5 = _mm256_unpacklo_ps(ymm2, ymm3); //x2 x3 y2 y3  x6 y6 x7 y7
        ymm6 = _mm256_unpackhi_ps(ymm0, ymm1); //z0 z1 w0 w1  z4 z5 w4 w5
        ymm7 = _mm256_unpackhi_ps(ymm2, ymm3); //z2 z3 w2 w3  z6 z6 w7 w7
        
        ymm0 = _mm256_shuffle_ps(ymm4, ymm5, 0b01000100); //x
        ymm1 = _mm256_shuffle_ps(ymm4, ymm5, 0b11101110); //y
        ymm2 = _mm256_shuffle_ps(ymm6, ymm7, 0b01000100); //x
        ymm3 = _mm256_shuffle_ps(ymm6, ymm7, 0b11101110); //x
        
        _mm256_store_ps((float* ) data() + i +  0, ymm0);
        _mm256_store_ps((float* ) data() + i +  8, ymm1);
        _mm256_store_ps((float* ) data() + i + 16, ymm2);
        _mm256_store_ps((float* ) data() + i + 24, ymm3);
    }
}

void vortexMath::Vec4x8::convertToAOS()
{
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7;
    for (int i = 0; i < size(); i+=32)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +  0);
        ymm1 = _mm256_load_ps((float* ) data() + i +  8);
        ymm2 = _mm256_load_ps((float* ) data() + i + 16);
        ymm3 = _mm256_load_ps((float* ) data() + i + 24);
        ymm4 = _mm256_unpacklo_ps(ymm0, ymm1); 
        ymm5 = _mm256_unpacklo_ps(ymm2, ymm3);
        ymm6 = _mm256_unpackhi_ps(ymm0, ymm1);
        ymm7 = _mm256_unpackhi_ps(ymm2, ymm3);
        ymm0 = _mm256_shuffle_ps(ymm4, ymm5, 0b01000100);
        ymm1 = _mm256_shuffle_ps(ymm4, ymm5, 0b11101110);
        ymm2 = _mm256_shuffle_ps(ymm6, ymm7, 0b01000100);
        ymm3 = _mm256_shuffle_ps(ymm6, ymm7, 0b11101110);
        _mm256_store_ps((float* ) data() + i +  0, ymm0);
        _mm256_store_ps((float* ) data() + i +  8, ymm1);
        _mm256_store_ps((float* ) data() + i + 16, ymm2);
        _mm256_store_ps((float* ) data() + i + 24, ymm3);
    }
}

vortexMath::Vec4x8 vortexMath::Vec4x8::retrieveSOAForm() const
{
    float * ret = (float*) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7;
    for (int i = 0; i < size(); i+=32)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +  0);
        ymm1 = _mm256_load_ps((float* ) data() + i +  8);
        ymm2 = _mm256_load_ps((float* ) data() + i + 16);
        ymm3 = _mm256_load_ps((float* ) data() + i + 24);
        ymm4 = _mm256_unpacklo_ps(ymm0, ymm1); //x0 x1 y0 y1  x4 x5 y4 y5
        ymm5 = _mm256_unpacklo_ps(ymm2, ymm3); //x2 x3 y2 y3  x6 y6 x7 y7
        ymm6 = _mm256_unpackhi_ps(ymm0, ymm1); //z0 z1 w0 w1  z4 z5 w4 w5
        ymm7 = _mm256_unpackhi_ps(ymm2, ymm3); //z2 z3 w2 w3  z6 z6 w7 w7
        ymm0 = _mm256_shuffle_ps(ymm4, ymm5, 0b01000100); //x
        ymm1 = _mm256_shuffle_ps(ymm4, ymm5, 0b11101110); //y
        ymm2 = _mm256_shuffle_ps(ymm6, ymm7, 0b01000100); //x
        ymm3 = _mm256_shuffle_ps(ymm6, ymm7, 0b11101110); //x
        _mm256_store_ps((float* ) ret + i +  0, ymm0);
        _mm256_store_ps((float* ) ret + i +  8, ymm1);
        _mm256_store_ps((float* ) ret + i + 16, ymm2);
        _mm256_store_ps((float* ) ret + i + 24, ymm3);
    }
    Vec4x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::Vec4x8 vortexMath::Vec4x8::retrieveAOSForm() const
{
    float * ret = (float*) aligned_alloc(32, size() * sizeof(float));
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7;
    for (int i = 0; i < size(); i+=32)
    {
        ymm0 = _mm256_load_ps((float* ) data() + i +  0);
        ymm1 = _mm256_load_ps((float* ) data() + i +  8);
        ymm2 = _mm256_load_ps((float* ) data() + i + 16);
        ymm3 = _mm256_load_ps((float* ) data() + i + 24);
        ymm4 = _mm256_unpacklo_ps(ymm0, ymm1); 
        ymm5 = _mm256_unpacklo_ps(ymm2, ymm3);
        ymm6 = _mm256_unpackhi_ps(ymm0, ymm1);
        ymm7 = _mm256_unpackhi_ps(ymm2, ymm3);
        ymm0 = _mm256_shuffle_ps(ymm4, ymm5, 0b01000100);
        ymm1 = _mm256_shuffle_ps(ymm4, ymm5, 0b11101110);
        ymm2 = _mm256_shuffle_ps(ymm6, ymm7, 0b01000100);
        ymm3 = _mm256_shuffle_ps(ymm6, ymm7, 0b11101110);
        _mm256_store_ps((float* ) ret + i +  0, ymm0);
        _mm256_store_ps((float* ) ret + i +  8, ymm1);
        _mm256_store_ps((float* ) ret + i + 16, ymm2);
        _mm256_store_ps((float* ) ret + i + 24, ymm3);
    }
    Vec4x8 retVec{ret, vecAmount()};
    free(ret);
    return retVec;
}

vortexMath::AlignedVector<float, 32> vortexMath::Vec4x8::get(const vortexMath::VecElementType t) const
{
    vortexMath::AlignedVector<float, 32> retVec(vecAmount());
    for(int i = 0; i < vecAmount(); i+=8)
    {
        _mm256_store_ps((float* ) retVec.data() + i, _mm256_load_ps((float* ) data() + (i * 4) + (t * 2)));
    }
    return retVec;
}

void vortexMath::Vec4x8::set(const vortexMath::VecElementType t, float val)
{
    __m256 ymm0 = _mm256_set1_ps(val);
    for(int i = 0; i < vecAmount(); i+=8)
    {   
        _mm256_store_ps((float* ) data() + (i * 4) + (t * 2), ymm0);
    }
}

void vortexMath::Vec4x8::set(const VecElementType t, const vortexMath::AlignedVector<float, 32>& values)
{
    for(int i = 0; i < vecAmount(); i+=8)
    {
        _mm256_store_ps((float* ) data() + (i * 4) + (t * 2), _mm256_load_ps((float* ) values.data() + i));
    }
}
