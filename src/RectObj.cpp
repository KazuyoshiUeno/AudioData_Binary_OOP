//
//  RectObj.cpp
//  AudioData_Binary
//
//  Created by koutaro fukui on 2/17/13.
//
//

#include "RectObj.h"

RectObj::RectObj(ofPoint _pos, int _width, int _height, ofColor _color, int _mode)
{
    pos = _pos;
    width = _width;
    height = _height;
    color = _color;
    mode = _mode;


}
RectObj::~RectObj()
{
}

void RectObj::setPos(ofPoint _pos)
{
    pos = _pos;
}
ofPoint RectObj::getPos()
{
    return pos;
}

void RectObj::setColor(ofColor _color)
{
    color = _color;
}
ofColor RectObj::getColor()
{
    return color;
}

void RectObj::setSize(int _width, int _height)
{
    width = _width;
    height = _height;
}

void RectObj::setMode(int _mode)
{
    mode = _mode;
}

void RectObj::draw()
{
    int selfColor;
    if (color.r == 255 && color.g == 255 && color.b == 255 ) {
        selfColor = 1;
    }else{
        selfColor = 0;
    }
    //ofEnableAlphaBlending();
    
    ofSetColor(color);
    //if (mode == 0) {
    
    ofRect(pos.x, pos.y, pos.z, width, height);
        
    //}

    
}