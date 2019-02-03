//
//  Sequencer.cpp
//  AmarikkoSound
//
//  Created by 村上晋太郎 on 2019/02/02.
//

#include "Sequencer.hpp"

// 12段階の音階を再生速度に変換する。
static float note2speed(int note) {
    // 12音上で2倍
    return pow(2, note / 12.0);
}

const int notes_in_octave_num = 5;
int notes_in_octave[notes_in_octave_num] = {
    0, // ド
    2, // レ
    5, // ファ
    7, // ソ
    9  // ラ
};

void Sequencer::setup() {
    start_time = ofGetElapsedTimef();
    
    for (int i = 0; i < num_notes; i++) {
        ofSoundPlayer sound;
        sound.load("sound.wav");
        
        int note_index = num_notes - i;
        int note = (note_index / notes_in_octave_num) * 12 + notes_in_octave[note_index % notes_in_octave_num];
        float speed = note2speed(note);
        sound.setSpeed(speed);
        
        sounds.push_back(sound);
    }
}

void Sequencer::update(cv::Mat canvas) {
    this->canvas = canvas;

    float time = ofGetElapsedTimef() - start_time;
    int next_pos = (int)(time * (tempo / 60.0)) % num_bars;
    
    trigger = next_pos != pos;
    pos = next_pos;
    
    if (trigger) { // 次の拍に移ってたら
        playSound();
    }
}

void Sequencer::playSound() {
    float width = canvas.cols;
    float height = canvas.rows;
    float cell_width = width / (float)num_bars;
    float cell_height = height / (float)num_notes;

    int x = cell_width * pos + cell_width * 0.5;
    
    for (int i = 0; i < num_notes; i++) {
        int y = cell_height * i + cell_height * 0.5;
        cv::Vec3b channel = canvas.at<cv::Vec3b>(y, x);
        
        int r = channel[0];
        int g = channel[1];
        int b = channel[2];
        
        if (r + g + b > 0) {
            sounds[i].play();
        }
    }
}

void Sequencer::draw() {
    ofSetColor(255, 255, 255, 128);

    float width = ofGetWidth() / (float)num_bars;
    float x = width * pos;
    
    ofDrawRectangle(x, 0, width, ofGetHeight());
}
