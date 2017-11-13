//
//  wrapper.cpp
//  framControl
//
//  Created by 宮本栄作 on 2017/10/30.
//  Copyright © 2017年 宮本栄作. All rights reserved.
//

#include "wrapper.hpp"
#include<GLFW/glfw3.h>
#include<cmath>

GLfloat mat[]={
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1
};

GLfloat move[]={
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1
};

GLfloat modelview[16];
GLfloat multi[16];

void glMultiMatrixf(GLfloat *src1, GLfloat *src2, GLfloat *dst){
    for(int y=0;y<4;y++){
        for(int x=0;x<4;x++){
            dst[y*4+x]=src2[y*4]*src1[x]+src2[y*4+1]*src2[y*4+1]*src1[x+4]+src2[y*4+2]*src1[x+8]+src2[y*4+3]*src1[x+12];
        }
    }
}

void normalize(GLfloat *v){
    float m = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
    if(m > 0.0f) m = 1.0f/m;
    else m = 0.0f;
    
    v[0] *= m;
    v[1] *= m;
    v[2] *= m;
}

void cross(float *src1, float *src2, float *dst){
    dst[0] = src1[1] * src2[2] - src1[2] * src2[1];
    dst[1] = src1[2] * src2[0] - src1[0] * src2[2];
    dst[2] = src1[0] * src2[1] - src1[1] * src2[0];
}

void gluLookAt(GLfloat eyex, GLfloat eyey, GLfloat eyez, GLfloat centerx,
               GLfloat centery, GLfloat centerz, GLfloat upx, GLfloat upy, GLfloat upz){
    float forward[3], side[3],up[3];
    
    forward[0] = centerx - eyex;
    forward[1] = centery - eyey;
    forward[2] = centerz - eyez;
    
    up[0] = upx;
    up[1] = upy;
    up[2] = upz;
    
    normalize(forward);
    cross(forward,up,side);
    normalize(side);
    cross(side,forward,up);
    
    GLfloat m[] = {
        side[0],up[0],-forward[0],0,
        side[1],up[1],-forward[1],0,
        side[2],up[2],-forward[2],0,
        0,0,0,1
    };
    GLfloat mov[]={
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        -eyex,-eyey,-eyez,1
    };
    
    glMultiMatrixf(m,mov,multi);
    glLoadMatrixf(multi);
}

void gluPerspective(float fovy,float aspect, float znear, float zfar){
    float radian = 2*M_PI+fovy/360.0;
    float t= (float)(1.0/tan(radian/2));
    GLfloat m[]={
        t/aspect,0,0,0,
        0,t,0,0,
        0,0,(zfar+znear)/(znear - zfar), -1,
        0,0,(2 * zfar * znear) / (znear - zfar), 0
    };
    glLoadMatrixf(m);
    
}
