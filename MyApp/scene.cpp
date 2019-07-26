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

glm::mat4 viewMatrix,projectionMatrix;
glm::vec3 cameraPos(1.0f,4.0f,4.0f);
Model model;

int frame = 0;
int dot = 0;

void Init(){
    frame = 0;
    dot = 0;
    model.Init("Res/Cube.obj");
    model.mShader->Init("Res/spot_light.vs", "Res/spot_light.fs");
    model.SetPosotion(0.0f, 0.0f, 0.0f);
    
    model.SetAmbientMaterial(0.1f, 0.1f, 0.1f, 1.0f);
    model.mShader->SetVec4("U_AmbientLight", 0.5f, 0.5f, 0.5f, 1.0f);
    
    model.SetDiffuseMatrial(0.3f, 0.3f, 0.3f, 1.0f);
    model.mShader->SetVec4("U_DiffuseLight", 0.8f, 0.8f, 0.8f, 1.0f);
    
    
    model.SetSpecularMaterial(0.7f, 0.7f, 0.7f, 1.0f);
    model.mShader->SetVec4("U_SpecularLight", 0.8f, 0.8f, 0.8f, 1.0f);
    
    model.mShader->SetVec4("U_LightPos", 0.0f, 1.5f, 0.0f, 0.0f);
    model.mShader->SetVec4("U_LightDirection", 0.0f, -1.0f, 0.0f, 15.0f);
    model.mShader->SetVec4("U_LightOption", 32.0f, 2.0f, 0.0f, 0.0f);
    model.mShader->SetVec4("U_CameraPos", cameraPos.x, cameraPos.y, cameraPos.z, 1.0f);

    viewMatrix = glm::lookAt(cameraPos, glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
}

void SetViewPortSize(float width,float height){
    projectionMatrix = glm::perspective(50.0f, width/height, 0.1f,100.0f);
}

void Draw(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    float xsin = sin(frame * 0.01f);
    float zcos = cos(frame * 0.01f);
    float xvalue = xsin * -8.0f;
    float zvalue = zcos * -8.0f;
    if(frame / 60 != dot){
        printf("value = {%f}\n",xvalue);
        dot = frame/60;
    }
    model.mShader->SetVec4("U_LightPos", 0.0f, 2.0f, 0.0f, 0.0f);
    model.Draw(viewMatrix, projectionMatrix, cameraPos.x, cameraPos.y, cameraPos.z);
    frame++;
}
