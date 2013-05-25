//
//  Rect.cpp
//  Era
//
//  Created by koutaro fukui on 2012/11/04.
//
//

#include "Rect.h"

rect::rect(ofPoint _pos, float _w, int _h, int _mode){
    
    pos = ofPoint(_pos);
    w = _w;
    h = _h;
    mode = _mode;
    
}

rect::~rect()
{
    
}

//void rect::update(){
//    
//}


ofPoint rect::getPos()
{
    return pos;
}

float rect::getWidth(){
    return w;
}

void rect::setPos(ofPoint _pos)
{
    pos = _pos;
}

void rect::setWidth(float _w)
{
    w = _w;
}

void rect::draw(){
    ofPoint stringPos;
    float string_W;
    ofSetColor(255, 255, 255);
    //ofSetRectMode(OF_RECTMODE_CENTER);
    ofRect(pos.x - w, pos.y, w, h);
    
    if (mode == 1) {
    
        if (w > 20) {
            string_W = 15;
        }else{
            string_W = w;
        }
        
        stringPos.x = pos.x + 30;
        stringPos.y = pos.y + string_W*8;

        ofSetColor(125, 125, 125);
        ofLine(pos.x-w/2, pos.y+h/2, stringPos.x, stringPos.y);
        
        if (w > 30) {
            ofSetColor(255, 0, 0);
        }else{
            if (w > 1) {
                ofSetColor(255, 255, 255);
            }
        }
        ofDrawBitmapString(ofToString(string_W), stringPos.x, stringPos.y);
      
    }
    
}