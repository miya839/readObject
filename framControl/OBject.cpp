//
//  OBject.cpp
//  framControl
//
//  Created by 宮本栄作 on 2017/10/30.
//  Copyright © 2017年 宮本栄作. All rights reserved.
//

#include "OBject.hpp"
#include<GLFW/glfw3.h>
#include "wrapper.hpp"

void reshape(int width, int height){
    static GLfloat lightPosition[4] = { 0.25f, 1.0f, 0.25f, 0.0f };
    static GLfloat lightDiffuse[3] = { 1.0f, 1.0f, 1.0f };
    static GLfloat lightAmbient[3] = { 0.25f, 0.25f, 0.25f };
    static GLfloat lightSpecular[3] = { 1.0f, 1.0f, 1.0f };
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glShadeModel(GL_SMOOTH);
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 0.1, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(0.5, 1.5, 2.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);


}
