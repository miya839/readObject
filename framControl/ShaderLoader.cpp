//
//  ShaderLoader.cpp
//  framControl
//
//  Created by 宮本栄作 on 2017/11/03.
//  Copyright © 2017年 宮本栄作. All rights reserved.
//

/*#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>*/

#include<iostream>
#include <cstdio>
#include <cstdlib>
#if defined(WIN32)
//#  pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#  pragma comment(lib, "glew32.lib")
#  include "glew.h"
#  include "glut.h"
#elif defined(__APPLE__) || defined(MACOSX)
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#else
#  define GL_GLEXT_PROTOTYPES
#  include <GL/glut.h>
#endif

#define DEF_BUF_SIZE BUFSIZ
using namespace std;

//#define GL_VERTEX_SHADER 0x8B31

/* ファイルの内容をメモリに割り当て */
char *get_file_contents(const char *file_name);

/*==============================*
 ** シェーダの読み込み
 **==============================*/
GLuint load_shader(
                   const char *vertex_shader_fname,
                   const char *fragment_shader_fname)
{
    GLuint vertex_shader, fragment_shader;
    GLuint program;
    char *contents;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    if(!vertex_shader){
        cerr << "vertex shader Error\n";
        exit(1);
    }
    contents = get_file_contents(vertex_shader_fname);
    glShaderSource(vertex_shader, 1, &contents, NULL);
    glCompileShader(vertex_shader);
    free(contents);
    
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    contents = get_file_contents(fragment_shader_fname);
    glShaderSource(fragment_shader, 1, &contents, NULL);
    glCompileShader(fragment_shader);
    free(contents);
    
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    
    glUseProgram(program);
    
    return program;
}

/*------------------------------*
 ** ファイルの内容をメモリに割り当て
 **------------------------------*/
char *get_file_contents(const char *file_name)
{
    char *buf;
    FILE *fp;
    size_t read_size, buf_size;
    
    fp = fopen(file_name, "r");
    if (!fp) {
        fprintf(stderr, "Cannot open %s.\n", file_name);
        exit(EXIT_FAILURE);
    }
    
    buf_size = DEF_BUF_SIZE;
    buf = new char[buf_size];
    if (!buf) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    
    read_size = 0;
    for (;;) {
        size_t s;
        s = fread(buf + read_size, sizeof(char), DEF_BUF_SIZE, fp);
        read_size += s;
        if (s < DEF_BUF_SIZE) {
            break;
        }
        buf_size += DEF_BUF_SIZE;
        buf = new char[buf_size];
        if (!buf) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }
    }
    *(buf + read_size) = '\0';
    
    return buf;
}
