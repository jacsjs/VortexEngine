#pragma once

#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline")
#pragma GCC target("avx2", "fma")

#include <immintrin.h>
#include <math.h> 

#include "mat.hpp"
#include "alignedVector.hpp"
    
namespace vortexMath
{
    //Forward declerations, not full class specification for this file.
    class Vec3x4;
    class Vec4x4;
    class Vec3x8;
    class Vec4x8;
    enum VecElementType
    {
        VEC_ELEMENT_X = 0,
        VEC_ELEMENT_Y = 4,
        VEC_ELEMENT_Z = 8,
        VEC_ELEMENT_W = 12
    };
    
    class Vec2x4
    {
    private:
        
        AlignedVector<float, 16> vecData{ 8 };
        
        int vecCount;

    public:
        
        /**
         * Reserve the given amount of vectors, default is 4.
         */
        Vec2x4(const int vectors=4);
        
        /**
         * Fill the vector with a given float, and int number of vectors, default is 4.
         */
        Vec2x4(const float value, int vectors=4);
        
        /**
         * Fill the vector with a given array of float data, only the requested amount of vectors are copied.
         */
        Vec2x4(const float* data, int vectors=4);
        
        /**
         * Fill the vector with predefined values, NOTE: This will result in this vector to be in SOA form.
         */
        Vec2x4(const AlignedVector<float, 16>& x, const AlignedVector<float, 16>& y,  const int vectors=4);
        
        /**
         * Create and returns a new vector @see Vec2x4()
         */
        inline static Vec2x4 vec2x4(const int vectors=4) { return Vec2x4(vectors); }
        
        /**
         * Create and returns a new vector @see Vec2x4(const float* data)
         */
        inline static Vec2x4 vec2x4(const float* data, const int vectors=4) { return Vec2x4(data, vectors); }
        
        /**
         * Create and returns a new vector @see Vec2x4(const AlignedVector<float, 16>& x, const AlignedVector<float, 16>& y)
         */
        inline static Vec2x4 vec2x4(const AlignedVector<float, 16>& x, const AlignedVector<float, 16>& y, const int vectors=4) 
        { return Vec2x4(x, y, vectors); }
        
        /**
         * Create a new Vec2x4 from the given Vec3x4, the z element will be ignored, NOTE: SOA data is required.
         */
        static Vec2x4 vec2x4(const Vec3x4& vec);
        
        /**
         * Create a new Vec2x4 from the given Vec4x4, the z and w elements will be ignored, NOTE: SOA data is required.
         */
        static Vec2x4 vec2x4(const Vec4x4& vec);
        
        /**
         * Component wise addition on this vector and the given Vec2x4.
         */
        void operator  +=(const Vec2x4& vec);
        
        /**
         * Component wise subtraction on this vector and the given Vec2x4.
         */
        void operator  -=(const Vec2x4& vec);
        
        /**
         * Component wise multiplication on this vector and the given Vec2x4.
         */
        void operator <<=(const Vec2x4& vec);
        
        /**
         * Component wise division on this vector and the given Vec2x4.
         */
        void operator >>=(const Vec2x4& vec);
        
        /**
         * Component wise multiplication on this vector with the given float value
         */
        void operator  *=(const float value);
        
        /**
         * @return Vec2x4 Result of component wise addition of this and the given Vec2x4.
         */
        Vec2x4 operator +(const Vec2x4& vec) const;
        
        /**
         * @return Vec2x4 Result of component wise subtraction of this and the given Vec2x4.
         */
        Vec2x4 operator -(const Vec2x4& vec) const;
        
        /**
         * @return Vec2x4 Result of component wise multiplication of this and the given Vec2x4.
         */
        Vec2x4 operator<<(const Vec2x4& vec) const;
        
        /**
         * @return Vec2x4 Result of component wise division of this and the given Vec2x4.
         */
        Vec2x4 operator>>(const Vec2x4& vec) const;
        
        /**
         * @return Vec2x4 Result of component wise multiplication of this with the given float value.
         */
        Vec2x4 operator *(const float value) const;
        
        /**
         * @return AlignedVector<float, 16> Dot-product of this vector and the given vector.
         */
        AlignedVector<float, 16> operator*(const Vec2x4& vec) const;
        
        /**
         * Normalizes this vector.
         */
        void normalize();
        
