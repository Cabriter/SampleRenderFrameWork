//
//  vertexbuffer.hpp
//  MyApp
//
//  Created by Cabrite on 2019/7/19.
//  Copyright © 2019 Cabrite. All rights reserved.
//

#ifndef vertexbuffer_h
#define vertexbuffer_h
#pragma once
#include <stdio.h>
#include "ggl.h"

struct Vertex {
    float Position[4];
    float Color[4];
    float Texcoord[4];
    float Normal[4];
};

class VertexBuffer{
public:
    static GLuint CreateBufferObject(GLenum buffeType,GLsizeiptr size,GLenum usage,void* data = nullptr);
    
public:
    Vertex* mVertexes;
    int mVertexCount;
    GLuint mVBO;
    void SetSize(int vertexCount);
    void SetPosition(int index,float x,float y,float z,float w = 1.0f);
    void SetColor(int index,float r,float g,float b,float a = 1.0f);
    void SetTexcoord(int index,float x,float y);
    void SetNormal(int index,float x,float y,float z);
    void Bind();
    void Unbind();
    Vertex& Get(int index);
};


#endif /* vertexbuffer_hpp */
