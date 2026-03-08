#pragma once
#include "esphome.h"
#include "BaseState.h"
#include "../Utilities/Draw.h"

namespace States {
    class Neutral : public BaseState {
    public:
        bool isActive() override {
            // Neutral is the default state when all other states are inactive
            return true;
        }

        void render(esphome::display::Display& display, float x, float y, float blinkPercentage, Color eyeColor, Color backgroundColor) override {
            int spacing = 20;
            int width = 60;
            int height = 80 * blinkPercentage;
            int centerX = display.get_width() / 2;
            int centerY = display.get_height() / 2;

            int leftX = centerX - spacing - width + (int)x;
            int rightX = centerX + spacing + (int)x;

            Utilities::Draw::roundedRectangle(display, leftX, centerY - height / 2 + (int)y, width, height, 15, eyeColor);
            Utilities::Draw::roundedRectangle(display, rightX, centerY - height / 2 + (int)y, width, height, 15, eyeColor);
        }
    };
};