        /**
         * @return AlignedVector<float, 16> Magnitude of this vector.
         */
        AlignedVector<float, 16> magnitude() const;
        
        /**
         * @return AlignedVector<float, 16> Square magnitude of this vector.
         */
        AlignedVector<float, 16> squareMagnitude() const;
        
        
        /**
         * Fused multiply-add function on this vector.
         */
        void addScaledVector(const Vec2x4& vec, float scale);
        
        /**
         * Sets the given element type to the given value.
         */
        void set(const VecElementType t, float val);
        
        /**
         * Sets the given element type to the given array.
         */
        void set(const VecElementType t, const AlignedVector<float, 16>& values);
        
        /**
         * Returns the given element type in array form.
         */
        AlignedVector<float, 16> get(const VecElementType t) const;
        
        /**
         * Converts this vector to SOA form (column major), required before calculations.
         */
        void convertToSOA();
        
        /**
         * Converts this vector to AOS form (row major).
         */
        void convertToAOS();
        
        /**
         * @return Vec2x4 This converted to AOS (row major).
         */
        Vec2x4 retrieveAOSForm() const;
        
        /**
         * @return Vec2x4 This converted to SOA (column major).
         */
        Vec2x4 retrieveSOAForm() const;
        
        inline float * data() { return vecData.data(); }
        inline const float * data() const noexcept { return vecData.data(); }
        
        inline int vecAmount() const { return vecCount; }
        inline int size() const { return vecCount * 2; }
    };

    class Vec3x4
    {
    private: 
        AlignedVector<float, 16> vecData{ 12 };
        
        int vecCount;
        
    public:
        
        /**
         * Reserve the given amount of vectors, default is 4.
         */
        Vec3x4(const int vectors=4);
        
        /**
         * Fill the vector with a given float, and int number of vectors, default is 4.
         */
        Vec3x4(const float value, int vectors=4);
        
        /**
         * Fill the vector with a given array of float data, only the requested amount of vectors are copied.
         */
        Vec3x4(const float* data, int vectors=4);
        
        /**
         * Fill the vector with predefined values, NOTE: This will result in this vector to be in SOA form.
         */
        Vec3x4(const AlignedVector<float, 16>& x, const AlignedVector<float, 16>& y, const AlignedVector<float, 16>& z, const int vectors=4);
        
        /**
         * Create and returns a new vector @see Vec3x4()
         */
        inline static Vec3x4 vec3x4(const int vectors=4) { return Vec3x4(vectors); }
        
        /**
         * Create and returns a new vector @see Vec3x4(const float* data)
         */
        inline static Vec3x4 vec3x4(const float* data, const int vectors=4) { return Vec3x4(data, vectors); }
        
        /**
         * Create and returns a new vector @see Vec3x4(const AlignedVector<float, 16>& x, const AlignedVector<float, 16>& y, const AlignedVector<float, 16>& z)
         */
        inline static Vec3x4 vec3x4(const AlignedVector<float, 16>& x, const AlignedVector<float, 16>& y, const AlignedVector<float, 16>& z, const int vectors=4) 
        { return Vec3x4(x, y, z, vectors); }
        
        /**
         * Create a new Vec3x4 from the given Vec2x4, with the given additional z element, NOTE: SOA data is required.
         */
        static Vec3x4 vec3x4(const Vec2x4& vec, const AlignedVector<float, 16>& z);
        
        /**
         * Create a new Vec3x4 from the given Vec4x4, the z and w elements will be ignored, NOTE: SOA data is required.
         */
        static Vec3x4 vec3x4(const Vec4x4& vec);
        
        /**
         * Component wise addition on this vector and the given Vec3x4.
         */
        void operator  +=(const Vec3x4& vec);
        
        /**
         * Component wise subtraction on this vector and the given Vec3x4.
         */
        void operator  -=(const Vec3x4& vec);
        
        /**
         * Component wise multiplication on this vector and the given Vec3x4.
         */
        void operator <<=(const Vec3x4& vec);
        
        /**
         * Component wise division on this vector and the given Vec3x4.
         */
        void operator >>=(const Vec3x4& vec);
        
        /**
         * Reassign this as the cross product of this and the given vector.
         */
        void operator%=(const Vec3x4& vec);
        
        /**
         * Component wise multiplication on this vector with the given float value
         */
        void operator  *=(const float value);
        
