//
//  ObjLoader.h
//  framControl
//
//  Created by 宮本栄作 on 2017/11/01.
//  Copyright © 2017年 宮本栄作. All rights reserved.
//

#ifndef OBJLOADER_HPP_INCLUDE
#define OBJLOADER_HPP_INCLUDE

typedef struct{
    float *vertices;
    int num_vertices;
}model;

extern void load_obj(model *m, const char *file_name);

#endif
