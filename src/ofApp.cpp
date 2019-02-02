#include "ofApp.h"
#include "ofxCv.h"


template <typename T>
static cv::Mat toCv(ofPixels_<T>& pix)
{
    int depth;
    switch(pix.getBytesPerChannel())
    {
        case 4: depth = CV_32F; break;
        case 2: depth = CV_16U; break;
        case 1: default: depth = CV_8U; break;
    }
    return cv::Mat(pix.getHeight(), pix.getWidth(), CV_MAKETYPE(depth, pix.getNumChannels()), pix.getData(), 0);
}

//--------------------------------------------------------------
void ofApp::setup(){
    // -----------------------------------
    // 画像関連のセットアップ
    //
    // フレームレートの設定
    ofSetFrameRate(30);
    // カメラの初期化。ウインドウサイズにあわせる。
    grabber.setup(ofGetWidth(), ofGetHeight(), OF_PIXELS_BGRA);
    // 昭和の書き方だと...
    // setupGrabber(grabber, ofGetWidth(), ofGetHeight(), OF_PIXELS_BGRA);
    
    
    // -----------------------------------
    // 音関連のセットアップ
    //
    // 音色をあらかじめロードしておく。
    sound.load("sound.wav");
}

//--------------------------------------------------------------
void ofApp::update(){
    // カメラから画像を取り込み
    grabber.update();
    if (!grabber.isFrameNew()) {
        // 画像が更新されていなかったら無視する
        return;
    }
    
    // カメラ画像を取得
    cv::Mat image = toCv(grabber.getPixels());
    //    output = image;
    //    return;

    // グレースケールに変換
    cv::Mat gray;
    cv::cvtColor(image, gray, CV_BGRA2GRAY);
//    output = gray; return;
    
    // 輪郭抽出のために二値化
    cv::Mat thresh;
    cv::threshold(gray, thresh, 127, 255, 0);
//    output = thresh; return;

    // 輪郭抽出
    //    cv::Point p;
    //    p.x = 100;
    //    p.y = 200;
    // cv::Point -> 位置を記録するデータ、オブジェクト、構造体、クラス
    // vector -> たくさんの情報を並べて記録する「配列」（貸し金庫）
    vector<cv::Vec4i> hierarchy; // 抽出した輪郭の相互関連の情報が入る入れ物（つかわない）
    cv::findContours(thresh, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    //                                            階層構造を考慮しつつ密に記録
    //                                                           一番精密に抽出
    
//    return cv::Mat(pix.getHeight(), pix.getWidth(), CV_MAKETYPE(depth, pix.getNumChannels()), pix.getData(), 0);
    canvas = cv::Mat(image.size(), CV_MAKETYPE(image.depth(), image.channels()), cv::Scalar(255, 255, 255, 255));
    const float full_area = ofGetHeight() * ofGetWidth();
    
    for (vector<cv::Point> contour : contours ) {
        float area = cv::contourArea(contour);
        float hue = 255 * area / full_area;
        ofColor color = ofColor::fromHsb(hue, 255, 255);

        vector<vector<cv::Point>> pts = {contour};

//        cv::Point * cts[1] = {contour};
//        int ss[] = {(int)contour.size()};
        cv::fillPoly(canvas, pts, cv::Scalar(color.r, color.g, color.b));

//        cv::fillPoly(canvas, cts, ss, 1, cv::Scalar(color.b, color.g, color.r));
//        cv::fillPoly(<#Mat &img#>, <#const Point **pts#>, <#const int *npts#>, <#int ncontours#>, <#const Scalar &color#>)
    }
    
    output = canvas;
//    cv::drawContours(output, contours, -1, {0, 255, 0});
    return;
}

//--------------------------------------------------------------
void ofApp::draw(){
    // 結果の表示
    ofImage img; // キャンバス
    ofxCv::toOf(output, img); // キャンバスにデータをいれる
    img.update(); // 一回アップデート
    img.draw(0, 0); //　描画
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
//    sound.setSpeed(2.0 * y / (float)ofGetHeight());
//    sound.play();
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
