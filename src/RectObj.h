//
//  RectObj.h
//  AudioData_Binary
//
//  Created by koutaro fukui on 2/17/13.
//
//

#ifndef __AudioData_Binary__RectObj__
#define __AudioData_Binary__RectObj__

#include "ofMain.h"

class RectObj {
    
public:
    RectObj(ofPoint pos, int _width, int _height, ofColor _color, int mode);
    ~RectObj();
    void draw();
    void setPos(ofPoint _pos);
    ofPoint getPos();
    void setSize(int _width, int _height);
    void setColor(ofColor _color);
    void setMode(int _mode);
    ofColor getColor();
    
private:
    ofPoint pos;
    int width;
    int height;
    int mode;
    ofColor color;
    //string str;
    //ofVbo vbo;
    //ofTrueTypeFont myfont;
    
};

#endif /* defined(__AudioData_Binary__RectObj__) */