        /**
         * @return Vec3x4 Result of component wise addition of this and the given Vec3x4.
         */
        Vec3x4 operator +(const Vec3x4& vec) const;
        
        /**
         * @return Vec3x4 Result of component wise subtraction of this and the given Vec3x4.
         */
        Vec3x4 operator -(const Vec3x4& vec) const;
        
        /**
         * @return Vec3x4 Result of component wise multiplication of this and the given Vec3x4.
         */
        Vec3x4 operator<<(const Vec3x4& vec) const;
        
        /**
         * @return Vec3x4 Result of component wise division of this and the given Vec3x4.
         */
        Vec3x4 operator>>(const Vec3x4& vec) const;
        
        /**
         * @return Vec3x4 Vector product of this and the given vector.
         */
        Vec3x4 operator%(const Vec3x4& vec) const;
        
        /**
         * @return Vec3x4 Result of component wise multiplication of this with the given float value.
         */
        Vec3x4 operator *(const float value) const;
        
        /**
         * @return AlignedVector<float, 16> Dot-product of this vector and the given vector.
         */
        AlignedVector<float, 16> operator*(const Vec3x4& vec) const;
        
        /**
         * Normalizes this vector.
         */
        void normalize();
        
        /**
         * @return AlignedVector<float, 16> Magnitude of this vector.
         */
        AlignedVector<float, 16> magnitude() const;
        
        /**
         * @return AlignedVector<float, 16> Square magnitude of this vector.
         */
        AlignedVector<float, 16> squareMagnitude() const;
        
        
        /**
         * Fused multiply-add function on this vector.
         */
        void addScaledVector(const Vec3x4& vec, float scale);
        
        /**
         * Generate an orthonormal Basis for this vector.
         * 
         * @param int End Index of which vector the basis should be generated from,
         * the right and up vectors will be located at endIndex -1 and endIndex -2 respectively.
         */
        void generateOrthonormalBasis(const int endIndex);
        
        /**
         * Sets the given element type to the given value.
         */
        void set(const VecElementType t, float val);
        
        /**
         * Sets the given element type to the given array.
         */
        void set(const VecElementType t, const AlignedVector<float, 16>& values);
        
        /**
         * Returns the given element type in array form.
         */
        AlignedVector<float, 16> get(const VecElementType t) const;
        
        /**
         * Converts this vector to SOA form (column major), required before calculations.
         */
        void convertToSOA();
        
        /**
         * Converts this vector to AOS form (row major).
         */
        void convertToAOS();
        
        /**
         * @return Vec3x4 This converted to AOS (row major).
         */
        Vec3x4 retrieveAOSForm() const;
        
        /**
         * @return Vec3x4 This converted to SOA (column major).
         */
        Vec3x4 retrieveSOAForm() const;
        
        inline float * data() { return vecData.data(); }
        inline const float * data() const noexcept { return vecData.data(); }
        
        inline int vecAmount() const { return vecCount; }
        inline int size() const { return vecCount * 3; }
    };

    class Vec4x4
    {
    private:
        
        AlignedVector<float, 16> vecData{ 16 };
        
        int vecCount;
        
    public:
        
        /**
         * Reserve the given amount of vectors, default is 4.
         */
        Vec4x4(const int vectors=4);
        
        /**
         * Fill the vector with a given float, and int number of vectors, default is 4.
         */
        Vec4x4(const float value, int vectors=4);
        
        /**
         * Fill the vector with a given array of float data, only the requested amount of vectors are copied.
         */
        Vec4x4(const float* data, int vectors=4);
        
        /**
         * Fill the vector with predefined values, NOTE: This will result in this vector to be in SOA form.
         */
        Vec4x4(const AlignedVector<float, 16>& x, const AlignedVector<float, 16>& y, const AlignedVector<float, 16>& z, const AlignedVector<float, 16>& w, const int vectors=4);
        
        /**
         * Create and returns a new vector @see Vec4x4()
         */
        inline static Vec4x4 vec4x4(const int vectors=4) { return Vec4x4(vectors); }
        
        /**
         * Create and returns a new vector @see Vec4x4(const float* data)
         */
        inline static Vec4x4 vec4x4(const float* data, const int vectors=4) { return Vec4x4(data, vectors); }
        
