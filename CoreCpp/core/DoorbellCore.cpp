//
//  DoorbellCore.cpp
//  Doorbell_PilotApp
//
//  Created by Gergo Gelegonya on 2026. 02. 23..
//
/*
 C++ engine
 state, algoritmusok, detektalas, tracking, kalibracio stb
 
 */
#include "DoorbellCore.hpp"
namespace doorbell {


Core& Core::shared() {
    static Core inst;
    return inst;
}



void Core::pushFrame(const DbFrameView& f) {
    lastW_.store(f.width);
}

void Core::pushOcr(const DbOcrBoxView*, int32_t count, double) {
    lastOcr_.store(count);
}

void Core::pushMotion(const DbMotionSample& m) {
    lastCal_.store(m.isCalibrated);
}

int32_t Core::lastFrameWidth() const { return lastW_.load(); }
int32_t Core::lastOcrCount() const { return lastOcr_.load(); }
bool Core::lastCalibrated() const { return lastCal_.load(); }

} //namespace doorbell
