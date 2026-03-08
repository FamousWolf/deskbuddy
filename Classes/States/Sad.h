#pragma once
#include "esphome.h"
#include "BaseState.h"
#include "../Status.h"
#include "../Utilities/Draw.h"

namespace States {
    class Sad : public BaseState {
    public:
        bool isActive() override {
            return Status::getInstance().getHappiness() < -50.0f;
        }

        void render(esphome::display::Display& display, float x, float y, float blinkPercentage, Color eyeColor, Color backgroundColor) override {
            int spacing = 20;
            int width = 60;
            int height = 60 * blinkPercentage;
            int centerX = display.get_width() / 2;
            int centerY = display.get_height() / 2 + 40;

            int leftX = centerX - spacing - width + x;
            int rightX = centerX + spacing + x;

            Utilities::Draw::roundedRectangleWithOverlayTriangle(display, leftX, centerY - height / 2 + y, width, height, 15,
                                                    eyeColor, backgroundColor, leftX, centerY + y, true);
            Utilities::Draw::roundedRectangleWithOverlayTriangle(display, rightX, centerY - height / 2 + y, width, height, 15,
                                                    eyeColor, backgroundColor, rightX + width, centerY + y, false);
        }
    };
};
