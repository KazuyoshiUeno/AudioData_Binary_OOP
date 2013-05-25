//
//  noteScore.cpp
//  AudioData_Binary
//
//  Created by koutaro fukui on 2013/05/06.
//
//

#include "noteScore.h"


//--------------------------------------------------------------
void noteScore::setup(){
    
    
    //OSC setting
    receiver.setup(noteScore_PORT);


    speed =30;

    float heightDev;
    heightDev = (ofGetHeight() - 50)/6;
    for (int i = 0; i < 6; i++) {
        
        yPos[i] = heightDev * i + 50;
        
    }
 
    modeSelect = 0;
    
    start = 1;
    
}

//--------------------------------------------------------------
void noteScore::update(){
    
    
    int strCellNum = 0;
    
    /////////////////////   OSC    //////////////////////////////
    
    while (receiver.hasWaitingMessages()) {
        
        ofxOscMessage m;
        receiver.getNextMessage(&m);

        
        
        int rectHeight = 50;
        
        if(m.getAddress() == "/event/mode"){
            

            modeSelect = m.getArgAsInt32(0);

            //cout << "trig" << endl;
            
        }
        
        if(m.getAddress() == "/event/sine"){
            
            //freq[0] = m.getArgAsInt32(0);
            duration[0] = m.getArgAsFloat(0);
            //cout << "trig" << endl;
            myRect_1.push_back(new rect(ofPoint(0, yPos[0]), duration[0] * 50, ofRandom(50) + 10, modeSelect));
            
            rectNum[0] += 1;
            if (rectNum[0] >= NUM) {
                rectNum[0] = 0;
            }
        }
        //Rect_2
        if(m.getAddress() == "/event/click"){
            
            duration[1] = m.getArgAsFloat(0);//
            
            myRect_2.push_back(new rect(ofPoint(0,  yPos[1]), duration[1] * 50, ofRandom(50) + 10, modeSelect));//
            
            rectNum[1] += 1;//
            if (rectNum[1] >= NUM) {//
                rectNum[1] = 0;//
            }
        }
        //3
        if(m.getAddress() == "/event/kick"){
            
            duration[2] = m.getArgAsFloat(0);
            
            if (duration[2] > 1) {
                duration[2] = 1;
            }
            
            myRect_3.push_back(new rect(ofPoint(0, yPos[2]), duration[2] * 50, ofRandom(50) + 10, modeSelect));
            
            rectNum[2] += 1;
            if (rectNum[2] >= NUM) {
                rectNum[2] = 0;
            }
        }
        //4
        if(m.getAddress() == "/event/sine_2"){
            
            duration[3] = m.getArgAsFloat(0);
            
            myRect_4.push_back(new rect(ofPoint(0, yPos[3]), duration[3] * 50, ofRandom(50) + 10, modeSelect));
            
            rectNum[3] += 1;
            if (rectNum[3] >= NUM) {
                rectNum[3] = 0;
            }
        }
        //5
        if(m.getAddress() == "/event/logisticMap"){
            
            duration[4] = m.getArgAsFloat(0);//
            myRect_5.push_back(new rect(ofPoint(0, yPos[4]), duration[4] * 50, ofRandom(50) + 10, modeSelect));//
            //cout << duration[4] << endl;
            rectNum[4] += 1;//
            if (rectNum[4] >= NUM) {//
                rectNum[4] = 0;//
            }
        }
        
        //6
        if(m.getAddress() == "/event/sineBass"){
            
            duration[5] = m.getArgAsFloat(0);//
            
            myRect_6.push_back(new rect(ofPoint(0, yPos[5]), duration[5] * 50, ofRandom(100), modeSelect));//
            
            rectNum[5] += 1;//
            if (rectNum[5] >= NUM) {//
                rectNum[5] = 0;//
            }
        }
        

        
    }//OSC End

    
    /////////////  modeType 1 movement update /////////////////////////////////////

        
        vector<rect *>::iterator rectIt_1;
        rectIt_1 = myRect_1.begin();
        vector<rect *>::iterator rectIt_2;
        rectIt_2 = myRect_2.begin();
        vector<rect *>::iterator rectIt_3;
        rectIt_3 = myRect_3.begin();
        vector<rect *>::iterator rectIt_4;
        rectIt_4 = myRect_4.begin();
        vector<rect *>::iterator rectIt_5;
        rectIt_5 = myRect_5.begin();
        vector<rect *>::iterator rectIt_6;
        rectIt_6 = myRect_6.begin();
        
        
        
        for(int i = 0; i < myRect_1.size(); i++){
            ofPoint pos;
            if (myRect_1[i]->getPos().x > ofGetWidth()) {
                delete myRect_1[0];
                myRect_1.erase(rectIt_1);
                
            }else{
                
                pos.x = myRect_1[i]->getPos().x + speed;
                pos.y = yPos[0];
                myRect_1[i]->setPos(ofPoint(pos.x, pos.y));
                
            }
        }
        
        for(int i = 0; i < myRect_2.size(); i++){
            ofPoint pos;
            if (myRect_2[i]->getPos().x > ofGetWidth()) {
                delete myRect_2[0];
                myRect_2.erase(rectIt_2);
                
            }else{
                
                pos.x = myRect_2[i]->getPos().x + speed;
                pos.y = yPos[1];
                myRect_2[i]->setPos(ofPoint(pos.x, pos.y));
                
            }
        }
        
        for(int i = 0; i < myRect_3.size(); i++){//
            ofPoint pos;
            if (myRect_3[i]->getPos().x > ofGetWidth()) {
                delete myRect_3[0];
                myRect_3.erase(rectIt_3);
                
            }else{
                
                pos.x = myRect_3[i]->getPos().x + speed;//
                pos.y = yPos[2];
                myRect_3[i]->setPos(ofPoint(pos.x, pos.y));//
            }
        }
        
        for(int i = 0; i < myRect_4.size(); i++){//
            ofPoint pos;
            if (myRect_4[i]->getPos().x > ofGetWidth()) {
                delete myRect_4[0];
                myRect_4.erase(rectIt_4);
                
            }else{
                pos.x = myRect_4[i]->getPos().x + speed;//
                pos.y = yPos[3];
                myRect_4[i]->setPos(ofPoint(pos.x, pos.y));//
            }
        }
        
        for(int i = 0; i < myRect_5.size(); i++){//
            ofPoint pos;
            if (myRect_5[i]->getPos().x > ofGetWidth()) {
                delete myRect_5[0];
                myRect_5.erase(rectIt_5);
                
            }else{
                pos.x = myRect_5[i]->getPos().x + speed;//
                pos.y = yPos[4];
                myRect_5[i]->setPos(ofPoint(pos.x, pos.y));//
            }
        }
        for(int i = 0; i < myRect_6.size(); i++){//
            ofPoint pos;
            if (myRect_6[i]->getPos().x > ofGetWidth()) {
                delete myRect_6[0];
                myRect_6.erase(rectIt_6);
                
            }else{
                pos.x = myRect_6[i]->getPos().x + speed;//
                pos.y = yPos[5];
                myRect_6[i]->setPos(ofPoint(pos.x, pos.y));//
            }
        }
        
        for(int i = 0; i < myRect_1.size(); i++){
            linePos_1_x[i] = myRect_1[i]->getPos().x;
            linePos_1_y[i] = myRect_1[i]->getPos().y;
        }
        for(int i = 0; i < myRect_2.size(); i++){
            linePos_2_x[i] = myRect_2[i]->getPos().x;
            linePos_2_y[i] = myRect_2[i]->getPos().y;
        }
        for(int i = 0; i < myRect_3.size(); i++){
            linePos_3_x[i] = myRect_3[i]->getPos().x;
            linePos_3_y[i] = myRect_3[i]->getPos().y;
        }
        for(int i = 0; i < myRect_4.size(); i++){
            linePos_4_x[i] = myRect_4[i]->getPos().x;
            linePos_4_y[i] = myRect_4[i]->getPos().y;
        }
        for(int i = 0; i < myRect_5.size(); i++){
            linePos_5_x[i] = myRect_5[i]->getPos().x;
            linePos_5_y[i] = myRect_5[i]->getPos().y;
        }
        for(int i = 0; i < myRect_6.size(); i++){
            linePos_6_x[i] = myRect_6[i]->getPos().x;
            linePos_6_y[i] = myRect_6[i]->getPos().y;
        }
        

    
    
}

