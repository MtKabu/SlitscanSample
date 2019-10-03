#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        // 画面サイズ
        int CAPSIZE_W = 640;
        int CAPSIZE_H = 480;
        // フレームレート
        int FPS = 30;
    
        // ウェブカメラ
        ofVideoGrabber grabber;
        // 画像変換用に一旦FBOに保存
        ofFbo fbo;
        // スリット数
        int NUM_SLIT = 120;
        // 現在のフレーム
        int nowslit = 0;
        // スリットの幅
        int slitwidth;
        // 画像配列初期化用フラグ
        bool isStart = false;
        // カメラアップデートフラグ
        bool isCamUpdate = false;
    
        // 画像一覧配列（1フレームずつの画像が入っている）
        ofxCvColorImage* orignalimages = new ofxCvColorImage[NUM_SLIT];
    
    
        // ムービー用
        // 動画再生用インスタンス
        ofVideoPlayer videoplayer;
        // 動画フラグ
        bool isVideo = true;
};
