//
//  framebufferobject.h
//  MyApp
//
//  Created by Cabrite on 2019/7/20.
//  Copyright © 2019 Cabrite. All rights reserved.
//

#ifndef framebufferobject_h
#define framebufferobject_h

#pragma once
#include "ggl.h"

class FrameBufferObject{
public:
    GLuint depthMap;
    GLuint colorBuffer;
    GLuint mFrameBufferObject;
    GLint mPrevFrameBuffer;
    std::map<std::string,GLuint> mBuffers;
    std::vector<GLenum> mDrawBuffers;
public:
    FrameBufferObject();
    void AttachColorBuffer(const char* bufferName,GLenum attachment,int width,int height);
    void AttachDepthBuffer(const char* bufferName,int width,int height);
    void Finish();
    void Bind();
    void Unbind();
    GLuint GetBuffer(const char* bufferName);
    void Release();
};


#endif /* framebufferobject_h */
