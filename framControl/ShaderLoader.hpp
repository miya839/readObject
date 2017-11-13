//
//  ShaderLoader.hpp
//  framControl
//
//  Created by 宮本栄作 on 2017/11/03.
//  Copyright © 2017年 宮本栄作. All rights reserved.
//

#ifndef SHADER_LOADER_H_INCLUDE
#define SHADER_LOADER_H_INCLUDE

#include <GL/glew.h>

/* シェーダの読み込み */
extern GLuint load_shader(
                   const char *vertex_shader_fname,
                   const char *fragment_shader_fname);

#endif
