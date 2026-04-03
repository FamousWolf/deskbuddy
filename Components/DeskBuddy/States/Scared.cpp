#include "Scared.h"

namespace DeskBuddy {
    namespace States {
        Scared::Scared(::DeskBuddy::DeskBuddy *parent) : BaseState(parent) {}

        std::string Scared::getName() const {
            return "Scared";
        }

        bool Scared::isActive() {
            return parent_->hasForcedState("") && parent_->isScared || parent_->hasForcedState(getName());
        }

        void Scared::render(esphome::display::Display* display, float x, float y, float blinkPercentage, esphome::Color eyeColor, esphome::Color backgroundColor) {
            int spacing = 35;
            int radius = 10;

            int jitterX = (esphome::millis() % 12) - 6;
            int jitterY = (esphome::millis() % 8) - 4;

            int centerX = display->get_width() / 2 + jitterX;
            int centerY = display->get_height() / 2 + jitterY;

            int leftX = centerX - spacing - radius + x;
            int rightX = centerX + spacing + radius + x;

            display->filled_circle(leftX, centerY, radius, eyeColor);
            display->filled_circle(rightX, centerY, radius, eyeColor);
        }
    }
}
