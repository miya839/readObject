//
//  Program.hpp
//  framControl
//
//  Created by 宮本栄作 on 2017/11/12.
//  Copyright © 2017年 宮本栄作. All rights reserved.
//

#ifndef Program_hpp
#define Program_hpp

#include "Program.hpp"

#define GLFW_INCLUDE_GLCOREAB
#include<GLFW/glfw3.h>

class Shader;

class Program{
    Program();
    ~Program();
    Program(const Program &other) = delete;
    Program &operator=(const Program &other) = delete;
    
    void attachShader(const Shader &shader);
    void linkProgram();
    GLuint getProgramObject() const{return programId_;}
    GLuint bind();
    GLuint unbind();
private:
    void deleteProgram();
    
    GLuint programId_;
    bool hasProgramId_;
};

#endif /* Program_hpp */
