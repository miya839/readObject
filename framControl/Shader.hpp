//
//  Shader.hpp
//  framControl
//
//  Created by 宮本栄作 on 2017/11/12.
//  Copyright © 2017年 宮本栄作. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include "Shader.hpp"

#include<string>

#define GLFW_INCLUDE_GLCOREARB
#include<GLFW/glfw3.h>

class Shader
{
public:
    Shader();
    ~Shader();
    Shader(const Shader &other) = delete;
    Shader &operator=(const Shader &other) = delete;
    
    void createShader(const char* shaderFile, GLenum type);
    GLuint getShaderObject() const {return shaderId_;}
    
private:
    void readShader(const char *shaderFile, std::string &code);
    void compileShader(const std::string &code);
    void deleteShader();
    
    GLuint shaderId_;
    bool hasShaderId_;
};

#endif /* Shader_hpp */
