#include "math/quaternion.hpp"

vortexMath::Quaternion::Quaternion(const Vec3<float>& vec, float rad)
{
    float s = sin(rad * 0.5f);
    i = vec.getX() * s;
    j = vec.getY() * s;
    k = vec.getZ() * s;
    w = cos(rad * 0.5f);
}

vortexMath::Quaternion vortexMath::Quaternion::conjugate() const
{
    return Quaternion(-i, -j, -k, w);
}

void vortexMath::Quaternion::operator*=(const vortexMath::Quaternion& q2)
{
    float i2 = w*q2.i + i*q2.w + j*q2.k - k*q2.j;
    float j2 = w*q2.j - i*q2.k + j*q2.w + k*q2.i;
    float k2 = w*q2.k + i*q2.j - j*q2.i + k*q2.w;
    float w2 = w*q2.w - i*q2.i - j*q2.j - k*q2.k;
        
    i = i2;
    j = j2;
    k = k2;
    w = w2;
}

vortexMath::Quaternion vortexMath::Quaternion::operator*(const vortexMath::Quaternion& q2) const
{
    return Quaternion
    (
        w*q2.i + i*q2.w + j*q2.k - k*q2.j,
        w*q2.j - i*q2.k + j*q2.w + k*q2.i,
        w*q2.k + i*q2.j - j*q2.i + k*q2.w,
        w*q2.w - i*q2.i - j*q2.j - k*q2.k
    );
}

void vortexMath::Quaternion::normalize()
{
    float mag = i*i + j*j + k*k + w*w;
        
    if (mag == 0.0f){ w = 1.0f; return; }
    
    mag = 1.0f / sqrt(mag);

    i *= mag;
    j *= mag;
    k *= mag;
    w *= mag;
}

void vortexMath::Quaternion::rotateByVector(const Vec3<float>& vec)
{
    Quaternion q(vec.getX(), vec.getY(), vec.getZ(), 0.0f);
    (*this) *= q;
}

void vortexMath::Quaternion::addScaledVector(const Vec3<float>& vec, float scale)
{
    Quaternion q(vec.getX() * scale, vec.getY() * scale, vec.getZ() * scale, 0.0f);
    q *= *this;
    
    i += q.i * 0.5f;
    j += q.j * 0.5f;
    k += q.k * 0.5f;
    w += q.w * 0.5f;
}
