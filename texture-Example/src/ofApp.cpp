#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	

	ofSetFrameRate(60);

	// 1DTexture;
	ofImage img;
	img.setUseTexture(false);
	img.load("1dtexture.png");
	tex1D.loadData(img);
	img.clear();


	//Cube Texture
	
	//Load by 6 Images.
	ofImage img1,img2, img3, img4, img5, img6;
	img1.setUseTexture(false);
	img2.setUseTexture(false);
	img3.setUseTexture(false);
	img4.setUseTexture(false);
	img5.setUseTexture(false);
	img6.setUseTexture(false);
	
	img1.load("sky01/right.jpg");
	img2.load("sky01/left.jpg");
	img3.load("sky01/top.jpg");
	img4.load("sky01/down.jpg");
	img5.load("sky01/front.jpg");
	img6.load("sky01/back.jpg");
	texSkyBox.loadData(img1,img2,img3,img4,img5,img6);
	img1.clear();
	img2.clear();
	img3.clear();
	img4.clear();
	img5.clear();
	img6.clear();
	texSkyBox.texData.bFlipTexture=true;

	//Load by single images.
	img.load("of.png");
	//texture 
	texCube3.loadData(img);
	texCube3.texData.bFlipTexture=true;
	//2D
	tex2D.loadData(img);
	img.clear();


	ofFloatImage imgHdr;
	imgHdr.setUseTexture(false);
	imgHdr.load("ennis_out.hdr");
	texHdrCube.allocate(256,256,GL_RGB16F,GL_RGB,GL_FLOAT);
	texHdrCube.loadData(imgHdr,GL_RGB);
	imgHdr.clear();


	mesh.load("lofi-bunny.ply");

	





}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){


	float _rotate=ofGetElapsedTimef()*15;

	//Drawing skyBox
	//Calculate vague camera posisiton, Fov is 60 (openframewokrs default)!
	float camZ=(ofGetHeight()*.5)/tanf(60.0f*.5f/180.0f*PI);
	ofDisableDepthTest();
	ofPushMatrix();
	ofTranslate(ofGetWidth()*.5,ofGetHeight()*.5,camZ);
	ofRotateY(_rotate);
	
	texSkyBox.drawCube(0,0,0,1024,1024,1024);

	ofPopMatrix();
	
	ofEnableDepthTest();

	//draw 1D texture 
	tex1D.draw(50,50,ofGetWidth()-100,10);
	tex2D.draw(50,100,100,100);

	//draw cube texture 
	ofPushMatrix();
	ofTranslate(ofGetWidth()*.2,ofGetHeight()*.5);
	ofRotateY(_rotate);
	texSkyBox.drawSphere(0,0,0,100);
	ofPopMatrix();

	//box
	ofPushMatrix();
	ofTranslate(ofGetWidth()*.5,ofGetHeight()*.5);
	ofRotateY(_rotate);
	texCube3.drawCube(0,0,0,150,150,150);
	ofPopMatrix();

	//hdr cube
	
	ofPushMatrix();
	ofTranslate(ofGetWidth()*.8,ofGetHeight()*.5);
	ofRotateY(_rotate);
	ofScale(0.5,-0.5,0.5);

	texHdrCube.begin();
	mesh.draw();
	texHdrCube.end();
	ofPopMatrix();


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}