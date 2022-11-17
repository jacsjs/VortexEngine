/**
 * Basic Vec2, Vec3 and Vec4 template classes
 */

#pragma once

#pragma GCC optimize("O3","omit-frame-pointer","inline")
#pragma GCC target("avx2", "fma")

#include <math.h>
    
namespace vortexMath
{
    template <class T3> class Vec3;
    template <class T4> class Vec4;

    template <class T2>
    class Vec2
    {
    private:
        struct alignas(32)
        {
            T2 x, y;
        };
        
        
    public:
        
        Vec2<T2>() 
        : 
        x(0), y(0)
        {
        }
        
        Vec2<T2>(T2 e) 
        : 
        x(e), y(e)
        {
        }
        
        Vec2<T2>(T2 x, T2 y) 
        : 
        x(x), y(y)
        {
        }

        inline static Vec2<T2> vec2() { return Vec2<T2>(); }
        inline static Vec2<T2> vec2(const T2 e) { return Vec2<T2>(e); }
        inline static Vec2<T2> vec2(const T2 x, const T2 y) { return Vec2<T2>(x, y); }
        inline static Vec2<T2> vec2(const Vec3<T2>& vec) { return Vec2<T2>(vec.getX(), vec.getY()); }
        inline static Vec2<T2> vec2(const Vec4<T2>& vec) { return Vec2<T2>(vec.getX(), vec.getY()); }
        
        inline void operator  +=(const Vec2<T2>& vec) {x+=vec.x; y+=vec.y;}
        inline void operator  -=(const Vec2<T2>& vec) {x-=vec.x; y-=vec.y;}
        inline void operator <<=(const Vec2<T2>& vec) {x*=vec.x; y*=vec.y;}
        inline void operator >>=(const Vec2<T2>& vec) {x/=vec.x; y/=vec.y;}
        
        inline Vec2<T2> operator +(const Vec2<T2>& vec) const { return Vec2<T2>(x+vec.x, y+vec.y); }
        inline Vec2<T2> operator -(const Vec2<T2>& vec) const { return Vec2<T2>(x-vec.x, y-vec.y); }
        inline Vec2<T2> operator<<(const Vec2<T2>& vec) const { return Vec2<T2>(x*vec.x, y*vec.y); }
        inline Vec2<T2> operator>>(const Vec2<T2>& vec) const { return Vec2<T2>(x/vec.x, y/vec.y); }
        
        inline T2 operator*(const Vec2<T2>& vec) const { return x*vec.x + y*vec.y;}
        
        inline void operator+=(const T2 e) {x+=e; y+=e;}
        inline void operator-=(const T2 e) {x-=e; y-=e;}
        inline void operator*=(const T2 e) {x*=e; y*=e;}
        
        inline Vec2<T2> operator+(const T2 e) const { return Vec2<T2>(x+e, y+e); }
        inline Vec2<T2> operator-(const T2 e) const { return Vec2<T2>(x-e, y-e); }
        inline Vec2<T2> operator*(const T2 e) const { return Vec2<T2>(x*e, y*e); }
        
        inline void addScaledVector(const Vec2<T2>& vec, T2 scale) { x+=vec.x*scale; y+=vec.y*scale; }
        
        inline T2 magnitude() const { return (T2) sqrt(x*x+y*y); }
        
        inline T2 squaredMagnitude() const { return x*x+y*y; }
        
        inline void normalize()
        {
            T2 mag = magnitude();
            
            if (mag < 0.00001f) return;
            
            x /= mag;
            y /= mag;
        }
        
        inline T2 getX() const { return x; }
        inline T2 getY() const { return y; }
        
        inline const T2 * data() const { return &x; }
    };

    template <class T3>
    class Vec3
    {
    private:
        struct alignas(32)
        {
            T3 x, y, z;
        };
        
    public:
        
        Vec3<T3>() 
        : 
        x(0), y(0), z(0)
        {
        }
        
