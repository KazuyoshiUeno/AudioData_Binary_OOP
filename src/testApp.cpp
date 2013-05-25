#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    // main setup
    invertMode = 0;
    
    //OSC setting
    receiver.setup(PORT);
    
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    
    
    ofSetFrameRate(60);
    
    //sound Setting
    sampleRate = 96000;
    ofSoundStreamSetup(0, 2, this, sampleRate, LENGTH, 4);
    
    modeType = 0;
    
    binaries.setup();
    noteScores.setup();
    particles.setup();
    
    ofFbo::Settings s = ofFbo::Settings();
    s.width = ofGetWidth();
    s.height = ofGetHeight();
    s.internalformat = GL_RGBA;
    s.useDepth = true;
    s.depthStencilAsTexture = true;
    lastScreen.allocate(s);
    
    invert.load("common.vert","inverse.frag");
    
}

//--------------------------------------------------------------
void testApp::update(){


/////////////////////   OSC    //////////////////////////////
    
    while (receiver.hasWaitingMessages()) {
        
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        // receive mode //
        if(m.getAddress() == "/event/modeType"){
            modeType = m.getArgAsInt32(0);
            binaries.setModeType(modeType);
            cout << modeType << endl;
        }
        
        if(m.getAddress() == "/event/invert"){
            
            invertMode = m.getArgAsInt32(0);
            
            
        }
   
    }//OSC End
    
//////////////////////////// Update Each Classes ////////////////////////////
    
    if (modeType == 0 || modeType == 2 || modeType == 5 || modeType == 6 || modeType == 7 ) {
        //cout << "update" <<endl;
        binaries.update();
    }
    if (modeType == 1) {
        noteScores.update();
    }
    
    if (modeType == 3) {
        particles.update();
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){

    ofBackground(0, 0, 0);
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    //FBO - Invert Color
    lastScreen.begin();
    
        ofBackground(0, 0, 0, 0);
        
        //ofSetColor(255, 255, 255);
        if (modeType == 0 || modeType == 2 || modeType == 5 || modeType == 6 || modeType == 7 ) {
            //cout << "draw" <<endl;
            binaries.draw();
        }
        if (modeType == 1) {
            noteScores.draw();
        }
        
        if (modeType == 3) {
            particles.draw();
        }
    
    lastScreen.end();
    
    glDisable(GL_DEPTH_TEST);
    ofDisableAlphaBlending();
    ofSetColor(255, 255, 255,255);
    if (invertMode == 1) {
        invert.begin();
        //invert.setUniform1f("num", ofMap(mouseX, 0, ofGetWidth(), 0.0, 1.0));
        lastScreen.draw(0, 0);
        invert.end();
    }else{
    
    lastScreen.draw(0, 0);
    
    }
    
    //END - Black Out the Whole Screen
    if (modeType == 4) {
        ofSetColor(0, 0, 0);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    }

    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if(key == 'f') {
		ofToggleFullscreen();
        ofHideCursor();
	}
    if(key == '0') {
		invertMode = 0;
	}
    if(key == '1') {
		invertMode = 1;
	}

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
    ofFbo::Settings s = ofFbo::Settings();
    s.width = ofGetWidth();
    s.height = ofGetHeight();
    s.internalformat = GL_RGBA;
    s.useDepth = true;
    s.depthStencilAsTexture = true;
    lastScreen.allocate(s);
    
    particles.windowResized(w, h);
    noteScores.windowResized(w, h);

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------

void testApp::audioIn( float * input, int bufferSize, int nChannels ){
    binaries.audioIn( input, bufferSize, nChannels);
}
