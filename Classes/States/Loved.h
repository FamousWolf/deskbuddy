#pragma once
#include "esphome.h"
#include "BaseState.h"
#include "../Status.h"
#include "../Utilities/Draw.h"

namespace States {
    class Loved : public BaseState {
    public:
        bool isActive() override {
            Status& status = Status::getInstance();
            return status.hasForcedState("") && status.isLoved || status.hasForcedState("Loved");
        }

        void render(esphome::display::Display& display, float x, float y, float blinkPercentage, Color eyeColor, Color backgroundColor) override {
            int spacing = 20;
            int size = 60;

            int centerX = display.get_width() / 2;
            int centerY = display.get_height() / 2;

            int leftX = centerX - spacing - size + x;
            int rightX = centerX + spacing + x;

            Utilities::Draw::heart(display, leftX, centerY - size / 2 + y, size, Color(255, 0, 0));
            Utilities::Draw::heart(display, rightX, centerY - size / 2 + y, size, Color(255, 0, 0));
        }
    };
};