        Vec3<T3>(T3 e) 
        : 
        x(e), y(e), z(e)
        {
        }
        
        Vec3<T3>(T3 x, T3 y, T3 z) 
        : 
        x(x), y(y), z(z)
        {
        }
        
        inline static Vec3<T3> vec3() { return Vec3<T3>(); };
        inline static Vec3<T3> vec3(const T3 e) { return Vec3<T3>(e); };
        inline static Vec3<T3> vec3(const T3 x, const T3 y, const T3 z) { return Vec3<T3>(x, y, z); };
        inline static Vec3<T3> vec3(const Vec2<T3>& vec, const T3 z) { return Vec3<T3>(vec.getX(), vec.getY(), z); }
        inline static Vec3<T3> vec3(const Vec4<T3>& vec) { return Vec3<T3>(vec.getX(), vec.getY(), vec.getZ()); }
        
        inline void operator  +=(const Vec3<T3>& vec) {x+=vec.x; y+=vec.y; z+=vec.z; }
        inline void operator  -=(const Vec3<T3>& vec) {x-=vec.x; y-=vec.y; z-=vec.z; }
        inline void operator <<=(const Vec3<T3>& vec) {x*=vec.x; y*=vec.y; z*=vec.z; }
        inline void operator >>=(const Vec3<T3>& vec) {x/=vec.x; y/=vec.y; z/=vec.z; }
        
        inline Vec3<T3> operator +(const Vec3<T3>& vec) const { return Vec3<T3>(x+vec.x, y+vec.y, z+vec.z); }
        inline Vec3<T3> operator -(const Vec3<T3>& vec) const { return Vec3<T3>(x-vec.x, y-vec.y, z-vec.z); }
        inline Vec3<T3> operator<<(const Vec3<T3>& vec) const { return Vec3<T3>(x*vec.x, y*vec.y, z*vec.z); }
        inline Vec3<T3> operator>>(const Vec3<T3>& vec) const { return Vec3<T3>(x/vec.x, y/vec.y, z/vec.z); }
        inline Vec3<T3> operator %(const Vec3<T3>& vec) const { return Vec3<T3>(y*vec.z-z*vec.y, z*vec.x-x*vec.z, x*vec.y-y*vec.x); };
        
        inline T3 operator*(const Vec3<T3>& vec) const { return x*vec.x + y*vec.y + z*vec.z; }
        
        inline void operator+=(const T3 e) {x+=e; y+=e; z+=e; }
        inline void operator-=(const T3 e) {x-=e; y-=e; z-=e; }
        inline void operator*=(const T3 e) {x*=e; y*=e; z*=e; }
        
        inline Vec3<T3> operator+(const T3 e) const { return Vec3<T3>(x+e, y+e, z+e); }
        inline Vec3<T3> operator-(const T3 e) const { return Vec3<T3>(x-e, y-e, z-e); }
        inline Vec3<T3> operator*(const T3 e) const { return Vec3<T3>(x*e, y*e, z*e); }
        
        inline void addScaledVector(const Vec3<T3>& vec, T3 scale) { x+=vec.x*scale; y+=vec.y*scale; z+=vec.z*scale; }
        
        inline T3 magnitude() const { return (T3) sqrt(x*x+y*y+z*z); }
        
        inline T3 squaredMagnitude() const { return x*x+y*y+z*z; }
        
        inline void normalize()
        {
            T3 mag = magnitude();
            
            if (mag < 0.00001f) return;
            
            x /= mag;
            y /= mag;
            z /= mag;
        }
        
        inline T3 getX() const { return x; }
        inline T3 getY() const { return y; }
        inline T3 getZ() const { return z; }
        
        inline const T3 * data() const { return &x; }
    };

    template <class T4>
    class Vec4
    {
    private:
        struct alignas(32)
        {
            T4 x, y, z, w;
        };
        
    public:
        
        Vec4<T4>() 
        : 
        x(0), y(0), z(0), w(0)
        {
        }
        
