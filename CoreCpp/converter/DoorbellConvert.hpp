//
//  DoorbellConvert.hpp
//  Doorbell_PilotApp
//
//  Created by Gergo Gelegonya on 2026. 03. 16..
//
//bridge conversion
#pragma once
#include "types/DoorbellTypes.hpp"
#include "domain/DoorbellDomain.hpp"
#include <vector>

namespace doorbell {

    PointF toPoint(const DbPointF& p);
    QuadF toQuad(const DbQuadF& q);
    std::vector<OcrBox> copyOcrBoxes(const DbOcrBoxView* boxes, int32_t count);

}