        /**
         * Create and returns a new vector @see Vec4x4(const AlignedVector<float, 16>& x, const AlignedVector<float, 16>& y, const AlignedVector<float, 16>& z, const AlignedVector<float, 16>& w)
         */
        inline static Vec4x4 vec4x4(const AlignedVector<float, 16>& x, const AlignedVector<float, 16>& y, const AlignedVector<float, 16>& z, const AlignedVector<float, 16>& w, const int vectors=4) 
        { return Vec4x4(x, y, z, w, vectors); }
        
        /**
         * Create a new Vec4x4 from the given Vec3x4, with the additional z and w elements, NOTE: SOA data is required.
         */
        static Vec4x4 vec4x4(const Vec2x4& vec, const AlignedVector<float, 16>& z, const AlignedVector<float, 16>& w);
        
        /**
         * Create a new Vec4x4 from the given Vec4x4, with the additional w element, NOTE: SOA data is required.
         */
        static Vec4x4 vec4x4(const Vec3x4& vec, const AlignedVector<float, 16>& w);
        
        /**
         * Component wise addition on this vector and the given Vec4x4.
         */
        void operator  +=(const Vec4x4& vec);
        
        /**
         * Component wise subtraction on this vector and the given Vec4x4.
         */
        void operator  -=(const Vec4x4& vec);
        
        /**
         * Component wise multiplication on this vector and the given Vec4x4.
         */
        void operator <<=(const Vec4x4& vec);
        
        /**
         * Component wise division on this vector and the given Vec4x4.
         */
        void operator >>=(const Vec4x4& vec);
        
        /**
         * Component wise multiplication on this vector with the given float value
         */
        void operator  *=(const float value);
        
        /**
         * @return Vec4x4 Result of component wise addition of this and the given Vec4x4.
         */
        Vec4x4 operator +(const Vec4x4& vec) const;
        
        /**
         * @return Vec4x4 Result of component wise subtraction of this and the given Vec4x4.
         */
        Vec4x4 operator -(const Vec4x4& vec) const;
        
        /**
         * @return Vec4x4 Result of component wise multiplication of this and the given Vec4x4.
         */
        Vec4x4 operator<<(const Vec4x4& vec) const;
        
        /**
         * @return Vec4x4 Result of component wise division of this and the given Vec4x4.
         */
        Vec4x4 operator>>(const Vec4x4& vec) const;
        
        /**
         * @return Vec4x4 Result of component wise multiplication of this with the given float value.
         */
        Vec4x4 operator *(const float value) const;
        
        /**
         * @return AlignedVector<float, 16> Dot-product of this vector and the given vector.
         */
        AlignedVector<float, 16> operator*(const Vec4x4& vec) const;
        
        /**
         * Normalizes this vector.
         */
        void normalize();
        
        /**
         * @return AlignedVector<float, 16> Magnitude of this vector.
         */
        AlignedVector<float, 16> magnitude() const;
        
        /**
         * @return AlignedVector<float, 16> Square magnitude of this vector.
         */
        AlignedVector<float, 16> squareMagnitude() const;
        
        
        /**
         * Fused multiply-add function on this vector.
         */
        void addScaledVector(const Vec4x4& vec, float scale);
        
        /**
         * Sets the given element type to the given value.
         */
        void set(const VecElementType t, float val);
        
        /**
         * Sets the given element type to the given array.
         */
        void set(const VecElementType t, const AlignedVector<float, 16>& values);
        
        /**
         * Returns the given element type in array form.
         */
        AlignedVector<float, 16> get(const VecElementType t) const;
        
        /**
         * Converts this vector to SOA form (column major), required before calculations.
         */
        void convertToSOA();
        
        /**
         * Converts this vector to AOS form (row major).
         */
        void convertToAOS();
        
        /**
         * @return Vec4x4 This converted to AOS (row major).
         */
        Vec4x4 retrieveAOSForm() const;
        
        /**
         * @return Vec4x4 This converted to SOA (column major).
         */
        Vec4x4 retrieveSOAForm() const;
        
        /**
         * Generate an orthonormal Basis for this vector.
         * 
         * @param int End Index of which vector the basis should be generated from,
         * the right and up vectors will be located at endIndex -1 and endIndex -2 respectively.
         */
        void generateOrthonormalBasis(const int endIndex);
        
        inline float * data() { return vecData.data(); }
        inline const float * data() const noexcept { return vecData.data(); }
        
        inline int vecAmount() const { return vecCount; }
        inline int size() const { return vecCount * 4; }
        
    };
    
