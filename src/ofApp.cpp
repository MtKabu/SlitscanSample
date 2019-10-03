#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //背景色
    ofBackground(0, 0, 0);
    //フレームレート
    ofSetFrameRate(FPS);
    if(isVideo) {
        // ビデオの準備
        videoplayer.load("input.mp4");
        videoplayer.play();
    } else {
        // ウェブカメラの設定
        grabber.initGrabber(CAPSIZE_W, CAPSIZE_H);
        grabber.setDeviceID(0);
    }
    
    // スリットの幅を設定
    slitwidth = (int) (CAPSIZE_H / (float) NUM_SLIT);
    // FBOの準備
    fbo.allocate(CAPSIZE_W, CAPSIZE_H, GL_RGB);
    // 画像配列の初期化
    for(int i = 0; i < NUM_SLIT; i++){
        orignalimages[i].allocate(CAPSIZE_W, CAPSIZE_H);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    // 一時変換用のピクセル配列
    ofPixels pixels;
    
    if(isVideo) {
        if (!isStart) {
            // 画像用配列の初期化
            for(int i = 0; i < NUM_SLIT; i++){
                // 一旦映像をFBOに書き込む
                fbo.begin();
                videoplayer.draw(0, 0, CAPSIZE_W, CAPSIZE_H);
                fbo.end();
                
                // FBOを一度pixelに変換
                fbo.readToPixels(pixels);
                
                // 画像編集した時にnullpointerにならないように、現在の画像を配列一覧すべてに一度保存
                orignalimages[i].setFromPixels(pixels);
            }
            isStart = true;
        } else {
            // 画像一覧を更新
            videoplayer.update();
            if(videoplayer.isFrameNew()){
                // 一旦映像をFBOに書き込む
                fbo.begin();
                videoplayer.draw(0, 0, CAPSIZE_W, CAPSIZE_H);
                fbo.end();
                
                // FBOを一度pixelに変換
                fbo.readToPixels(pixels);
                
                // 現在の撮影映像を保存していく
                orignalimages[nowslit].setFromPixels(pixels);
                
                // カメラアップデートフラグをtrueに
                isCamUpdate = true;
            }
        }
    } else {
        if (!isStart) {
            // 画像用配列の初期化
            for(int i = 0; i < NUM_SLIT; i++){
                // 一旦映像をFBOに書き込む
                fbo.begin();
                grabber.draw(0, 0, CAPSIZE_W, CAPSIZE_H);
                fbo.end();
                
                // FBOを一度pixelに変換
                fbo.readToPixels(pixels);
                
                // 画像編集した時にnullpointerにならないように、現在の画像を配列一覧すべてに一度保存
                orignalimages[i].setFromPixels(pixels);
            }
            isStart = true;
        } else {
            // 画像一覧を更新
            grabber.update();
            if(grabber.isFrameNew()){
                // 一旦映像をFBOに書き込む
                fbo.begin();
                grabber.draw(0, 0, CAPSIZE_W, CAPSIZE_H);
                fbo.end();
                
                // FBOを一度pixelに変換
                fbo.readToPixels(pixels);
                
                // 現在の撮影映像を保存していく
                orignalimages[nowslit].setFromPixels(pixels);
                
                // カメラアップデートフラグをtrueに
                isCamUpdate = true;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (isCamUpdate) {
        int tmpFrame;
        for (int i = 0; i < NUM_SLIT; i++) {
            tmpFrame = nowslit + i + 1;
            if(tmpFrame > NUM_SLIT - 1) {
                tmpFrame = tmpFrame - NUM_SLIT;
            }
            
            // 画像をスリット幅にトリミングして表示
            orignalimages[tmpFrame].setROI(0, i*slitwidth, (int)CAPSIZE_W, slitwidth);
            orignalimages[tmpFrame].drawROI(0, i*slitwidth, (int)CAPSIZE_W, slitwidth);
        }
        
        // 現在のスリットを更新
        nowslit++;
        if(nowslit > NUM_SLIT-1){
            // 全体のスリット数を越した場合、0に戻す
            nowslit = 0;
        }
        
        // フラグをもとに戻す
        isCamUpdate = false;
    }
}



// 失敗版（他で使えそうなので残しておく）
////--------------------------------------------------------------
//void ofApp::setup(){
//    //背景色
//    ofBackground(0, 0, 0);
//    //フレームレート
//    ofSetFrameRate(FPS);
//    // ウェブカメラの設定
//    grabber.initGrabber(CAPSIZE_W, CAPSIZE_H);
//    grabber.setDeviceID(0);
//
//    // スリットの幅を設定
//    slitwidth = (int) (CAPSIZE_H / (float) NUM_SLIT);
//
//    // FBOの準備
//    fbo.allocate(CAPSIZE_W, CAPSIZE_H, GL_RGB);
//    fbo2.allocate(CAPSIZE_W, CAPSIZE_H, GL_RGB);
//    fbo3.allocate(CAPSIZE_W, slitwidth, GL_RGB);
//
//    // 画像の初期化
//    for(int i = 0; i < NUM_SLIT; i++){
//        orignalimages[i].allocate(CAPSIZE_W, CAPSIZE_H);
//        slitimages[i].allocate(CAPSIZE_W, slitwidth);
//    }
//}
//
////--------------------------------------------------------------
//void ofApp::update(){
//    if (!isStart) {
//        // 画像用配列の初期化
//        for(int i = 0; i < NUM_SLIT; i++){
//            // 一旦映像をFBOに書き込む
//            fbo.begin();
//            grabber.draw(0, 0, CAPSIZE_W, CAPSIZE_H);
//            fbo.end();
//
//            // FBOを一度pixelに変換
//            ofPixels pixels;
//            fbo.readToPixels(pixels);
//
//            // 現在の撮影映像を取得
//            orignalimages[i].setFromPixels(pixels);
//        }
//        isStart = true;
//    } else {
//        grabber.update();
//        if(grabber.isFrameNew()){
//
//            // 一旦映像をFBOに書き込む
//            fbo2.begin();
//            grabber.draw(0, 0, CAPSIZE_W, CAPSIZE_H);
//            fbo2.end();
//
//            // FBOを一度pixelに変換
//            ofPixels pixels2;
//            fbo2.readToPixels(pixels2);
//
//            // 現在の撮影映像を取得
//            orignalimages[nowslit].setFromPixels(pixels2);
//
//            int tmpFrame;
//            for (int i = 0; i < NUM_SLIT; i++) {
//                tmpFrame = nowslit + i + 1;
//                if(tmpFrame > NUM_SLIT - 1) {
//                    tmpFrame = tmpFrame - NUM_SLIT;
//                }
//
//                // 一旦FBOに書き込む（トリミング）
//                fbo3.begin();
//                orignalimages[tmpFrame].setROI(0, i*slitwidth, (int)CAPSIZE_W, slitwidth);
//                orignalimages[tmpFrame].drawROI(0, i*slitwidth, (int)CAPSIZE_W, slitwidth);
//                fbo3.end();
//
//                // FBOを一度pixelに変換
//                ofPixels pixels3;
//                fbo3.readToPixels(pixels3);
//
//                slitimages[i].setFromPixels(pixels3);
//            }
//
//            // 現在のスリットを更新
//            nowslit++;
//            if(nowslit > NUM_SLIT-1){
//                // 全体のスリット数を越した場合、0に戻す
//                nowslit = 0;
//            }
//        }
//    }
//}
//
////--------------------------------------------------------------
//void ofApp::draw(){
//    for(int i = 0; i < NUM_SLIT; i++) {
//        slitimages[i].draw(0, i*slitwidth, (int)CAPSIZE_W, slitwidth);
//    }
//}
