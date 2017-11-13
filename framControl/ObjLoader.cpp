//
//  ObjLoader.cpp
//  framControl
//
//  Created by 宮本栄作 on 2017/11/01.
//  Copyright © 2017年 宮本栄作. All rights reserved.
//

#include<iostream>
#include<cstdio>
#include<vector>
#include "ObjLoader.hpp"
using namespace std;

#define DEF_BUF_SIZE 2

typedef struct{
    int buf_size;
    int current_index;
    float *buf;
}float_buffer;

typedef struct{
    int buf_size;
    int current_index;
    int *buf;
}int_buffer;


void read_vertices(const char *line, float_buffer *vs);
void read_indices(const char *line, int_buffer *fs);
void create_model(model *m, float_buffer *vs, int_buffer *fs);

float_buffer *alloc_float_buffer(void);
void free_float_buffer(int_buffer *ibuf);
void add_float(float_buffer *fbuf, float value);
float get_float(float_buffer *fbuf, int index);

int_buffer *alloc_int_buffer(void);
void free_int_buffer(int_buffer *ibuf);
void add_int(int_buffer *ibuf, int value);
int get_int(int_buffer *ibuf, int index);

void load_obj(model *m, const char *file_name){
    FILE *fp;
    char line[1024];
    float_buffer *fs;
    int_buffer *is;
    
    fp = fopen(file_name,"r");
    if(!fp){
        fprintf(stderr,"Cannot open %s.\n",file_name);
        exit(EXIT_FAILURE);
    }
    fs = new float_buffer;
    is = new int_buffer;
    
    while(!feof(fp)){
        fgets(line, sizeof(line), fp);
        if(line[0] == 'v' && line[1] == ' '){
            read_vertices(line, fs);
        }
        else if(line[0] == 'f' && line[1] == ' '){
            read_indices(line, is);
        }
    }
    
    create_model(m,fs,is);
    
    delete fs;
    delete is;
    
    fclose(fp);
}

//read vertex
void read_vertices(const char *line, float_buffer *fs){
    float x,y,z;
    int count;
    
    count = sscanf(line, "%*s%f%f%f",&x,&y,&z);
    
    if(count == 3){
        add_float(fs,x);
        add_float(fs,y);
        add_float(fs,z);
        
    }
    
}

// read index
void read_indices(const char *line, int_buffer *is){
    int v1,v2,v3;
    int count;
    
    count = sscanf(line, "%*s%d%d%d",&v1,&v2,&v3);
    
    if(count == 3){
        add_int(is,v1);
        add_int(is,v2);
        add_int(is,v3);
    }
}

//make model
void create_model(model *m, float_buffer *fs, int_buffer *is){
    int i,j;
    
    m->num_vertices = fs->current_index * 3;
    m->vertices = new float[m->num_vertices];
    
    if(!m->vertices){
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    
    for(i = 0;i< is->current_index; i++){
        int idx = is->buf[i] - 1;
        for(j = 0; j < 3; j++){
            m->vertices[i*3+j] = fs->buf[idx * 3 + j];
        }
    }
}

float_buffer *alloc_float_buffer(void){
    float_buffer *fbuf;
    
    fbuf = new float_buffer;
    if(!fbuf){
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    
    fbuf->buf_size = DEF_BUF_SIZE;
    fbuf->current_index = 0;
    fbuf->buf = new float[fbuf->buf_size];
    
    return fbuf;
}

void add_float(float_buffer *fbuf, float value){
    fbuf->buf[fbuf->current_index] = value;
    cout << value;
    fbuf->current_index++;
    if(fbuf->current_index >= fbuf->buf_size){
        fbuf->buf_size *=2;
        fbuf->buf = (float*)realloc(fbuf->buf, sizeof(float) * fbuf->buf_size);
        if(!fbuf->buf){
            fprintf(stderr, "Memory Allocation error.\n");
        }
    }
}

float get_float(float_buffer *fbuf, int index){
    return fbuf->buf[index];
}

int_buffer *alloc_int_buffer(void){
    int_buffer *ibuf;
    
    ibuf = new int_buffer;
    if(!ibuf){
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    
    ibuf->buf_size = DEF_BUF_SIZE;
    ibuf->current_index = 0;
    ibuf->buf = new int[ibuf->buf_size];
    
    return ibuf;
}

void add_int(int_buffer *ibuf, int value){
    ibuf->buf[ibuf->current_index] = value;
    ibuf->current_index++;
    if(ibuf->current_index >= ibuf->buf_size){
        ibuf->buf_size *=2;
        ibuf->buf = (int*)realloc(ibuf->buf, sizeof(int) * ibuf->buf_size);
        if(!ibuf->buf){
            fprintf(stderr, "Memory Allocation error.\n");
        }
    }
}

int get_int(int_buffer *ibuf, int index){
    return ibuf->buf[index];
}







