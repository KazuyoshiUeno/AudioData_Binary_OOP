//
//  noteScore.h
//  AudioData_Binary
//
//  Created by koutaro fukui on 2013/05/06.
//
//

#ifndef __AudioData_Binary__noteScore__
#define __AudioData_Binary__noteScore__

#pragma once

#include "ofMain.h"
#include <iostream>

#include "ofxOsc.h"

#include "Rect.h"


#define noteScore_PORT 7773
#define NUM 31
#define DIV 16

#define LENGTH 256


class noteScore {
    
public:
    void setup();
    void update();
    void draw();
    void windowResized(int w, int h);
    

private:
    float winDivWidth;
    float winDivHeight;

    int speed;
    int modeType;
    
    bool condition;
    
    int linePos_1_x[1000];
    int linePos_1_y[1000];
    int linePos_2_x[1000];
    int linePos_2_y[1000];
    int linePos_3_x[1000];
    int linePos_3_y[1000];
    int linePos_4_x[1000];
    int linePos_4_y[1000];
    int linePos_5_x[1000];
    int linePos_5_y[1000];
    int linePos_6_x[1000];
    int linePos_6_y[1000];
    
    
    ofxOscReceiver receiver;
    

    ofEasyCam cam;
    
    
    int rectNum[6];
    float yPos[6];
    int freq[6];
    float duration[6];
    
    int modeSelect;
    
    vector<rect *> myRect_1;
    vector<rect *> myRect_2;
    vector<rect *> myRect_3;
    vector<rect *> myRect_4;
    vector<rect *> myRect_5;
    vector<rect *> myRect_6;
    
    ////////////////////////////////////////////////////

    int start;

};


#endif /* defined(__AudioData_Binary__noteScore__) */
