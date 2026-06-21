//
//  DoorbellCore.hpp
//  Doorbell_PilotApp
//
//  Created by Gergo Gelegonya on 2026. 02. 23..
//
#pragma once

#include "DoorbellPipeline.hpp"
#include <atomic>
#include <mutex>
#include <optional>

namespace doorbell {

class Core {
public:
    static Core& shared();

    void pushFrame(const DbFrameView& frame);
    void pushOcr(const DbOcrBoxView* boxes, int32_t count, double timestamp);
    void pushMotion(const DbMotionSample& motion);

    int32_t lastFrameWidth() const;
    int32_t lastOcrCount() const;
    bool lastCalibrated() const;

    std::optional<PipelineOutput> lastOutput() const;

private:
    Core() = default;
    void tryProcess();

private:
    mutable std::mutex mutex_;

    std::optional<DbFrameView> lastFrame_;
    std::vector<OcrBox> lastOcrOwned_;
    double lastOcrTimestamp_ = 0.0;
    std::optional<DbMotionSample> lastMotion_;

    Pipeline pipeline_;
    std::optional<PipelineOutput> lastOutput_;

    std::atomic<int32_t> lastW_ {0};
    std::atomic<int32_t> lastOcr_ {0};
    std::atomic<bool> lastCal_ {false};
};

} // namespace doorbell
