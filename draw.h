#include "esphome.h"

class Draw {
    public:
        static void roundedRectangle(
            display::Display &it,
            float x,
            float y,
            float width,
            float height,
            float cornerRadius,
            Color color
        ) {
            float maxDimension = std::min(width, height) / 2;

            if (maxDimension <= cornerRadius) {
                it.filled_rectangle(x, y, width, height, color);
                return;
            }

            it.filled_rectangle(x + cornerRadius, y, width - 2 * cornerRadius, height, color);
            it.filled_rectangle(x, y + cornerRadius, cornerRadius, height - 2 * cornerRadius, color);
            it.filled_rectangle(x + width - cornerRadius, y + cornerRadius, cornerRadius, height - 2 * cornerRadius, color);

            float rightEdge = x + width - cornerRadius - 1;
            float bottomEdge = y + height - cornerRadius - 1;

            it.filled_circle(x + cornerRadius, y + cornerRadius, cornerRadius, color);
            it.filled_circle(rightEdge, y + cornerRadius, cornerRadius, color);
            it.filled_circle(x + cornerRadius, bottomEdge, cornerRadius, color);
            it.filled_circle(rightEdge, bottomEdge, cornerRadius, color);
        }

        static void roundedRectangleWithOverlayTriangle(
            display::Display &it,
            float x,
            float y,
            float width,
            float height,
            float cornerRadius,
            Color baseColor,
            Color overlayColor,
            float targetX,
            float targetY,
            bool fromRight = false
        ) {
            roundedRectangle(it, x, y, width, height, cornerRadius, baseColor);

            float startX = fromRight ? (x + width) : x;

            if (targetY > y + height) {
                targetY = y + height;
            }

            float anchorX = fromRight ? x : (x + width);
            it.filled_triangle(startX, y, anchorX, y, targetX, targetY, overlayColor);
        }

        static void heart(
            display::Display &it,
            float x,
            float y,
            float size,
            Color color
        ) {
            float radius = size / 4;

            it.filled_circle(x + radius, y + radius, radius, color);
            it.filled_circle(x + 3 * radius, y + radius, radius, color);

            it.filled_triangle(
                x, y + radius + 5,
                x + size, y + radius + 5,
                x + (size / 2), y + size,
                color
            );
        }

        static void topHalfOval(
            display::Display &it,
            float x,
            float y,
            float width,
            float height,
            Color color
        ) {
            float rx = width / 2.0f;
            float centerY = y + height;
            float centerX = x + rx;

            for (int i = 0; i <= (int)rx; i++) {
                float normalizedX = (float)i / rx;
                int h = (int)(height * sqrtf(1.0f - (normalizedX * normalizedX)));

                it.vertical_line(centerX - i, centerY - h, h, color);
                it.vertical_line(centerX + i, centerY - h, h, color);
            }
        }
};