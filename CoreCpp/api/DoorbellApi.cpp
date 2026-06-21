//
//  DoorbellApi.cpp
//  Doorbell_PilotApp
//
//  Created by Gergo Gelegonya on 2026. 02. 23..
//

#include "DoorbellApi.hpp"
#include "DoorbellCore.hpp"

using doorbell::Core;

void DbPushFrame(const DbFrameView& f) { Core::shared().pushFrame(f); }
void DbPushOcr(const DbOcrBoxView* boxes, int32_t count, double ts) { Core::shared().pushOcr(boxes, count, ts); }
void DbPushMotion(const DbMotionSample& m) { Core::shared().pushMotion(m); }

int32_t DbLastFrameWidth() { return Core::shared().lastFrameWidth(); }
int32_t DbLastOcrCount() { return Core::shared().lastOcrCount(); }
bool DbLastCalibrated() { return Core::shared().lastCalibrated(); }
