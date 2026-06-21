//
//  DoorbellBrdige.mm
//  Doorbell_PilotApp
//
//  Created by Gergo Gelegonya on 2026. 02. 23..
//

#import "DoorbellBridge.h"
#import "DoorbellApi.hpp"
#import <CoreVideo/CoreVideo.h>
#include <vector>
#include <string>
#include <utility>
@implementation DoorbellBridge

+ (instancetype)shared {
    static DoorbellBridge *s;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        s = [DoorbellBridge new];
    });
    return s;
}

- (void)pushPixelBuffer:(CVPixelBufferRef)pixelBuffer timestamp:(double)timestamp {
    CVPixelBufferLockBaseAddress(pixelBuffer, kCVPixelBufferLock_ReadOnly);
    void *base = CVPixelBufferGetBaseAddress(pixelBuffer);

    if (!base) {
        CVPixelBufferUnlockBaseAddress(pixelBuffer, kCVPixelBufferLock_ReadOnly);
        return;
    }

    const int width = (int)CVPixelBufferGetWidth(pixelBuffer);
    const int height = (int)CVPixelBufferGetHeight(pixelBuffer);
    const int bpr = (int)CVPixelBufferGetBytesPerRow(pixelBuffer);
    const int byteCount = bpr * height;

    DbFrameView f;
    f.format = DB_BGRA8888;
    f.width = width;
    f.height = height;
    f.bytesPerRow = bpr;
    f.timestamp = timestamp;
    f.bytes = (const uint8_t*)base;
    f.byteCount = byteCount;

    DbPushFrame(f);

    CVPixelBufferUnlockBaseAddress(pixelBuffer, kCVPixelBufferLock_ReadOnly);
}

- (void)pushMotionQx:(double)qx qy:(double)qy qz:(double)qz qw:(double)qw
                 yaw:(double)yaw pitch:(double)pitch roll:(double)roll
           timestamp:(double)timestamp calibrated:(BOOL)calibrated {

    DbMotionSample m;
    m.quat = DbQuatD{qx, qy, qz, qw};
    m.yaw = yaw;
    m.pitch = pitch;
    m.roll = roll;
    m.timestamp = timestamp;
    m.isCalibrated = (bool)calibrated;

    DbPushMotion(m);
}

- (void)pushOcrRects:(const float *)rectsXYWH
               texts: texts
         confidences:(const float *)confidences
               count:(int)count
           timestamp:(double)timestamp {

    // build views
    std::vector<DbOcrBoxView> boxes;
    boxes.reserve(count);

    std::vector<std::string> ownedStrings;
    ownedStrings.reserve(count);

    for (int i = 0; i < count; i++) {
        float x = rectsXYWH[i*4 + 0];
        float y = rectsXYWH[i*4 + 1];
        float w = rectsXYWH[i*4 + 2];
        float h = rectsXYWH[i*4 + 3];

        NSString *s = texts[i];
        std::string utf8 = s ? std::string([s UTF8String]) : std::string();
        ownedStrings.push_back(std::move(utf8));

        DbOcrBoxView b;
        b.rect = DbRectF{x,y,w,h};
        b.textUtf8 = ownedStrings.back().c_str(); // stable until end of function
        b.confidence = confidences[i];
        boxes.push_back(b);
    }

    DbPushOcr(boxes.data(), (int32_t)boxes.size(), timestamp);
}

- (NSDictionary *)debugStats {
    return @{
        @"w": @(DbLastFrameWidth()),
        @"ocr": @(DbLastOcrCount()),
        @"cal": @(DbLastCalibrated())
    };
}

@end
