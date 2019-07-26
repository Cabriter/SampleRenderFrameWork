//
//  scene.cpp
//  MyApp
//
//  Created by Cabrite on 2019/7/19.
//  Copyright © 2019 Cabrite. All rights reserved.
//

#include <stdio.h>
#include "scene.h"
#include "utils.h"
#include "model.h"
#include "framebufferobject.h"
#include "fullscreenquad.h"

glm::mat4 viewMatrix,projectionMatrix;
glm::vec3 cameraPos(6.0f,6.0f,6.0f);
glm::vec3 lightPos(0.0f,4.0f,0.0f);
glm::mat4 lightProjection,lightView;
Model sphere,cube;
FrameBufferObject* depthFBO;
FullScreenQuad* fsq;

int frame = 0;
int dot = 0;

void Init(){
    frame = 0;
    dot = 0;
    sphere.Init("Res/Sphere.obj");
    sphere.mShader->Init("Res/direction_light_s.vs", "Res/direction_light_s.fs");
    sphere.mModelMatrix = glm::translate(0.0f, 2.0f, 0.0f);
    
    sphere.SetAmbientMaterial(0.5f, 0.5f, 0.5f, 1.0f);
    sphere.mShader->SetVec4("U_AmbientLight", 0.5f, 0.5f, 0.5f, 1.0f);

    sphere.SetDiffuseMatrial(0.4f, 0.4f, 0.4f, 1.0f);
    sphere.mShader->SetVec4("U_DiffuseLight", 0.8f, 0.8f, 0.8f, 1.0f);

    sphere.SetSpecularMaterial(1.0f, 1.0f, 1.0f, 1.0f);
    sphere.mShader->SetVec4("U_SpecularLight", 1.0f, 1.0f, 1.0f, 1.0f);

    sphere.mShader->SetVec4("U_LightPos", 0.0f, 1.0f, 0.0f, 0.0f);
    sphere.mShader->SetVec4("U_CameraPos", cameraPos.x, cameraPos.y, cameraPos.z, 1.0f);
    
    cube.Init("Res/Cube.obj");
    cube.mShader->Init("Res/direction_light_s.vs", "Res/direction_light_s.fs");
    cube.mModelMatrix = glm::scale(9.0f, 1.0f, 9.0f);
    
    cube.SetAmbientMaterial(0.5f, 0.5f, 0.5f, 5.0f);
    cube.mShader->SetVec4("U_AmbientLight", 0.5f, 0.5f, 0.5f, 1.0f);
    
    cube.SetDiffuseMatrial(0.4f, 0.4f, 0.4f, 1.0f);
    cube.mShader->SetVec4("U_DiffuseLight", 0.8f, 0.8f, 0.8f, 1.0f);
    
    cube.SetSpecularMaterial(1.0f, 1.0f, 1.0f, 1.0f);
    cube.mShader->SetVec4("U_SpecularLight", 1.0f, 1.0f, 1.0f, 1.0f);
    
    cube.mShader->SetVec4("U_LightPos", 0.0f, 1.0f, 0.0f, 0.0f);
    cube.mShader->SetVec4("U_CameraPos", cameraPos.x, cameraPos.y, cameraPos.z, 1.0f);
    
//    model.mShader->SetVec4("U_LightDirection", 0.0f, -1.0f, 0.0f, 15.0f);
//    model.mShader->SetVec4("U_LightOption", 32.0f, 2.0f, 0.0f, 0.0f);
    
    viewMatrix = glm::lookAt(cameraPos, glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
    lightProjection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 5.0f);
    lightView = glm::lookAt(lightPos, glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,-1.0f));
}

void SetViewPortSize(float width,float height){
    projectionMatrix = glm::perspective(50.0f, width/height, 0.1f,100.0f);
//    depthFBO = new FrameBufferObject();
//    depthFBO->AttachColorBuffer("color", GL_COLOR_ATTACHMENT0, (int)width, (int)height);
//    depthFBO->AttachDepthBuffer("depth", (int)width, (int)height);
//    depthFBO->Finish();
    fsq = new FullScreenQuad();
    fsq->Init();
    fsq->mShader->Init("Res/fullscreenquad.vs", "Res/fullscreenquad.fs");
}
const char* color = "color";
const char* depth = "depth";
void Draw(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

    float xsin = sin(frame * 0.01f);
    float zcos = cos(frame * 0.01f);
    float xvalue = xsin * -4.0f;
    float zvalue = zcos * -4.0f;
    sphere.SetPosotion(xvalue, 2.0f, zvalue);
    
    depthFBO = new FrameBufferObject();
    depthFBO->AttachColorBuffer(color, GL_COLOR_ATTACHMENT0, (int)800, (int)600);
    depthFBO->AttachDepthBuffer(depth, (int)800, (int)600);
    depthFBO->Finish();
    
    depthFBO->Bind();
    cube.mLightViewMatrix = nullptr;
    cube.mLightProjectMatrix = nullptr;
    cube.Draw(lightView, lightProjection, lightPos.x, lightPos.y, lightPos.z);
    sphere.Draw(lightView, lightProjection, lightPos.x, lightPos.y,lightPos.z);
    depthFBO->Unbind();
//    fsq->mShader->SetTexture("U_Texture", depthFBO->GetBuffer("depth"));
//    fsq->Draw();
    cube.mShader->SetTexture("U_ShadowMap", depthFBO->GetBuffer("depth"));
    cube.mLightViewMatrix = glm::value_ptr(lightView);
    cube.mLightProjectMatrix = glm::value_ptr(lightProjection);
    cube.Draw(viewMatrix, projectionMatrix, cameraPos.x, cameraPos.y, cameraPos.z);
    sphere.Draw(viewMatrix, projectionMatrix, cameraPos.z, cameraPos.y, cameraPos.z);
    
    if(frame / 60 != dot){
        dot = frame/60;
    }
    depthFBO->Release();
    delete depthFBO;
    frame++;
}
