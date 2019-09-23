#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        // ウェブカメラ
        ofVideoGrabber grabber;
        // 画像トリミング用に一旦FBOに保存
        ofFbo fbo;
        // 画面サイズ
        int CAPSIZE_W = 640;
        int CAPSIZE_H = 480;
    
        ofxCvColorImage slit_img;
};
