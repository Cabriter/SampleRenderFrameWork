//
//  MyOpenGLView.m
//  MyApp
//
//  Created by Cabrite on 2019/7/18.
//  Copyright © 2019 Cabrite. All rights reserved.
//

#import "MyOpenGLView.h"
#include "scene.h"
#include "utils.h"

unsigned char* LoadFileContent(const char* path,int& filesize){
    unsigned char* fileContent = nullptr;
    filesize = 0;
    
    NSString *nsPath=[[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:path] ofType:nil];
    NSData* data = [NSData dataWithContentsOfFile:nsPath];
    
    if([data length] > 0){
        filesize = [data length];
        fileContent = new unsigned char[filesize +1];
        memcpy(fileContent, [data bytes], filesize);
        fileContent[filesize] = '\0';
    }
    return fileContent;
}

@implementation MyOpenGLView

-(void)prepareOpenGL{
    [super prepareOpenGL];
    Init();
    SetViewPortSize(800.0f, 600.0f);
    
    [NSTimer scheduledTimerWithTimeInterval:0.016 target:self selector:@selector(renderOneFrame) userInfo:nil repeats:YES];
}

-(void) drawRect:(NSRect)dirtyRect{
    [super drawRect:dirtyRect];
    Draw();
    glFlush();
}

-(void)renderOneFrame{
    [self setNeedsDisplay:YES];
}

@end
