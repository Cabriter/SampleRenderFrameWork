//
//  Model.cpp
//  MyApp
//
//  Created by Cabrite on 2019/7/20.
//  Copyright © 2019 Cabrite. All rights reserved.
//

#include <stdio.h>
#include "model.h"
#include "utils.h"

Model::Model(){
    
}

void Model::Init(const char *modelPath){
    struct VertexDefine{
        int posIndex;
        int texcoordIndex;
        int normalIndex;//这里的法线是垂直切平面的法线
        int tangentIndex;
    };
    //TBN矩阵生成
    //T轴为三点面中其中一个轴，N为平面垂直法线，B为TN叉乘所得
    //前提，模型中的法线坐标系都是在模型空间下，要确定一个TBN坐标系，
    //将法线贴图中的法线转换到TBN坐标系下，将新的法线和T轴在模型坐标系下的向量保存下来，T轴就是tangent向量
    
    int nFileSize = 0;
    unsigned char* fileContent = LoadFileContent(modelPath, nFileSize);
    if(fileContent == nullptr){
        return;
    }
    std::vector<glm::vec3> positions,normals,tangents;;
    std::vector<glm::vec2> texcoords;
    std::vector<VertexDefine> vertexes;
    std::stringstream ssFileContent((char*)fileContent);
    std::string temp;
    char szOneLine[256];
    while (!ssFileContent.eof()) {
        memset(szOneLine, 0, 256);
        ssFileContent.getline(szOneLine, 256);
        if(strlen(szOneLine) > 0){
            if(szOneLine[0] == 'v'){
                std::stringstream ssOneLine(szOneLine);
                if(szOneLine[1] == 't'){
                    ssOneLine >> temp;
                    glm::vec2 floatData;
                    ssOneLine >> floatData.x;
                    ssOneLine >> floatData.y;
                    texcoords.push_back(floatData);
                }else if(szOneLine[1] == 'n'){
                    ssOneLine >> temp;
                    glm::vec3 floatData;
                    ssOneLine >> floatData.x;
                    ssOneLine >> floatData.y;
                    ssOneLine >> floatData.z;
                    normals.push_back(floatData);
                }else{
                    ssOneLine >> temp;
                    glm::vec3 floatData;
                    ssOneLine >> floatData.x;
                    ssOneLine >> floatData.y;
                    ssOneLine >> floatData.z;
                    positions.push_back(floatData);
                }
            }else if(szOneLine[0] == 'f'){
                std::stringstream ssOneLine(szOneLine);
                ssOneLine >> temp;
                std::string vertexStr;
                std::vector<VertexDefine> tempPos;
                for(int i = 0;i<3;i++){
                    ssOneLine >> vertexStr;
                    size_t pos = vertexStr.find_first_of("/");
                    std::string posIndexStr = vertexStr.substr(0,pos);
                    size_t pos2 = vertexStr.find_first_of("/",pos+1);
                    std::string texcoordIndexStr = vertexStr.substr(pos+1,pos2-1-pos);
                    std::string normalIndexStr = vertexStr.substr(pos2+1,vertexStr.length()-1-pos2);
                    VertexDefine vd;
                    vd.posIndex = atoi(posIndexStr.c_str());
                    vd.texcoordIndex = atoi(texcoordIndexStr.c_str());
                    vd.normalIndex = atoi(normalIndexStr.c_str());
                    vertexes.push_back(vd);
                    tempPos.push_back(vd);
                }
                
                glm::vec3 vecPos1 = positions[tempPos[0].posIndex];;
                glm::vec3 vecPos2 = positions[tempPos[1].posIndex];;
                glm::vec3 vecPos3 = positions[tempPos[2].posIndex];;
                
                glm::vec2 vecTexcoord1 = texcoords[tempPos[0].texcoordIndex];;
                glm::vec2 vecTexcoord2 = texcoords[tempPos[1].texcoordIndex];;
                glm::vec2 vecTexcoord3 = texcoords[tempPos[2].texcoordIndex];;
                
                glm::vec3 tangent1;
                glm::vec3 edge1 = vecPos2 - vecPos1;
                glm::vec3 edge2 = vecPos3 - vecPos1;
                glm::vec2 deltaUV1 = vecTexcoord2 - vecTexcoord1;
                glm::vec2 deltaUV2 = vecTexcoord3 - vecTexcoord1;
                
                GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
                tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
                tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
                tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
                tangent1 = glm::normalize(tangent1);
                
                tangents.push_back(tangent1);
                //遍历tempPos中的三个点，计算出tangent向量，存储在tangents数组中，并记录存储的index
                
                int tangentIndex = tangents.size();
                
                for(std::vector<VertexDefine>::iterator iter = tempPos.begin();iter != tempPos.end();iter++)
                {
                    iter->tangentIndex = tangentIndex;
                }
            }
        }
    }
    delete fileContent;
    int vertexCount = (int)vertexes.size();
    mVertexBuffer = new VertexBuffer();
    mVertexBuffer->SetSize(vertexCount);
    for (int i = 0; i<vertexCount; ++i) {
        glm::vec3 pos = positions[vertexes[i].posIndex - 1];
        mVertexBuffer->SetPosition(i, pos.x, pos.y, pos.z);
        glm::vec2 texcoord = texcoords[vertexes[i].texcoordIndex - 1];
        mVertexBuffer->SetTexcoord(i, texcoord.x, texcoord.y);
        glm::vec3 normal = normals[vertexes[i].normalIndex - 1];
        mVertexBuffer->SetNormal(i, normal.x, normal.y, normal.z);
    }
    mShader = new Shader();
}

void Model::Draw(glm::mat4 &viewMatrix, glm::mat4 projectionMatrix, float x, float y, float z){
    mShader->SetVec4("UI_CameraPos", x, y, z, 1.0f);
    glEnable(GL_DEPTH_TEST);
    mVertexBuffer->Bind();
    if(mShader->mProgram > 0){
        mShader->Bind(glm::value_ptr(mModelMatrix), glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix));
        glm::mat4 it = glm::inverseTranspose(mModelMatrix);
        GLint itLocation = glGetUniformLocation(mShader->mProgram, "IT_ModelMatrix");
        glUniformMatrix4fv(itLocation, 1,GL_FALSE, glm::value_ptr(it));
        itLocation = glGetUniformLocation(mShader->mProgram, "LightViewMatrix");
        if(itLocation >= 0 && mLightViewMatrix != nullptr){
            glUniformMatrix4fv(itLocation, 1, GL_FALSE, mLightViewMatrix);
        }
        itLocation = glGetUniformLocation(mShader->mProgram, "LightProjectionMatrix");
        if(itLocation >= 0 && mLightProjectMatrix != nullptr){
            glUniformMatrix4fv(itLocation, 1, GL_FALSE, mLightProjectMatrix);
        }
    }
    glDrawArrays(GL_TRIANGLES, 0, mVertexBuffer->mVertexCount);
    mVertexBuffer->Unbind();
}

void Model::SetPosotion(float x, float y, float z){
    mModelMatrix = glm::translate(x, y, z);
}

void Model::SetAmbientMaterial(float r, float g, float b, float a){
    mShader->SetVec4("U_AmbientMaterial", r, g, b, a);
}

void Model::SetDiffuseMatrial(float r, float g, float b, float a){
    mShader->SetVec4("U_DiffuseMaterial", r, g, b, a);
}

void Model::SetSpecularMaterial(float r, float g, float b, float a){
    mShader->SetVec4("U_SpecularMaterial", r, g, b, a);
}

void Model::SetTexture(const char *imagePath){
    mShader->SetTexture("U_Texture", imagePath);
}
