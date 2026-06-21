//
// Created by Gergo Gelegonya on 2026. 03. 17..
//
#include "bridge/DoorbellConvert.hpp"

namespace doorbell {

    PointF toPoint(const DbPointF& p) {
        return PointF{p.x, p.y};
    }

    QuadF toQuad(const DbQuadF& q) {
        return QuadF{
            toPoint(q.tl),
            toPoint(q.tr),
            toPoint(q.br),
            toPoint(q.bl)
        };
    }

    std::vector<OcrBox> copyOcrBoxes(const DbOcrBoxView* boxes, int32_t count) {
        std::vector<OcrBox> out;

        if (boxes == nullptr || count <= 0) {
            return out;
        }

        out.reserve(static_cast<size_t>(count));

        for (int32_t i = 0; i < count; ++i) {
            const DbOcrBoxView& b = boxes[i];

            OcrBox o;
            o.quad = toQuad(b.quad);
            o.text = b.textUtf8 ? std::string(b.textUtf8) : std::string();
            o.confidence = b.confidence;

            out.push_back(std::move(o));
        }

        return out;
    }

} // namespace doorbell