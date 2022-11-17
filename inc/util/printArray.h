#pragma once

#include <iostream>
#include <iomanip>

namespace vortexOutput
{
    
    template <typename T>
    void print2DArray(T *inputBuffer, int rows, int cols)
    {
        for (int i = 0; i < rows; i++)
        {
            std::cout << "[ " << std::setw(sizeof(T) + 5);
            for (int j = 0; j < cols ; j++)
            {
                if (j != (cols - 1))
                {
                    std::cout << *(inputBuffer + i*4 + j) << std::setw(sizeof(T) + 5);
                }
                else
                {
                    std::cout << *(inputBuffer + i*4 + j);
                }
            }
            std::cout << " ]";
            
            if (i != (rows - 1))
            {
                std::cout << "\n" << "[" << std::setw(3 + (sizeof(T) + 5) * cols) <<"]" << std::endl;
            }
        }
        
        std::cout << std::endl;
    }
            
    template <typename T>
    void printArray(T *inputBuffer, int elements)
    {
        std::cout << "[ " << std::setw(sizeof(T) + 8);
        for (int i = 0; i < elements; i++)
        {
            if (i != (elements - 1))
                {
                    std::cout << *(inputBuffer + i) << std::setw(sizeof(T) + 8);
                }
                else
                {
                    std::cout << *(inputBuffer + i);
                }
        }
        
        std::cout << "]" << std::endl;
    }

    
};
