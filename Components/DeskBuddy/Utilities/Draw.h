#pragma once
#include "esphome.h"

namespace DeskBuddy {
    namespace Utilities {
        class Draw {
        public:
            static void roundedRectangle(
                esphome::display::Display* display,
                float x,
                float y,
                float width,
                float height,
                float cornerRadius,
                esphome::Color color
            );
            static void roundedRectangleWithOverlayTriangle(
                esphome::display::Display* display,
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
            );

            static void heart(
                esphome::display::Display* display,
                float x,
                float y,
                float size,
                esphome::Color color
            );

            static void topHalfOval(
                esphome::display::Display* display,
                float x,
                float y,
                float width,
                float height,
                esphome::Color color
            );

            static void topHalfDonut(
                esphome::display::Display* display,
                float x,
                float y,
                float width,
                float height,
                float thickness,
                esphome::Color color
            );
        };
    }
}
