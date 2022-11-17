/**
 * Wrapper class for boost aligned std::vector.
 */

#pragma once

#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline")

#include <vector>
#include <boost/align/aligned_allocator.hpp>

namespace vortexMath
{
    //To abstract from a unnecessarily long iterator names
    enum ITERATOR_TYPE
    {
        ITERATOR_BEGIN,
        ITERATOR_END,
        ITERATOR_REVERSE_BEGIN,
        ITERATOR_REVERSE_END
    };
    template <class T, const int S>
    class AlignedVector
    {
    private:
        std::vector<T, boost::alignment::aligned_allocator<T, S>> vecData;
    public:
        
        inline AlignedVector(const int numElements) { vecData.reserve(numElements); }
        inline AlignedVector(const T* pData, const int numElements) { vecData = {pData, pData + numElements}; }
        inline AlignedVector(const int numElements, const T value) { vecData = std::vector<T, boost::alignment::aligned_allocator<T, S>>(numElements, value); }
        inline T * data() { return vecData.data(); }
        inline const T * data() const noexcept { return vecData.data(); }
        inline T & operator[](const int i) { return vecData[i]; }
        inline T const & at(const int i) const { return vecData.at(i); }
        inline int size() const { return vecData.size(); }
        inline int capacity() const { return vecData.capacity(); }
        inline int alignment() const { return S; }
        inline void reserve(const int elements) { vecData.reserve(elements); };
        
        /**
         * @return std::vector Copy of this
         */
        inline std::vector<T> convertToStdVector() { return std::vector<T>(vecData.data(), vecData.data() + vecData.size()); }
        
        /**
         * Return an iterator over this vector, defined by ITERATOR_TYPE
         */
        inline typename std::vector<T, boost::alignment::aligned_allocator<T, S>>::iterator iterator(ITERATOR_TYPE type) 
        { 
            return type == ITERATOR_BEGIN ? vecData.begin() : vecData.end(); 
        }
        
        /**
         * Return an reversed iterator over this vector, defined by ITERATOR_TYPE
         */
        inline typename std::vector<T, boost::alignment::aligned_allocator<T, S>>::reverse_iterator reverse_iterator(ITERATOR_TYPE type) 
        { 
            return type == ITERATOR_REVERSE_BEGIN ? vecData.rbegin() : vecData.rend(); 
        }
        
        /**
         * Insert an array of elements @ offset 
         * The offset depends upon the chosen iterator type, 
         * for example if ITERATOR_TYPE is ITERATOR_BEGIN then offset will be starting index.
         */
        void insert(ITERATOR_TYPE type, const int offset, const T* data, const int numElements)
        {
            vecData.insert(iterator(type) + offset, data, data + numElements);
        }
        
        /**
         * Insert from a std::vector @ offset 
         * The offset depends upon the chosen iterator type, 
         * for example if ITERATOR_TYPE is ITERATOR_BEGIN then offset will be starting index.
         */
        void insert(ITERATOR_TYPE type, const int offset, std::vector<T> data)
        {
            vecData.insert(iterator(type) + offset, data.begin(), data.end());
        }
    };
    
}