        Vec4<T4>(T4 e) 
        : 
        x(e), y(e), z(e), w(e)
        {
        }

        Vec4<T4>(T4 x, T4 y, T4 z, T4 w) 
        : 
        x(x), y(y), z(z), w(w)
        {
        }

        inline static Vec4<T4> vec4() { return Vec4<T4>(); };
        inline static Vec4<T4> vec4(const T4 e) { return Vec4<T4>(e); };
        inline static Vec4<T4> vec4(const T4 x, const T4 y, const T4 z, const T4 w) { return Vec4<T4>(x, y, z, w); }
        inline static Vec4<T4> vec4(const Vec2<T4>& vec, const T4 z, const T4 w) { return Vec4<T4>(vec.getX(), vec.getY(), z, w); }
        inline static Vec4<T4> vec4(const Vec3<T4>& vec, const T4 w) { return Vec4<T4>(vec.getX(), vec.getY(), vec.getZ(), w); }
        
        inline void operator  +=(const Vec4<T4>& vec) {x+=vec.x; y+=vec.y; z+=vec.z; w+=vec.w; }
        inline void operator  -=(const Vec4<T4>& vec) {x-=vec.x; y-=vec.y; z-=vec.z; w-=vec.w; }
        inline void operator <<=(const Vec4<T4>& vec) {x*=vec.x; y*=vec.y; z*=vec.z; w*=vec.w; }
        inline void operator >>=(const Vec4<T4>& vec) {x/=vec.x; y/=vec.y; z/=vec.z; w/=vec.w; }
        
        inline Vec4<T4> operator +(const Vec4<T4>& vec) const { return Vec4<T4>(x+vec.x, y+vec.y, z+vec.z, w+vec.w); }
        inline Vec4<T4> operator -(const Vec4<T4>& vec) const { return Vec4<T4>(x-vec.x, y-vec.y, z-vec.z, w-vec.w); }
        inline Vec4<T4> operator<<(const Vec4<T4>& vec) const { return Vec4<T4>(x*vec.x, y*vec.y, z*vec.z, w*vec.w); }
        inline Vec4<T4> operator>>(const Vec4<T4>& vec) const { return Vec4<T4>(x/vec.x, y/vec.y, z/vec.z, w/vec.w); }
        
        inline T4 operator*(const Vec4<T4>& vec) const { return x*vec.x + y*vec.y + z*vec.z + w*vec.w; }
        
        inline void operator+=(const T4 e) {x+=e; y+=e; z+=e; w+=e; }
        inline void operator-=(const T4 e) {x-=e; y-=e; z-=e; w-=e; }
        inline void operator*=(const T4 e) {x*=e; y*=e; z*=e; w*=e; }
        
        inline Vec4<T4> operator+(const T4 e) const { return Vec4<T4>(x+e, y+e, z+e, w+e); }
        inline Vec4<T4> operator-(const T4 e) const { return Vec4<T4>(x-e, y-e, z-e, w-e); }
        inline Vec4<T4> operator*(const T4 e) const { return Vec4<T4>(x*e, y*e, z*e, w*e); }
        
        inline void addScaledVector(const Vec4<T4>& vec, T4 scale) { x+=vec.x*scale; y+=vec.y*scale; z+=vec.z*scale; w+=vec.w*scale; }
        
        inline T4 magnitude() const { return (T4) sqrt(x*x+y*y+z*z+w*w); }
        
        inline T4 squaredMagnitude() const { return x*x+y*y+z*z+w*w; }
        
        inline void normalize()
        {
            T4 mag = magnitude();
            
            if (mag < 0.00001f) return;
            
            x /= mag;
            y /= mag;
            z /= mag;
            w /= mag;
        }
        
        inline T4 getX() const { return x; };
        inline T4 getY() const { return y; };
        inline T4 getZ() const { return z; };
        inline T4 getW() const { return w; }; 
        
        inline const T4 * data() const { return &x; }
    };
};
