//
//  DoorbellClusterEngine.cpp
//  Doorbell_PilotApp
//
//  Created by Gergo Gelegonya on 2026. 03. 16..
//

#pragma once

#include "DoorbellClusterTypes.hpp"
#include "DoorbellDomain.hpp"
#include <string_view>
#include <vector>

namespace doorbell {

class ClusterEngine {
public:
    ClusterEngine() = default;

    ClusterResult updateFinalGrid(const std::vector<OcrBox>& boxes);

    void reset();

    const GridMap& finalGrid() const noexcept { return finalGrid_; }

private:
    // Main stages
    GridMap buildClusteredGrid(const std::vector<OcrBox>& boxes);
    GridMap clusterBoxes(const std::vector<OcrBox>& boxes);
    ClusterMetrics extractBoxMetrics(const std::vector<OcrBox>& boxes) const;

    float getMostCommonDistanceVertical(const std::vector<OcrBox>& boxes) const;
    float getMostCommonDistanceHorizontal(const std::vector<OcrBox>& boxes) const;

    void predictPossibleMerges(GridMap& grid) const;
    void applyMerges(GridMap& grid) const;
    void reindexGridAfterMerges(GridMap& grid) const;

    void storeHighConfidenceCells(const GridMap& newGrid);
    NumpadDetection detectNumpadStructure(const GridMap& grid) const;
    bool isNumpadRegionSafe(const GridMap& grid) const;

    GridOffset estimateGridOffset(const GridMap& newGrid) const;
    bool isSimilarOcrText(std::string_view a, std::string_view b) const;

    void detectColumnTypes(GridMap& grid) const;
    std::vector<CellText> convertGridToCellTexts(const GridMap& grid) const;
    void insertNumpadStructure(GridMap& grid, const NumpadDetection& numpad) const;

    std::string normalizeNumpadLabel(std::string_view s) const;
    std::string normalizeText(std::string_view s) const;
    int levenshteinDistance(std::string_view a, std::string_view b) const;

private:
    GridMap finalGrid_;
};

} // namespace doorbell
