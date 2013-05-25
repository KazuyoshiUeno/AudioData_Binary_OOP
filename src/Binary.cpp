//
//  Binary.cpp
//  AudioData_Binary
//
//  Created by koutaro fukui on 2013/05/14.
//
//

#include "Binary.h"


//--------------------------------------------------------------
void binary::setup(){

    //OSC setting
    receiver.setup(binary_PORT);

    rectDirection = 0;
    speed =30;
    
    zDepth = 0;
    
    rectVerticalPos = ofPoint(0,0);
  
}

void binary::setModeType(int _modeType){
    modeType = _modeType;
}

//--------------------------------------------------------------
void binary::update(){

    
    /////////////////////   OSC    //////////////////////////////
    
    while (receiver.hasWaitingMessages()) {
        
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        // receive mode //
//        if(m.getAddress() == "/event/modeType"){
//            modeType = m.getArgAsInt32(0);
//            cout << modeType << endl;
//        }
        

        
        if(m.getAddress() == "/event/peak"){
            
            zDepth = m.getArgAsFloat(0);
            
            
        }
        
        if(m.getAddress() == "/event/xyz"){
            float viewX, viewY, viewZ;
            
            viewX = m.getArgAsFloat(0);
            viewY = m.getArgAsFloat(1);
            viewZ = m.getArgAsFloat(2);
            
            cam.setTarget(ofVec3f(0));
            cam.setPosition(viewX, viewY, viewZ);
            
            //cam.lookAt(ofVec3f(viewX, viewY, viewZ));
            
        }
        
        

        ///////////////////////// break Section Start ///////////////////////////////
        
        
        
        if(m.getAddress() == "/event/loopBassAmp"){
            float loopBass = m.getArgAsFloat(0);
            if(loopBass > 0){
                rectPos = ofPoint(0,0);
                rectRandPos_1 = 100 - ofRandom(200);
                rectRandPos_2 = 100 - ofRandom(200);
            }
        }
        if(m.getAddress() == "/event/revSaw"){
            float revSaw = m.getArgAsFloat(0);
            if(revSaw > 0){
                rectVerticalPos = ofPoint(0,0);
                cout << " OSC : "<< "is triggered" << endl;
                
            }
        }
        
    }//OSC End
    
    int strCellNum = 0;
    
    if (modeType == 0 || modeType == 2 || modeType == 5 || modeType == 6 || modeType == 7) {
        if(modeType == 6 || modeType == 7){
            rectPos.y += 5;
            rectVerticalPos.x += 8;
            cout << rectVerticalPos.x << endl;
        }
        
        
        if (rectDirection == 0) {
            winDivWidth = ofGetWidth()/32/8;
            winDivHeight = ofGetHeight()/32/2;
        }
        if (rectDirection == 1) {
            winDivWidth = ofGetWidth()/32/2;
            winDivHeight = ofGetHeight()/32/8;
        }
        
        
        for (int i = 0; i < 8; i++) {
            strCellNum = i * 32;
            ofColor tempColor;
            
            for (int j = 0; j < 32; j++) {
                
                if (stringCell_L[j+strCellNum] == 1) {
                    tempColor.set(255, 255, 255, 255);
  
                    if (rectDirection == 0) {
                        
                        rects_L.push_back(new RectObj(ofPoint(0 - i * winDivWidth - winDivWidth, j * winDivHeight, ofRandom(1000) * zDepth),  winDivWidth, winDivHeight, tempColor, modeType));
                    }
                    if (rectDirection == 1) {
                        rects_L.push_back(new RectObj(ofPoint( j * winDivWidth,0 - i * winDivHeight - winDivHeight, ofRandom(1000) * zDepth),  winDivWidth, winDivHeight, tempColor, modeType));
                    }
                    
                }else{
                    tempColor.set(0, 0, 0, 0);

                    if (rectDirection == 0) {
                        rects_L.push_back(new RectObj(ofPoint(0 - i * winDivWidth - winDivWidth, j * winDivHeight, ofRandom(1000) * zDepth),  winDivWidth, winDivHeight, tempColor, modeType));
                    }
                    if (rectDirection == 1) {
                        rects_L.push_back(new RectObj(ofPoint( j * winDivWidth, 0 - i * winDivHeight - winDivHeight, ofRandom(1000) * zDepth),  winDivWidth, winDivHeight, tempColor, modeType));
                    }
                    
                }
                
                
                if (stringCell_R[j+strCellNum] == 1) {
                    tempColor.set(255, 255, 255, 255);

                    if (rectDirection == 0) {
                        rects_R.push_back(new RectObj(ofPoint(0 - i * winDivWidth - winDivWidth, j * winDivHeight + ofGetHeight()/2, ofRandom(1000) * zDepth),  winDivWidth, winDivHeight, tempColor, modeType));
                    }
                    if (rectDirection == 1) {
                        rects_R.push_back(new RectObj(ofPoint(j * winDivWidth + ofGetWidth()/2, 0 - i * winDivHeight - winDivHeight, ofRandom(1000) * zDepth),  winDivWidth, winDivHeight, tempColor, modeType));
                    }
                    //cout << j * winDivHeight << endl;
                }else{
                    tempColor.set(0, 0, 0, 0);

                    if (rectDirection == 0) {
                        rects_R.push_back(new RectObj(ofPoint(0 - i * winDivWidth - winDivWidth, j * winDivHeight + ofGetHeight()/2, ofRandom(1000) * zDepth),  winDivWidth, winDivHeight, tempColor, modeType));
                    }
                    if (rectDirection == 1) {
                        rects_R.push_back(new RectObj(ofPoint(j * winDivWidth + ofGetWidth()/2, 0 - i * winDivHeight - winDivHeight, ofRandom(1000) * zDepth),  winDivWidth, winDivHeight, tempColor, modeType));
                    }
                    
                }
                
                
            }
        }
        
        
        vector<RectObj *>::iterator rectsIt_L;
        rectsIt_L = rects_L.begin();
        
        for (int i = 0; i < rects_L.size(); i++) {
            ofPoint tempPos;
            
            tempPos = rects_L[i]->getPos();
            
            if (rectDirection == 0) {
                if (tempPos.x >= ofGetWidth()) {
                    
                    delete rects_L[0];
                    rectsIt_L[i];
                    rectsIt_L = rects_L.erase(rectsIt_L);
                    
                }else{
                    
                    rects_L[i]->setPos(ofPoint(tempPos.x + winDivWidth* 8, tempPos.y, tempPos.z));
                }
            }
            if (rectDirection == 1) {
                if (tempPos.y >= ofGetHeight()) {
                    
                    delete rects_L[0];
                    rectsIt_L[i];
                    rectsIt_L = rects_L.erase(rectsIt_L);
                    
                }else{
                    
                    rects_L[i]->setPos(ofPoint(tempPos.x, tempPos.y + winDivHeight* 8, tempPos.z));
                }
            }
            
        }
        ////////////////////////  modeType 0 & 2 movement update //////////////////////////////////////////
        vector<RectObj *>::iterator rectsIt_R;
        rectsIt_R = rects_R.begin();
        
        for (int i = 0; i < rects_R.size(); i++) {
            ofPoint tempPos;
            
            tempPos = rects_R[i]->getPos();
            
            if (rectDirection == 0) {
                if (tempPos.x >= ofGetWidth()) {
                    
                    delete rects_R[0];
                    rectsIt_R[i];
                    rectsIt_R = rects_R.erase(rectsIt_R);
                    
                    
                    
                }else{
                    //rects_R[i]->setPos(ofPoint(tempPos.x+winDivWidth * speed, tempPos.y));
                    rects_R[i]->setPos(ofPoint(tempPos.x + winDivWidth * 8, tempPos.y, tempPos.z));
                }
            }
            if (rectDirection == 1) {
                if (tempPos.y > ofGetHeight()) {
                    //delete rects_R[i];
                    //for (int i = 0; i < 32; i++) {
                    delete rects_R[0];
                    rectsIt_R[i];
                    rectsIt_R = rects_R.erase(rectsIt_R);
                    
                    
                    //delete rects_R[i];
                    
                }else{
                    //rects_R[i]->setPos(ofPoint(tempPos.x+winDivWidth * speed, tempPos.y));
                    rects_R[i]->setPos(ofPoint(tempPos.x, tempPos.y + winDivHeight * 8, tempPos.z));
                }
                
            }
        }
        
    }
    
    
}