//--------------------------------------------------------------
void noteScore::draw(){
    

        for (int i = 0; i < myRect_1.size(); i++) {
            myRect_1[i]->draw();
        }
        for (int i = 0; i < myRect_2.size(); i++) {
            myRect_2[i]->draw();
        }
        for (int i = 0; i < myRect_3.size(); i++) {
            myRect_3[i]->draw();
        }
        for (int i = 0; i < myRect_4.size(); i++) {
            myRect_4[i]->draw();
        }
        for (int i = 0; i < myRect_5.size(); i++) {
            myRect_5[i]->draw();
        }
        for (int i = 0; i < myRect_6.size(); i++) {
            myRect_6[i]->draw();
        }
    
        
        //lines
    ofSetColor(255, 255, 255, 125);
    int lineConnectorStatPos_vertical;
    lineConnectorStatPos_vertical = 40;
        for (int i = 0; i <myRect_1.size(); i++) {
            ofLine(0, yPos[0] - lineConnectorStatPos_vertical, linePos_1_x[i], linePos_1_y[i]);
        }
        for (int i = 0; i <myRect_2.size(); i++) {
            ofLine(0, yPos[1] - lineConnectorStatPos_vertical, linePos_2_x[i], linePos_2_y[i]);
        }
        for (int i = 0; i <myRect_3.size(); i++) {
            ofLine(0, yPos[2] - lineConnectorStatPos_vertical, linePos_3_x[i], linePos_3_y[i]);
        }
        for (int i = 0; i <myRect_4.size(); i++) {
            ofLine(0, yPos[3] - lineConnectorStatPos_vertical, linePos_4_x[i], linePos_4_y[i]);
        }
        for (int i = 0; i <myRect_5.size(); i++) {
            ofLine(0, yPos[4] - lineConnectorStatPos_vertical, linePos_5_x[i], linePos_5_y[i]);
        }
        for (int i = 0; i <myRect_6.size(); i++) {
            ofLine(0, yPos[5] - lineConnectorStatPos_vertical, linePos_6_x[i], linePos_6_y[i]);
        }

    
}

void noteScore::windowResized(int w, int h){
    

    float heightDev;
    heightDev = (ofGetHeight() - 50)/6;
    for (int i = 0; i < 6; i++) {
        
        yPos[i] = heightDev * i + 50;
        
    }
    
}
