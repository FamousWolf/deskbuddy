#pragma once
#include "esphome.h"
#include "BaseState.h"
#include "../Status.h"
#include "../Utilities/Draw.h"

namespace States {
    class Scared : public BaseState {
    public:
        bool isActive() override {
            return Status::getInstance().isScared;
        }

        void render(esphome::display::Display& display, float x, float y, float blinkPercentage, Color eyeColor, Color backgroundColor) override {
            int spacing = 35;
            int radius = 10;

            int jitterX = (esphome::millis() % 12) - 6;
            int jitterY = (esphome::millis() % 8) - 4;

            int centerX = display.get_width() / 2 + jitterX;
            int centerY = display.get_height() / 2 + jitterY;

            int leftX = centerX - spacing - radius + x;
            int rightX = centerX + spacing + radius + x;

            display.filled_circle(leftX, centerY, radius, eyeColor);
            display.filled_circle(rightX, centerY, radius, eyeColor);
        }
    };
};
