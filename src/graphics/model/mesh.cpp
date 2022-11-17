#include "graphics/model/mesh.hpp"

vortexGraphics::Mesh::Mesh(const vortexMath::Vec3x8& positions, const vortexMath::Vec3x8& normals, const vortexMath::Vec2x8& texCoords, const vortexMath::AlignedVector<unsigned int, 32>& indices, const vortexMath::Mat4& modelMat)
: positions(positions), normals(normals), texCoords(texCoords), indices(indices), modelMat(modelMat)
{
}

void vortexGraphics::Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenTextures(1, &texture);
    
    //Texture data setup TODO: temp, will make a dedicated texture handler class later
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    pTexData = stbi_load("/home/jacob/paint-texture.jpg", &width, &height, &nrChannels, 0); 
    
    //General Setup
    glBindVertexArray(VAO); //Sets this as the currect active VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Bind the VBO Buffer to GL_ARRAY_BUFFER type
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //Bind the EBO Buffer-object to GL_ELEMENT_ARRAY_BUFFER type.
    
    //Vertex data copying
    int posSize = positions.size() * sizeof(float);
    int normalSize = normals.size() * sizeof(float);
    int texSize = texCoords.size() * sizeof(float);
    
    glBufferData(GL_ARRAY_BUFFER, posSize + normalSize + texSize, NULL, GL_STATIC_DRAW); //Allocating memory
    
    //Copying over vertex data
    glBufferSubData(GL_ARRAY_BUFFER, 0, posSize, positions.data());
    //glBufferSubData(GL_ARRAY_BUFFER, posSize, normalSize, normals.data());
    glBufferSubData(GL_ARRAY_BUFFER, posSize + normalSize, texSize, texCoords.data());
    
    //Defining vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), BUFFER_START_OFFSET);
    glEnableVertexAttribArray(0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), BUFFER_OFFSET(posSize));
    //glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), BUFFER_OFFSET(posSize + normalSize));
    glEnableVertexAttribArray(2);
    
    //Index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW); //Send over index data (to tell openGL draw order etc.)
    
    if (pTexData)
    {
        //Texture loading TODO: temporary solution
        glBindTexture(GL_TEXTURE_2D, texture); //Any texture commands on GL_TEXTURE_2D will be referenced to the texture object
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pTexData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    
    glEnable(GL_DEPTH_TEST); //Z buffer for 3D
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); //VBO
    glBindVertexArray(0); //VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //EBO
}


void vortexGraphics::Mesh::draw(vortexGraphics::Shader* shader)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear buffers before rendering
    
    shader->setMat4("modelMat", modelMat);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    glBindVertexArray(0); //NOTE: Remeber to unbind
}

