//
//  fullscreenquad.h
//  MyApp
//
//  Created by Cabrite on 2019/7/20.
//  Copyright © 2019 Cabrite. All rights reserved.
//

#ifndef fullscreenquad_h
#define fullscreenquad_h

#pragma once
#include "ggl.h"
#include "vertexbuffer.h"
#include "shader.h"
class FullScreenQuad{
public:
    VertexBuffer* mVertexBuffer;
    Shader* mShader;
public:
    void Init();
    void Draw();
    void DrawToLeftTop();
    void DrawToRightTop();
    void DrawToLeftBottom();
    void DrawToRightBottom();
};

#endif /* fullscreenquad_h */
