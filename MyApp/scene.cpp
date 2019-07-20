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
glm::vec3 cameraPos(4.0f,3.0f,4.0f);
Model model;

void Init(){
    model.Init("Res/Cube.obj");
    model.mShader->Init("Res/rgbcube.vs", "Res/rgbcube.fs");
    model.SetPosotion(0.0f, 0.0f, 0.0f);
    viewMatrix = glm::lookAt(cameraPos, glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
}

void SetViewPortSize(float width,float height){
    projectionMatrix = glm::perspective(50.0f, width/height, 0.1f,100.0f);
}

void Draw(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    model.Draw(viewMatrix, projectionMatrix, cameraPos.x, cameraPos.y, cameraPos.z);
}
