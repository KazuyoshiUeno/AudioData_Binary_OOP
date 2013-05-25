#pragma once

#include "ofMain.h"
#include <iostream>
#include <bitset>

#include "ofxOsc.h"
#include "ofVbo.h"

#include "Binary.h"
#include "Particle.h"
#include "noteScore.h"

#define PORT 7770
#define NUM 31
#define DIV 16

#define LENGTH 256


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void audioIn( float * input, int bufferSize, int nChannels );

    
    ofxOscReceiver receiver;
    
    float buffer[LENGTH];
    int sampleRate;

    int modeType;
    
    bool condition;


    
    int mode;


    particle particles;
    noteScore noteScores;
    binary binaries;
    int invertMode;
    ofShader invert;
    ofFbo lastScreen;
    
};
