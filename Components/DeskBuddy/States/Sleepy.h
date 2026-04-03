#pragma once
#include "esphome.h"
#include "BaseState.h"
#include "../Utilities/Draw.h"
#include "../Utilities/FloatAnimator.h"

namespace DeskBuddy {
    namespace States {
        class Sleepy : public BaseState {
        public:
            Sleepy(::DeskBuddy::DeskBuddy *parent);

            std::string getName() const override;
            bool isActive() override;
            void render(
                esphome::display::Display* display,
                float x, float y,
                float blinkPercentage,
                esphome::Color eyeColor,
                esphome::Color backgroundColor
            ) override;
        private:
            ::DeskBuddy::Utilities::FloatAnimator sleepyAnimator;
        };
    }
}
