//
//  OverlayView.swift
//  Doorbell_PilotApp
//
//  Created by Gergo Gelegonya on 2026. 02. 23..
//

/*
 OCR bounding boxok (vision normalized rect) kirajzolasa preview kore
 Ataliktja a vision normalized koordinatakat (bottom-left origin) swiftUI koordinatakra (top-left)
 */


import SwiftUI
import CoreGraphics

struct OverlayBox: Identifiable, Equatable {
    let id = UUID()
    let rectNormalized: CGRect  // Vision boundingBox
    let text: String
    let confidence: Float
}

struct OverlayView: View {
    let boxes: [OverlayBox]

    var body: some View {
        GeometryReader { geo in
            ZStack(alignment: .topLeading) {
                ForEach(boxes) { b in
                    let r = toViewRect(normalized: b.rectNormalized, size: geo.size)

                    // Rectangle
                    Path { p in
                        p.addRect(r)
                    }
                    .stroke(lineWidth: 2)

                    // Label background + text
                    VStack(alignment: .leading, spacing: 2) {
                        Text(b.text)
                            .font(.caption2)
                            .lineLimit(1)
                        Text(String(format: "%.0f%%", b.confidence * 100))
                            .font(.caption2)
                            .opacity(0.85)
                    }
                    .padding(4)
                    .background(.ultraThinMaterial)
                    .clipShape(RoundedRectangle(cornerRadius: 6))
                    .position(x: r.minX + min(90, r.width/2),
                              y: max(10, r.minY - 12))
                }
            }
        }
        .allowsHitTesting(false)
    }

    private func toViewRect(normalized: CGRect, size: CGSize) -> CGRect {
        let w = normalized.width * size.width
        let h = normalized.height * size.height
        let x = normalized.minX * size.width

        // flip Y (Vision bottom-left -> SwiftUI top-left)
        let yFromBottom = normalized.minY * size.height
        let y = size.height - yFromBottom - h

        return CGRect(x: x, y: y, width: w, height: h)
    }
}
