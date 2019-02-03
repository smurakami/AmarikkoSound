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

const int rythm_loop_num = 16;

enum RythmKind {
    RYTHM_CHI = 0,
    RYTHM_SHAN = 1,
    RYTHM_TAN = 2,
};

char rythm_filename[3][20] = {
    "chi.WAV",
    "shan.WAV",
    "tan.WAV"
};

int rythm_loop[rythm_loop_num] = {
    RYTHM_CHI,
    RYTHM_CHI,
    RYTHM_CHI,
    RYTHM_SHAN,
    
    RYTHM_CHI,
    RYTHM_CHI,
    RYTHM_TAN,
    RYTHM_CHI,
    
    RYTHM_CHI,
    RYTHM_CHI,
    RYTHM_CHI,
    RYTHM_SHAN,
    
    RYTHM_CHI,
    RYTHM_CHI,
    RYTHM_TAN,
    RYTHM_TAN,
};



void Sequencer::setup() {
    // 音階楽器のセットアップ
    for (int i = 0; i < num_notes; i++) {
        ofSoundPlayer sound;
        sound.load("sound.wav");
        
        int note_index = num_notes - i;
        int note = (note_index / notes_in_octave_num) * 12 + notes_in_octave[note_index % notes_in_octave_num];
        
        note -= 12 * 3; // 4オクターブくらい下げておく。
        
        float speed = note2speed(note);
        sound.setSpeed(speed);
        
        sounds.push_back(sound);
    }
    
    // リズム楽器のセットアップ
    
    for (int i = 0; i < rythm_loop_num; i++) {
        ofSoundPlayer sound;
        
        int rythm_kind = rythm_loop[i];
        char* filename = rythm_filename[rythm_kind];
        
        sound.load(filename);
        
        rythm.push_back(sound);
    }
}

void Sequencer::update(cv::Mat canvas) {
    this->canvas = canvas;

    int next_pos = (counter / beat) % num_bars;
    
    trigger = next_pos != pos;
    pos = next_pos;
    
    if (trigger) { // 次の拍に移ってたら
        playSound();
    }
    
    counter++;
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
            ofColor color(r, g, b);
            float hue = color.getHue();
            if (hue < 255 / 3) { // 赤なら
                sounds[i].play();
            } else if (hue < 255 / 3 * 2) { // 緑？
            } else {
            }
        }
    }
    
    rythm[pos % rythm_loop_num].play();
}

void Sequencer::draw() {
    ofSetColor(255, 255, 255, 128);

    float width = ofGetWidth() / (float)num_bars;
    float x = width * pos;
    
    ofDrawRectangle(x, 0, width, ofGetHeight());
}