    class Vec2x8
    {
    private:
        
        AlignedVector<float, 32> vecData{ 16 };
        
        int vecCount;

    public:
        
        /**
         * Reserve the given amount of vectors, default is 4.
         */
        Vec2x8(const int vectors=8);
        
        /**
         * Fill the vector with a given float, and int number of vectors, default is 4.
         */
        Vec2x8(const float value, int vectors=8);
        
        /**
         * Fill the vector with a given array of float data, only the requested amount of vectors are copied.
         */
        Vec2x8(const float* data, int vectors=8);
        
        /**
         * Fill the vector with predefined values, NOTE: This will result in this vector to be in SOA form.
         */
        Vec2x8(const AlignedVector<float, 32>& x, const AlignedVector<float, 32>& y,  const int vectors=8);
        
        /**
         * Create and returns a new vector @see Vec2x8()
         */
        inline static Vec2x8 vec2x8(const int vectors=8) { return Vec2x8(vectors); }
        
        /**
         * Create and returns a new vector @see Vec2x8(const float* data)
         */
        inline static Vec2x8 vec2x8(const float* data, const int vectors=8) { return Vec2x8(data, vectors); }
        
        /**
         * Create and returns a new vector @see Vec2x8(const AlignedVector<float, 32>& x, const AlignedVector<float, 32>& y)
         */
        inline static Vec2x8 vec2x8(const AlignedVector<float, 32>& x, const AlignedVector<float, 32>& y, const int vectors=4) 
        { return Vec2x8(x, y, vectors); }
        
        /**
         * Create a new Vec2x8 from the given Vec3x8, the z element will be ignored, NOTE: SOA data is required.
         */
        static Vec2x8 vec2x8(const Vec3x8& vec);
        
        /**
         * Create a new Vec2x8 from the given Vec4x8, the z and w elements will be ignored, NOTE: SOA data is required.
         */
        static Vec2x8 vec2x8(const Vec4x8& vec);
        
        /**
         * Create a new Vec2x8 from the given array of data.
         * 
         * @param int startIndex indicates the index of the first vector to be copied.
         * 
         * @param int Size the total number of elements in the array (NOT VECTORS NOR BYTES!)
         * 
         * @param int Vectors the total amount of vectors between startIndex and Size.
         */
        static Vec2x8 generateVecFromArray(const float* inputBuffer, const int startIndex, const int size, const int vectors);
        
        /**
         * Component wise addition on this vector and the given Vec2x8.
         */
        void operator  +=(const Vec2x8& vec);
        
        /**
         * Component wise subtraction on this vector and the given Vec2x8.
         */
        void operator  -=(const Vec2x8& vec);
        
        /**
         * Component wise multiplication on this vector and the given Vec2x8.
         */
        void operator <<=(const Vec2x8& vec);
        
        /**
         * Component wise division on this vector and the given Vec2x8.
         */
        void operator >>=(const Vec2x8& vec);
        
        /**
         * Component wise multiplication on this vector with the given float value
         */
        void operator  *=(const float value);
        
        /**
         * @return Vec2x8 Result of component wise addition of this and the given Vec2x8.
         */
        Vec2x8 operator +(const Vec2x8& vec) const;
        
        /**
         * @return Vec2x8 Result of component wise subtraction of this and the given Vec2x8.
         */
        Vec2x8 operator -(const Vec2x8& vec) const;
        
        /**
         * @return Vec2x8 Result of component wise multiplication of this and the given Vec2x8.
         */
        Vec2x8 operator<<(const Vec2x8& vec) const;
        
        /**
         * @return Vec2x8 Result of component wise division of this and the given Vec2x8.
         */
        Vec2x8 operator>>(const Vec2x8& vec) const;
        
        /**
         * @return Vec2x8 Result of component wise multiplication of this with the given float value.
         */
        Vec2x8 operator *(const float value) const;
        
        /**
         * @return AlignedVector<float, 32> Dot-product of this vector and the given vector.
         */
        AlignedVector<float, 32> operator*(const Vec2x8& vec) const;
        
        /**
         * Normalizes this vector.
         */
        void normalize();
        
        /**
         * @return AlignedVector<float, 32> Magnitude of this vector.
         */
        AlignedVector<float, 32> magnitude() const;
        
