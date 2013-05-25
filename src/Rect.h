//
//  Rect.h
//  Era
//
//  Created by koutaro fukui on 2012/11/04.
//
//

#ifndef _RECT
#define _RECT

#include "ofMain.h"

class rect {
public:
    //method
    void update();
    void draw();
    ofPoint getPos();
    float getWidth();
    void setPos(ofPoint _pos);
    void setWidth(float _w);

    //constractor
    rect(ofPoint pos, float w, int h, int mode);
    //deconstractor
    ~rect();
    
    //variable
    //position
    
private:
    ofPoint pos;
    float w;
    int h;
    int mode;

    
};

#endif /* defined(_OF_BOX) */