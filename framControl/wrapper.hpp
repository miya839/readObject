//
//  wrapper.hpp
//  framControl
//
//  Created by 宮本栄作 on 2017/10/30.
//  Copyright © 2017年 宮本栄作. All rights reserved.
//

#ifndef wrapper_hpp
#define wrapper_hpp

#include <stdio.h>
#include<GLFW/glfw3.h>

extern void glMultiMatrixf(GLfloat *src1, GLfloat *src2, GLfloat *dst);
extern void normalize(GLfloat *v);
extern void cross(float *src1, float *src2, float *dst);
extern void gluLookAt(GLfloat eyex, GLfloat eyey, GLfloat eyez, GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat upx, GLfloat upy, GLfloat upz);
extern void gluPerspective(float fovy,float aspect, float znear, float zfar);

#endif /* wrapper_hpp */
