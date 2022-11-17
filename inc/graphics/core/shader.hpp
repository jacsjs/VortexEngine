#pragma once

#include "../../math/mat.hpp"
#include "../../glad/glad.h"

#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
  
namespace vortexGraphics
{
    class Shader
    {
    public:
        // the program ID
        unsigned int ID;
    
        // constructor reads and builds the shader
        Shader(const std::string& vertexPath, const std::string& fragmentPath);

        // use/activate the shader
        void use();
        // utility uniform functions
        void setBool(const std::string &name, bool value) const;  
        void setInt(const std::string &name, int value) const;   
        void setFloat(const std::string &name, float value) const;
        void setMat4(const std::string& name, vortexMath::Mat4& mat4);
        
        unsigned int getID();
        
        bool getBool(const std::string &name);
        int getInt(const std::string &name);
        float getFloat(const std::string &name);
    };
};
