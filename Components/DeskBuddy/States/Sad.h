#pragma once
#include "esphome.h"
#include "BaseState.h"
#include "../Utilities/Draw.h"

namespace DeskBuddy {
    namespace States {
        class Sad : public BaseState {
        public:
            Sad(::DeskBuddy::DeskBuddy *parent);

            std::string getName() const override;
            bool isActive() override;
            void render(
                esphome::display::Display* display,
                float x, float y,
                float blinkPercentage,
                esphome::Color eyeColor,
                esphome::Color backgroundColor
            ) override;
        };
    }
}