//--------------------------------------------------------------
void binary::draw(){
    
    //ofBackground(0, 0, 0);
    //ofEnableAlphaBlending();
    //ofEnableBlendMode(OF_BLENDMODE_ADD);

    
    
    
    if (modeType == 0 || modeType == 2 || modeType == 5 || modeType == 6 || modeType == 7 ) {
        //cout << "draw" <<endl;
        
        if (modeType == 0) {
            //cout << "draw" <<endl;
            for (int i = 0; i < rects_L.size(); i++) {
                rects_L[i]->draw();
            }
            
            for (int i = 0; i < rects_R.size(); i++) {
                rects_R[i]->draw();
            }
            
        }
        
        if (modeType == 2) {
            
            glEnable(GL_DEPTH_TEST);
            cam.disableMouseInput();
            cam.begin();
            
            ofPushMatrix();
            
            ofTranslate(0-ofGetWidth()/2, 0-ofGetHeight()/2);
            
            for (int i = 0; i < rects_L.size(); i++) {
                
                rects_L[i]->draw();
            }
            for (int i = 0; i < rects_R.size(); i++) {
                rects_R[i]->draw();
            }
            ofPopMatrix();
            cam.end();
        }
        
        ////////////////////////////////////// NEW Section ( Break ) /////////////////////////////////////////////////////////////////////////////
        
        if (modeType == 5 || modeType == 6 || modeType == 7) {
            
            glEnable(GL_DEPTH_TEST);
            ofColor tempColor_L;
            ofColor tempColor_R;
            ofPushMatrix();
            ofTranslate(ofGetWidth(), ofGetHeight()/2);
            ofRotateY(90);
            for (int i = 0; i < rects_L.size(); i++) {
                
                rects_L[i]->draw();
                tempColor_L = rects_L[i]->getColor();
                
            }
            ofPopMatrix();
            
            ofPushMatrix();
            ofRotateY(90);
            
            for (int i = 0; i < rects_R.size(); i++) {
                rects_R[i]->draw();
                tempColor_R = rects_R[i]->getColor();
            }
            ofPopMatrix();
            
            if (modeType == 6 || modeType == 7) {
                
                for (int i = 0; i < rects_L.size(); i++) {
                    if(rects_L[i]->getPos().x > ofGetWidth() -10 && rects_L[i]->getPos().x < ofGetWidth())
                    {
                        
                        float tempoNum = ofRandom(winDivHeight* 32);
                        
                        ofPoint pos_S(0, tempoNum + ofGetHeight()/2, -ofGetWidth());
                        ofPoint pos_E(ofGetWidth(), tempoNum + ofGetHeight()/2, -ofGetWidth());
                        ofLine(pos_S, pos_E);
                        
                    }
                }
                
                if (modeType == 7) {
                    
                    ofPushMatrix();
                    
                    ofTranslate(0, ofGetHeight(), -ofGetWidth()/1.75);
                    ofSetColor(255, 255, 255, 255);
                    ofRotateX(90);
                    //ofRect(0, ofGetHeight() - rectPos.y, ofGetWidth(), 100);
                    
                    ofNoFill();
                    ofSetColor(0, 0, 255, 125);
                    ofRect(0, ofGetHeight() - rectPos.y + rectRandPos_1, ofGetWidth(), 100);
                    ofSetColor(255, 0, 0, 125);
                    ofRect(0, ofGetHeight() - rectPos.y + rectRandPos_2, ofGetWidth(), 100);
                    
                    ofFill();
                    ofSetColor(255, 255, 255, 255);
                    ofRect(0, ofGetHeight() - rectPos.y, ofGetWidth(), 100);
                    
                    ofPopMatrix();
                    
                    ofPushMatrix();
                    
                    ofTranslate(0, ofGetHeight(), -ofGetWidth());
                    ofRotateX(90);
                    
                    for(int i = 0; i < 8; i++)
                    {
                        ofFill();
                        ofSetColor(255, 255, 255, 100 + ((5 - i) * 20));
                        ofLine(rectVerticalPos.x - (i*20), 0, rectVerticalPos.x  - (i*20), ofGetHeight()*2);
                        //ofRect(rectVerticalPos.x - (i*20), 0, 30, ofGetHeight()*2);
                    }
                    ofPopMatrix();
                    
                    
                    
                }
                
            }
            
            
        }
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
        
    }
    
    
}

//--------------------------------------------------------------




void binary::audioIn( float * input, int bufferSize, int nChannels ){
    
    int strPos_L = 0;
    int strPos_R = 0;
    if (modeType == 0 || modeType == 2 || modeType == 5 || modeType == 6 || modeType == 7) {
        //cout << "audioIn" <<endl;
        for (int i = 0; i < bufferSize; i++) {
            strPos_L = i%32;
            data_L.input = input[i*2];
            
            bitset<sizeof(float) * CHAR_BIT>   bits_L(data_L.output);
            
            str_L = bits_L.to_string();
            
            stringCell_L[i] = str_L[strPos_L] - 48;
            //cout << "L : "<< stringCell_L[i] << endl;
        }
        for (int i = 0; i < bufferSize; i++) {
            strPos_R = i%32;
            data_R.input = input[i*2+1];
            
            bitset<sizeof(float) * CHAR_BIT>   bits_R(data_R.output);
            
            str_R = bits_R.to_string();
            
            stringCell_R[i] = str_R[strPos_R] - 48;
            //cout << "R : "<< stringCell_R[i] << endl;
            
        }
    }
    
    
    
    
    
}
