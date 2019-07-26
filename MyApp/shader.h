//
//  shader.h
//  MyApp
//
//  Created by Cabrite on 2019/7/19.
//  Copyright © 2019 Cabrite. All rights reserved.
//

#ifndef shader_h
#define shader_h

#pragma once
#include "ggl.h"

struct UniformTexture{
    GLint mLocation;
    GLuint mTexture;
    char* name;
    UniformTexture(){
        mLocation = -1;
        mTexture = 0;
    }
};

struct UniformTextureCube{
    GLint mLocation;
    GLuint mTexture;
    char* name;
    UniformTextureCube(){
        mLocation = -1;
        mTexture = 0;
    }
};

struct UniformVector4f{
    GLint mLocation;
    std::string name;
    float v[4];
    UniformVector4f(){
        mLocation = -1;
        memset(v,0,sizeof(float) * 4);
    }
};

class Shader{
public:
    static GLuint CompileShader(GLenum shaderType,const char* shaderCode);
    static GLuint CreateProgram(GLuint vsShader,GLuint fsShader);
    
public:
    GLuint mProgram;
    std::map<std::string,UniformTexture*> mUniformTextures;
    std::map<std::string,UniformTextureCube*> mUniformTextureCubes;
    std::map<std::string,UniformVector4f*> mUniformVec4s;
    
    GLint mModeMatrixLocation,mViewMatrixLocation,mProjectMatrixLocation;
    GLint mPositionLocation,mColorLocation,mTexcoordLocation,mNormalLocation;
    void Init(const char* vs,const char* fs);
    void Bind(float *M,float* V,float* P);
    void SetTexture(const char* name,const char* imagePath);
    GLuint SetTexture(const char* name,GLuint texture);
    GLuint SetTextureCube(const char* name,GLuint texture);
    void SetVec4(const char* name,float x,float y,float z,float w);
};

#endif /* shader_h */
