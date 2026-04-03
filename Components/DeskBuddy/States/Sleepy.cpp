#include "Sleepy.h"

namespace DeskBuddy {
    namespace States {
        Sleepy::Sleepy(::DeskBuddy::DeskBuddy *parent) : BaseState(parent) {
            this->sleepyAnimator = ::DeskBuddy::Utilities::FloatAnimator();
        }

        std::string Sleepy::getName() const {
            return "Sleepy";
        }

        bool Sleepy::isActive() {
            return parent_->hasForcedState("") && parent_->isSleepy || parent_->hasForcedState(getName());
        }

        void Sleepy::render(esphome::display::Display* display, float x, float y, float blinkPercentage, esphome::Color eyeColor, esphome::Color backgroundColor) {
            int spacing = 20;
            int width = 60;
            int height = 60;
            int centerX = display->get_width() / 2;
            int centerY = display->get_height() / 2;
            int leftX = centerX - spacing - width;
            int rightX = centerX + spacing;

            if (sleepyAnimator.isDone()) {
                sleepyAnimator.startAnimation(0.0f, 5.0f, 5000);
            }
            float animationValue = sleepyAnimator.update();
            float yOffset = 0.0f;
            float heightOffset = 0.0f;

            if (animationValue <= 3.0f) {
                animationValue = animationValue / 3.0f;
                yOffset = 20.0f * animationValue;
                heightOffset = height * animationValue;
            } else if (animationValue <= 3.05f) {
                animationValue = (animationValue - 3.0f) * 20.0f;
                yOffset = 20.f * (1.0f - animationValue);
                heightOffset = height * (1.0f - animationValue);
            }

            ::DeskBuddy::Utilities::Draw::roundedRectangle(display, leftX, centerY - height / 2 + (int)heightOffset + (int)yOffset, width, height - (int)heightOffset, 15, eyeColor);
            ::DeskBuddy::Utilities::Draw::roundedRectangle(display, rightX, centerY - height / 2 + (int)heightOffset + (int)yOffset, width, height - (int)heightOffset, 15, eyeColor);
        }
    }
}
