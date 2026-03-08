#pragma once
#include "esphome.h"

namespace Utilities {
    class Draw {
    public:
        static void roundedRectangle(
            esphome::display::Display &display,
            float x,
            float y,
            float width,
            float height,
            float cornerRadius,
            esphome::Color color
        ) {
            float maxDimension = std::min(width, height) / 2;

            if (maxDimension <= cornerRadius) {
                display.filled_rectangle(x, y, width, height, color);
                return;
            }

            display.filled_rectangle(x + cornerRadius, y, width - 2 * cornerRadius, height, color);
            display.filled_rectangle(x, y + cornerRadius, cornerRadius, height - 2 * cornerRadius, color);
            display.filled_rectangle(x + width - cornerRadius, y + cornerRadius, cornerRadius, height - 2 * cornerRadius, color);

            float rightEdge = x + width - cornerRadius - 1;
            float bottomEdge = y + height - cornerRadius - 1;

            display.filled_circle(x + cornerRadius, y + cornerRadius, cornerRadius, color);
            display.filled_circle(rightEdge, y + cornerRadius, cornerRadius, color);
            display.filled_circle(x + cornerRadius, bottomEdge, cornerRadius, color);
            display.filled_circle(rightEdge, bottomEdge, cornerRadius, color);
        }

        static void roundedRectangleWithOverlayTriangle(
            esphome::display::Display &display,
            float x,
            float y,
            float width,
            float height,
            float cornerRadius,
            esphome::Color baseColor,
            esphome::Color overlayColor,
            float targetX,
            float targetY,
            bool fromRight = false
        ) {
            roundedRectangle(display, x, y, width, height, cornerRadius, baseColor);

            float startX = fromRight ? (x + width) : x;

            if (targetY > y + height) {
                targetY = y + height;
            }

            float anchorX = fromRight ? x : (x + width);
            display.filled_triangle(startX, y, anchorX, y, targetX, targetY, overlayColor);
        }

        static void heart(
            esphome::display::Display &display,
            float x,
            float y,
            float size,
            esphome::Color color
        ) {
            float radius = size / 4;

            display.filled_circle(x + radius, y + radius, radius, color);
            display.filled_circle(x + 3 * radius, y + radius, radius, color);

            display.filled_triangle(
                x, y + radius + 5,
                x + size, y + radius + 5,
                x + (size / 2), y + size,
                color
            );
        }

        static void topHalfOval(
            esphome::display::Display &display,
            float x,
            float y,
            float width,
            float height,
            esphome::Color color
        ) {
            float rx = width / 2.0f;
            float centerY = y + height;
            float centerX = x + rx;

            for (int i = 0; i <= (int)rx; i++) {
                float normalizedX = (float)i / rx;
                int h = (int)(height * sqrtf(1.0f - (normalizedX * normalizedX)));

                display.vertical_line(centerX - i, centerY - h, h, color);
                display.vertical_line(centerX + i, centerY - h, h, color);
            }
        }

        static void topHalfDonut(
            esphome::display::Display &display,
            float x,
            float y,
            float width,
            float height,
            float thickness,
            esphome::Color color
        ) {
            const float centerX = x + width / 2.0f;
            const float centerY = y + height / 2.0f;

            const int segments = 30;
            const float startAngle = 180.0f;
            const float endAngle = 360.0f;

            float outerRadiusX = width / 2.0f;
            float outerRadiusY = height;

            float innerRadiusX = std::max(0.0f, outerRadiusX - thickness);
            float innerRadiusY = std::max(0.0f, outerRadiusY - thickness);

            float prevOuterX, prevOuterY;
            float prevInnerX, prevInnerY;

            for (int i = 0; i <= segments; i++) {
                float angleDeg = startAngle + (float)i * (endAngle - startAngle) / segments;
                float angleRad = angleDeg * (M_PI / 180.0f);

                float currentOuterX = centerX + cos(angleRad) * outerRadiusX;
                float currentOuterY = centerY + sin(angleRad) * outerRadiusY;
                float currentInnerX = centerX + cos(angleRad) * innerRadiusX;
                float currentInnerY = centerY + sin(angleRad) * innerRadiusY;

                if (i > 0) {
                    display.filled_triangle(prevOuterX, prevOuterY, currentOuterX, currentOuterY, currentInnerX, currentInnerY, color);
                    display.filled_triangle(prevOuterX, prevOuterY, prevInnerX, prevInnerY, currentInnerX, currentInnerY, color);
                }

                prevOuterX = currentOuterX;
                prevOuterY = currentOuterY;
                prevInnerX = currentInnerX;
                prevInnerY = currentInnerY;
            }
        }
    };
};
