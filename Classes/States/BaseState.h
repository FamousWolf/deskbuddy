#pragma once
#include "esphome.h"

namespace States {
    class BaseState {
    public:
        virtual bool isActive() = 0;

        virtual void render(esphome::display::Display& display, float x, float y, float blinkPercentage, Color eyeColor, Color backgroundColor) = 0;
    };
};
