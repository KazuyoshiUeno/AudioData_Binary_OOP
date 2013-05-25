//
//  Pirticle.h
//  AudioData_Binary
//
//  Created by koutaro fukui on 2013/05/06.
//
//

#ifndef __AudioData_Binary__Particle__
#define __AudioData_Binary__Particle__

#pragma once

#include "ofxOsc.h"
#include "ofVbo.h"

#define particle_PORT 7772


#define NUM_PARTICLES 150000

class particle {
    
public:
    void setup();
    void update();
    void draw();
    void windowResized(int w, int h);
    
    void setmode(int _mode);

private:
    ofxOscReceiver receiver;
    
    //int speed;
    int modeType;
    
    bool condition;

    //float  zDepth;
    ofEasyCam cam;
    
    float viewX, viewY, viewZ;
    
    int rectNum[6];
    float yPos[6];
    int freq[6];
    float duration[6];
    
    
    ofLight light;
    ofEasyCam camera;
    ofVbo vbo;
    ofFbo fbo;
    
    ofFbo fbo_total;
    ofFbo vFbo;
    ofFbo hFbo;
    
    ofShader blurV;
    ofShader blurH;
    
    ofVec3f pos[NUM_PARTICLES];
    ofVec2f vel[NUM_PARTICLES];
    ofVec2f frc[NUM_PARTICLES];
    float drag[NUM_PARTICLES];
    
    int mode;
    int degDev;
    int deg;
    
    int mX;
    int mY;
    
    float scaling;
    int start;
    

    float blurDepth;
    
    
};

#endif /* defined(__AudioData_Binary__Pirticle__) */
