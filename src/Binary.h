//
//  Binary.h
//  AudioData_Binary
//
//  Created by koutaro fukui on 2013/05/14.
//
//

#ifndef __AudioData_Binary__Binary__
#define __AudioData_Binary__Binary__

#include "ofMain.h"
#include <iostream>
#include <bitset>

#include "ofxOsc.h"
#include "ofVbo.h"

#include "Rect.h"

#include "RectObj.h"


#define binary_PORT 7771

#define binary_LENGTH 256


class binary {
    
public:
    void setup();
    void update();
    void draw();

    void audioIn( float * input, int bufferSize, int nChannels );
    
    void setModeType(int modeType);
private:
    ofxOscReceiver receiver;
    
    float buffer[binary_LENGTH];

    float audioData;
    float winDivWidth;
    float winDivHeight;
    int rectDirection;
    int speed;
    int modeType;
    
    bool condition;
    
    
    union
    {
        float input;   // assumes sizeof(float) == sizeof(int)
        int   output;
    }    data_L;
    
    union
    {
        float input;   // assumes sizeof(float) == sizeof(int)
        int   output;
    }    data_R;
    
    bitset<sizeof(float) * CHAR_BIT>   bits_L;
    bitset<sizeof(float) * CHAR_BIT>   bits_R;
    string str_L;
    string str_R;
    int stringSize_L[binary_LENGTH];
    int stringSize_R[binary_LENGTH];
    int stringCell_L[binary_LENGTH];
    int stringCell_R[binary_LENGTH];
    vector <RectObj *> rects_L;
    vector <RectObj *> rects_R;
    float  zDepth;
    ofEasyCam cam;
    
    
    
    ////////////////////////////////////////////////////
    
    
    
    int mode;
    
    
    ofPoint rectPos;
    ofPoint rectVerticalPos;
    float rectRandPos_1;
    float rectRandPos_2;
};

#endif /* defined(__AudioData_Binary__Binary__) */