        /**
         * @return AlignedVector<float, 32> Square magnitude of this vector.
         */
        AlignedVector<float, 32> squareMagnitude() const;
        
        
        /**
         * Fused multiply-add function on this vector.
         */
        void addScaledVector(const Vec2x8& vec, float scale);
        
        /**
         * Sets the given element type to the given value.
         */
        void set(const VecElementType t, float val);
        
        /**
         * Sets the given element type to the given array.
         */
        void set(const VecElementType t, const AlignedVector<float, 32>& values);
        
        /**
         * Returns the given element type in array form.
         */
        AlignedVector<float, 32> get(const VecElementType t) const;
        
        /**
         * Converts this vector to SOA form (column major), required before calculations.
         */
        void convertToSOA();
        
        /**
         * Converts this vector to AOS form (row major).
         */
        void convertToAOS();
        
        /**
         * @return Vec2x8 This converted to AOS (row major).
         */
        Vec2x8 retrieveAOSForm() const;
        
        /**
         * @return Vec2x8 This converted to SOA (column major).
         */
        Vec2x8 retrieveSOAForm() const;
        
        inline float * data() { return vecData.data(); }
        inline const float * data() const noexcept { return vecData.data(); }
        
        inline int vecAmount() const { return vecCount; }
        inline int size() const { return vecCount * 2; }
    };

    class Vec3x8
    {
    private:
        
        AlignedVector<float, 32> vecData{ 24 };
        
        int vecCount;
        
    public:
        
        /**
         * Reserve the given amount of vectors, default is 4.
         */
        Vec3x8(const int vectors=8);
        
        /**
         * Fill the vector with a given float, and int number of vectors, default is 4.
         */
        Vec3x8(const float value, int vectors=8);
        
        /**
         * Fill the vector with a given array of float data, only the requested amount of vectors are copied.
         */
        Vec3x8(const float* data, int vectors=8);
        
        /**
         * Fill the vector with predefined values, NOTE: This will result in this vector to be in SOA form.
         */
        Vec3x8(const AlignedVector<float, 32>& x, const AlignedVector<float, 32>& y, const AlignedVector<float, 32>& z, const int vectors=8);
        
        /**
         * Create and returns a new vector @see Vec3x8()
         */
        inline static Vec3x8 vec3x8(const int vectors=8) { return Vec3x8(vectors); }
        
        /**
         * Create and returns a new vector @see Vec3x8(const float* data)
         */
        inline static Vec3x8 vec3x8(const float* data, const int vectors=8) { return Vec3x8(data, vectors); }
        
        /**
         * Create and returns a new vector @see Vec3x8(const AlignedVector<float, 32>& x, const AlignedVector<float, 32>& y, const AlignedVector<float, 32>& z)
         */
        inline static Vec3x8 vec3x8(const AlignedVector<float, 32>& x, const AlignedVector<float, 32>& y, const AlignedVector<float, 32>& z, const int vectors=8) 
        { return Vec3x8(x, y, z, vectors); }
        
        /**
         * Create a new Vec3x8 from the given Vec2x8, with the given additional z element, NOTE: SOA data is required.
         */
        static Vec3x8 vec3x8(const Vec2x8& vec, const AlignedVector<float, 32>& z);
        
        /**
         * Create a new Vec3x8 from the given Vec4x8, the z and w elements will be ignored, NOTE: SOA data is required.
         */
        static Vec3x8 vec3x8(const Vec4x8& vec);
        
        /**
         * Create a new Vec3x8 from the given array of data.
         * 
         * @param int startIndex indicates the index of the first vector to be copied.
         * 
         * @param int Size the total number of elements in the array (NOT VECTORS NOR BYTES!)
         * 
         * @param int Vectors the total amount of vectors between startIndex and Size.
         */
        static Vec3x8 generateVecFromArray(const float* inputBuffer, const int startIndex, const int size, const int vectors);
        
        /**
         * Component wise addition on this vector and the given Vec3x8.
         */
        void operator  +=(const Vec3x8& vec);
        
        /**
         * Component wise subtraction on this vector and the given Vec3x8.
         */
        void operator  -=(const Vec3x8& vec);
        
        /**
         * Component wise multiplication on this vector and the given Vec3x8.
         */
        void operator <<=(const Vec3x8& vec);
        
        /**
         * Component wise division on this vector and the given Vec3x8.
         */
        void operator >>=(const Vec3x8& vec);
        
