//
//  Pirticle.cpp
//  AudioData_Binary
//
//  Created by koutaro fukui on 2013/05/06.
//
//

#include "Particle.h"

//--------------------------------------------------------------
void particle::setup(){
    
    
    //OSC setting
    receiver.setup(particle_PORT);

    ofSetVerticalSync(true);
    ofEnableSmoothing();
    
    
    ofSetFrameRate(60);
    
    //speed =30;
    //modeType = 3;
    mode = 0;
    //zDepth = 0;

    viewX = 0;
    viewY = 0;
    viewZ = 0;
    
    
    ofFbo::Settings s = ofFbo::Settings();
    s.width = ofGetWidth();
    s.height = ofGetHeight();
    s.internalformat = GL_RGBA;
    s.useDepth = true;
    s.depthStencilAsTexture = true;
    
    fbo.allocate(s);//particle
    
    vFbo.allocate(s);//blur_vertical
    hFbo.allocate(s);//blur_horizonal
    
    fbo_total.allocate(s);//show on the window
    
    //loading shader files
    blurV.load("common.vert","blurVertical.frag");
    blurH.load("common.vert","blurHorizontal.frag");
    
    // initialize pos, vel
    for(int i =0; i < NUM_PARTICLES; i++)
    {
        pos[i].x = ofRandomWidth();
        pos[i].y = ofRandomHeight();
        
        pos[i].z = ofRandomWidth() - ofRandomWidth()/2;
        //pos[i].z = 0;
        
        vel[i].x = ofRandomf();
        vel[i].y = ofRandomf();
        
        drag[i] = ofRandom(0.95, 0.99);
        ;
    }
    
    vbo.setVertexData(pos, NUM_PARTICLES, GL_DYNAMIC_DRAW);
    
    deg = 0;
    
    start = 1;
    
    
    blurDepth = 0;
    
}

//--------------------------------------------------------------
void particle::update(){
/////////////////////   OSC    //////////////////////////////
    
    while (receiver.hasWaitingMessages()) {
        
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        // receive mode //
//        if(m.getAddress() == "/event/modeType"){
//            modeType = m.getArgAsInt32(0);
//            //cout << modeType << endl;
//        }
        //
//        if(m.getAddress() == "/event/xyz"){
//            float viewX, viewY, viewZ;
//            
//            viewX = m.getArgAsFloat(0);
//            viewY = m.getArgAsFloat(1);
//            viewZ = m.getArgAsFloat(2);
//            
//            cam.setTarget(ofVec3f(0));
//            cam.setPosition(viewX, viewY, viewZ);
//            
//            //cam.lookAt(ofVec3f(viewX, viewY, viewZ));
//            
//        }
//        if(m.getAddress() == "/event/peak"){
//            
//            zDepth = m.getArgAsFloat(0);
//            
//            
//        }
        if(m.getAddress() == "/event/blur"){
            
            blurDepth = m.getArgAsFloat(0);
            
            
        }
        
         
        ///////////////////////////////////////////////////////////////////////////////////////////////
        //Particle control xy
        if(m.getAddress() == "/event/particle_pos"){
            float pos_x, pos_y;
            pos_x = m.getArgAsFloat(0);
            pos_y = m.getArgAsFloat(1);
            
            mX = ofMap(pos_x, 0, 1, 0, ofGetWidth());
            mY = ofMap(pos_y, 0, 1, 0, ofGetHeight());
        }
        
        //Particle Rotating_Scale
        if(m.getAddress() == "/event/particle_Scale"){
            float scale;
            scale = m.getArgAsFloat(0);
            
            scaling = ofMap(scale, 0, 1, 0, ofGetHeight());
        }
        
        //Particle Pos_Random
        if(m.getAddress() == "/event/particle_random"){
            int posRand;
            posRand = m.getArgAsInt32(0);
            
            if (posRand == 1) {
                for (int i=0; i<NUM_PARTICLES; i++) {
                    pos[i].x = ofRandomWidth();
                    pos[i].y = ofRandomHeight();
                }
            }
            
        }
        if(m.getAddress() == "/event/particle_rotateMode"){
            int inCom;
            inCom = m.getArgAsInt32(0);
            if (inCom ==1) {
                mode = 1;
            }
        }
        
        if(m.getAddress() == "/event/particle_view"){
            int inCom;
            
            inCom = m.getArgAsInt32(0);
            if (inCom == 1) {
                degDev += 1;
                //}
                if (degDev >= 4) {
                    degDev = 0;
                }
                // /*
                if (deg >= 90) {
                    deg = 0;
                }
                while (deg < 90) {
                    deg++;
                }
                //cout << "1" << endl;
            }else if (inCom == 0)
            {
                deg = 0;
                degDev = 0;
                //cout << "0" << endl;
            }
        }

        
        
    }//OSC End


        for(int i=0; i <NUM_PARTICLES; i++){
            //ofPoint attractPt(ofGetMouseX(), ofGetMouseY());
            ofPoint attractPt(mX, mY);
            frc[i] = attractPt-pos[i]; // we get the attraction force/vector by looking at the mouse pos relative to our pos
            frc[i].normalize(); //by normalizing we disregard how close the particle is to the attraction point
            
            vel[i] *= drag[i]; //apply drag
            vel[i] += frc[i] * 0.6; //apply force
            
            pos[i] += vel[i];
            
            if( pos[i].x > ofGetWidth() ){
                pos[i].x = ofGetWidth();
                vel[i].x *= -1.0;
            }else if( pos[i].x < 0 ){
                pos[i].x = 0;
                vel[i].x *= -1.0;
            }
            if( pos[i].y > ofGetHeight() ){
                pos[i].y = ofGetHeight();
                vel[i].y *= -1.0;
            }
            else if( pos[i].y < 0 ){
                pos[i].y = 0;
                vel[i].y *= -1.0;
            }
            
        }

    
}

