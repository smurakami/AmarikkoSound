//

//  Sequencer.hpp
//  AmarikkoSound
//
//  Created by 村上晋太郎 on 2019/02/02.
//

#ifndef Sequencer_hpp
#define Sequencer_hpp
#include <stdio.h>
#include "ofMain.h"
#include "ofxCv.h"

class Sequencer {
    vector<ofSoundPlayer> sounds;
    vector<ofSoundPlayer> rythm;
    float start_time; // 開始時間。
    
    int num_bars = 32; // 一小節の拍数
    int num_notes = 16; // 音階の数
    
    int counter = 0; // 時間計測用
    int beat = 4; // 一拍のフレーム数
    
    int pos = 0; // 譜面上の横位置
    bool trigger = false; // 音を鳴らすか
    
    cv::Mat canvas;
public:
    void setup();
    void update(cv::Mat canvas);
    void playSound();
    void draw();
};

#endif /* Sequencer_hpp */
