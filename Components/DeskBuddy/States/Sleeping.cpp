#include "Sleeping.h"

namespace DeskBuddy {
    namespace States {
        Sleeping::Sleeping(::DeskBuddy::DeskBuddy *parent) : BaseState(parent) {
            this->sleepAnimator = ::DeskBuddy::Utilities::FloatAnimator();
        }

        std::string Sleeping::getName() const {
            return "Sleeping";
        }

        bool Sleeping::isActive() {
            return parent_->hasForcedState("") && parent_->isSleeping || parent_->hasForcedState(getName());
        }

        void Sleeping::render(esphome::display::Display* display, float x, float y, float blinkPercentage, esphome::Color eyeColor, esphome::Color backgroundColor) {
            int spacing = 20;
            int width = 60;
            int height = 3;
            int centerX = display->get_width() / 2;
            int centerY = display->get_height() / 2;
            int leftX = centerX - spacing - width;
            int rightX = centerX + spacing;

            if (sleepAnimator.isDone()) {
                sleepAnimator.startAnimation(0.0f, 2.0f, 3000);
            }
            float animationValue = sleepAnimator.update();
            float yOffset = 20.0f;
            if (animationValue <= 1.0f) {
                yOffset += sleepAnimator.calculateV(animationValue) * 5.0f;
            } else {
                yOffset += 5;
            }

            display->filled_rectangle(leftX, centerY - height / 2 + yOffset, width, height, eyeColor);
            display->filled_rectangle(rightX, centerY - height / 2 + yOffset, width, height, eyeColor);
        }
    }
}
