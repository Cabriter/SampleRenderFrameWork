//
//  model.h
//  MyApp
//
//  Created by Cabrite on 2019/7/20.
//  Copyright © 2019 Cabrite. All rights reserved.
//

#ifndef model_h
#define model_h

#pragma once
#include "ggl.h"
#include "vertexbuffer.h"
#include "shader.h"

class Model{
public:
    VertexBuffer* mVertexBuffer;
    Shader* mShader;
public:
    glm::mat4 mModelMatrix;
    float* mLightViewMatrix,*mLightProjectMatrix;
    Model();
    void Init(const char* modelPath);
    void Draw(glm::mat4& viewMatrix,glm::mat4 projectionMatrix,float x,float y,float z);
    void SetPosotion(float x,float y,float z);
    void SetAmbientMaterial(float r,float g,float b,float a);
    void SetDiffuseMatrial(float r,float g,float b,float a);
    void SetSpecularMaterial(float r,float g,float b,float a);
    void SetTexture(const char* imagePath);
};


#endif /* model_h */
