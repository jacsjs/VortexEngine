#pragma once

#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline")
#pragma GCC target("avx2", "fma")

#include <immintrin.h>
#include <stdint.h> //For unsigned int conversion of pointers

#include "memory/memoryManager.hpp"
#include "quaternion.hpp"
#include "vec.hpp"

namespace vortexMath
{
    class Mat2
    {
    private:
        alignas(32) float mat[4];
        
    public:

        Mat2() 
        { 
        }
        
        Mat2(const float* data) 
        { 
            for (int i = 0; i < 4; i++)
            {
                mat[i] = *(data + i);
            }
        }
        
        Mat2(const float value)
        {
            mat[0] = value;
            mat[2] = value;
        }
        
    };
    class Mat3 
    {
    private:
        
        float * mat;
        
    public:

        /**
        * Create a new matrix filled with zero's.
        */
        Mat3();
        
        Mat3(const float* data);
        
        /**
        * Create a Mat3 with the given float as its diagonal.
        */
        Mat3(const float value);
        
        ~Mat3();
        
        /**
         * Set this matrix to the given orientation Quaternion
         */
        void orientate(const Quaternion& q);
        
        Mat3 operator*(const Mat3& matrixB) const;
        Mat3 operator+(const Mat3& matrixB) const;
        Mat3 operator-(const Mat3& matrixB) const;
        
        /**
         * Transposes this matrix.
         */
        void transpose();
        
        /**
         * Inverts this matrix.
         */
        void invert();
        
        /**
         * Calculates and returns the determinant of this matrix.
         */
        float determinant() const;
        
        inline const float * data() const { return mat; }
        inline int size() const { return 16; }
    };

    class Mat4
    {
        
    private:
        
        float * mat;
        
    public:
        
        /**
        * Create a new matrix filled with zero's.
        */
        Mat4();
        
        Mat4(const float* initData);
        
        Mat4(const float& col1, const float& col2, const float& col3, const float& col4);
        
        Mat4(const Vec4<float>& col1, const Vec4<float>& col2, const Vec4<float>& col3, const Vec4<float>& col4);

        /**
        * Create a Mat4 with the given float as its diagonal.
        */
        Mat4(const float value);

        ~Mat4();
        
        /**
         * @return Mat4 Creates a new projection matrix with the specified fov and plane distances.
         * 
         */
        static Mat4 * projection(const float fov, const float near, const float far);
        
        
        /**
         * Translate the 4th column of this matrix to the given translation Vec4<float>
         */
        void translate(const Vec4<float>& vec);
        
        /**
         * Translate the 4th column of this matrix to the given translation Vec4<float>
         */
        void translate(const Vec3<float>& vec);
        
        /**
         * Set the orientation part of this matrix with the given orientation Quaternion
         */
        void orientate(const Quaternion& q);
        
        Mat4 operator*(const Mat4& matrixB) const;
        Mat4 operator+(const Mat4& matrixB) const;
        Mat4 operator-(const Mat4& matrixB) const;
        
        /**
         * Transposes this matrix.
         */
        void transpose();
        
        /**
         * Inverts this matrix.
         */
        void invert();
        
        /**
         * Calculates and returns the determinant of this matrix.
         */
        float determinant() const;
        
        inline float * data() { return mat; }
        inline int size() const { return 16; }
    };

};

