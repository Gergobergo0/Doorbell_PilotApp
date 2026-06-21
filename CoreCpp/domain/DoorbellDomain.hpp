//
//  DoorbellDomain.hpp
//  Doorbell_PilotApp
//
//  Created by Gergo Gelegonya on 2026. 03. 16..
//

#pragma once

#include "DoorbellTypes.hpp"
#include <string>
#include <vector>
#include <optional>
#include <cstdint>

namespace doorbell {

//belso cpp tipusok

struct RectF {
    float x {};
    float y {};
    float w {};
    float h {};
};

struct OcrBox {
    RectF rect;
    std::string text;
    float confidence {};
};

struct MotionState {
    DbQuatD quat {};
    double yaw {};
    double pitch {};
    double roll {};
    double timestamp {};
    bool isCalibrated {};
};

struct FrameMeta {
    DbPixelFormat format {DbPixelFormat::BGRA8888};
    int32_t width {};
    int32_t height {};
    int32_t bytesPerRow {};
    int32_t byteCount {};
    double timestamp {};
};

struct CellText {
    int row {};
    int col {};
    std::string text;
    float confidence {};
    RectF rect {};
};

struct PipelineOutput {
    bool hasGrid = false;
    bool motionCalibrated = false;
    int32_t frameWidth = 0;
    int32_t frameHeight = 0;
    std::vector<CellText> cells;
};

} // namespace doorbell
