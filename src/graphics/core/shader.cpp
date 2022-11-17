#include "graphics/core/shader.hpp"

/** Reads and builds the shader from a source file */
vortexGraphics::Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    
    /** ensure ifstream objects can throw exceptions. */
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        /** Open the shader files. */
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        
        /** Create string stream objects.*/
        std::stringstream vShaderStream, fShaderStream;
        
        /** Read file's buffer contents into them. */
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();		
        
        /** Close the files after reading. */
        vShaderFile.close();
        fShaderFile.close();
        
        /** Lastly convert the received streams into strings.*/
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();		
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    
    /** Create C style Strings (Array with a corresponding pointer
     * pointing at the first char in the array.
     */
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    /** create a shader object using glCreateShader() and store the shader
     * id as an unsigned int, we'll be using that ID to make further
     * modifications to the shader object, such as defining the source code
     * for the shader
     */
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    
    /** Create the fragment shader. */
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);
    
    /** Create the shader program that links together all shaders. */
    ID = glCreateProgram();
    
    /** Attatch our shaders (with shader ID given by openGL) to the shader program. */
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    
    /** Link the shader program with all attached shaders. */
    glLinkProgram(ID);
    
    /** Delete the shader objects afterwards. */
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

/** Use this shader */
void vortexGraphics::Shader::use()
{
    glUseProgram(ID);
}

/** Set a uniform bool with the specified name to the specified value. */
void vortexGraphics::Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

/** Set a uniform int with the specified name to the specified value. */
void vortexGraphics::Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void vortexGraphics::Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void vortexGraphics::Shader::setMat4(const std::string& name, vortexMath::Mat4& mat4)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, mat4.data());
}

unsigned int vortexGraphics::Shader::getID()
{
    return this->ID;
}


