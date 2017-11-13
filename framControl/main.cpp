//
//  main.cpp
//  framControl
//
//  Created by 宮本栄作 on 2017/10/27.
//  Copyright © 2017年 宮本栄作. All rights reserved.
//

#include<cstdlib>
#include<iostream>
#include<cstring>
#include<vector>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include"FPS.h"
#include"loadObj.hpp"
#include"ShaderLoader.hpp"
#include"View.hpp"
#include"Perspective.hpp"

using namespace std;
using namespace glm;

#define WIDTH 640
#define HEIGHT 480

#define DEF_BUF_SIZE BUFSIZ

FPS *fps = new FPS(60);

float anglex = 0.0f;
static double cursorX;
static double cursorY;

GLfloat alpha = 210.f,beta = -70.f;

GLfloat gray[] = {0.8f,0.8f,0.8f,1.0f};
GLfloat lightpos[] = {200.0f,150.0f,-500.0f,1.0f};

static void error_callback(int error,const string description){
    cout << stderr << '\n';
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int modes){
    if(key == GLFW_KEY_Q)
        glfwSetWindowShouldClose(window, 1);
    if(key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(window, 1);
}

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods){
    if(button != GLFW_MOUSE_BUTTON_LEFT)
        return;
    if(button != GLFW_MOUSE_BUTTON_RIGHT)
        return;
    if(action == GLFW_PRESS){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        //glfwSetCursorPos(window, &cursorX, &cursorY);
    }
    else
        glfwSetInputMode(window,GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

static void cursor_position_callback(GLFWwindow *window, double x, double y){
    if(glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED){
        alpha += (GLfloat)(x - cursorX) / 10.0f;
        beta += (GLfloat)(y - cursorY) / 10.0f;
        
        cursorX = x;
        cursorY = y;
    }
}


/*void Idle(void){
    fps->GetFPS();
    if(fps->draw)
        glutPostRedisplay();
}*/
void drawOpenGL(float degree){
    //static float r = 0.0f;
    glClearColor(.0f,1.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //glUniformMatrix4fv(matrixHandle, 1, GL_FALSE, &mvpMatrix[0][0]);
    glEnd();
}

/*void Init_glfw(GLFWwindow *window){
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /*glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GL_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
 
    window = glfwCreateWindow(WIDTH, HEIGHT, "title",NULL, NULL);
    
    if(!window){
        cout << "CreateWindow failed!\n";
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    
}*/

int main(int argc,char *argv[]){
    GLuint program;
    //model model;
    
    GLuint position_buffer;
    GLuint vertex_array;
    
    float degree = 0;
    
    const GLuint position_location = 0;
    const GLuint position_bindindex = 0;
    //glfwSetErrorCallback(error_callback);
    if(!glfwInit()){
        cout << "Initialization failes!\n";
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
     
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "title",NULL, NULL);
    if(!window){
        cout << "CreateWindow failed!\n";
        glfwTerminate();
        exit(1);
        
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
        cout << " ";
        cerr << "Failed to initialize GLEW.";
        cerr << glewGetErrorString(glewInit()) << '\n';
        exit(EXIT_FAILURE);
    }
    
    program = load_shader("/Users/miyamoto/opengl/framControl/framControl/Vertex.glsl", "/Users/miyamoto/opengl/framControl/framControl/Fragment.glsl");
    
    Mesh mesh;
    mesh.load("/Users/miyamoto/opengl/framControl/framControl/cube.obj");
    
    GLuint vboHandle;
    glGenBuffers(1,&vboHandle);
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(float),
                 mesh.vertices.data(), GL_STATIC_DRAW);
    
    GLuint iboHandle;
    glGenBuffers(1,&iboHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.vertexIndex.size() * sizeof(unsigned int),
                 mesh.vertexIndex.data(), GL_STATIC_DRAW);
    
    GLuint vaoHandle;
    glGenBuffers(1,&vaoHandle);
    glBindVertexArray(vaoHandle);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboHandle);
    glBindVertexArray(0);
    
    glEnable(GL_CULL_FACE);
    
    View camera({0.0,0.0,5.0});
    camera.setDirectionHorizontalAngle(3.14f);
    camera.setDirectionVerticalAngle(0.0f);
    
    Perspective perspective;
    perspective.setFieldofView(45.0f);
    perspective.setAspect(static_cast<float>(WIDTH) / static_cast<float>(HEIGHT));
    perspective.setNearClippingPlane(0.1f);
    perspective.setFarClippingPlane(100.0f);
    
    //GLuint matrixHandle = glGetUniformLocation(program.getProgramObject(), "MVP");
    
    while(!glfwWindowShouldClose(window)){
        drawOpenGL(degree);
        //Idle();
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

