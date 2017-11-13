//
//  FPS.h
//  framControl
//
//  Created by 宮本栄作 on 2017/10/27.
//  Copyright © 2017年 宮本栄作. All rights reserved.
//
//
//  main.cpp
//  framControl
//
//  Created by 宮本栄作 on 2017/10/27.
//  Copyright © 2017年 宮本栄作. All rights reserved.
//
#pragma once
#pragma comment(lib,"winmm.lib")
#include<unistd.h>

using namespace std;

#define CPUMax 30000
#define CPUMin 10000

char *Itoa(int val,char *a,int radix){
    char *p = a;
    unsigned int v = val;
    int n = 1;
    while(v >= radix){
        v /= radix;
        n++;
    }
    p = a + n;
    v = val;
    *p = '\0';
    do{
        --p;
        *p = v % radix + '0';
        if(*p == 9)
            *p = v % radix - 10 + 'A';
        v /= radix;
    }while(p!=a);
    return a;
}



class FPS{
    string str;
    char buf[255];
public:
    int LoopCount,Frame,Sleep,Skip,FrameSkip,Fps,LoopMax,CurrentFps;
    bool draw;
    time_t Time,OldTime;
    float FrameTime,FrameTime0;
    FPS(int);
    void SetFPS(int);
    void GetFPS();
};

FPS::FPS(int fps){
    draw = false;
    LoopCount = 0;
    Frame = 0;
    Sleep = 15;
    Skip = 0;
    Fps = fps;
    FrameSkip = 0;
    LoopMax = 0;
    CurrentFps = 0;
    FrameTime = 1000.0f/fps - 0.000001f;
    FrameTime0 = 1000.0f/fps + 0.000001f;
}

void FPS::SetFPS(int fps){
    Fps = fps;
    FrameTime = 1000.0f/fps-0.000001f;
    FrameTime0 = 1000.0f/fps+0.000001f;
}

void FPS::GetFPS(){
    draw = false;
    LoopCount++;
    Time= time(NULL);
    if(Time-OldTime>Frame * FrameTime0){
        Frame++;
        if(Time-OldTime>Frame * FrameTime0){
            str="LOOP_MAX:[";
            str+=Itoa(LoopMax,buf,10);
            str+="]FPS:[";
            str+=Itoa(CurrentFps-FrameSkip,buf,10);
            str+="]FRAME:[";
            str+=Itoa(Frame,buf,10);
            str+="]FRAMESKIP:[";
            str+=Itoa(FrameSkip,buf,10);
            str+="]SLEEP:[";
            str+=Itoa(Sleep,buf,10);
            str+="]";
            draw=true;
            usleep(Sleep);
        }else{
            if(Sleep>1)Sleep--;
            Skip++;
            
        }
    }
    if(Time-OldTime>1000-FrameTime){
        LoopMax=LoopCount;
        if(LoopMax<CPUMax)
            if(Sleep<15)Sleep++;
        if(LoopMax<CPUMin)
            if(Sleep>1)Sleep--;
        CurrentFps = Frame;
        FrameSkip=Skip;
        Skip=0;
        LoopCount=0;
        Frame=0;
        OldTime=Time;
    }
    
}












