#pragma once

#define BUFFER_OFFSET(index) (static_cast<char*>(0) + (index))
#define BUFFER_START_OFFSET (static_cast<char*>(0))

#include "../../glad/glad.h"
#include "../../math/vecSOA.hpp"
#include "../../math/mat.hpp"

#include "../core/shader.hpp"
#include "../core/stb_image.h"

#include <GLFW/glfw3.h>

namespace vortexGraphics
{
    class Mesh
    {
    private:
        
        vortexMath::Vec3x8 positions;
        vortexMath::Vec3x8 normals;
        vortexMath::Vec2x8 texCoords;
        
        vortexMath::AlignedVector<unsigned int, 32> indices;
        
        vortexMath::Mat4 modelMat;
        
        unsigned int VAO, VBO, EBO, texture;
        
        unsigned char * pTexData;
    public:
        
        Mesh(const vortexMath::Vec3x8& positions, const vortexMath::Vec3x8& normals, const vortexMath::Vec2x8& texCoords, const vortexMath::AlignedVector<unsigned int, 32>& indices, const vortexMath::Mat4& modelMat);
        
        void setupMesh();
        
        /**
         * Render this mesh.
         */
        void draw(Shader * shader);
        
        /**
         * Set up this mesh, sending vertex data to the render engine.
         */
        inline void update(const vortexMath::Mat4& modelMat)
        {
            this->modelMat = modelMat;
        }
        
        inline const vortexMath::Mat4 * modelMatrix() const { return &modelMat; }
        inline const unsigned int getVAO() const { return VAO; }
        inline const unsigned int getVBO() const { return VBO; }
        inline const unsigned int getEBO() const { return EBO; }
    };
    
}
