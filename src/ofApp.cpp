#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

int X = 0;
int range = 1;
//--------------------------------------------------------------
void ofApp::setup(){
    //背景色
    ofBackground(0, 0, 0);
    //フレームレート
    ofSetFrameRate(60);
    // ofApp::draw() の直前に画面クリアしない(前フレームの描画を残す)
    ofSetBackgroundAuto(false);
    // ウェブカメラの設定
    grabber.initGrabber(CAPSIZE_W, CAPSIZE_H);
    grabber.setDeviceID(0);
    // トリミング用に一旦FBOに書き込む
    fbo.allocate(CAPSIZE_W, CAPSIZE_H, GL_RGB);
    // スリット部分の画像
    slit_img.allocate(CAPSIZE_W, CAPSIZE_H);
}

//--------------------------------------------------------------
 void ofApp::update(){
     // ウェブカメラがから取得した映像（画像）の更新
     grabber.update();
    if(grabber.isFrameNew()){
        // 毎フレーム
        X += range;
        
        // FBOに書き込み
        fbo.begin();
        grabber.draw(0, 0, fbo.getWidth(), fbo.getHeight());
        fbo.end();
        
        // FBOを一度pixelに変換
        ofPixels pixels;
        fbo.readToPixels(pixels);
        
        // 画像に変換
        slit_img.setFromPixels(pixels);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // 画像をトリミング(切り抜き)
    slit_img.setROI((X%CAPSIZE_W), 0, 1, CAPSIZE_H);
    slit_img.drawROI((X%CAPSIZE_W), 0, 1, CAPSIZE_H);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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




//
//#include "ofApp.h"
//
//using namespace ofxCv;
//using namespace cv;
//
//int X = 0;
//int range = 1;
////--------------------------------------------------------------
//void ofApp::setup(){
//    //背景色
//    ofBackground(0, 0, 0);
//    //フレームレート
//    ofSetFrameRate(60);
//    // ofApp::draw() の直前に画面クリアしない(前フレームの描画を残す)
//    ofSetBackgroundAuto(false);
//    // ウェブカメラの設定
//    grabber.initGrabber(CAPSIZE_W, CAPSIZE_H);
//    grabber.setDeviceID(0);
//    // トリミング用に一旦FBOに書き込む
//    fbo.allocate(CAPSIZE_W, CAPSIZE_H, GL_RGB);
//    // スリット部分の画像
//    slit_img.allocate(CAPSIZE_W, CAPSIZE_H);
//}
//
////--------------------------------------------------------------
//void ofApp::update(){
//    // ウェブカメラがから取得した映像（画像）の更新
//    grabber.update();
//    if(grabber.isFrameNew()){
//        // 毎フレーム
//        X += range;
//
//        // FBOに書き込み
//        fbo.begin();
//        grabber.draw(0, 0, fbo.getWidth(), fbo.getHeight());
//        fbo.end();
//
//        // FBOを一度pixelに変換
//        ofPixels pixels;
//        fbo.readToPixels(pixels);
//
//        // 画像に変換
//        slit_img.setFromPixels(pixels);
//    }
//}
//
////--------------------------------------------------------------
//void ofApp::draw(){
//    // 画像をトリミング(切り抜き)
//    slit_img.setROI((CAPSIZE_W/2), 0, 1, CAPSIZE_H);
//    slit_img.drawROI((X%CAPSIZE_W), 0, 1, CAPSIZE_H);
//}
