#pragma once

#include "ofMain.h"
#include <opencv2/opencv.hpp>

class ofApp : public ofBaseApp{
    
    ofSoundPlayer sound;
    ofVideoGrabber grabber; // カメラの情報を受けとる受け皿
    vector<vector<cv::Point>> contours;
    cv::Mat canvas; // 色情報の保存用
    cv::Mat output; // 結果画像をいれるいれもの

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
		
};
