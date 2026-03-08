#pragma once
#include "esphome.h"
#include "BaseState.h"
#include "../Status.h"
#include "../Utilities/Draw.h"

namespace States {
    class Happy : public BaseState {
    public:
        bool isActive() override {
            return Status::getInstance().getHappiness() > 50.0f;
        }

        void render(esphome::display::Display& display, float x, float y, float blinkPercentage, Color eyeColor, Color backgroundColor) override {
            int spacing = 20;
            int width = 60;
            int height = 20 * blinkPercentage;
            int centerX = display.get_width() / 2;
            int centerY = display.get_height() / 2 - 40;

            int leftX = centerX - spacing - width + x;
            int rightX = centerX + spacing + x;

            if (height <= 7) {
                Utilities::Draw::topHalfOval(display, leftX, centerY - height / 2 + y, width, height, eyeColor);
                Utilities::Draw::topHalfOval(display, rightX, centerY - height / 2 + y, width, height, eyeColor);
            } else {
                Utilities::Draw::topHalfDonut(display, leftX, centerY - height / 2 + y, width, height, 7, eyeColor);
                Utilities::Draw::topHalfDonut(display, rightX, centerY - height / 2 + y, width, height, 7, eyeColor);
            }
        }
    };
};
