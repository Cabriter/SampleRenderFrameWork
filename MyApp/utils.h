//
//  utils.h
//  MyApp
//
//  Created by Cabrite on 2019/7/19.
//  Copyright © 2019 Cabrite. All rights reserved.
//

#ifndef utils_h
#define utils_h

#pragma once
#include "ggl.h"

unsigned char * LoadFileContent(const char* path,int& filesize);

unsigned char* DecodeBMP(unsigned char* bmpFileData,int& width,int& height);
GLuint CreateTexture2D(unsigned char* pixelData,int width,int height,GLenum type);
GLuint CreateTexture2DFromBMP(const char* bmpPath);
GLuint CreateTextureCubeFromBMP(const char* front,const char* back,const char* left,const char* right,const char* top,const char* bottom);

#endif /* utils_h */