        /**
         * Reassign this as the cross product of this and the given vector.
         */
        void operator%=(const Vec3x8& vec);
        
        /**
         * Component wise multiplication on this vector with the given float value
         */
        void operator  *=(const float value);
        
        /**
         * @return Vec3x8 Result of component wise addition of this and the given Vec3x8.
         */
        Vec3x8 operator +(const Vec3x8& vec) const;
        
        /**
         * @return Vec3x8 Result of component wise subtraction of this and the given Vec3x8.
         */
        Vec3x8 operator -(const Vec3x8& vec) const;
        
        /**
         * @return Vec3x8 Result of component wise multiplication of this and the given Vec3x8.
         */
        Vec3x8 operator<<(const Vec3x8& vec) const;
        
        /**
         * @return Vec3x8 Result of component wise division of this and the given Vec3x8.
         */
        Vec3x8 operator>>(const Vec3x8& vec) const;
        
        /**
         * @return Vec3x8 Vector product of this and the given vector.
         */
        Vec3x8 operator%(const Vec3x8& vec) const;
        
        /**
         * @return Vec3x8 Result of component wise multiplication of this with the given float value.
         */
        Vec3x8 operator *(const float value) const;
        
        /**
         * @return AlignedVector<float, 32> Dot-product of this vector and the given vector.
         */
        AlignedVector<float, 32> operator*(const Vec3x8& vec) const;
        
        /**
         * Normalizes this vector.
         */
        void normalize();
        
        /**
         * @return AlignedVector<float, 32> Magnitude of this vector.
         */
        AlignedVector<float, 32> magnitude() const;
        
        /**
         * @return AlignedVector<float, 32> Square magnitude of this vector.
         */
        AlignedVector<float, 32> squareMagnitude() const;
        
        
        /**
         * Fused multiply-add function on this vector.
         */
        void addScaledVector(const Vec3x8& vec, float scale);
        
        /**
         * Generate an orthonormal Basis for this vector.
         * 
         * @param int End Index of which vector the basis should be generated from,
         * the right and up vectors will be located at endIndex -1 and endIndex -2 respectively.
         */
        void generateOrthonormalBasis(const int endIndex);
        
        /**
         * Sets the given element type to the given value.
         */
        void set(const VecElementType t, float val);
        
        /**
         * Sets the given element type to the given array.
         */
        void set(const VecElementType t, const AlignedVector<float, 32>& values);
        
        /**
         * Returns the given element type in array form.
         */
        AlignedVector<float, 32> get(const VecElementType t) const;
        
        /**
         * Converts this vector to SOA form (column major), required before calculations.
         */
        void convertToSOA();
        
        /**
         * Converts this vector to AOS form (row major).
         */
        void convertToAOS();
        
        /**
         * @return Vec3x8 This converted to AOS (row major).
         */
        Vec3x8 retrieveAOSForm() const;
        
        /**
         * @return Vec3x8 This converted to SOA (column major).
         */
        Vec3x8 retrieveSOAForm() const;
        
        inline float * data() { return vecData.data(); }
        inline const float * data() const noexcept { return vecData.data(); }
        
        inline int vecAmount() const { return vecCount; }
        inline int size() const { return vecCount * 3; }
    };

    class Vec4x8
    {
    private:
        
        AlignedVector<float, 32> vecData{ 32 };
        
        int vecCount;
        
    public:
        
        /**
         * Reserve the given amount of vectors, default is 4.
         */
        Vec4x8(const int vectors=8);
        
        /**
         * Fill the vector with a given float, and int number of vectors, default is 4.
         */
        Vec4x8(const float value, int vectors=8);
        
        /**
         * Fill the vector with a given array of float data, only the requested amount of vectors are copied.
         */
        Vec4x8(const float* data, int vectors=8);
    
        /**
         * Fill the vector with predefined values, NOTE: This will result in this vector to be in SOA form.
         */
        Vec4x8(const AlignedVector<float, 32>& x, const AlignedVector<float, 32>& y, const AlignedVector<float, 32>& z, const AlignedVector<float, 32>& w, const int vectors=8);
        
        /**
         * Create and returns a new vector @see Vec4x8()
         */
        inline static Vec4x8 vec4x8(const int vectors=8) { return Vec4x8(vectors); }
        
        /**
         * Create and returns a new vector @see Vec4x8(const float* data)
         */
        inline static Vec4x8 vec4x8(const float* data, const int vectors=8) { return Vec4x8(data, vectors); }
        
