#pragma once

//http://gl.ict.usc.edu/Data/HighResProbes/


#include "ofMain.h"
#include "ofx1DTexture.h"
#include "ofxCubeTexture.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofx1DTexture tex1D;
		ofTexture tex2D;
		ofxCubeTexture texSkyBox;
		ofxCubeTexture texCube3;

		ofxCubeTexture texHdrCube;

		ofMesh mesh;

};