//--------------------------------------------------------------
void particle::draw(){
    ofBackground(0, 0, 0);
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);

        
        ofLight();
        
        //ofDisableAlphaBlending();
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        //ofEnableBlendMode(OF_BLENDMODE_DISABLED);
        fbo.begin();
        //camera.begin();
        ofBackground(0, 0, 0, 0);
        if (start == 0) {
            ofSetColor(0, 0, 0, 0);
        }
        if (start == 1) {
            ofSetColor(255, 255, 255, 220);
        }
        
        vbo.updateVertexData(pos, NUM_PARTICLES);
        
        ofPushMatrix();
        ofTranslate(ofGetWidth()*0.5, ofGetHeight()*0.5);
        ofRotateY(deg * degDev);
        //ofRotateY(ofMap(mouseX, 0.0, ofGetWidth(), 0, 360));
        ofTranslate(-ofGetWidth()*0.5, -ofGetHeight()*0.5);
        vbo.draw(GL_POINTS, 0, NUM_PARTICLES);
        ofPopMatrix();
        //camera.end();
        fbo.end();
        // /*
        if (mode == 0) {
            fbo_total.begin();//shading last picture
            ofBackground(0, 0, 0, 0);//added for shader
            
            fbo.draw(0, 0);
            
            fbo_total.end();
        }
        if (mode == 1) {
            
            fbo_total.begin();//shading last picture
            ofBackground(0, 0, 0, 0);//added for shader
            
            ofDisableLighting();
            glDisable(GL_DEPTH_TEST);
            ofSetColor(255, 255, 255,255);
            for (int i = 0; i < 24; i++) {
                float mapping_x;
                ofSetColor(255, 255, 255, 150);
                ofPushMatrix();
                ofTranslate(ofGetWidth()*0.5, ofGetHeight()*0.5);
                //ofRotateZ(mouseX*i);
                mapping_x = ofMap(mX, 0, ofGetWidth(), 0, 360);
                ofRotateZ(mapping_x*i);
                
                ofTranslate(-ofGetWidth()*0.5, -ofGetHeight()*0.5);
                //ofScale(mouseY*0.02, mouseY*0.01, 0.0);
                ofScale(scaling*0.02, scaling*0.01, 0.0);
                fbo.draw(0, 0);
                ofPopMatrix();
            }
            fbo_total.end();
        }
        // */
        
        //show last picture with shader
        
        ofDisableLighting();
        glDisable(GL_DEPTH_TEST);
        ofDisableAlphaBlending();
        ofSetColor(255, 255, 255,255);
        
        hFbo.begin();
        ofBackground(0, 0, 0, 0);
        fbo_total.draw(0, 0);
        hFbo.end();
        
        vFbo.begin();
        ofBackground(0, 0, 0, 0);
        blurV.begin();
        blurV.setUniform1f("val",blurDepth*0.005);
        hFbo.draw(0,0);
        blurV.end();
        vFbo.end();
        
        hFbo.begin();
        ofBackground(0, 0, 0, 0);
        blurH.begin();
        blurH.setUniform1f("val",blurDepth*0.005);
        vFbo.draw(0,0);
        blurH.end();
        hFbo.end();
        
        hFbo.draw(0,0);

    
    
}

void particle::windowResized(int w, int h){
    
    ofFbo::Settings s = ofFbo::Settings();
    s.width = ofGetWidth();
    s.height = ofGetHeight();
    s.internalformat = GL_RGBA;
    s.useDepth = true;
    s.depthStencilAsTexture = true;
    fbo.allocate(s);
    
    fbo_total.allocate(s);
    vFbo.allocate(s);
    hFbo.allocate(s);
    
    float heightDev;
    heightDev = (ofGetHeight() - 50)/6;
    for (int i = 0; i < 6; i++) {
        
        yPos[i] = heightDev * i + 50;
        
    }
    
}

void particle::setmode(int _mode){
    mode = _mode;
}
