#pragma once

#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline")
#pragma GCC target("avx", "fma")

#include "vec.hpp"

namespace vortexMath
{
    class Quaternion
    {
    private:    
        struct
        {
            float i, j, k, w;
        };
    public:
        
        Quaternion() 
            : i(0.0f), j(0.0f), k(0.0f), w(1.0f)
        {
        }
        
        Quaternion(const float i, const float j, const float k, const float w) 
            : i(i), j(j), k(k), w(w)
        {
        }
        
        Quaternion(const Vec3<float>& vec, float rad);
        
        Quaternion conjugate() const;
        
        void operator*=(const Quaternion& q2);
        
        Quaternion operator*(const Quaternion& q2) const;
        
        void normalize();
        
        void rotateByVector(const Vec3<float>& vec);
        
        void addScaledVector(const Vec3<float>& vec, float scale);
        
        inline const float getI() const { return i; }
        inline const float getJ() const { return j; }
        inline const float getK() const { return k; }
        inline const float getW() const { return w; }
        inline float * data() { return &i; }
    };
};