        /**
         * Create and returns a new vector @see Vec4x8(const AlignedVector<float, 32>& x, const AlignedVector<float, 32>& y, const AlignedVector<float, 32>& z, const AlignedVector<float, 32>& w)
         */
        inline static Vec4x8 vec4x8(const AlignedVector<float, 32>& x, const AlignedVector<float, 32>& y, const AlignedVector<float, 32>& z, const AlignedVector<float, 32>& w, const int vectors=8) 
        { return Vec4x8(x, y, z, w, vectors); }
        
        /**
         * Create a new Vec4x8 from the given Vec3x8, with the additional z and w elements, NOTE: SOA data is required.
         */
        static Vec4x8 vec4x8(const Vec2x8& vec, const AlignedVector<float, 32>& z, const AlignedVector<float, 32>& w);
        
        /**
         * Create a new Vec4x8 from the given Vec4x8, with the additional w element, NOTE: SOA data is required.
         */
        static Vec4x8 vec4x8(const Vec3x8& vec, const AlignedVector<float, 32>& w);
        
        /**
         * Component wise addition on this vector and the given Vec4x8.
         */
        void operator  +=(const Vec4x8& vec);
        
        /**
         * Component wise subtraction on this vector and the given Vec4x8.
         */
        void operator  -=(const Vec4x8& vec);
        
        /**
         * Component wise multiplication on this vector and the given Vec4x8.
         */
        void operator <<=(const Vec4x8& vec);
        
        /**
         * Component wise division on this vector and the given Vec4x8.
         */
        void operator >>=(const Vec4x8& vec);
        
        /**
         * Component wise multiplication on this vector with the given float value
         */
        void operator  *=(const float value);
        
        /**
         * @return Vec4x8 Result of component wise addition of this and the given Vec4x8.
         */
        Vec4x8 operator +(const Vec4x8& vec) const;
        
        /**
         * @return Vec4x8 Result of component wise subtraction of this and the given Vec4x8.
         */
        Vec4x8 operator -(const Vec4x8& vec) const;
        
        /**
         * @return Vec4x8 Result of component wise multiplication of this and the given Vec4x8.
         */
        Vec4x8 operator<<(const Vec4x8& vec) const;
        
        /**
         * @return Vec4x8 Result of component wise division of this and the given Vec4x8.
         */
        Vec4x8 operator>>(const Vec4x8& vec) const;
        
        /**
         * @return Vec4x8 Result of component wise multiplication of this with the given float value.
         */
        Vec4x8 operator *(const float value) const;
        
        /**
         * @return AlignedVector<float, 32> Dot-product of this vector and the given vector.
         */
        AlignedVector<float, 32> operator*(const Vec4x8& vec) const;
        
        /**
         * Normalizes this vector.
         */
        void normalize();
        
        /**
         * @return AlignedVector<float, 32> Magnitude of this vector.
         */
        AlignedVector<float, 32> magnitude() const;
        
        /**
         * @return AlignedVector<float, 32> Square magnitude of this vector.
         */
        AlignedVector<float, 32> squareMagnitude() const;
        
        
        /**
         * Fused multiply-add function on this vector.
         */
        void addScaledVector(const Vec4x8& vec, float scale);
        
        /**
         * Sets the given element type to the given value.
         */
        void set(const VecElementType t, float val);
        
        /**
         * Sets the given element type to the given array.
         */
        void set(const VecElementType t, const AlignedVector<float, 32>& values);
        
        /**
         * Returns the given element type in array form.
         */
        AlignedVector<float, 32> get(const VecElementType t) const;
        
        /**
         * Converts this vector to SOA form (column major), required before calculations.
         */
        void convertToSOA();
        
        /**
         * Converts this vector to AOS form (row major).
         */
        void convertToAOS();
        
        /**
         * @return Vec4x8 This converted to AOS (row major).
         */
        Vec4x8 retrieveAOSForm() const;
        
        /**
         * @return Vec4x8 This converted to SOA (column major).
         */
        Vec4x8 retrieveSOAForm() const;
        
        inline float * data() { return vecData.data(); }
        inline const float * data() const noexcept { return vecData.data(); }
        
        inline int vecAmount() const { return vecCount; }
        inline int size() const { return vecCount * 4; }
        
    };
};
