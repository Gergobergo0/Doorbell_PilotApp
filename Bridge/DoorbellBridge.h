//
//  DoorbellBrdige.hpp
//  Doorbell_PilotApp
//
//  Created by Gergo Gelegonya on 2026. 02. 23..
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>

NS_ASSUME_NONNULL_BEGIN

@interface DoorbellBridge : NSObject

+ (instancetype)shared;

- (void)pushPixelBuffer:(CVPixelBufferRef)pixelBuffer timestamp:(double)timestamp;

- (void)pushMotionQx:(double)qx qy:(double)qy qz:(double)qz qw:(double)qw
                 yaw:(double)yaw pitch:(double)pitch roll:(double)roll
           timestamp:(double)timestamp calibrated:(BOOL)calibrated;

- (void)pushOcrRects:(const float *)rectsXYWH
               texts:(NSArray<NSString*> *)texts
         confidences:(const float *)confidences
               count:(int)count
           timestamp:(double)timestamp;

- (NSDictionary *)debugStats;

@end

NS_ASSUME_NONNULL_END
